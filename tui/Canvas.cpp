//
// Created by mslxl on 11/4/2022.
//

#include "Canvas.h"

namespace tui {
    Canvas::Canvas(HANDLE handle) : hwnd(handle), base(0, 0) {
        SetConsoleOutputCP(CP_UTF8);
    }

    Canvas Canvas::limitCoord(short offsetX, short offsetY) {
        auto newCanvas = Canvas(hwnd);
        newCanvas.base = base.narrowX(offsetX).narrowY(offsetY);
        return newCanvas;
    }

    void Canvas::fill(const Coord &coord, std::size_t size, char c) {
        FillConsoleOutputCharacter(hwnd, c, size, applyBase(coord).unwrap(), nullptr);
    }

    void Canvas::line(const Coord &coord, const std::string &text) {
        move(applyBase(coord));
        WriteConsole(hwnd, text.c_str(), text.size(), nullptr, nullptr);
    }

    void Canvas::fillAttr(const Coord &coord, std::size_t size, const Color &attr) {
        FillConsoleOutputAttribute(hwnd, attr.code, size, applyBase(coord).unwrap(), nullptr);
    }

    void Canvas::character(const Coord &coord, char ch) {
        move(applyBase(coord));
        WriteConsole(hwnd, &ch, 1, nullptr, nullptr);
    }

    void Canvas::move(const Coord &coord) {
        SetConsoleCursorPosition(hwnd, applyBase(coord).unwrap());
    }

    Coord Canvas::applyBase(const Coord &origin) const {
        return {short(base.x + origin.x), short(base.y + origin.y)};
    }

} // tui