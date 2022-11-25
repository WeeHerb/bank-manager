//
// Created by mslxl on 11/25/2022.
//


#pragma once

#include "Button.h"
#include "BasicText.h"

namespace tui {
    template<typename T>
    class BasicTextButton : public Button {
    public:
        explicit BasicTextButton(T text) : Button(ui<BasicText<T>> (text)) {}

        explicit BasicTextButton(std::shared_ptr<T> text) : Button(ui<BasicText<T>>(text)) {}

        ~BasicTextButton() override = default;
    };

    using TextButton = BasicTextButton<std::string>;
    using WTextButton = BasicTextButton<std::wstring>;
}
