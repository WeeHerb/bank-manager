//
// Created by mslxl on 12/2/2022.
//

#include "Padding.h"

namespace tui {
    short Padding::getRows() const {
        return short(Container::getRows() + top + bottom);
    }

    short Padding::getCols() const {
        return short(Container::getCols() + left + right);
    }

    void Padding::draw(Canvas &canvas) {
        auto newCanvas = canvas.limitCoord(left, top);
        child->draw(newCanvas);
    }

    Padding::Padding(const std::shared_ptr<Widget> &ptr, short left, short right, short top, short bottom) : Container(
            ptr), left(left), right(right), top(top), bottom(bottom) {

    }
} // tui