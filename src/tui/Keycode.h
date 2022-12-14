//
// Created by mslxl on 11/15/2022.
//

#pragma once
#include<array>

namespace tui {

    class Keycode {
    public:
        enum {
            ArrowUp,
            ArrowDown,
            ArrowLeft,
            ArrowRight,
            Enter,
            Alpha,
            Num,
            Symbol,
            Backspace,
            Tab,
            Undecided,
            Holding
        }type = Holding;

        std::array<int,3> data{0,0,0};
        short size=0;

        [[nodiscard]] inline int first() const ;
        [[nodiscard]] inline int second() const ;
        [[nodiscard]] inline int third() const ;

        void push(int v);

    private:
        void updateType() ;

    };

} // tui
