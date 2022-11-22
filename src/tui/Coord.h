//
// Created by mslxl on 11/4/2022.
//

#pragma once

#include<windows.h>
#include<ostream>

namespace tui {
    class Coord {
    public:
        short x;
        short y;

        Coord operator+(const Coord &rhs) const;

        Coord operator-(const Coord &rhs) const;

        [[nodiscard]] Coord narrowX(short offset) const;

        [[nodiscard]] Coord narrowY(short offset) const;

        _COORD unwrap() const;

        Coord(short x, short y);
    };

    std::ostream & operator<<(std::ostream& , const Coord&);
} // tui
