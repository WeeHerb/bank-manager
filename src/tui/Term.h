//
// Created by mslxl on 11/4/2022.
//

#pragma once
#include<windows.h>
#include<stack>
#include<memory>

#include "Context.h"
#include "tui/widget/Widget.h"

namespace tui {
    class Term {
    private:
        std::stack<ContentLayer> contents;
        bool needDrawAll;

        void updateSize();
        void drawBG() const;
        void draw();
        void refreshHover();

    public:
        bool border;
        HANDLE hwnd;
        short rows;
        short cols;

        void push(std::shared_ptr<tui::Widget> content);
        void pop();

        void capture();

        void invalidate();

        void rebuild();

        int waitKey();

        explicit Term(HANDLE hwnd);
    };
} // tui
