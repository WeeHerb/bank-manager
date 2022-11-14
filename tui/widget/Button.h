//
// Created by mslxl on 11/8/2022.
//

#pragma once

#include<functional>
#include "Container.h"

namespace tui {
    class Button : public Container{
    private:
        std::function<void()> action;
    public:
        explicit Button(std::shared_ptr<Widget>);
        ~Button() override = default;

        void click();
        void setActionListener(std::function<void()>);

        void draw(Canvas &canvas) override;
    };

} // tui
