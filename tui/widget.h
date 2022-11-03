//
// Created by mslxl on 10/30/2022.
//


#pragma once

#include <ostream>
#include <memory>
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
    private:
        short rows = 0;
        short cols = 0;
    public:
        std::shared_ptr<widget> child;

        panel(short width, short height, std::shared_ptr<widget> w);

        ~panel() override = default;

        void notify() override;

        int get_rows() override;

        int get_cols() override;

        void draw(std::ostream &ostream, const TermAttr &attr, const Coop &coop) override;
    };

    class attr : public widget {
    public:
        color c;
        std::shared_ptr<widget> child;

        attr(color c, std::shared_ptr<widget> child);

        ~attr() override = default;

        void notify() override;

        int get_rows() override;

        int get_cols() override;

        void draw(std::ostream &ostream, const TermAttr &attr, const Coop &coop) override;

    };

    class bg : public widget {
    public:
        color c;
        std::shared_ptr<widget> child;

        bg(color c, std::shared_ptr<widget> child);

        ~bg() override = default;

        void notify() override;

        int get_rows() override;

        int get_cols() override;

        void draw(std::ostream &ostream, const TermAttr &attr, const Coop &coop) override;

    };
}

