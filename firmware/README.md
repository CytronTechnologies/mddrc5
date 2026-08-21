# MDDRC5 Firmware

This folder contains the official firmware files for the Cytron MDDRC5 Dual Channel R/C Motor Driver.

## Download

Download the latest `.uf2` firmware file from this folder and save it to your computer.

## Firmware Update

1. Connect the MDDRC5 to your computer using a data-capable USB-C cable.
2. Press and hold the **BOOT** button.
3. While holding the BOOT button, press and release the **RESET** button.
4. Release the BOOT button.
5. Wait for the **RPI-RP2** USB drive to appear.
6. Copy the MDDRC5 `.uf2` firmware file to the RPI-RP2 drive.
7. Wait for the file transfer to finish. The board will restart automatically.

> **Important:** Do not disconnect the USB-C cable while the UF2 file is being copied.

## Motor Power

The USB-C port powers the control circuit during the firmware update, but it does not power the motors. Connect a suitable 7–30 V DC source to **V+** and **V-** when motor operation is required.

## Recommended Firmware

For normal R/C operation, always use the latest official MDDRC5 firmware available in this folder.

## Documentation

For complete firmware update instructions and RP2040 pin mapping, refer to the MDDRC5 Firmware & Programming tutorial:

[https://my.cytron.io/tutorial/mddrc5-firmware-programming](https://my.cytron.io/tutorial/mddrc5-firmware-programming)

## Disclaimer

The supplied firmware is intended for use with the Cytron MDDRC5. Ensure that all battery, motor and R/C connections are correct before operating the board.
