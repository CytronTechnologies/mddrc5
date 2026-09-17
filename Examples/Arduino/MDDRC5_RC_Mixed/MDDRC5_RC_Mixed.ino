/*
  MDDRC5 - Simple RC mixed-mode example

  RC1: throttle
  RC2: steering

  - This example contains only the basic RC-to-motor control.
  - Motor alignment is set with the four MAX_* constants below.
  - The onboard alignment potentiometers, mode switch,
    test button and error LEDs are not used.

  Software: Arduino IDE
  Board: Raspberry Pi Pico
*/

// ---------------- User settings ----------------

// true:  RC1 = throttle, RC2 = steering
// false: RC1 = steering, RC2 = throttle
const bool RC1_IS_THROTTLE = true;

// Motor alignment (0 to 255). Reduce the faster motor as required.
const uint8_t MAX_LEFT_FORWARD = 255;
const uint8_t MAX_LEFT_REVERSE = 255;
const uint8_t MAX_RIGHT_FORWARD = 255;
const uint8_t MAX_RIGHT_REVERSE = 255;

const uint16_t RC_CENTER_US = 1500;
const uint16_t RC_MIN_US = 1000;
const uint16_t RC_MAX_US = 2000;
const uint16_t RC_DEADBAND_US = 35;

// ---------------- MDDRC5 pins ----------------

const uint8_t RC1_PIN = 1;
const uint8_t RC2_PIN = 0;

const uint8_t M1_DIR_PIN = 10;
const uint8_t M1_PWM_PIN = 11;
const uint8_t M1_SLEEP_PIN = 12;

const uint8_t M2_DIR_PIN = 21;
const uint8_t M2_PWM_PIN = 20;
const uint8_t M2_SLEEP_PIN = 18;

const uint32_t RC_READ_TIMEOUT_US = 30000;
const uint16_t RC_VALID_MIN_US = 950;
const uint16_t RC_VALID_MAX_US = 2050;

// Convert an RC pulse to -255..255. The deadband is simply set to zero;
// the remaining range is not re-scaled after the deadband.
int16_t pulseToCommand(uint16_t pulseUs)
{
  int32_t offset = (int32_t)pulseUs - RC_CENTER_US;

  if (abs(offset) <= RC_DEADBAND_US) {
    return 0;
  }

  if (offset > 0) {
    return constrain(map(pulseUs, RC_CENTER_US, RC_MAX_US, 0, 255), 0, 255);
  }

  return constrain(map(pulseUs, RC_MIN_US, RC_CENTER_US, -255, 0), -255, 0);
}

int16_t applyMotorLimit(int16_t command, uint8_t maxForward, uint8_t maxReverse)
{
  if (command > 0) {
    return (int32_t)command * maxForward / 255;
  }

  return (int32_t)command * maxReverse / 255;
}

void setMotor(uint8_t dirPin, uint8_t pwmPin, int16_t command)
{
  command = constrain(command, -255, 255);

  // MDDRC5 motor-driver polarity: HIGH is physical forward.
  digitalWrite(dirPin, command > 0 ? HIGH : LOW);
  analogWrite(pwmPin, abs(command));
}

void stopMotors()
{
  analogWrite(M1_PWM_PIN, 0);
  analogWrite(M2_PWM_PIN, 0);
}

void setup()
{
  pinMode(RC1_PIN, INPUT_PULLUP);
  pinMode(RC2_PIN, INPUT_PULLUP);

  pinMode(M1_DIR_PIN, OUTPUT);
  pinMode(M1_PWM_PIN, OUTPUT);
  pinMode(M1_SLEEP_PIN, OUTPUT);
  pinMode(M2_DIR_PIN, OUTPUT);
  pinMode(M2_PWM_PIN, OUTPUT);
  pinMode(M2_SLEEP_PIN, OUTPUT);

  analogWriteFreq(20000);
  stopMotors();

  // Wake both motor drivers.
  digitalWrite(M1_SLEEP_PIN, HIGH);
  digitalWrite(M2_SLEEP_PIN, HIGH);
}

void loop()
{
  // The MDDRC5 RC input circuitry produces active-LOW pulses.
  uint32_t rc1Pulse = pulseIn(RC1_PIN, LOW, RC_READ_TIMEOUT_US);
  uint32_t rc2Pulse = pulseIn(RC2_PIN, LOW, RC_READ_TIMEOUT_US);

  uint32_t throttlePulse = RC1_IS_THROTTLE ? rc1Pulse : rc2Pulse;
  uint32_t steeringPulse = RC1_IS_THROTTLE ? rc2Pulse : rc1Pulse;

  // Stop when either RC channel is missing or outside the normal pulse range.
  bool throttleValid = throttlePulse >= RC_VALID_MIN_US &&
                       throttlePulse <= RC_VALID_MAX_US;
  bool steeringValid = steeringPulse >= RC_VALID_MIN_US &&
                       steeringPulse <= RC_VALID_MAX_US;

  if (!throttleValid || !steeringValid) {
    stopMotors();
    return;
  }

  int16_t throttle = pulseToCommand((uint16_t)throttlePulse);
  int16_t steering = pulseToCommand((uint16_t)steeringPulse);

  // Differential-drive mixing.
  int16_t leftCommand = constrain(throttle + steering, -255, 255);
  int16_t rightCommand = constrain(throttle - steering, -255, 255);

  leftCommand = applyMotorLimit(leftCommand, MAX_LEFT_FORWARD, MAX_LEFT_REVERSE);
  rightCommand = applyMotorLimit(rightCommand, MAX_RIGHT_FORWARD, MAX_RIGHT_REVERSE);

  setMotor(M1_DIR_PIN, M1_PWM_PIN, leftCommand);
  setMotor(M2_DIR_PIN, M2_PWM_PIN, rightCommand);
}
