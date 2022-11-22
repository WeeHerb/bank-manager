//
// Created by mslxl on 11/4/2022.
//

#include "Canvas.h"

#include "logger/logger.h"

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
        DWORD out;
        FillConsoleOutputCharacter(hwnd, c, size, applyBase(coord).unwrap(), &out);
    }

    void Canvas::line(const Coord &coord, const std::string_view &text) {
        move(applyBase(coord));
        LoggerPrinter("Canvas") << "print text " << text << "\n";
        WriteConsole(hwnd, text.data(), text.size(), nullptr, nullptr);
    }
    void Canvas::lineW(const Coord &coord, const std::wstring_view &text) {
        move(applyBase(coord));
        LoggerPrinter("Canvas") << "print wide text len " << text.length() << "\n";
        WriteConsoleW(hwnd, text.data(), text.size(), nullptr, nullptr);
    }

    void Canvas::fillAttr(const Coord &coord, std::size_t size, const Color &attr) {
        LoggerPrinter("Canvas") << "cover canvas attr " << applyBase(coord) << " len " << size<< " with " << attr.code << "\n";
        DWORD out;
        FillConsoleOutputAttribute(hwnd, attr.code, size, applyBase(coord).unwrap(), &out);
    }

    void Canvas::character(const Coord &coord, char ch) {
        auto absCoord = applyBase(coord);
        move(absCoord);
        LoggerPrinter("Canvas") << "print char " << ch <<"\n";
        WriteConsole(hwnd, &ch, 1, nullptr, nullptr);
    }

    void Canvas::move(const Coord &coord) {
        LoggerPrinter("Canvas") << "move to " << coord << "\n";
        SetConsoleCursorPosition(hwnd, coord.unwrap());
    }

    Coord Canvas::applyBase(const Coord &origin) const {
        return {short(base.x + origin.x), short(base.y + origin.y)};
    }

} // tui