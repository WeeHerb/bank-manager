//
// Created by mslxl on 11/4/2022.
//

#pragma once
#include<windows.h>
#include<stack>
#include<memory>

#include "widget/Widget.h"

namespace tui {
    class Term {
    private:
        std::stack<std::shared_ptr<tui::Widget>> contents;

        void updateSize();
        void drawBG() const;
    public:
        HANDLE hwnd;
        short rows;
        short cols;

        void push(std::shared_ptr<tui::Widget> content);
        void pop();

        void draw();

        void invalidate();

        explicit Term(HANDLE hwnd);
    };
} // tui
