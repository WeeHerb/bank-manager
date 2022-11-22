//
// Created by mslxl on 11/4/2022.
//

#pragma once
#include "Container.h"

namespace tui {
    class Box: public Container {
    public:
        bool measure(std::pair<short, short> parentSize) override;

        [[nodiscard]] short getRows() const override;

        [[nodiscard]] short getCols() const override;

        void draw(Canvas &canvas) override;

        explicit Box(std::shared_ptr<Widget>);
        ~Box() override = default;
    };
} // tui
