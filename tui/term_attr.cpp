//
// Created by mslxl on 10/30/2022.
//

#include <iostream>


#include "tui/term_attr.h"
#include "tui/widget.h"

void tui::TermAttr::set_text_attr(const tui::color &c) const {
    SetConsoleTextAttribute(hwnd, c.code);
}

void tui::TermAttr::reset_text_attr() const {
    SetConsoleTextAttribute(hwnd, 0);
}

void tui::TermAttr::refresh_size() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void tui::TermAttr::clear(std::ostream& stream) {
    COORD top_left = {0, 0};
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(hwnd, &screen);
    FillConsoleOutputCharacterA(
            hwnd, ' ', screen.dwSize.X * screen.dwSize.Y, top_left, &written
    );
    FillConsoleOutputAttribute(
            hwnd, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | BACKGROUND_BLUE,
            screen.dwSize.X * screen.dwSize.Y, top_left, &written
    );
    SetConsoleCursorPosition(hwnd, top_left);
    draw_border(stream);
}

char tui::TermAttr::wait_key() {
    return char(_getch());
}

void tui::TermAttr::draw_border(std::ostream& stream) {
    SetConsoleCursorPosition(hwnd, {0,0});

    for(int x = 0; x < cols; x++){
        if(x == 0){
            stream << "┌";
        }else if(x == cols-1){
            stream << "┐";
        }else{
            stream << "─";
        }
    }

    for(short y = 1; y < rows - 1; y++){
        SetConsoleCursorPosition(hwnd, {0, y});
        stream << "│";
        SetConsoleCursorPosition(hwnd, {short(cols-1), y});
        stream << "│";
    }

    SetConsoleCursorPosition(hwnd, {cols, rows});
    for(int x = 0; x < cols; x++){
        if(x == 0){
            stream << "└";
        }else if(x == cols-1){
            stream << "┘";
        }else{
            stream << "─";
        }
    }
    SetConsoleCursorPosition(hwnd, {1, 1});
}

void tui::TermAttr::init(std::ostream &stream) {
    refresh_size();
    clear(stream);
}

void tui::TermAttr::proceed(tui::widget &widget, std::ostream& stream) {
    tui::panel panel(short(cols), short(rows), widget);
    panel.notify();
    panel.draw(stream, *this, Coop(1,1));
}

