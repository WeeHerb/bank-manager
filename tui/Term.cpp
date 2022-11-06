//
// Created by mslxl on 11/4/2022.
//
#include <conio.h>

#include "Term.h"
#include "core.h"
#include<iostream>

namespace tui {
    void Term::updateSize() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hwnd, &csbi);
        cols = short(csbi.srWindow.Right - csbi.srWindow.Left + 1);
        rows = short(csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
    }

    Term::Term(HANDLE handle) : hwnd(handle), rows(0), cols(0) {
        updateSize();
    }

    void Term::invalidate() {
        updateSize();

        draw();
    }

    void Term::push(std::shared_ptr<tui::Widget> content) {
        contents.emplace(std::move(content));
    }

    void Term::pop() {
        contents.pop();
    }

    void Term::draw() {
        auto content = contents.top();
        Canvas canvas = Canvas(hwnd).limitCoord(1, 1);
        drawBG();
        content->measure({cols - 1, rows - 1});
        content->draw(canvas);
    }

    void Term::drawBG() const {
        static const auto attr = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | BACKGROUND_BLUE;
        DWORD written;
        SetConsoleTextAttribute(hwnd, attr);
        FillConsoleOutputCharacterA(hwnd, ' ', rows * cols, {0, 0}, &written);
        FillConsoleOutputAttribute(hwnd, attr, rows * cols, {0, 0}, &written);
        SetConsoleCursorPosition(hwnd, {0, 0});


        WriteConsole(hwnd, border::leftTop.data(), border::leftTop.size(), nullptr, nullptr);
        for (int i = 0; i < cols - 2; i++)
            WriteConsole(hwnd, border::hLine.data(), border::hLine.size(), nullptr, nullptr);
        WriteConsole(hwnd, border::rightTop.data(), border::rightTop.size(), nullptr, nullptr);

        for (short y = 1; y < rows - 1; y++) {
            SetConsoleCursorPosition(hwnd, {0, y});
            WriteConsole(hwnd, border::vLine.data(), border::vLine.size(), nullptr, nullptr);
            SetConsoleCursorPosition(hwnd, {short(cols - 1), y});
            WriteConsole(hwnd, border::vLine.data(), border::vLine.size(), nullptr, nullptr);
        }

        SetConsoleCursorPosition(hwnd, {0, short(rows - 1)});
        WriteConsole(hwnd, border::leftBottom.data(), border::leftBottom.size(), nullptr, nullptr);
        for (int i = 0; i < cols - 2; i++)
            WriteConsole(hwnd, border::hLine.data(), border::hLine.size(), nullptr, nullptr);
        WriteConsole(hwnd, border::rightBottom.data(), border::rightBottom.size(), nullptr, nullptr);
        SetConsoleCursorPosition(hwnd, {1, 1});
    }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"
    void Term::waitKey() {
        _getch();
    }
#pragma clang diagnostic pop

} // tui