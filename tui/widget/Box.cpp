//
// Created by mslxl on 11/4/2022.
//

#include "Box.h"

namespace tui {

    bool Box::measure(std::pair<short, short> parentSize) {
        return child->measure({short(parentSize.first - 2), short(parentSize.second - 2)});
    }

    short Box::getRows() const {
        return short(child->getRows() + 2);
    }

    short Box::getCols() const {
        return short(child->getCols() + 2);
    }

    void Box::draw(Canvas &canvas) {


        auto childCanvas = canvas.limitCoord(1,1);
        child->draw(childCanvas);
    }
} // tui