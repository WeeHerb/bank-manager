//
// Created by mslxl on 12/6/2022.
//
#include<gtest/gtest.h>
#include<iostream>
#include "core/data/struct/linkedlist.h"

TEST(LinkedListTest, Push) {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);

    list.push_front(2);
    list.push_front(3);
    list.push_front(4);
    list.push_front(5);

    int expect[] = {5,4,3,2,1,2,3,4,5};
    int i = 0;
    for(auto begin = list.begin(); begin != list.end(); ++begin, i++){
        EXPECT_EQ(expect[i], *begin);
    }
}

TEST(LinkedListTest, Erase) {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);

    list.push_front(2);
    list.push_front(3);
    list.push_front(4);
    list.push_front(5);

    list.erase(list.begin());
    list.erase(--list.end());

    int expect[] = {4,3,2,1,2,3,4};
    int i = 0;
    for(auto begin = list.begin(); begin != list.end(); ++begin, i++){
        EXPECT_EQ(expect[i], *begin);
    }

    auto iter = ++++++list.begin();
    EXPECT_EQ(*iter, 1);
    list.erase(iter);

    int expectEr[] = {4,3,2,2,3,4};
    i = 0;
    for(auto begin = list.begin(); begin != list.end(); ++begin, i++){
        EXPECT_EQ(expectEr[i], *begin);
    }
    for(auto begin = list.begin(); begin != list.end(); ){
        begin = list.erase(begin);
    }
    EXPECT_TRUE(list.empty());
}
