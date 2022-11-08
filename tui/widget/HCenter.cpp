//
// Created by mslxl on 11/6/2022.
//

#include "HCenter.h"

#include <utility>

namespace tui {

    HCenter::HCenter(std::shared_ptr<Widget> child) : Container(std::move(child)), rows(0), cols(0) {

    }

    bool HCenter::measure(std::pair<short, short> parentSize) {
        if (parentSize.first <= 0 && parentSize.second <= 0) {
            if(!child->measure({0,0})){
                return false;
            }
            cols = child->getCols();
            rows = child->getRows();
            return false;
        }
        cols = parentSize.first;
        if (!child->measure({cols, parentSize.second})) {
            std::abort();
        }
        rows = child->getRows();
        return true;
    }

    short HCenter::getRows() const {
        return this->rows;
    }

    short HCenter::getCols() const {
        return this->cols;
    }

    void HCenter::draw(Canvas &canvas) {
        LoggerPrinter("Widget") << "Widget "<< typeid(this).name() <<" draw begin\n";
        short child_cols = child->getCols();
        auto x = short(getCols() / 2 - child_cols/2);
        if(x < 0) x = 0;
        auto childCanvas = canvas.limitCoord(x, 0);
        child->draw(childCanvas);
        LoggerPrinter("Widget") << "Widget "<< typeid(this).name() <<" draw end\n";
    }


} // tui