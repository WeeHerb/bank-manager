//
// Created by mslxl on 10/31/2022.
//


#pragma once
#include<string_view>

namespace tui {
    void stub();

    namespace border{
        extern std::string_view leftTop;
        extern std::string_view rightTop;
        extern std::string_view leftBottom;
        extern std::string_view rightBottom;

        extern std::string_view hLine;
        extern std::string_view vLine;

        std::string topLineWithCorner(short);
        std::string bottomLineWithCorner(short);
    }

}
