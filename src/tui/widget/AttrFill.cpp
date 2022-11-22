//
// Created by mslxl on 11/6/2022.
//

#include "AttrFill.h"

namespace tui {
    void AttrFill::draw(Canvas &canvas) {
        LoggerPrinter("Widget") << "Widget "<< typeid(this).name() <<" draw begin\n";
        const short size = child->getCols();
        const short line = child -> getRows();
        child->draw(canvas);
        for(short y = 0; y < line; y++){
            canvas.fillAttr({0,y}, size, attr);
        }
        LoggerPrinter("Widget") << "Widget "<< typeid(this).name() <<" draw end\n";
    }

    AttrFill::AttrFill(Color color, std::shared_ptr<Widget> child) : attr(color), Container(std::move(child)) {

    }
} // tui