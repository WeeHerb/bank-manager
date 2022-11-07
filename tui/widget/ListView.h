//
// Created by mslxl on 11/7/2022.
//

#pragma once

#include<vector>
#include<memory>

#include"Widget.h"

namespace tui {

    class ListView : public Widget{
    private:
        short cols;
        short rows;
        std::vector<std::shared_ptr<Widget>> children;
    public:
        ListView(std::initializer_list<std::shared_ptr<Widget>>);

        ~ListView() override = default;

        bool measure(std::pair<short, short> parentSize) override;

        [[nodiscard]] short getRows() const override;

        [[nodiscard]] short getCols() const override;

        void draw(Canvas &canvas) override;
    };

} // tui
