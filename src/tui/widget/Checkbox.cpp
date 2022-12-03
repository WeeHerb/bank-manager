//
// Created by mslxl on 12/3/2022.
//

#include "Checkbox.h"

namespace tui {

    Checkbox::Checkbox(bool *checked) : checked(checked) {}

    short Checkbox::getRows() const {
        return 1;
    }

    short Checkbox::getCols() const {
        return 3;
    }

    void Checkbox::draw(Canvas &canvas) {
        if (*checked) {
            canvas.line({0, 0}, "[ ]");
        } else {
            canvas.line({0, 0}, "[*]");
        }
        drawHoverBackground(canvas);
    }

    bool Checkbox::acceptKey(Keycode keyCode) {
        if (keyCode.type == Keycode::Enter) {
            *checked = !*checked;
            return true;
        }
        return false;
    }

    bool Checkbox::measure(std::pair<short, short> parentSize) {
        return true;
    }

    void Checkbox::drawHoverBackground(Canvas &canvas) {
        if (this->hasFocus) {
            canvas.fillAttr({0, 0}, getCols(),
                            color::BG_COMMON | color::BG_INTENSITY | color::FG_COMMON | color::FG_INTENSITY);
        } else {
            canvas.fillAttr({0, 0}, getCols(), color::BG_COMMON | color::FG_COMMON);
        }
    }

} // tui