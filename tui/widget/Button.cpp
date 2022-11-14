//
// Created by mslxl on 11/8/2022.
//

#include "Button.h"

#include <utility>

namespace tui {
    Button::Button(std::shared_ptr<Widget> child) : Container(child) {

    }

    void Button::click() {
        action();
    }

    void Button::setActionListener(std::function<void()> listener) {
        action = std::move(listener);
    }

    void Button::draw(Canvas &canvas) {
        const short size = child->getCols();
        const short line = child->getRows();
        child->draw(canvas);
        if (this->hasFocus) {
            for (short y = 0; y < line; y++) {
                canvas.fillAttr({0, y}, size,
                                color::BG_COMMON | color::BG_INTENSITY | color::FG_COMMON | color::FG_INTENSITY);
            }
        } else {
            for (short y = 0; y < line; y++) {
                canvas.fillAttr({0, y}, size, color::BG_COMMON | color::FG_COMMON);
            }
        }

    }

} // tui