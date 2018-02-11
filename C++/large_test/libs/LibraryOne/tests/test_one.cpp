#include <catch/catch.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include "LibraryOne/one.hpp"


TEST_CASE( "oneone prints the correct value", "[LibraryOne]" )
{
    auto test_value = std::string("test");
    auto expected = std::string("test, test, test");
    auto oss = std::ostringstream();
    
    REQUIRE( oss.str().empty() );
    oneone(oss, test_value);
    REQUIRE( oss.str() == expected );
}
