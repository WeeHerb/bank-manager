//
// Created by mslxl on 10/30/2022.
//


#pragma once

#include <ostream>
#include "tui/core.h"
#include "tui/term_attr.h"

namespace tui {
    class widget {
    public:
        widget *parent = nullptr;

        virtual ~widget() = default;


        virtual void notify();

        virtual int get_rows();

        virtual int get_cols();

        virtual void draw(std::ostream &, const TermAttr &attr, const Coop &coop);
    };


    class center : public widget {
    public:
        widget &child;

        explicit center(widget &child) : child(child) {
            child.parent = this;
        }


        ~center() override = default;

        void notify() override;

        int get_rows() override;

        int get_cols() override;

        void draw(std::ostream &ostream, const TermAttr &attr, const Coop &coop) override;
    };


    class box : public widget {
    private:
        short rows;
        short cols;

    public:
        widget &child;

        explicit box(widget &child) : child(child) {
            child.parent = this;
        }

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



    class panel : widget {
    private:
        short rows = 0;
        short cols = 0;
    public:
        widget &child;

        panel(short width, short height, widget &w);

        ~panel() override = default;

        void notify() override;

        int get_rows() override;

        int get_cols() override;

        void draw(std::ostream &ostream, const TermAttr &attr, const Coop &coop) override;
    };
}

