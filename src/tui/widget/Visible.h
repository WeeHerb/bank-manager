//
// Created by mslxl on 11/22/2022.
//


#pragma once
#include "Widget.h"
#include "Container.h"

namespace tui{
    class Visible : public Container {
    private:
        std::shared_ptr<bool> isVisible;
    public:
        Visible(bool visible, std::shared_ptr<Widget> child);
        Visible(std::shared_ptr<bool> visible, std::shared_ptr<Widget> child);

    private:
        bool measure(std::pair<short, short> parentSize) override;

        [[nodiscard]] short getRows() const override;

        [[nodiscard]] short getCols() const override;

        void draw(Canvas &canvas) override;
    };
}