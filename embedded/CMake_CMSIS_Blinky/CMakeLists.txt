cmake_minimum_required( VERSION 3.10 )

# The Toolchain needs to be set before declaring the project.
# It also needs to be a CACHE STRING (only STRING works for some reason...)
# and it needs to be FORCEd.
# Setting paths relative to ${PROJECT_SOURCE_DIR} or ${CMAKE_SOURCE_DIR}
# doesn't seem to work either...
set( CMAKE_TOOLCHAIN_FILE tm4c123.cmake CACHE STRING "toolchain file" FORCE)

project( hello_embedded CXX C ASM )

# Execute with the following flags
# -DOPENOCD_PATH_HINT=/path/to/OpenOCD/bin
# -DOPENOCD_BOARD_CFG=/path/to/openocd/board/script
# The default board script is located at openocd/share/openocd/scripts/board/ek-tm4c123gxl.cfg

# The toolchain file is now forced - setting it on the command line doesn't seem to work
# -DCMAKE_TOOLCHAIN_FILE=../tm4c123.cmake   - path to the toolchain

# These no longer seem necessary since setting the C and CXX compilers with a CACHE STRING FORCE
# variable seems to work. Try anyway in case of issues
# -DCMAKE_C_COMPILER_FORCED=1 - prevent CMake attempting to compile a compiler test exe
# -DCMAKE_CXX_COMPILER_FORCED=1 - same

# set( CMAKE_TOOLCHAIN_FILE tm4c123.cmake )
set( LINKER_SCRIPT ${PROJECT_SOURCE_DIR}/TM4C123.ld )

set( CMAKE_C_STANDARD 11 )
set( CMAKE_CXX_STANDARD 14 )
# set( CMAKE_C_STANDARD_REQUIRED FALSE )
# set( CMAKE_CXX_STANDARD_REQUIRED FALSE )

# set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti" )
set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T${LINKER_SCRIPT}" )

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

# Allow C flags to be passed to ASM files
set_source_files_properties(src/startup_TM4C123.S PROPERTIES LANGUAGE C)

# Use either ASM or C startup code.
# When compiling with libraries link them in the linker script and call `_start`
# at the end of the Reset_Handler.
# When compiling without any libs add `-nostartfiles` compile and link flags
# and --specs=nosys.specs link spec.
set( CMAKE_EXECUTABLE_SUFFIX ".elf" )
add_executable( ${PROJECT_NAME}
    src/startup_TM4C123.S
    # src/startup_TM4C123.c
    src/system_TM4C123.c
    src/main.cpp
    )

target_include_directories( ${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/inc
    )

target_compile_definitions( ${PROJECT_NAME} PUBLIC
    PART_TM4C123GH6PM
    TARGET_IS_TM4C123_RA1
    TM4C123GH6PM
)

target_compile_options( ${PROJECT_NAME} PUBLIC
    -Os
    -flto
    # -nostartfiles
    )
target_link_libraries( ${PROJECT_NAME} PUBLIC
    -flto
    # -nostartfiles
    --specs=nosys.specs
    )


# Post-build: dump the .elf file into a binary image suitable for flashing the board.
set( BINARY_SUFFIX .bin )
set( DUMP_BIN
    ${CMAKE_OBJCOPY}
        ${CMAKE_PROJECT_NAME}${CMAKE_EXECUTABLE_SUFFIX}
        -O binary ${CMAKE_PROJECT_NAME}${BINARY_SUFFIX}
    )
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${DUMP_BIN}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Convert ${CMAKE_PROJECT_NAME} ELF into binary image"
    )


# Add a target for flashing the board. Defined only if openocd is found and an openocd board config
# is specified using the OPENOCD_BOARD_CFG variable. Path where to look for openocd can be given
# using the OPENOCD_PATH_HINT variable
find_program( OPENOCD NAMES openocd HINTS ${OPENOCD_PATH_HINT} NO_DEFAULT_PATH )
find_program( OPENOCD NAMES openocd )   # fallback, only called if not found in hinted paths
if( OPENOCD AND OPENOCD_BOARD_CFG )
    message( STATUS "openocd found: ${OPENOCD}" )
    message( STATUS "board config: ${OPENOCD_BOARD_CFG}" )
    message( STATUS "use \"flash\" target to program the board" )
    ADD_CUSTOM_TARGET(
        "flash-elf" DEPENDS ${CMAKE_PROJECT_NAME}
        COMMAND
            ${OPENOCD} -f ${OPENOCD_BOARD_CFG}
            -c "program ${CMAKE_PROJECT_NAME}${CMAKE_EXECUTABLE_SUFFIX} verify reset exit"
        )
    ADD_CUSTOM_TARGET(
        "flash-bin" DEPENDS ${CMAKE_PROJECT_NAME}
        COMMAND
            ${OPENOCD} -f ${OPENOCD_BOARD_CFG}
            -c "program ${CMAKE_PROJECT_NAME}${BINARY_SUFFIX} verify reset exit"
        )
endif()
