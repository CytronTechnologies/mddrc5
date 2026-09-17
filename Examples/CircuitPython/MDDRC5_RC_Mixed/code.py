"""
MDDRC5 - simple RC mixed-mode example for CircuitPython

This example intentionally contains only the basic RC-to-motor control.
The onboard alignment potentiometers, mode switch, test button and error
LEDs are not used.
"""

import time
import board
import digitalio
import pulseio
import pwmio


# ---------------- User settings ----------------

RC_CENTER_US = 1500
RC_MIN_US = 1000
RC_MAX_US = 2000
RC_DEADBAND_US = 35

# True:  RC1 = throttle, RC2 = steering
# False: RC1 = steering, RC2 = throttle
RC1_IS_THROTTLE = True

# Motor alignment (0 to 255). Reduce the faster motor as required.
MAX_LEFT_FORWARD = 255
MAX_LEFT_REVERSE = 255
MAX_RIGHT_FORWARD = 255
MAX_RIGHT_REVERSE = 255


# ---------------- MDDRC5 pins ----------------

RC1_PIN = board.GP1
RC2_PIN = board.GP0

M1_DIR_PIN = board.GP10
M1_PWM_PIN = board.GP11
M1_SLEEP_PIN = board.GP12

M2_DIR_PIN = board.GP21
M2_PWM_PIN = board.GP20
M2_SLEEP_PIN = board.GP18

RC_READ_TIMEOUT_S = 0.1
RC_VALID_MIN_US = 950
RC_VALID_MAX_US = 2050
PWM_FREQUENCY = 20000


def clamp(value, minimum, maximum):
    return max(minimum, min(value, maximum))


def make_output(pin, initial_value=False):
    output = digitalio.DigitalInOut(pin)
    output.direction = digitalio.Direction.OUTPUT
    output.value = initial_value
    return output


# The MDDRC5 RC input circuitry produces active-LOW pulses, so the input
# idles HIGH. Each PulseIn starts by recording the first LOW pulse.
rc1 = pulseio.PulseIn(RC1_PIN, maxlen=4, idle_state=True)
rc2 = pulseio.PulseIn(RC2_PIN, maxlen=4, idle_state=True)
rc1.pause()
rc2.pause()

m1_dir = make_output(M1_DIR_PIN)
m1_sleep = make_output(M1_SLEEP_PIN)
m2_dir = make_output(M2_DIR_PIN)
m2_sleep = make_output(M2_SLEEP_PIN)

m1_pwm = pwmio.PWMOut(
    M1_PWM_PIN, frequency=PWM_FREQUENCY, duty_cycle=0
)
m2_pwm = pwmio.PWMOut(
    M2_PWM_PIN, frequency=PWM_FREQUENCY, duty_cycle=0
)


def read_rc_pulses():
    """Return the latest (RC1, RC2) LOW pulse widths, or (None, None)."""
    rc1.clear()
    rc2.clear()
    rc1.resume()
    rc2.resume()

    start = time.monotonic()
    while len(rc1) == 0 or len(rc2) == 0:
        if time.monotonic() - start >= RC_READ_TIMEOUT_S:
            rc1.pause()
            rc2.pause()
            return None, None

    rc1.pause()
    rc2.pause()
    return rc1[0], rc2[0]


def pulse_to_command(pulse_us):
    """Convert an RC pulse to -255..255 without re-scaling the deadband."""
    offset = pulse_us - RC_CENTER_US

    if abs(offset) <= RC_DEADBAND_US:
        return 0

    if offset > 0:
        command = offset * 255 // (RC_MAX_US - RC_CENTER_US)
        return clamp(command, 0, 255)

    command = -((-offset) * 255 // (RC_CENTER_US - RC_MIN_US))
    return clamp(command, -255, 0)


def apply_motor_limit(command, max_forward, max_reverse):
    if command > 0:
        return command * max_forward // 255

    return -((-command) * max_reverse // 255)


def set_motor(direction, pwm, command):
    command = clamp(command, -255, 255)

    # MDDRC5 motor-driver polarity: HIGH is physical forward.
    direction.value = command > 0
    pwm.duty_cycle = abs(command) * 65535 // 255


def stop_motors():
    m1_pwm.duty_cycle = 0
    m2_pwm.duty_cycle = 0


# Wake both motor drivers only after their PWM outputs are at zero.
stop_motors()
m1_sleep.value = True
m2_sleep.value = True


while True:
    rc1_pulse, rc2_pulse = read_rc_pulses()

    if rc1_pulse is None or rc2_pulse is None:
        stop_motors()
        continue

    if RC1_IS_THROTTLE:
        throttle_pulse = rc1_pulse
        steering_pulse = rc2_pulse
    else:
        throttle_pulse = rc2_pulse
        steering_pulse = rc1_pulse

    throttle_valid = RC_VALID_MIN_US <= throttle_pulse <= RC_VALID_MAX_US
    steering_valid = RC_VALID_MIN_US <= steering_pulse <= RC_VALID_MAX_US

    if not throttle_valid or not steering_valid:
        stop_motors()
        continue

    throttle = pulse_to_command(throttle_pulse)
    steering = pulse_to_command(steering_pulse)

    # Differential-drive mixing.
    left_command = clamp(throttle + steering, -255, 255)
    right_command = clamp(throttle - steering, -255, 255)

    left_command = apply_motor_limit(
        left_command, MAX_LEFT_FORWARD, MAX_LEFT_REVERSE
    )
    right_command = apply_motor_limit(
        right_command, MAX_RIGHT_FORWARD, MAX_RIGHT_REVERSE
    )

    set_motor(m1_dir, m1_pwm, left_command)
    set_motor(m2_dir, m2_pwm, right_command)
