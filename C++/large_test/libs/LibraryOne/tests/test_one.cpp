#include "gtest/gtest.h"
#include <iostream>
#include <sstream>
#include <string>
#include "LibraryOne/one.hpp"

class OneOne : public ::testing::Test { };

TEST_F( OneOne, LibraryOne )
{
    auto test_value = std::string("test");
    auto expected = std::string("test, test, test");
    auto oss = std::ostringstream();
    
    EXPECT_TRUE( oss.str().empty() );
    oneone(oss, test_value);
    EXPECT_EQ( oss.str(), expected );
}
