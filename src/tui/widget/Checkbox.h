//
// Created by mslxl on 12/3/2022.
//

#pragma once

#include "Widget.h"

namespace tui {

    class Checkbox :public Widget{
    protected:
        bool *checked;

        void drawHoverBackground(Canvas &canvas);
    public:
        explicit Checkbox(bool *checked);

        [[nodiscard]] short getRows() const override;

        [[nodiscard]] short getCols() const override;

        void draw(Canvas &canvas) override;

        bool acceptKey(Keycode keyCode) override;

        bool measure(std::pair<short, short> parentSize) override;

        ~Checkbox() override = default;

    };

} // tui
