//
// Created by mslxl on 10/30/2022.
//
#include "Color.h"

namespace tui {
    const extern Color FG_RED = Color(FOREGROUND_RED);
    const extern Color FG_BLUE = Color(FOREGROUND_BLUE);
    const extern Color FG_GREEN = Color(FOREGROUND_GREEN);

    const extern Color BG_RED = Color(BACKGROUND_RED);
    const extern Color BG_BLUE = Color(BACKGROUND_BLUE);
    const extern Color BG_GREEN = Color(BACKGROUND_GREEN);

    const extern Color FG_INTENSITY = Color(FOREGROUND_INTENSITY);
    const extern Color BG_INTENSITY = Color(BACKGROUND_INTENSITY);

    const extern Color BG_COMMON = BG_BLUE;
    const extern Color FG_COMMON = FG_BLUE | FG_GREEN | FG_RED;
}