//
// Created by mslxl on 11/7/2022.
//

#include "VCenter.h"

#include <utility>

namespace tui {
    VCenter::VCenter(std::shared_ptr<Widget> child) : HCenter(std::move(child)) {

    }

    bool VCenter::measure(std::pair<short, short> parentSize) {
        if (parentSize.first <= 0 && parentSize.second <= 0) {
            if(!child->measure({0,0})){
                return false;
            }
            rows = child->getRows();
            cols = child->getCols();
            return false;
        }
        rows = parentSize.second;
        if (!child->measure({parentSize.first, rows})) {
            std::abort();
        }
        cols = child->getCols();
        return true;
    }

    void VCenter::draw(Canvas &canvas) {
        LoggerPrinter("Widget") << "Widget "<< typeid(this).name() <<" draw begin\n";
        short child_rows = child->getRows();
        auto y = short(getRows() / 2 - child_rows / 2);
        if(y < 0) y = 0;
        auto childCanvas = canvas.limitCoord(0,y);
        child->draw(childCanvas);
        LoggerPrinter("Widget") << "Widget "<< typeid(this).name() <<" draw end\n";
    }
} // tui