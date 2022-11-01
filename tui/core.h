//
// Created by mslxl on 10/31/2022.
//


#pragma once

namespace tui {
    void stub();

    struct Coop{
        int x,y;
        Coop(int x,int y):x(x), y(y){

        }

        bool operator <(const Coop& rhs) const {
            if(x == rhs.x) return y < rhs.y;
            else return x < rhs.x;
        }
    };
}
