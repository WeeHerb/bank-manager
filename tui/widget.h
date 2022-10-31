//
// Created by mslxl on 10/30/2022.
//


#pragma once

namespace tui{
    class widget{
        virtual ~widget() = default;

        virtual int rows();
        virtual int cols();
        virtual void draw();
    };
}