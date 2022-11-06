//
// Created by mslxl on 11/4/2022.
//

#pragma once
#include <cassert>
#include "Widget.h"

namespace tui {

    template<class T>
    class BasicText : public Widget{
    private:
        short cols;
        short rows;
    public:
        T content;
        explicit BasicText(T);
        bool measure(std::pair<short, short> parentSize) override;

        [[nodiscard]] short getRows() const override;

        [[nodiscard]] short getCols() const override;

        void draw(Canvas &canvas) override;

    };

    using Text = BasicText<std::string>;
    using WText = BasicText<std::wstring>;

    template<class T>
    bool BasicText<T>::measure(std::pair<short, short> parentSize) {
        int h = 1, w = 0;
        int curLineW = 0;
        for(const auto& ch: content){
            assert(ch != '\r' && ch != '\n'); //先判掉，一时半会没实现
            if(ch == '\r') continue;
            else if(ch == '\n'){
                w = std::max(w, curLineW);
                curLineW = 0;
                h++;
            }else{
                curLineW++;
            }
        }

        rows = short(h);
        cols = short(std::max(w, curLineW));

        return true;
    }

    template<class T>
    short BasicText<T>::getRows() const {
        return this->rows;
    }
    template<class T>
    short BasicText<T>::getCols() const {
        return this->cols;
    }
    template<>
    short BasicText<std::wstring>::getCols() const {
        return short(this->cols * 2);
    }
    template<class T>
    void BasicText<T>::draw(Canvas &canvas) {
        canvas.line({0,0}, content);
    }

    template<>
    void BasicText<std::wstring>::draw(Canvas &canvas) {
        canvas.lineW({0,0}, content);
    }

    template<class T>
    BasicText<T>::BasicText(T text): content(std::move(text)), cols(0), rows(0) {
    }
} // tui
