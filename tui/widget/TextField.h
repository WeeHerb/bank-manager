//
// Created by mslxl on 11/14/2022.
//

#pragma once
#include "Widget.h"


namespace tui {

    class TextField: public  Widget{
    private:
        std::vector<char> *text;
        short cols;
    public:
        TextField(std::vector<char> *content, short cols);

        bool measure(std::pair<short, short> parentSize) override;

        void draw(Canvas &canvas) override;

        bool acceptKey(int keyCode) override;

        [[nodiscard]] short getRows() const override;

        [[nodiscard]] short getCols() const override;

        ~TextField() override = default;
    };

} // tui
