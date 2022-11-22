//
// Created by mslxl on 11/6/2022.
//

#pragma once
#include "Container.h"
namespace tui {
    class HCenter: public Container {
    private:
        short rows;
        short cols;
    public:
        explicit HCenter(std::shared_ptr<Widget>);
        bool measure(std::pair<short, short> parentSize) override;

        [[nodiscard]] short getRows() const override;

        [[nodiscard]] short getCols() const override;

        void draw(Canvas &canvas) override;

        ~HCenter() override = default;

        friend class VCenter;
    };
} // tui
