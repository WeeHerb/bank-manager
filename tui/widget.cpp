//
// Created by mslxl on 10/30/2022.
//

#include <utility>

#include "tui/widget.h"
#include "tui/core.h"


void tui::widget::notify() {
    stub();
}

int tui::widget::get_rows() {
    stub();
    return -1;
}

int tui::widget::get_cols() {
    stub();
    return -1;
}

void tui::widget::draw(std::ostream &, const TermAttr &attr, const tui::Coop &coop) {
    stub();
}


// Impl below

void tui::center::notify() {
    child.notify();
}

int tui::center::get_rows() {
    return parent->get_rows();
}

int tui::center::get_cols() {
    return parent->get_cols();
}

void tui::center::draw(std::ostream &ostream, const TermAttr &attr, const tui::Coop &coop) {
    int child_width = child.get_cols();
    int child_height = child.get_rows();
    int start_x = get_cols() / 2 - child_width / 2;
    int start_y = get_rows() / 2 - child_height / 2;
    child.draw(ostream, attr, Coop(start_x, start_y));
}


void tui::box::notify() {
    child.notify();
    rows = child.get_rows() + 2;
    cols = child.get_cols() + 2;
}

int tui::box::get_rows() {
    return rows;
}

int tui::box::get_cols() {
    return cols;
}

void tui::box::draw(std::ostream &stream, const TermAttr &attr, const tui::Coop &coop) {
    SetConsoleCursorPosition(attr.hwnd, {short(coop.x), short(coop.y)});
    for (int x = 0; x < cols; x++) {
        if (x == 0) {
            stream << "┌";
        } else if (x == cols - 1) {
            stream << "┐";
        } else {
            stream << "─";
        }
    }

    for (short y = 1; y < rows - 1; y++) {
        SetConsoleCursorPosition(attr.hwnd, {short(coop.x), short(coop.y + y)});
        stream << "│";
        SetConsoleCursorPosition(attr.hwnd, {short(coop.x + get_cols() - 1), short(coop.y + y)});
        stream << "│";
    }

    SetConsoleCursorPosition(attr.hwnd, {short(coop.x), short(coop.y + get_rows() - 1)});

    for (int x = 0; x < cols; x++) {
        if (x == 0) {
            stream << "└";
        } else if (x == cols - 1) {
            stream << "┘";
        } else {
            stream << "─";
        }
    }
    child.draw(stream, attr, Coop(coop.x + 1, coop.y + 1));
}

tui::text::text(std::string content) : content(std::move(content)) {
    notify();
}

void tui::text::notify() {
    short width = 0;
    short height = 1;

    short width_cnt = 0;
    for (const auto &c: content) {
        width_cnt++;
        if (c == '\n') {
            width = std::max(width, width_cnt);
            height++;
            width_cnt = 0;
        }
    }
    width = std::max(width, width_cnt);
    rows = height;
    cols = width;
}

int tui::text::get_rows() {
    return rows;
}

int tui::text::get_cols() {
    return cols;
}

void tui::text::draw(std::ostream &ostream, const tui::TermAttr &attr, const tui::Coop &coop) {
    SetConsoleCursorPosition(attr.hwnd, {short(coop.x), short(coop.y)});
    int height_offset = 0;
    for (const char &c: content) {
        if (c == '\r') continue;
        if (c == '\n') {
            height_offset++;
            SetConsoleCursorPosition(attr.hwnd, {short(coop.x), short(coop.y + height_offset)});
            continue;
        }
        ostream << c;
    }
}

tui::panel::panel(short w, short h, widget &ww) : cols(w), rows(h), child(ww) {
    child.parent = this;
}

void tui::panel::notify() {
    child.notify();
}

int tui::panel::get_rows() {
    return rows;
}

int tui::panel::get_cols() {
    return cols;
}

void tui::panel::draw(std::ostream &ostream, const tui::TermAttr &attr, const tui::Coop &coop) {
    child.draw(ostream, attr, coop);
}
