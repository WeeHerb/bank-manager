//
// Created by mslxl on 12/7/2022.
//


#pragma once

#include<functional>
#include "Table.h"

namespace tui {
    // Somehow a bit trick
    template<short COLS, short ROWS, class Container, class T>
    class TableBuilder : public Table<COLS> {
    public:
        using Builder = std::function<std::array<std::shared_ptr<Widget>, COLS>(T &)>;

        short &curPage;
        Builder builder;
        Container &dataContainer;

        TableBuilder(short &curPage, Container &_container, Builder builder) : builder(builder), curPage(curPage),
                                                                               dataContainer(_container) {
        }

        void buildComponent() {
            this->components.clear();
            for (short i = 0; i < ROWS; i++) {
                auto index = curPage * ROWS + i;

                auto iter = dataContainer.begin();
                for(int offset = 0; offset < index; offset++) {
                    if(iter != dataContainer.end()){
                        ++iter;
                    }else{
                        return;
                    }
                }

                auto widget = builder(*iter);
                this->components.push_back(widget);
            }
        }

        bool measure(std::pair<short, short> parentSize) override {
            if (parentSize.first == -1 && parentSize.second == -1) {
                buildComponent();
            }
            return Table<COLS>::measure(parentSize);
        }
    };

};