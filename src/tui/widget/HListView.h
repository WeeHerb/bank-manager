//
// Created by mslxl on 11/7/2022.
//

#pragma once
#include "VListView.h"

namespace tui {

    class HListView :public VListView{
    public:
        HListView(std::initializer_list<std::shared_ptr<Widget>>);

        template<class ...T>
        explicit HListView(T ...children): VListView(std::initializer_list<std::shared_ptr<Widget>>({children...})) {

        }

        ~HListView() override = default;

        bool measure(std::pair<short, short> parentSize) override;

        void draw(Canvas &canvas) override;

        void rebuild() override;
    };

} // tui
