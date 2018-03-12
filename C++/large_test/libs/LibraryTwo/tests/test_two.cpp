#include "gtest/gtest.h"
#include <LibraryTwo/two.hpp>

class TestTwo : public ::testing::Test { };

TEST_F( TestTwo, testtwo_gtest )
{
    int test_value[]{ 3, 2, 5, 7, 2, 5, 9, 0, 1, 2, 3, 4 };
    auto expected = std::accumulate( test_value, test_value+8, 0 );
    EXPECT_EQ( twotwo(test_value), expected );
}
