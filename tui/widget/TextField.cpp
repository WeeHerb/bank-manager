//
// Created by mslxl on 11/14/2022.
//

#include "TextField.h"

namespace tui {
    bool TextField::measure(std::pair<short, short> parentSize) {
        return true;
    }

    void TextField::draw(Canvas &canvas) {
        if(text->size() < cols){
            canvas.fill({short(std::max(text->size()-2, 0ull)), 0}, cols-text->size()+1, ' ');
        }
        if (text->size() < cols) {
            canvas.line({0, 0}, text->data());
        } else {
            canvas.line({0, 0}, text->data() + (text->size() - cols));
        }

        if (hasFocus) {
            canvas.fillAttr({0, 0}, getCols(),
                            color::BG_COMMON | color::BG_INTENSITY | color::FG_COMMON | color::FG_INTENSITY);
        } else {
            canvas.fillAttr({0, 0}, getCols(),
                            color::BG_COMMON | color::FG_COMMON);
        }
    }

    bool TextField::acceptKey(Keycode keyCode) {
        if (keyCode.type == Keycode::Backspace && text->size() >= 2) {
            LoggerPrinter("TextField") << "Erase key\n";
            text->erase(text->end()-2);
        } else {
            LoggerPrinter("TextField") << "Insert char " << char(keyCode.first()) << "(" << keyCode.first() << ")"
                                       << "\n";
            text->insert(text->end() - 1, char(keyCode.first()));
        }
        return true;
    }

    short TextField::getRows() const {
        return 1;
    }

    short TextField::getCols() const {
        return cols;
    }

    TextField::TextField(std::vector<char> *content, short cols) : text(content), cols(cols) {
        text->clear();
        text->push_back('\0');
    }
} // tui