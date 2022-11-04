//
// Created by mslxl on 11/4/2022.
//

#include "Container.h"

#include <utility>

namespace tui {
    bool Container::measure(std::pair<short, short> parentSize) {
        return child->measure(parentSize);
    }

    short Container::getRows() const {
        return child->getRows();
    }

    short Container::getCols() const {
        return child->getCols();
    }

    void Container::draw(Canvas &canvas) {
        child->draw(canvas);
    }

    Container::Container(std::shared_ptr<Widget> cp) : child(std::move(cp)){

    }
} // tui