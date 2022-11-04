//
// Created by mslxl on 11/4/2022.
//

#pragma once
#include "Widget.h"

namespace tui {

    class Text : public Widget{
    private:
        short cols;
        short rows;
    public:
        std::string content;
        explicit Text(std::string);
        bool measure(std::pair<short, short> parentSize) override;

        [[nodiscard]] short getRows() const override;

        [[nodiscard]] short getCols() const override;

        void draw(Canvas &canvas) override;

    };

} // tui
