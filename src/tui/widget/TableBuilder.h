//
// Created by mslxl on 12/7/2022.
//


#pragma once

#include<functional>
#include <cmath>
#include "Table.h"

namespace tui {
    // Somehow a bit trick
    template<short COLS, short ROWS, class Container, class T>
    class TableBuilder : public Table<COLS> {
    public:
        using Builder = std::function<std::array<std::shared_ptr<Widget>, COLS>(short,T &)>;

        short &curPage;
        Builder builder;
        Container &dataContainer;

        std::optional<std::array<std::shared_ptr<Widget>, COLS>> header;

        TableBuilder(short &curPage, Container &_container, Builder builder) : builder(builder), curPage(curPage),
                                                                               dataContainer(_container),
                                                                               Table<COLS>(ROWS), header(std::nullopt) {
        }

        void setHeader(std::array<std::shared_ptr<Widget>, COLS> head){
            header = head;
        }

        void buildComponent() {
            this->components.clear();
            std::fill(this->rowHeight.begin(), this->rowHeight.end(), 0);
            std::fill(this->colWidth.begin(), this->colWidth.end(), 0);
            short contentRow = !header.has_value() ? ROWS : ROWS - 1;

            const int minPageNum = 0;
            const int maxPageNum = dataContainer.size()/contentRow;

            curPage = std::max(short(minPageNum), curPage);
            curPage = std::min(short(maxPageNum), curPage);

            if(header.has_value()){
                this->components.push_back(header.value());
            }
            for (short i = 0; i < contentRow; i++) {
                auto index = curPage * contentRow + i;

                auto iter = dataContainer.begin();
                for (int offset = 0; offset < index; offset++) {
                    if (iter != dataContainer.end()) {
                        ++iter;
                    } else {
                        return;
                    }
                }
                if(iter == dataContainer.end()){
                    return;
                }

                auto widget = builder(index,*iter);
                this->components.push_back(widget);
            }
        }

        void rebuild() override {
            buildComponent();
        }

        bool measure(std::pair<short, short> parentSize) override {
            bool certain = Table<COLS>::measure(parentSize);
            if(certain) LoggerPrinter("TableBuilder") << "Need second measure\n";
            LoggerPrinter("TableBuilder") << "Current nodeNum: " << this->getCols() << "x" << this->getRows() << "\n";
            return certain;
        }
    };

};