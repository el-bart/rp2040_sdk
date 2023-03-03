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
# flash
openocd_rp2040 -c 'program ./blink.elf verify reset exit'
```

in order to debug program start OpenOCD in one terminal:
```
./rp2040_sdk openocd_rp2040
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
