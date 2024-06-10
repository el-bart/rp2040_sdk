# release notes

## dev
* added `example/` dir with end-to-end build flow example
* all helper scripts in SDK are now following `rp2040_*` naming convention
* `rp2040_flash` helper added, to make flashing less typing

## v1.1
* when image exists, output from build is quiet (minimizes noise on the screen)
* bugfix: absence of programmer does not prevent builds

## v1.0
* docker-based SDK
* GDB integration
* SWD picoprobe programmer integration
* helper script for running SDK env
* helper script for exporting SDK to a different project
* automated SDK building
* using stable versions of software
* instructions of SDK usage
* doc on simple way of programming
* SDK running as regular user
