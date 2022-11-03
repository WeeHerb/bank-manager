//
// Created by mslxl on 10/30/2022.
//


#pragma once

#include<ostream>
#include<memory>
#include<windows.h>
#include<conio.h>

#include "tui/color.h"

namespace tui {
    struct widget;

    class TermAttr{
    public:
        HANDLE hwnd;

        short rows;
        short cols;

        void refresh_size();

        explicit TermAttr(HANDLE handle) : hwnd(handle) {}

        void reset_text_attr() const;

        void set_text_attr(const color &c) const;

        void init(std::ostream &stream);

        void clear(std::ostream &stream);

        char wait_key();

        void proceed(std::shared_ptr<widget> widget,std::ostream& stream);


    private:
        void draw_border(std::ostream &stream);
    };
}