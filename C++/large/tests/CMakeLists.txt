cmake_minimum_required( VERSION 3.1 )

###############################################################################
# It is assumed that the the Catch2 library header is made available
# in the form of a cmake INTERFACE library with ALIAS Catch::Test
###############################################################################

set( TestProject "test_${CMAKE_PROJECT_NAME}" )
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


###############################################################################
# Build executable

# test_main.cpp assumed to contain the main() function or the appropriate
# Catch2 define.
add_executable( ${PROJECT_NAME}
    main.cpp
    )
target_sources( ${PROJECT_NAME}
    PUBLIC ${TestSources}
    )
target_link_libraries( ${PROJECT_NAME}
    Project_config
    Catch::Test
    ${AllInternalLibraries}
    )
# --- test sources of all the defined internal libraries
foreach( lib ${InternalLibraries} )
    file( GLOB "Test${lib}Sources_"
          "${CMAKE_SOURCE_DIR}/libs/${lib}/tests/test_*.cpp"
        )
    target_sources( ${PROJECT_NAME}
        PUBLIC "${Test${lib}Sources_}")
endforeach()

###############################################################################
# CTest
# enable_testing()

# add_test( test_all
#     ${TestProject}
#     )

# foreach( lib ${InternalLibraries} )
#     add_test( test_all "${CMAKE_BINARY_DIR}/libs/${lib}/tests/test_${lib}")
#     add_test( "test_${lib}" "${CMAKE_BINARY_DIR}/libs/${lib}/tests/test_${lib}")
# endforeach()
