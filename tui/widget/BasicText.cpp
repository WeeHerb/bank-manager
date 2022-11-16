//
// Created by mslxl on 11/16/2022.
//
#include "BasicText.h"

namespace tui{
    template<>
    short BasicText<std::wstring>::getCols() const {
        return short(this->cols * 2);
    }

    template<>
    void BasicText<std::wstring>::draw(Canvas &canvas) {
        LoggerPrinter("Widget") << "Widget "<< typeid(this).name() <<" draw begin\n";
        canvas.lineW({0,0}, content);
        LoggerPrinter("Widget") << "Widget "<< typeid(this).name() <<" draw end\n";
    }

};
