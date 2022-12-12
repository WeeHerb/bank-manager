//
// Created by mslxl on 11/7/2022.
//

#include "HListView.h"

namespace tui {
    HListView::HListView(std::initializer_list<std::shared_ptr<Widget>> children) : VListView(children) {

    }

    bool HListView::measure(std::pair<short, short> parentSize) {
        std::vector<std::shared_ptr<Widget>> second_measure_vec;

        short fuzzyCols = 0; //模糊行宽，仅用于二次测量
        short certainCols = 0; // 已经确定的最小行宽，不包含需要二次测量的 Widget
        for(auto& child: children){
            if(!child->measure({0,0})){
                second_measure_vec.push_back(child);
            }else{
                certainCols = short(certainCols + child->getCols());
            }
            rows = std::max(rows, child->getRows());
            fuzzyCols = short(fuzzyCols + child->getCols());
        }

        for(auto &child: second_measure_vec){
            if(!child->measure({fuzzyCols, rows})){
                std::abort();
            }
            certainCols = short(certainCols + child->getCols());
            rows = std::max(rows, child->getRows());
        }
        cols = certainCols;
        return true;
    }

    void HListView::draw(Canvas &canvas) {
        LoggerPrinter("Widget") << "Widget "<< typeid(this).name() <<" draw begin\n";
        short drawX = 0;
        for(auto& child:children){
            auto subCanvas = canvas.limitCoord(drawX, 0);
            child->draw(subCanvas);
            drawX += child->getCols(); // NOLINT(cppcoreguidelines-narrowing-conversions)
        }
        LoggerPrinter("Widget") << "Widget "<< typeid(this).name() <<" draw end\n";
    }

    void HListView::rebuild() {
        for(auto& child: children){
            child->rebuild();
        }
    }
} // tui