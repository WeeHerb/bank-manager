//
// Created by mslxl on 11/22/2022.
//

#include "Visible.h"

#include <utility>

bool tui::Visible::measure(std::pair<short, short> parentSize) {
    if(*isVisible){
        return Container::measure(parentSize);
    }else{
        return true;
    }

}

void tui::Visible::draw(tui::Canvas &canvas) {
    if(*isVisible){
        Container::draw(canvas);
    }
}

tui::Visible::Visible(bool visible, std::shared_ptr<Widget> child) : Container(std::move(child)),
                                                                     isVisible(std::make_shared<bool>(visible)) {

}

tui::Visible::Visible(std::shared_ptr<bool> visible, std::shared_ptr<Widget> child) : Container(std::move(child)),
                                                                                      isVisible(std::move(visible)) {

}

short tui::Visible::getRows() const {
    if(*isVisible) return Container::getRows();
    else return 0;
}

short tui::Visible::getCols() const {
    if(*isVisible) return Container::getCols();
    else return 0;
}
