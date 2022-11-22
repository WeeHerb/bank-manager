//
// Created by mslxl on 11/4/2022.
//

#pragma once

#include <functional>
#include <memory>

#include "tui/Canvas.h"
#include "tui/Context.h"
#include "tui/Keycode.h"
#include "logger/logger.h"

namespace tui {

    class Widget;

    using WidgetTracker = std::function<void(std::shared_ptr<Widget>&)>;

    class Widget {
    public:
        using FocusOrderIdx = char;
    private:
        FocusOrderIdx focusOrder = -1;

    public:
        bool hasFocus = false;
        /// Measure this widget by its parent
        /// Return false if it need second measure
        /// Usually, only `match_parent` need second measure, other layout like `wrap_content` can give correct information without parent size
        /// \param parentSize (cols, rows)
        /// \return Needn't second measure
        virtual bool measure(std::pair<short, short> parentSize);

        [[nodiscard]] virtual short getRows() const;

        [[nodiscard]] virtual short getCols() const;

        virtual void draw(tui::Canvas &canvas);

        virtual void track(WidgetTracker&);

        void setFocusOrder(FocusOrderIdx order);

        [[nodiscard]] FocusOrderIdx getFocusOrder() const;

        [[nodiscard]] bool isFocusable() const;

        virtual void hover();
        virtual void unhover();

        /// Accept a key code, return true if it can process it successfully
        /// \param keyCode
        /// \return
        virtual bool acceptKey(Keycode keyCode);


        virtual ~Widget() = default;
    };

#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-reserved-identifier"
    template<typename T,typename... _Args>
    inline  std::shared_ptr<T> ui(_Args&&... args){
        return std::make_shared<T>(args...);
    }

    template<typename T,typename... _Args>
    inline std::shared_ptr<T> ui_args(std::function<void(T&)> init, _Args&&... args){
        auto value = std::make_shared<T>(args...);
        init(*value);
        return value;
    }
#pragma clang diagnostic pop

} // tui
