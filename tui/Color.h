//
// Created by mslxl on 10/30/2022.
//


#pragma once
#include <ostream>
#include <windows.h>

namespace tui {
    struct Color{
        int code;
        explicit Color(int code): code(code){}
        Color operator | (const Color& rhs) const {
            return Color(this->code | rhs.code);
        }
        Color operator +(const Color& rhs) const {
            return Color(this->code ^ rhs.code);
        }
    };

    const extern Color FG_RED;
    const extern Color FG_BLUE ;
    const extern Color FG_GREEN;

    const extern Color BG_RED ;
    const extern Color BG_BLUE;
    const extern Color BG_GREEN ;

    const extern Color FG_INTENSITY ;
    const extern Color BG_INTENSITY ;

    const extern Color BG_COMMON ;
    const extern Color FG_COMMON ;
}
