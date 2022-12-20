//
// Created by mslxl on 12/13/2022.
//

#pragma once

#include <string>
#include <ctime>


struct Transaction {
    long long timestamp;
    std::string name;
    long double offset;

    [[nodiscard]] std::string timeStr() const {
        auto tick = (time_t) timestamp;
        struct tm tm{};
        char s[40];
        tm = *localtime(&tick);
        strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", &tm);
        std::string str(s);
        return str;
    }
    bool operator<(const Transaction& rhs) const {
        return timestamp < rhs.timestamp;
    }
};
