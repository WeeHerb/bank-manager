//
// Created by mslxl on 11/4/2022.
//

#include "Term.h"

namespace tui {
    void Term::updateSize() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hwnd, &csbi);
        cols = short(csbi.srWindow.Right - csbi.srWindow.Left + 1);
        rows = short(csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
    }

    Term::Term(HANDLE handle):hwnd(handle), rows(0), cols(0){
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
        Canvas canvas(hwnd);
        drawBG();
        content->measure({rows, cols});
        content->draw(canvas);
    }

    void Term::drawBG() const {
        static const auto attr = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | BACKGROUND_BLUE;
        DWORD written;
        SetConsoleTextAttribute(hwnd, attr);
        FillConsoleOutputCharacterA(hwnd, ' ', rows * cols, {0,0}, &written);
        FillConsoleOutputAttribute(hwnd, attr, rows * cols, {0,0}, &written);
        SetConsoleCursorPosition(hwnd, {0,0});

    }

} // tui