# Blinky TM4C123g project configured using CMSIS and CMake

Can be adapted, extended and used as a project template for other ARM/CortexM/CMSIS/any microcontroller.

## Introduction
The project needs to be configured with CMake using the included toolchain file.
It's set up and tested for gcc-arm-none-eabi 7.3.1.
Run CMake from the build directory with the following flags:

> -DCMAKE_TOOLCHAIN_FILE=../tm4c123.cmake  
> -DCMAKE_C_COMPILER_FORCED=1  
> -DCMAKE_CXX_COMPILER_FORCED=1  
> -DOPENOCD_PATH_HINT=/path/to/OpenOCD/bin  
> -DOPENOCD_BOARD_CFG=/path/to/openocd/board/script  

* The toolchain file configures cmake for compiling a bare metal project using.
    * Make sure to enter a correct toolchain path pointing to the bin/ of your installatioin of gcc-arm-non-eabi compiler,within the toolchain file.
    * When adapting the project for another processor make sure to change the CPU and FPU compiler flags within the toolchain file.

* The CMAKE_C/CXX_COMPILER_FORCED flags cause CMake not to attempt compiling a test
executable program to check if the compiler is working.

* The OPENOCD_PATH_HINT is optional. It should be provided if CMake refuses to find the system installation of openocd or if a different installation is preffered over the system one.

* The OPENOCD_BOARD_CFG is required to enable a `flash` build target, which uses openocd to program the generated binary.

### Example usage:
>mkdir build; cd build  
>$ `cmake` -DCMAKE_TOOLCHAIN_FILE=../tm4c123.cmake -DCMAKE_C_COMPILER_FORCED=1 -DCMAKE_CXX_COMPILER_FORCED=1 -DOPENOCD_PATH_HINT=~/OpenOCD/bin -DOPENOCD_BOARD_CFG=~/OpenOCD/share/openocd/scripts/board/ek-tm4c123gxl.cfg ..  
>$ `make`  
>$ `make flash`

Or use ninja-build
>$ mkdir build; cd build  
>$ `cmake` -G"Ninja" (same flags as above) ..  
>$ `ninja`  
>$ `ninja flash`

Alternatively use openocd manually, or some other tool for flashing the board.
Example using openocd:
>$ `openocd` `--file` path/to/board/script/ek-tm4c123gxl.cfg `-c` "`program` blinky.bin `verify` `reset`"

Also see: http://openocd.org/doc/html/Flash-Programming.html#Flash-Programming

Should also work on Windows. Tested using MSYS2 and external installations of gcc-arm-non-eabi and openocd. If using ninja, should potentially work without any other dependencies.


## Debugging
Use openocd and gcc-arm-non-eabi-gdb for debugging purposes. The same board script as for flashing should be used to connect to the board. Run OpenOCD in one terminal window:
>$ `openocd` `-f` board/ek-tm4c123gxl.cfg  
And arm-none-eabi-gdb in another  
>$ `arm-none-eabi-gdb` `-x` gdbinit blinky.elf

Also see: http://openocd.org/doc/html/GDB-and-OpenOCD.html#GDB-and-OpenOCD

## Adapting the project for other microcontrollers
1. Provide a linker script or edit the existing one with appropriate Flash and Ram memory regions. Probably change the name too.
2. Provide a startup file for your microcontroller or edit the existing one. The obvious areas to change are the interrupt vector table, stack size and heap size.
3. If using an CMSIS supported micro swap all the `cmsis_` file to appropriate ones for your processor and compiler. All of the `<device>` files (here system_TM4C123.h, system_TM4C123.c, TM4C123.h, TM4C123GH6PM.h) should be provided by your chip vendor. Not all chips are well supported though (TM4C123GH6PM has terrible/no CMSIS support). It should be possible to find the necessary files with sufficient amounts of google or adapt existing ones for other micros from the same family, e.g. CortexM4. Also refer to: https://developer.arm.com/embedded/cmsis
4. Edit `tm4c123.cmake` toolchain file `CPU` and `FPU` with proper flags for the target processor.
5. Edit the main `CMakeLists.txt` file to reflect all of the above changes, change target specific defines etc.

## Other notes
1. If compiling a project without any c libraries comment out the libraries in the linker script and change the `startup_<device>` code to call `main` directly, rather than `_start`. You'll also need to include the `-nostartfiles` compiler and linker flags and the `--specs=nosys.specs` linker flag. If compiling with C libraries do the exact opposite.
2. Make sure the interrupt vector section in the startup script and reference to the interrupt vector table in the linker script have the same name - e.g. `.vectors` or `.isr_vector`.
