//
// Created by mslxl on 11/7/2022.
//

#include "Struct.h"

namespace tui {

    Struct::Struct(short rows, short cols) : rows(rows), cols(cols) {}

    bool Struct::measure(std::pair<short, short> parentSize) {
        return true;
    }

    short Struct::getRows() const {
        return rows;
    }

    short Struct::getCols() const {
        return cols;
    }

    void Struct::draw(Canvas &canvas) {

    }
} // tui