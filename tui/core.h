//
// Created by mslxl on 10/31/2022.
//


#pragma once
#include<string_view>

namespace tui {
    void stub();

    struct BorderRes{
        constexpr const static std::string_view leftTop = "┌";
        constexpr const static std::string_view rightTop = "┐";
        constexpr const static std::string_view leftBottom = "└";
        constexpr const static std::string_view rightBottom = "┘";

        constexpr const static std::string_view hLine = "─";
        constexpr const static std::string_view vLine = "│";
    };
}
