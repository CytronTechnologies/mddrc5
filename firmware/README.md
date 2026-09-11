# MDDRC5 firmware

| File | Status in this package |
| --- | --- |
| [mddrc5_v1.0.5.uf2](mddrc5_v1.0.5.uf2) | Highest-numbered supplied version |
| [mddrc5_v1.0.4.uf2](mddrc5_v1.0.4.uf2) | Earlier supplied version |

Both binaries are preserved unchanged. The supplied files do not include release notes, build instructions, or source code, so differences between these versions are not documented here.

## Install a UF2 file

The following procedure comes from the accompanying MDDRC5 firmware tutorial.

1. Disconnect the robot battery, motors, and R/C devices before updating.
2. Connect the MDDRC5 to the computer using a data-capable USB-C cable.
3. Hold **BOOT**, press and release **RESET**, then release **BOOT**.
4. Wait for the **RPI-RP2** USB drive to appear.
5. Copy the downloaded MDDRC5 `.uf2` file to that drive.
6. Wait for the transfer to finish. The board restarts and the drive disconnects automatically. Do not unplug the cable during copying.

USB-C supplies the control circuit for updating; it does not power the motors.

## Check after installation

With motors and receiver disconnected, confirm that the PWR LED turns on. The supplied tutorial describes repeated double blinks on both ERR LEDs as the standard firmware indication for missing valid R/C input. This indicator check does not identify the firmware version or verify all motor-control functions.

Before a motor test, disconnect power, restore the wiring, and raise the robot so its wheels are clear of the surface. Follow the operation tutorial for Mixed Mode setup, motor alignment, and R/C checks.

[Return to repository overview](../README.md)
