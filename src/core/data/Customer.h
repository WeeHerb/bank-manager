//
// Created by mslxl on 11/25/2022.
//

#pragma once

#include<string>
#include<vector>

#include<fstream>
#include<cstring>
#include<ostream>
#include<iostream>

#include "Transaction.h"
#include "big/BigIntTiny.h"

struct Customer {
    std::string cardID;
    std::string password;
    std::string name;
    std::string telephone;
    std::string id;
    bool vip;
    std::vector<Transaction> amountChange;
    std::vector<Transaction> debitChange;

    long double amount() {
        long double num = 0;
        const double yearProfit = 0.021, moProfit = 0.011, dayProfit = 0.009;
        std::sort(amountChange.begin(), amountChange.end());
        if (!amountChange.empty()) {
            long long lastTime = amountChange[0].timestamp;
            for (auto &trans: amountChange) {
                num += trans.offset;
                const auto curTimestamp = trans.timestamp;
                num *= 1 + ((long double) (curTimestamp - lastTime) / 1000 / 60 / 60 / 24 / 365 * yearProfit);
                num *= 1 + ((long double) (curTimestamp - lastTime) / 1000 / 60 / 60 / 24 / 30 * moProfit);
                num *= 1 + ((long double) (curTimestamp - lastTime) / 1000 / 60 / 60 / 24 * dayProfit);
            }
        }
        return num;
    }

    long double debit() {
        long double num = 0;
        for (auto &trans: debitChange) {
            num += trans.offset;
        }
        return num;
    }
};

