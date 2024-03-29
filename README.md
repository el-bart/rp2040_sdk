# RP2040 SDK

fully automated, dockerized SDK for reproducible builds for RP2040 µC and Raspberry Pico board.

## usage

first instantiate SDK in your project:
`./export_template /path/to/your/rp2040/project`

then compile your sources.
here we'll use official RP2040 examples:
```
cd /path/to/your/rp2040/project
./rp2040_sdk
```

from now on you work in the SDK env, with tools version set
```
git clone "https://github.com/raspberrypi/pico-examples.git" --branch master
cd pico-examples
# compile
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
cd blink
make -j8
# flash - full command
rp2040_openocd -c 'program ./blink.elf verify reset exit'
# flash - shorthand
rp2040_flash ./blink.elf
```

in order to debug program start OpenOCD in one terminal:
```
./rp2040_sdk rp2040_openocd
```

while in the second start GDB
```
./rp2040_sdk
# note: from now on you work in the SDK env, with tools version set
gdb-multiarch --tui pico-examples/build/blink/blink.elf
# now inside GDB type:
target remote localhost:3333
```
welcome to the program debugging! :)

note that it is also possible to use locally installed `gdb-multiarch`:
```
gdb-multiarch --tui pico-examples/build/blink/blink.elf
```
it will work just fine, since by default:
- all paths in SDK container and local machine are the same
- GDB port from within SDK is exposed to host machine

## programming

the easiest way to start is to use one [picoboard as SWD programmer for another picoboard](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html#debugging-using-another-raspberry-pi-pico).
first upload [picoprobe.uf2](https://github.com/raspberrypi/picoprobe/releases/latest/download/picoprobe.uf2) into the 'programmer' board.
then wire both boards as in [getting started guide](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf), "Appendix A: Using Picoprobe" section.
