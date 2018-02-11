#include <catch/catch.hpp>
#include <LibraryTwo/two.hpp>


TEST_CASE( "test two" )
{
    int test_value[]{ 3, 2, 5, 7, 2, 5, 9, 0, 1, 2, 3, 4 };
    auto expected = std::accumulate( test_value, test_value+8, 0 );
    REQUIRE( twotwo(test_value) );
}
