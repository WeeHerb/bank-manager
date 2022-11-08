//
// Created by mslxl on 11/7/2022.
//

#include "VListView.h"


namespace tui {
    VListView::VListView(std::initializer_list<std::shared_ptr<Widget>> child) : cols(0), rows(0),
                                                                                 children(child) {}

    bool VListView::measure(std::pair<short, short> parentSize) {
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

    short VListView::getRows() const {
        return rows;
    }

    short VListView::getCols() const {
        return cols;
    }

    void VListView::draw(Canvas &canvas) {
        LoggerPrinter("Widget") << "Widget "<< typeid(this).name() <<" draw begin\n";
        short drawY = 0;
        for(auto& child:children){
            auto subCanvas = canvas.limitCoord(0, drawY);
            child->draw(subCanvas);
            drawY += child->getRows(); // NOLINT(cppcoreguidelines-narrowing-conversions)
        }
        LoggerPrinter("Widget") << "Widget "<< typeid(this).name() <<" draw end\n";
    }
} // tui