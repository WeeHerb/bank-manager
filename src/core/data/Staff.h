//
// Created by mslxl on 12/12/2022.
//

#pragma once

#define MESSAGE_HEAD Staff
#define MESSAGE_BODY \
    FIELD_STR(cardID)\
    FIELD_STR(name)  \
    FIELD_STR(telephone) \
    FIELD_STR(id)         \
    FIELD_STR(level) \
                     \

#include "xmarco/xmarco.h"
