//
// Created by mslxl on 11/4/2022.
//

#include "Text.h"
#include <cassert>

namespace tui {
    bool Text::measure(std::pair<short, short> parentSize) {
        int h = 0, w = 0;
        int curLineW = 0;
        for(const auto& ch: content){
            assert(ch != '\r' && ch != '\n'); //先判掉，一时半会没实现
            if(ch == '\r') continue;
            else if(ch == '\n'){
                w = std::max(w, curLineW);
                curLineW = 0;
                h++;
            }else{
                curLineW++;
            }
        }

        rows = short(h);
        cols = short(std::max(w, curLineW));

        return true;
    }

    short Text::getRows() const {
        return this->rows;
    }

    short Text::getCols() const {
        return this->cols;
    }

    void Text::draw(Canvas &canvas) {
        canvas.line({0,0}, content);
    }

    Text::Text(std::string text): content(std::move(text)), cols(0), rows(0) {

    }
} // tui