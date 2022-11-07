//
// Created by mslxl on 11/7/2022.
//

#include "ListView.h"


namespace tui {
    ListView::ListView(std::initializer_list<std::shared_ptr<Widget>> child) : cols(0), rows(0),
                                                                               children(child) {}

    bool ListView::measure(std::pair<short, short> parentSize) {
        std::vector<std::shared_ptr<Widget>> second_measure_vec;
        short fuzzyRows = 0; //模糊行高，仅用于二次测量
        short certainRows = 0; // 已经确定的最小行高，不包含需要二次测量的 Widget
        for(auto& child: children){
            if(!child->measure({0,0})){
                second_measure_vec.push_back(child);
            }else{
                certainRows = short(certainRows + child->getRows());
            }
            cols = std::max(cols, child->getCols());
            fuzzyRows = short(fuzzyRows + child->getRows());
        }

        for(auto &child: second_measure_vec){
            if(!child->measure({cols, fuzzyRows})){
                std::abort();
            }
            certainRows = short(certainRows + child->getRows());
            cols = std::max(cols, child->getCols());
        }
        rows = certainRows;
        return true;
    }

    short ListView::getRows() const {
        return rows;
    }

    short ListView::getCols() const {
        return cols;
    }

    void ListView::draw(Canvas &canvas) {
        short drawY = 0;
        for(auto& child:children){
            auto subCanvas = canvas.limitCoord(0, drawY);
            child->draw(subCanvas);
            drawY += child->getRows(); // NOLINT(cppcoreguidelines-narrowing-conversions)
        }
    }
} // tui