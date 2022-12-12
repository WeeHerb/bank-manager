//
// Created by mslxl on 12/13/2022.
//

#pragma once

#include <string>
#include <ctime>


struct Transaction {
    long long timestamp;
    long double offset;

    [[nodiscard]] std::string timeStr() const {
        int ms = int(timestamp % 1000);
        auto tick = (time_t) (timestamp / 1000);
        struct tm tm{};
        char s[40];
        tm = *localtime(&tick);
        strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", &tm);
        std::string str(s);
        str = str + " " + std::to_string(ms);
        return str;
    }
    bool operator<(const Transaction& rhs) const {
        return timestamp < rhs.timestamp;
    }
};
