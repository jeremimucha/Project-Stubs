cmake_minimum_required(VERSION 3.1)

set( ProjectName Enter_name_here )
project( ${ProjectName} )


###############################################################################
# Prepare external dependencies
###############################################################################
# If using any external libraries create a 'external'
# subdir with an appropriate CMakeLists and add the following
# for each library
# add_subdirectory( third-party/some_lib )
add_subdirectory( external/catch )


# Find any external libraries via find_backage
# see cmake --help-module-list and cmake --help-module ModuleName
# for details on a specific module
# If using boost
# find_package( Boost 1.60.0 REQUIRED COMPONENTS filesystem system iostreams )
#
# if( Boost_FOUND )
#   message( "boost found" )
# else()
#   message( FATAL_ERROR "Cannon find Boost" )
# endif()


###############################################################################
# Prepare source files for build
###############################################################################
# Create a Sources variable to all the cpp files necessary
# to build the target
set( Sources
     src/file1.cpp
     src/file2.cpp
   )

# Or glob all the files
# file( GLOB Sources 
#       "${PROJECT_SOURCE_DIR}/src/*.cpp"
#     )


###############################################################################
# Configure build
###############################################################################
# Set required C++ standard
set( CMAKE_CXX_STANDARD 17 )
# Set build type
if( NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message("Setting build type to 'RelWithDebInfo' as none was specified.")
  set( CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
endif()


###############################################################################
# Build target
###############################################################################
set( ExecutableName Enter_exec_name_here )

add_executable( ${ExecutableName} ${Sources} )

target_include_directories( ${ExecutableName}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    )

target_compile_definitions( ${ExecutableName}
    PUBLIC Wall Wextra Wpedantic)

# if using any external libraries include them here
# they need to be properly found first. See find_package section
target_link_libraries( ${ExecutableName}
    some_lib
    )


###############################################################################
# Unit Tests
###############################################################################
include_subdirectory( tests )


###############################################################################
# Install
###############################################################################
# for make install
# Set installation root directory
set( CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" )
install( TARGETS ${ExecutableName}
         DESTINATION bin
       )

# On Windows
# install( TARGETS ${ExecutableName}
#          LIBRARY DESTINATION lib
#          RUNTIME DESTINATION bin
#        )

# install any additional files
# install( FILES enter-file-dir-here 
#          DESTINATION etc
#        )

# Create a cpack-based installer
include( InstallRequiredSystemLibraries )
set( CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt )
set( CPACK_PACKAGE_VERSION_MAJOR "${${ProjectName}_VERSION_MAJOR} )
set( CPACK_PACKAGE_VERSION_MINOR "${${ProjectName}_VERSION_MINOR} )
include( CPack )
