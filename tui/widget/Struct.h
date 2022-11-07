//
// Created by mslxl on 11/7/2022.
//

#pragma once
#include "Widget.h"

namespace tui {

    class Struct: public Widget {
    private:
        short rows;
        short cols;
    public:
        Struct(short rows, short cols);
        ~Struct() override = default;

        bool measure(std::pair<short, short> parentSize) override;

        [[nodiscard]] short getRows() const override;

        [[nodiscard]] short getCols() const override;

        void draw(Canvas &canvas) override;
    };

} // tui
