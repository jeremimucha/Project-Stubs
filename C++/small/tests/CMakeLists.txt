cmake_minimum_required( VERSION 3.1 )

###############################################################################
# It is assumed that the the Catch2 library header is made available
# in the form of a cmake INTERFACE library with ALIAS Catch::Test
###############################################################################

set( TestProject "Tests_${Project}" )
project( ${TestProject} )


###############################################################################
# Prepare test sources

# These are all sources EXCLUDING the tests_main.cpp which contains main()
# function or the appropriate Catch2 define.
# Naming convention is assumed - test_someFeatureUnderTest.cpp
file( GLOB TestSources
      RELATIVE "${PROJECT_SOURCE_DIR}"
      "${PROJECT_SOURCE_DIR}/test_*.cpp"
    )

# enable CTest testing
enable_testing()


###############################################################################
# Build executable

set( TestExecutable "test_${Executable}" )
# test_main.cpp assumed to contain the main() function or the appropriate
# Catch2 define.
add_executable( ${TestExecutable}
    tests_main.cpp
    )
target_sources( ${TestExecutable}
    PUBLIC ${TestSources}
    )
target_link_libraries( ${TestExecutable}
    Lib::InternalLibrary
    Catch::Test
    )

add_test( test_all ${TestProject} )
