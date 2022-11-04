//
// Created by mslxl on 11/4/2022.
//

#include "Coord.h"

namespace tui {
    Coord::Coord(short x, short y) : x(x), y(y) {

    }

    Coord Coord::operator+(const Coord &rhs) const {
        return {short(x + rhs.x), short(y + rhs.y)};
    }

    Coord Coord::operator-(const Coord &rhs) const {
        return {short(x - rhs.x), short(y - rhs.y)};
    }

    _COORD Coord::unwrap() const {
        return {x, y};
    }

    Coord Coord::narrowX(short offset) const {
        return {short(x + offset), y};
    }

    Coord Coord::narrowY(short offset) const {
        return {x, short(y + offset)};
    }

} // tui