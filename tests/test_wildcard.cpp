//
// Created by mslxl on 11/23/2022.
//
#include <gtest/gtest.h>
#include "glob/wildcard.hpp"


TEST(WildcardTest, BasicMatch) {
    using namespace glob;
    ASSERT_TRUE(match("hello,a", "hello.."));
    ASSERT_FALSE(match("hello,a", "hello."));
    ASSERT_TRUE(match("hello,a", "hello.a"));
    ASSERT_TRUE(match("astastbbc", "*stbbc"));
}