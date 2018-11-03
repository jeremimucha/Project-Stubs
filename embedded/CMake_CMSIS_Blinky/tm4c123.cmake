# The Generic system is used with CMake to specify bare metal
set( CMAKE_SYSTEM_NAME      Generic )
set( CMAKE_SYSTEM_PROCESSOR arm )

# Setup the path where the toolchain is located
set( TOOLCHAIN_PATH "I:/gcc-arm-none-eabi/bin" )

# The toolchain prefix for all toolchain executables
set( TOOLCHAIN_PREFIX ${TOOLCHAIN_PATH}/arm-none-eabi- )

set( CMAKE_C_COMPILER   "${TOOLCHAIN_PREFIX}gcc.exe" )
set( CMAKE_CXX_COMPILER "${TOOLCHAIN_PREFIX}g++.exe" )
set( CMAKE_LINKER       "${TOOLCHAIN_PREFIX}ld.exe" )
set( CMAKE_AR           "${TOOLCHAIN_PREFIX}ar.exe" )
set( CMAKE_ASM_COMPILER "${TOOLCHAIN_PREFIX}as.exe" )

# Setup objcopy to allow us to take the linker output and change it to another format
# e.g. convert .elf into raw binary format
set( CMAKE_OBJCOPY      "${TOOLCHAIN_PREFIX}objcopy.exe"
     CACHE FILEPATH "The toolchain objcopy command" FORCE )
set( CMAKE_OBJDUMP      "${TOOLCHAIN_PREFIX}objdump.exe" )

# Compile static libraries instead of .exe files to avoid linkage issues
set( CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY )

# Let CMake find executable on the host, but don't let it use libraries from the host
# search for programs in the build host directories
set( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER )
# for libraries and headers in the target directories
set( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY )
set( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY )
set( CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY )

# Try uncommenting in case of linker errors
# set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
# set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

# Set the CMake C flags (should also be used by the assembler!)
set( CPU "-mthumb -mcpu=cortex-m4 -mtune=cortex-m4" )
set( FPU "-mfpu=fpv4-sp-d16 -mfloat-abi=hard")
#-ffunction-sections -fdata-sections -MD

set( CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${CPU} ${FPU}" CACHE STRING "ASMFLAGS" )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CPU} ${FPU}" CACHE STRING "CFLAGS" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CPU} ${FPU}" CACHE STRING "CXXFLAGS" )

# cache the flags, so that anything that tries to use them, can find them
# set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "CFLAGS" )
# set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "CXXFLAGS" )
# set( CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS}" CACHE STRING "ASMFLAGS" )
