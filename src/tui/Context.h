//
// Created by mslxl on 11/9/2022.
//

#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <optional>

#include "tui/widget/Widget.h"

namespace tui {
    struct Widget;

    class Context {
    public:
        /// 该上下文对应的 [Term.contents] 中的索引
        std::size_t contentLayer = 0;
        /// 当前焦点，如果对应的位置没有 Widget 则为选中（屎山迭代）
        std::size_t focusOn = 0;

        /// 具备可选中属性的所有 Widget 集合
        std::vector<std::weak_ptr<Widget>> widgets{};
        std::vector<int> widgetIdx{};

        void trackFocus(std::shared_ptr<Widget> &);

        void collect(std::shared_ptr<Widget> &);

        void hoverNext();

        void hoverPrev();

        std::optional<std::shared_ptr<Widget>> getHoverPtr();

    };

    struct ContentLayer {
        std::shared_ptr<Widget> widget;
        Context context;
    };
}
