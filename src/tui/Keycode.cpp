//
// Created by mslxl on 11/15/2022.
//

#include<cctype>
#include "Keycode.h"

namespace tui {
    int Keycode::first() const  {
        return data[0];
    }

    int Keycode::third() const  {
        return data[2];
    }

    int Keycode::second() const  {
        return data[1];
    }

    void Keycode::push(int v) {
        data[(size++) % 3] = v;
        updateType();
    }

    void Keycode::updateType()  {
        if (first() == 224) {
            if (size < 2) {
                type = Holding;
            } else
                switch (second()) {
                    case 72:
                        type = ArrowUp;
                        break;
                    case 80:
                        type = ArrowDown;
                        break;
                    case 75:
                        type = ArrowLeft;
                        break;
                    case 77:
                        type = ArrowRight;
                        break;
                    default:
                        type = Undecided;
                        break;
                }
        }else if(first() == 8){
            type = Backspace;
        } else if(first() == 9){
            type = Tab;
        } else if (std::isalpha(first())) {
            type = Alpha;
        } else if (std::isdigit(first())) {
            type = Num;
        } else if (first() == 13) {
            type = Enter;
        } else if (std::ispunct(first())) {
            type = Symbol;
        } else {
            type = Undecided;
        }
    }
} // tui