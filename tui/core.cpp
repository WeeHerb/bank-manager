//
// Created by mslxl on 10/31/2022.
//
#include <cassert>
#include <sstream>

#include "tui/core.h"


void tui::stub() {
	std::abort();
}

namespace tui::border{
    std::string_view leftTop = "┌";
    std::string_view rightTop = "┐";
    std::string_view leftBottom = "└";
    std::string_view rightBottom = "┘";

    std::string_view hLine = "─";
    std::string_view vLine = "│";

    std::string line(short width){
        std::stringstream ss;
        while(width--){
            ss << hLine;
        }
        return ss.str();
    }

    std::string topLineWithCorner(short width){
        if(width == 1) return std::string(hLine);
        std::string l = width - 2 > 0 ? line(short(width - 2)): "";
        return std::string(leftTop) + l + std::string(rightTop);
    }
    std::string bottomLineWithCorner(short width){
        if(width == 1) return std::string(hLine);
        std::string l = width - 2 > 0 ? line(short(width - 2)): "";
        return std::string(leftBottom) + l + std::string(rightBottom);
    }
}