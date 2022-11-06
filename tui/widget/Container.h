//
// Created by mslxl on 11/4/2022.
//

#pragma once

#include<memory>

#include "Widget.h"


namespace tui {
    class Container : public Widget{
    public:
        std::shared_ptr<Widget> child;

        explicit Container(std::shared_ptr<Widget>);

        bool measure(std::pair<short, short> parentSize) override;

        [[nodiscard]] short getRows() const override;

        [[nodiscard]] short getCols() const override;

        void draw(Canvas &canvas) override;

        ~Container() override = default;
    };
} // tui
