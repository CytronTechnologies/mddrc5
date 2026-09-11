# MDDRC5 — Robot Sumo 500g R/C

Firmware and 3D-printable parts for the Robot Sumo 500g R/C tutorial using the Cytron MDDRC5 motor driver.

## Downloads

| Resource | Files |
| --- | --- |
| MDDRC5 firmware | [v1.0.5](firmware/mddrc5_v1.0.5.uf2) · [v1.0.4](firmware/mddrc5_v1.0.4.uf2) |
| Sumo robot body | [Sumo500gRCBody.stl](3d-files/robot-sumo-500g-rc/Sumo500gRCBody.stl) |
| Sumo motor bracket | [Sumo500gRCBracket.stl](3d-files/robot-sumo-500g-rc/Sumo500gRCBracket.stl) |

On GitHub, open the required file and choose **Download raw file**. To download everything, choose **Code → Download ZIP** and extract the archive.

Version v1.0.5 is the highest-numbered firmware included in this repository. Release notes and firmware source code are not included in the supplied materials.

## Repository structure

```text
.
├── README.md
├── SHA256SUMS
├── firmware/
│   ├── README.md
│   ├── mddrc5_v1.0.4.uf2
│   └── mddrc5_v1.0.5.uf2
└── 3d-files/
    ├── README.md
    ├── robot-sumo-500g-rc/
    │   ├── README.md
    │   ├── Sumo500gRCBody.stl
    │   └── Sumo500gRCBracket.stl
    └── robot-battle-karnival-stem/
        └── (existing Battle robot STL files)
```

## Build the Robot Sumo 500g R/C

1. Download the [body and motor bracket](3d-files/robot-sumo-500g-rc/README.md) and print the parts.
2. Prepare two compatible DC gearmotors, rims and tyres, weights, a metal or copper base plate, battery, MDDRC5, R/C transmitter and receiver, cables, fasteners, front shield, and blade according to the assembly tutorial.
3. With the battery disconnected, assemble the robot and connect the left motor to M1A/M1B and the right motor to M2A/M2B. Connect the battery cable to V+/V− with the correct polarity.
4. Connect RC1 to receiver throttle and RC2 to receiver steering. The tutorial's HotRC receiver uses CH2 for throttle and CH1 for steering. Check signal, +5V, and GND orientation at both ends.
5. Follow the MDDRC5 Operation tutorial for Mixed Mode setup and motor alignment. Perform the first powered test with the wheels raised.
6. Measure and weigh the completed robot against the applicable competition rules. The project name does not guarantee a finished weight of 500 g.

Disconnect the battery before assembly or wiring. Cover the blade edge during handling and keep cables clear of the wheels.

## Firmware and printing guides

- [Firmware files and installation](firmware/README.md)
- [Sumo printing notes](3d-files/robot-sumo-500g-rc/README.md)
- [3D file index](3d-files/README.md)

These notes are adapted from the accompanying local assembly and firmware tutorials. The HTML tutorials remain separate from this upload folder.

## File integrity

`SHA256SUMS` records the SHA-256 hash of each UF2 and STL file. From the repository root, verify with `shasum -a 256 -c SHA256SUMS` on macOS, or `sha256sum -c SHA256SUMS` on Linux.

The supplied UF2 block structure and binary STL lengths have been checked. Firmware operation, print fit, and completed robot weight still require hardware validation.

## Licensing

No license file was supplied with these materials. Confirm the applicable firmware and 3D-design distribution terms with the rights holder before public publication.
