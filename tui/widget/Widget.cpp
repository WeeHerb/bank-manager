//
// Created by mslxl on 11/4/2022.
//

#include "Widget.h"
#include "../core.h"

namespace tui {
    void Widget::draw(Canvas &canvas) {
        stub();
    }

    short Widget::getRows() const {
        stub();
        return 0;
    }

    short Widget::getCols() const {
        stub();
        return 0;
    }

    bool Widget::measure(std::pair<short, short> parentSize) {
        stub();
        return true;
    }

    void Widget::setFocusOrder(FocusOrderIdx order) {
        focusOrder = order;
    }

    Widget::FocusOrderIdx Widget::getFocusOrder() const {
        return focusOrder;
    }

    bool Widget::isFocusable() const {
        return getFocusOrder() != -1;
    }

    void Widget::track(WidgetTracker &track) {

    }

    void Widget::hover() {
        hasFocus = true;
    }

    void Widget::unhover() {
        hasFocus = false;
    }

    bool Widget::acceptKey(int keyCode) {
        return false;
    }



} // tui