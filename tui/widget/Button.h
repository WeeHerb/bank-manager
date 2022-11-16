//
// Created by mslxl on 11/8/2022.
//

#pragma once

#include<functional>
#include<optional>

#include "Container.h"

namespace tui {
    class Button : public Container{
    private:
        std::optional<std::function<void()>> action;

        void preform();
    public:
        explicit Button(std::shared_ptr<Widget>);
        ~Button() override = default;

        void setActionListener(std::function<void()>);

        void draw(Canvas &canvas) override;

        bool acceptKey(Keycode keyCode) override;
    };

} // tui
