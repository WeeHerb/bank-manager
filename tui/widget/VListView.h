//
// Created by mslxl on 11/7/2022.
//

#pragma once

#include<vector>
#include<memory>

#include"Widget.h"

namespace tui {

    class VListView : public Widget {
    private:
        short cols;
        short rows;
        std::vector<std::shared_ptr<Widget>> children;
    public:
        VListView(std::initializer_list<std::shared_ptr<Widget>>);

        template<class ...T>
        explicit VListView(T ...children): cols(0), rows(0), children(std::initializer_list<std::shared_ptr<Widget>>({children...})) {

        }

        ~VListView() override = default;

        bool measure(std::pair<short, short> parentSize) override;

        [[nodiscard]] short getRows() const override;

        [[nodiscard]] short getCols() const override;

        void draw(Canvas &canvas) override;

        friend class HListView;
    };

} // tui
