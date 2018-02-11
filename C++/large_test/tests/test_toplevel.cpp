#include "toplevel.hpp"
#include "catch/catch.hpp"


TEST_CASE( "test toplevel" )
{
    int test_value[]{1,2,3,4,5};
    toplevel_function(test_value);
    REQUIRE( true );
}
