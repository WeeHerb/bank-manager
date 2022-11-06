//
// Created by mslxl on 11/6/2022.
//

#pragma once
#include "Container.h"
#include "../Color.h"

namespace tui {

    class AttrFill : public Container{
    private:
        Color attr;
    public:
        AttrFill(Color,std::shared_ptr<Widget>);
        void draw(Canvas &canvas) override;
        ~AttrFill() override = default;
    };

} // tui
