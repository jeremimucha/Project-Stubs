cmake_minimum_required( VERSION 3.1 )

set( Project !!_ENTER_PROJECT_NAME_HERE_!! )
project( ${Project} )

###############################################################################
# Prepare external dependencies
###############################################################################
# If using any external libraries create a 'external'
# subdir with an appropriate CMakeLists and add the following
# for each library
# add_subdirectory( external/some_lib )
add_subdirectory( external/catch )


# Find any external libraries via find_backage
# see cmake --help-module-list and cmake --help-module ModuleName
# for details on a specific module
# If using boost
# find_package( Boost 1.60.0
#   REQUIRED COMPONENTS
#   filesystem system iostreams
#   )
#
# if( Boost_FOUND )
#   include_directories( ${Boost_INCLUDE_DIRS} )
# else()
#   message( FATAL_ERROR "Cannon find Boost" )
# endif()


###############################################################################
# Prepare source files for build
###############################################################################
# Create a Sources variable to all the cpp files necessary
# to build the target
set( MainSources
    ${PROJECT_SOURCE_DIR}/src/main.cpp
   )

# Add all of the remaining source files to be build as a static library
# linked against the main executable
# set( TopLevelLibrarySources
#      ${PROJECT_SOURCE_DIR}/src/small_test.cpp
#    )
# Or let all of the source files be globed, minus the one given in MainSources
file( GLOB TopLevelLibrarySources
      "${PROJECT_SOURCE_DIR}/src/*.cpp"
    )
list( REMOVE_ITEM TopLevelLibrarySources ${MainSources} )


###############################################################################
# Configure build
###############################################################################
# Set required C++ standard
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED TRUE )
# Set build type
if( NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message("Setting build type to 'Debug' as none was specified.")
  set( CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

# Export compile_commands.json for use with cppcheck
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

option(ENABLE_ASAN "Enable memory sanitizers" FALSE)
option(ENABLE_USAN "Enable undefined sanitizers" FALSE)
option(ENABLE_TSAN "Enable thread sanitizers" FALSE)
option(ENABLE_WERROR "Treat warnings as errors" TRUE)

if(CMAKE_COMPILER_IS_GNUCC)
  option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)
endif()

add_library(Project_config INTERFACE)
if( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
    target_compile_options( Project_config INTERFACE /W4 /WX )
else()
    target_compile_options( Project_config INTERFACE
      -Wall
      -Wextra # reasonable and standard
      -Weffc++ # Warn about violations of Effective C++ style rules
      -Wshadow # warn the user if a variable declaration shadows one from a parent context
      -Wnon-virtual-dtor # warn the user if a class with virtual functions has a
                      # non-virtual destructor. This helps catch hard to track down memory errors
      -Wold-style-cast # warn for c-style casts
      -Wcast-align # warn for potential performance problem casts
      -Wunused # warn on anything being unused
      -Woverloaded-virtual # warn if you overload (not override) a virtual function
      -Wpedantic # warn if non-standard C++ is used
      -Wconversion # warn on type conversions that may lose data
      -Wsign-conversion # warn on sign conversions
      -Wnull-dereference # warn if a null dereference is detected
      -Wdouble-promotion # warn if float is implicit promoted to double
      -Wformat=2 # warn on security issues around functions that format output
              # (ie printf) 
    )
    if(ENABLE_WERROR)
      target_compile_options( Project_config INTERFACE
        -Werror
      )
    endif()
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU" )
      target_compile_options( Project_config INTERFACE
        -Wmisleading-indentation # warn if identation implies blocks where blocks do not exist
        -Wduplicated-cond # warn if if / else chain has duplicated conditions
        -Wduplicated-branches # warn if if / else branches have duplicated code
        -Wlogical-op # warn about logical operations being used where bitwise were probably wanted
        -Wuseless-cast # warn if you perform a cast to the same type
      )
    endif()
    if(ENABLE_ASAN OR ENABLE_USAN OR ENABLE_TSAN)
      if(CMAKE_BUILD_TYPE NOT (MATCHES "Debug"))
        message(WARNING "Sanitizers used with build other than 'Debug' flags set -O0 -g")
      endif()
      target_compile_options( Project_config INTERFACE
          -g
          -O0
      )
    endif()
    if(ENABLE_COVERAGE)
      target_compile_options( Project_config INTERFACE
          -fprofile-arcs
          -ftest-coverage
        #   --coverage  # only needed at linktime
      )
      target_link_libraries( Project_config INTERFACE
          -fprofile-arcs
          -ftest-coverage
          --coverage
      )
    endif()
    if(ENABLE_ASAN OR ENABLE_USAN OR ENABLE_TSAN)
    #   target_compile_options( Project_config INTERFACE
    #       -fuse-ld=gold   # only needed at linktime
    #   )
      target_link_libraries( Project_config INTERFACE
          -fuse-ld=gold
      )
    endif()
    if(ENABLE_ASAN)
      target_compile_options( Project_config INTERFACE
        -fno-omit-frame-pointer
        -fsanitize=address
        -fsanitize=leak
      )
      target_link_libraries( Project_config INTERFACE
          -fno-omit-frame-pointer
          -fsanitize=address
          -fsanitize=leak
      )
    endif()
    if(ENABLE_USAN)
      target_compile_options( Project_config INTERFACE
        -fsanitize=undefined
      )
      target_link_libraries( Project_config INTERFACE
          -fsanitize=undefined
      )
    endif()
    if(ENABLE_TSAN)
      target_compile_options( Project_config INTERFACE
        -fsanitize=thread
      )
      target_link_libraries( Project_config INTERFACE
          -fsanitize=thread
      )
    endif()
endif()

option(CPP_USE_CPPCHECK "Enable cppcheck build step" TRUE)
if(CPP_USE_CPPCHECK)
  find_program(Cppcheck NAMES cppcheck)
  if (Cppcheck)
      list(
          APPEND Cppcheck 
              "--enable=all"
              "--inconclusive"
              "--force"
              "--verbose"
              "--language=c++"
              "--inline-suppr"
              "${CMAKE_SOURCE_DIR}/include/*.h"
              "${CMAKE_SOURCE_DIR}/src/*.cpp"
              "${CMAKE_SOURCE_DIR}/test/*.cpp"
      )
      message(${Cppcheck})
  endif()
endif()

option(CPP_USE_CLANGTIDY "Enable clang-tidy build step" TRUE)
if(CPP_USE_CLANGTIDY)
  find_program(Clangtidy NAMES clang-tidy)
  if (Clangtidy)
      list(
          APPEND Clangtidy 
              "-checks='*'"
              "-header-filter='.*'"
      )
      message(${Clangtidy})
  endif()
endif()
###############################################################################
# Build target
###############################################################################
# Libraries
# Define a list of all the internal libraries here
set( InternalLibraries
     !!_LIST_ALL_INTERNAL_LIBRARIES_HERE_!!
   )
foreach( lib ${InternalLibraries} )
    add_subdirectory( "libs/${lib}" )
endforeach()

# Toplevel internal library
set( TopLevelLibrary "${PROJECT_NAME}_" ) # cmake will add a "lib" prefix to the name

add_library( ${TopLevelLibrary}
    ${TopLevelLibrarySources}
    )
add_library( Lib::TopLevelLibrary
    ALIAS ${TopLevelLibrary}
    )
target_include_directories( ${TopLevelLibrary}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    )
    if(CPP_USE_CPPCHECK)
    set_target_properties( ${TopLevelLibrary}
        PROPERTIES
        CXX_CPPCHECK "${Cppcheck}"
    )
endif()
if(CPP_USE_CLANGTIDY)
    set_target_properties( ${TopLevelLibrary}
        PROPERTIES
        CXX_CLANG_TIDY "${Clangtidy}"
    )
endif()
# target_compile_options( ${TopLevelLibrary}
#     PRIVATE
#     # -fconcepts
#     # -lstdc++fs
#     )
target_link_libraries( ${TopLevelLibrary}
    Project_config
    # ${Boost_LIBRARIES}
    # ${InternalLibraries}
    )

set( AllInternalLibraries ${InternalLibraries} ${TopLevelLibrary} )

# Then the executable

add_executable( ${PROJECT_NAME}
    ${MainSources}
    )
target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    )
    if(CPP_USE_CPPCHECK)
    set_target_properties( ${PROJECT_NAME}
        PROPERTIES
        CXX_CPPCHECK "${Cppcheck}"
    )
endif()
if(CPP_USE_CLANGTIDY)
    set_target_properties( ${PROJECT_NAME}
        PROPERTIES
        CXX_CLANG_TIDY "${Clangtidy}"
    )
endif()
# target_compile_options( ${PROJECT_NAME}
#     PRIVATE
#     # -fconcepts
#     # -lstdc++fs
#     )
target_link_libraries( ${PROJECT_NAME}
    Project_config
    ${AllInternalLibraries}
    # ${Boost_LIBRARIES}
    )


###############################################################################
# Unit Tests
###############################################################################
add_subdirectory( tests )


###############################################################################
# Install
###############################################################################
# for make install
# Set installation root directory
set( CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" )
install( TARGETS ${PROJECT_NAME}
         DESTINATION bin
       )
install( TARGETS ${InternalLibraries}
         LIBRARY DESTINATION lib
       )

# On Windows
# install( TARGETS ${PROJECT_NAME}
#          RUNTIME DESTINATION .
#        )

# install any additional files
# install( FILES enter-file-dir-here 
#          DESTINATION .
#        )

# Create a cpack-based installer
include( InstallRequiredSystemLibraries )
# set( CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt" )
# set( CPACK_PACKAGE_VERSION_MAJOR "${${Project}_VERSION_MAJOR}" )
# set( CPACK_PACKAGE_VERSION_MINOR "${${Project}_VERSION_MINOR}" )
include( CPack )
