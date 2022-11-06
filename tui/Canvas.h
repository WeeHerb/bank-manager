//
// Created by mslxl on 11/4/2022.
//

#pragma once

#include<windows.h>
#include<ostream>

#include "Color.h"
#include "Coord.h"

namespace tui {
    class Canvas {
    private:
        HANDLE hwnd;

        Coord base;

        [[nodiscard]] Coord applyBase(const Coord &origin) const;
    public:
        explicit Canvas(HANDLE handle);

        /// Narrow coordination in a new canvas
        /// \param offsetX
        /// \param offsetY
        /// \return
        Canvas limitCoord(short offsetX, short offsetY);

        void fill(const Coord& coord, std::size_t size, char c);
        void fillAttr(const Coord& coord, std::size_t size, const tui::Color& attr);
        void line(const Coord& coord, const std::string_view & text);
        void character(const Coord& coord, char ch);
        void move(const Coord& coord);
    };
} // tui
