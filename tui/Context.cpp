//
// Created by mslxl on 11/9/2022.
//

#include "Context.h"
#include "logger/logger.h"

void tui::Context::trackFocus(std::shared_ptr<Widget> &widget) {
    if (widget->isFocusable()) {
        LoggerPrinter("Context") << "Track focus " << typeid(*widget).name() << "\n";
        this->widgets.push_back(std::weak_ptr(widget));
    }
}

void tui::Context::collect(std::shared_ptr<Widget> &widget) {
    this->widgets.clear();
    this->widgetIdx.clear();

    auto collector = [this](std::shared_ptr<Widget> &w) {
        this->trackFocus(w);
    };
    auto func = std::function(collector);
    widget->track(func);
    std::sort(this->widgets.begin(), this->widgets.end(),
              [](const std::weak_ptr<Widget> &lhs, const std::weak_ptr<Widget> &rhs) {
                  return lhs.lock()->getFocusOrder() < rhs.lock()->getFocusOrder();
              });
    std::transform(this->widgets.begin(), this->widgets.end(), std::back_inserter(this->widgetIdx),
                   [](const std::weak_ptr<Widget> &item) {
                       return item.lock()->getFocusOrder();
                   });
}

void tui::Context::hoverNext() {
    auto focusing = getHoverPtr();
    if(focusing.has_value()){
        focusing.value()->unhover();
    }

    auto iter = std::lower_bound(this->widgetIdx.begin(), this->widgetIdx.end(), focusOn+1);
    if(iter == this->widgetIdx.end()) return;


    std::size_t idx = iter - this->widgetIdx.begin();
    focusOn = idx;

    auto widget = this->widgets[idx].lock();
    LoggerPrinter("Context") << "focus on " << idx << "(focus order " << *iter << ") " << typeid(widget.get()).name() << "\n";
    widget->hover();
}

void tui::Context::hoverPrev() {
    auto focusing = getHoverPtr();
    if(focusing.has_value()){
        focusing.value()->unhover();
    }


    auto iter = std::lower_bound(this->widgetIdx.begin(), this->widgetIdx.end(), focusOn-1);
    if(iter == this->widgetIdx.end()) return;
    focusOn--;

    std::size_t idx = iter - this->widgetIdx.begin();
    focusOn = idx;

    auto widget = this->widgets[idx].lock();
    LoggerPrinter("Context") << "focus on " << idx << "(focus order " << *iter << ") " << typeid(widget.get()).name() << "\n";
    widget->hover();
}

std::optional<std::shared_ptr<tui::Widget>> tui::Context::getHoverPtr() {
    auto iter = std::lower_bound(this->widgetIdx.begin(), this->widgetIdx.end(), focusOn);
    if(iter == this->widgetIdx.end()) return std::nullopt;

    std::size_t idx = iter - this->widgetIdx.begin();
    auto widget = this->widgets[idx].lock();
    return std::make_optional(widget);
}


