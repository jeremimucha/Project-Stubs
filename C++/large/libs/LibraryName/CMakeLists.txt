cmake_minimum_required( VERSION 3.1 )

set( LibraryName !!_ENTER_LIBRARY_NAME_HERE_!! )
project( ${LibraryName} )


###############################################################################
# Prepare external dependencies
###############################################################################
# If using any external libraries create a 'external' subdir with an appropriate
# CMakeLists and add the following for each library
# add_subdirectory( external/some_lib ) 
# If an external dependency is used
# in more than one internal libs preffer including the dependency in top-most
# CMakeLists, otherwise create a external subdir for the specific library.

# add_subdirectory( external/catch )


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

# Add all of the remaining source files to be build as a static library
# linked against the main executable
# set( LibrarySources
#      ${PROJECT_SOURCE_DIR}/src/large_test.cpp
#    )
# Or let all of the source files be globed
file( GLOB LibrarySources
      "${PROJECT_SOURCE_DIR}/src/*.cpp"
    )


###############################################################################
# Configure build
###############################################################################

# Inherit the config from top-level CMakeLists otherwise - override here
# # Set required C++ standard
# set( CMAKE_CXX_STANDARD 17 )
# # Set build type
# if( NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
#   message("Setting build type to 'RelWithDebInfo' as none was specified.")
#   set( CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
# endif()

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
              "${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME}/*.h"
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
# Build target library
###############################################################################

add_library( ${PROJECT_NAME}
    STATIC      # STATIC or SHARED
    ${LibrarySources}
    )
add_library( Lib::${PROJECT_NAME}
    ALIAS ${PROJECT_NAME}
    )
target_include_directories( ${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    )
target_include_directories( ${PROJECT_NAME}
    PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/${LibraryName}
    $<INSTALL_INTERFACE:include/${LibraryName}
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
target_compile_options( ${PROJECT_NAME}
    PRIVATE
    # -fconcepts
    # -lstdc++fs
    )
target_link_libraries( ${PROJECT_NAME}
    Project_config
    # ${Boost_LIBRARIES}
    )


###############################################################################
# Unit Tests
###############################################################################
add_subdirectory( tests )

###############################################################################
# Install
###############################################################################
install( TARGETS ${PROJECT_NAME}
         DESTINATION lib
         LIBRARY
       )
