//
// Created by mslxl on 10/30/2022.
//


#pragma once
#include <ostream>
#include <windows.h>

namespace tui {
    struct color{
        int code;
        explicit color(int code):code(code){}
        color operator | (const color& rhs) const {
            return color(this->code | rhs.code);
        }
    };

    const static color FG_INTENSITY = color(FOREGROUND_INTENSITY);
    const static color BG_INTENSITY = color(BACKGROUND_INTENSITY);

    const static color BG_COMMON = color(BACKGROUND_BLUE);
    const static color FG_COMMON = color(FOREGROUND_BLUE| FOREGROUND_GREEN | FOREGROUND_RED);

}
