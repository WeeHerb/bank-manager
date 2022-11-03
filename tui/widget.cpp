//
// Created by mslxl on 10/30/2022.
//

#include <utility>

#include "tui/widget.h"

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
    child->notify();
}

int tui::center::get_rows() {
    return parent->get_rows();
}

int tui::center::get_cols() {
    return parent->get_cols();
}

void tui::center::draw(std::ostream &ostream, const TermAttr &attr, const tui::Coop &coop) {
    int child_width = child->get_cols();
    int child_height = child->get_rows();
    int start_x = get_cols() / 2 - child_width / 2;
    int start_y = get_rows() / 2 - child_height / 2;
    child->draw(ostream, attr, Coop(start_x, start_y));
}

tui::center::center(std::shared_ptr<tui::widget> cp) : child(std::move(cp)) {
    child->parent = this;
}


void tui::box::notify() {
    child->notify();
    rows = child->get_rows() + 2;
    cols = child->get_cols() + 2;
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
    child->draw(stream, attr, Coop(coop.x + 1, coop.y + 1));
}

tui::box::box(std::shared_ptr<tui::widget> cp) : child(std::move(cp)) {
    child->parent = this;
}

tui::text::text(std::string content) : content(std::move(content)) {
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

tui::panel::panel(short w, short h, std::shared_ptr<widget> ww) : cols(w), rows(h), child(std::move(ww)) {
    child->parent = this;
}

void tui::panel::notify() {
    child->notify();
}

int tui::panel::get_rows() {
    return rows;
}

int tui::panel::get_cols() {
    return cols;
}

void tui::panel::draw(std::ostream &ostream, const tui::TermAttr &attr, const tui::Coop &coop) {
    child->draw(ostream, attr, coop);
}

void tui::attr::notify() {
    return child->notify();
}

int tui::attr::get_rows() {
    return child->get_rows();
}

int tui::attr::get_cols() {
    return child->get_cols();
}

void tui::attr::draw(std::ostream &ostream, const tui::TermAttr &attr, const tui::Coop &coop) {

    attr.set_text_attr(this->c);
    child->draw(ostream, attr, coop);
    attr.set_text_attr(tui::FG_COMMON | tui::BG_COMMON);
}

tui::attr::attr(tui::color color, std::shared_ptr<widget> cp) : c(color), child(std::move(cp)) {

}

void tui::bg::notify() {
    child->notify();
}

int tui::bg::get_rows() {
    return child->get_rows();
}

int tui::bg::get_cols() {
    return child->get_cols();
}

void tui::bg::draw(std::ostream &ostream, const tui::TermAttr &attr, const tui::Coop &coop) {
    DWORD written;
    for (int y = 0; y < this->get_rows(); y++) {
        COORD bg_coop = {short(coop.x), short(coop.y + y)};
        FillConsoleOutputAttribute(
                attr.hwnd, this->c.code,
                this->get_cols(), bg_coop, &written
        );
    }

    child->draw(ostream, attr, coop);
}

tui::bg::bg(tui::color color, std::shared_ptr<widget> cp) : c(color), child(std::move(cp)) {

}
