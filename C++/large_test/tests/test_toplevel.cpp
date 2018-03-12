#include "toplevel.hpp"
#include "gtest/gtest.h"

class TopLevel : public ::testing::Test { };

TEST_F( TopLevel, topleveltest )
{
    int test_value[]{1,2,3,4,5};
    toplevel_function(test_value);
    EXPECT_TRUE( true );
}
