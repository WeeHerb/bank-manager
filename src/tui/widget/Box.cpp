//
// Created by mslxl on 11/4/2022.
//

#include "Box.h"
#include "tui/core.h"

#include <utility>

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
        LoggerPrinter("Widget") << "Widget "<< typeid(this).name() <<" draw begin\n";
        auto childCanvas = canvas.limitCoord(1,1);
        child->draw(childCanvas);
        const auto rightBorder = short(getCols()-1);
        const auto bottomBorder = short(getRows() - 1);
        for(short y = 1; y < getRows(); y++){
            canvas.line({0,y}, border::vLine);
            canvas.line({rightBorder,y}, border::vLine);
        }
        canvas.line({0,0},border::topLineWithCorner(getCols()));
        canvas.line({0,bottomBorder},border::bottomLineWithCorner(getCols()));
        LoggerPrinter("Widget") << "Widget "<< typeid(this).name() <<" draw end\n";
    }

    Box::Box(std::shared_ptr<Widget> child) : Container(std::move(child)) {
    }

} // tui