//
// Created by mslxl on 11/7/2022.
//

#pragma once
#include "HCenter.h"

namespace tui {

    class VCenter:public HCenter {
    public:
        explicit VCenter(std::shared_ptr<Widget>);
        ~VCenter() override = default;

        bool measure(std::pair<short, short> parentSize) override;

        void draw(Canvas &canvas) override;
    };

} // tui
