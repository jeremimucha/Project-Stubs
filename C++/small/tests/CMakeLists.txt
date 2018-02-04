cmake_minimum_required( VERSION 3.1 )

###############################################################################
# It is assumed that the the Catch2 library header is made available
# in the form of a cmake INTERFACE library with ALIAS Catch::Test
###############################################################################

set( TestProjectName ${Enter_project_name_here} )
project( ${TestProjectName} )


###############################################################################
# Prepare test sources

# These are all sources EXCLUDING the tests_main.cpp which contains main()
# or the appropriate Catch2 define
file( GLOB TestSources
      RELATIVE "${PROJECT_SOURCE_DIR}"
               "${PROJECT_SOURCE_DIR}/test_*.cpp
    )

# enable CTest testing
enable_testing()


###############################################################################
# Build executable

set( TestExecutableName Enter_test_exec_here )
add_executable( ${TestExecutableName} tests_main.cpp )
target_sources( ${TestExecutableName}
    PUBLIC ${TestSources}
    )

target_include_directories( ${TestExecutableName}
    PUBLIC ${CMAKE_SOURCE_DIR}
    )

target_link_libraries( ${TestExecutableName}
    Catch::Test
    )

add_test( test_all ${TestExecutableName} )
