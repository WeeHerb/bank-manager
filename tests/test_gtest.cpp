//
// Created by mslxl on 11/23/2022.
//

#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
// Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
// Expect equality.
    EXPECT_EQ(7 * 6, 42);

    std::string aa;
    for(int i = 0; i < 5; i++){
        aa += '\0';
    }
    ASSERT_EQ(aa.size(), 5);
}