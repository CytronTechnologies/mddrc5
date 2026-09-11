# MDDRC5

This repository contains firmware and 3D-printable files for projects using the Cytron MDDRC5 5 Amp 7V–30V DC Motor Driver for R/C (2 Channels).

## Tutorials

- [Getting Started with MDDRC5](https://my.cytron.io/tutorial/getting-started-with-mddrc5)
- [Build a Robot Sumo 500g R/C with MDDRC5](https://my.cytron.io/tutorial/build-robot-sumo-500g-rc-mddrc5)

## Resources

| Resource | GitHub folder |
| --- | --- |
| MDDRC5 Firmware | [firmware](firmware/) |
| Robot Sumo 500g R/C 3D Files | [robot-sumo-500g-rc](3d-files/robot-sumo-500g-rc/) |
| Robot Battle 3D Files | [robot-battle-karnival-stem](3d-files/robot-battle-karnival-stem/) |

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
