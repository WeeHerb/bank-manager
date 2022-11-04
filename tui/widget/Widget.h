//
// Created by mslxl on 11/4/2022.
//

#pragma once
#include "../Canvas.h"

namespace tui {
    class Widget {
    public:
        using FocusOrderIdx = char;
    private:
        FocusOrderIdx focusOrder = 0;
    public:
        /// Measure this widget by its parent
        /// Return false if it need second measure
        /// Usually, only `match_parent` need second measure, other layout like `wrap_content` can give correct information without parent size
        /// \param parentSize
        /// \return Needn't second measure
        virtual bool measure(std::pair<short,short> parentSize);

        [[nodiscard]] virtual short getRows() const;
        [[nodiscard]] virtual short getCols() const;

        virtual void draw(tui::Canvas& canvas);

        void setFocusOrder(FocusOrderIdx order);
        [[nodiscard]] FocusOrderIdx getFocusOrder() const;

        [[nodiscard]] bool isFocusable() const;
    };
} // tui
