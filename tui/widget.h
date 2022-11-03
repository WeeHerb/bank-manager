//
// Created by mslxl on 10/30/2022.
//


#pragma once

#include <ostream>
#include <memory>
#include <utility>
#include <vector>

#include "tui/color.h"
#include "tui/core.h"
#include "tui/term_attr.h"

namespace tui {
    class widget {
    public:
        widget *parent;

        virtual ~widget() = default;


        virtual void notify();

        virtual int get_rows();

        virtual int get_cols();

        virtual int get_min_rows();
        virtual int get_min_cols();

        virtual void draw(std::ostream &, const TermAttr &attr, const Coop &coop);
    };


    class center : public widget {
    public:
        std::shared_ptr<widget> child;

        explicit center(std::shared_ptr<widget> child);


        ~center() override = default;

        void notify() override;

        int get_rows() override;

        int get_cols() override;

        int get_min_rows() override;

        int get_min_cols() override;

        void draw(std::ostream &ostream, const TermAttr &attr, const Coop &coop) override;
    };


    class box : public widget {
    private:
        short rows;
        short cols;

    public:
        std::shared_ptr<widget> child;

        explicit box(std::shared_ptr<widget> child);

        ~box() override = default;

        void notify() override;

        int get_rows() override;

        int get_cols() override;

        void draw(std::ostream &ostream, const TermAttr &attr, const Coop &coop) override;

    };


    class text : public widget {
    private:
        short rows = 0;
        short cols = 0;
    public:
        std::string content;

        explicit text(std::string content);

        ~text() override = default;

        void notify() override;

        int get_rows() override;

        int get_cols() override;

        void draw(std::ostream &ostream, const TermAttr &attr, const Coop &coop) override;
    };

    class panel : public widget {
    public:
        std::shared_ptr<widget> child;

        explicit panel(std::shared_ptr<widget> child);

        ~panel() override = default;

        void notify() override;

        int get_rows() override;

        int get_cols() override;

        void draw(std::ostream &ostream, const TermAttr &attr, const Coop &coop) override;
    };


    class sized_panel : public widget {
    private:
        short rows = 0;
        short cols = 0;
    public:
        std::shared_ptr<widget> child;

        sized_panel(short width, short height, std::shared_ptr<widget> w);

        ~sized_panel() override = default;

        void notify() override;

        int get_rows() override;

        int get_cols() override;

        void draw(std::ostream &ostream, const TermAttr &attr, const Coop &coop) override;
    };


    class attr : public panel {
    public:
        color c;

        attr(color c, std::shared_ptr<widget> child);

        ~attr() override = default;

        void draw(std::ostream &ostream, const TermAttr &attr, const Coop &coop) override;

    };

    class filled_attr : public panel {
    public:
        color c;

        filled_attr(color c, std::shared_ptr<widget> child);

        ~filled_attr() override = default;

        void draw(std::ostream &ostream, const TermAttr &attr, const Coop &coop) override;
    };

    class vert_panel : public widget {
    public:
        short cols;
        short rows;

        std::vector<std::shared_ptr<widget>> children;

        vert_panel(std::initializer_list<std::shared_ptr<widget>> children);

        template<class ...T>
        explicit vert_panel(T...children) {
            add_children(children...);
        }

        void add_children(std::shared_ptr<widget> child);

        template<class ...T>
        void add_children(std::shared_ptr<widget> child, T ...children) {
            add_children(std::move(child));
            add_children(children...);
        }

        ~vert_panel() override = default;

        void notify() override;

        int get_rows() override;

        int get_cols() override;

        void draw(std::ostream &ostream, const TermAttr &attr, const Coop &coop) override;
    };
}

