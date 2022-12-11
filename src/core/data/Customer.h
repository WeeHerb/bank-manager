//
// Created by mslxl on 11/25/2022.
//

#pragma once

#include<string>

//class Customer {
//    std::string name;
//    std::string telephone;
//    std::string id;
//    std::string cardID;
//    bool vip;
//    unsigned long amount;
//    unsigned long debit;
//};

#define MESSAGE_HEAD Customer
#define MESSAGE_BODY \
    FIELD_STR(cardID)\
    FIELD_STR(name)  \
    FIELD_STR(telephone) \
    FIELD_STR(id)         \
    FIELD_BOOL(vip)  \
    FIELD_I128(amount)   \
    FIELD_I128(debit)\
                     \



#include "xmarco/xmarco.h"