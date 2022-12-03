//
// Created by mslxl on 12/2/2022.
//

#pragma once
#include "Container.h"

namespace tui {

    class Padding: public Container {
    private:
        short left,right,top,bottom;
    public:
        explicit Padding(const std::shared_ptr<Widget> &ptr, short left=1, short right=1, short top=1, short bottom=1);

        [[nodiscard]] short getRows() const override;

        [[nodiscard]] short getCols() const override;

        void draw(Canvas &canvas) override;

        ~Padding() override = default;
    };

} // tui
