//
// Created by mslxl on 12/4/2022.
//

#pragma once

#include "Checkbox.h"
#include "BasicText.h"

namespace tui {

    template<typename T_ON, typename T_OFF>
    class Switch : public Checkbox {
    private:
        std::shared_ptr<BasicText<T_ON>> on;
        std::shared_ptr<BasicText<T_OFF>> off;
    public:

        explicit Switch(bool *checked, const T_ON &on,
                        const T_OFF &off) :
                Checkbox(checked), on(std::make_shared<BasicText<T_ON>>(on)),
                off(std::make_shared<BasicText<T_OFF>>(off)) {}


        [[nodiscard]] short getRows() const override {
            return std::max(on->getRows(), off->getRows());
        }

        [[nodiscard]] short getCols() const override {
            return short(on->getCols() + off->getCols() + 3);
        }


        bool measure(std::pair<short, short> parentSize) override {
            return on->measure(parentSize) && off->measure(parentSize);
        }

        void draw(Canvas &canvas) override {
            if (*checked) {
                canvas.line({0, 0}, "[");
                auto offset1 = canvas.limitCoord(1, 0);
                on->draw(offset1);
                offset1.line({on->getCols(), 0}, "]/");
                auto offset2 = offset1.limitCoord(short(on->getCols() + 2), 0);
                off->draw(offset2);
            } else {
                on->draw(canvas);
                canvas.line({on->getCols(), 0}, "/[");
                auto offset1 = canvas.limitCoord(short(on->getCols() + 2), 0);
                off->draw(offset1);
                offset1.line({short(off->getCols()), 0}, "]");
            }
            drawHoverBackground(canvas);
        }

        ~Switch() override = default;
    };

} // tui
