//
// Created by mslxl on 2022/12/17.
//
#include <gtest/gtest.h>
#include "core/data/Database.h"

TEST(IOTEST_READ, IOTest) {
    auto db = Database::getInstance();
    for (auto &item: db->staff){
        std::cout << item.id << std::endl;
    }
    std::cout << "-------------\n";

    for (auto &item: db->customer){
        std::cout << item.id << std::endl;
    }
}


TEST(IOTEST_WRITE, IOTest){
    auto db = Database::getInstance();
    for (int i = 0; i < 10; ++i) {
        auto idx = std::to_string(i);
        db->customer.push_back(Customer{
            idx,
            idx,
            idx,
            idx,
            idx,
            true,
            {},
            {}
        });
    }
    db->flush();
}