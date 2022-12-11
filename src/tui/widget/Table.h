//
// Created by mslxl on 12/2/2022.
//

#pragma once

#include <list>
#include <numeric>

#include "Widget.h"
#include "tui/core.h"

namespace tui {
    template<short COLS>
    class Table : public Widget {
    public:
        using ElementVec = std::vector<std::array<std::shared_ptr<Widget>, COLS>>;
        ElementVec components;
        std::vector<short> rowHeight;
        std::array<short, COLS> colWidth;

    public:
        explicit Table(ElementVec table) : components(table), rowHeight(table.size(), -1) {
            std::fill(colWidth.begin(), colWidth.end(), -1);
        }

        explicit Table(short predictRowHeight): rowHeight(predictRowHeight, -1){

        }

        template<typename... T>
        explicit
        Table(T... table): Table(ElementVec(std::initializer_list({table...}))) {}

        bool measure(std::pair<short, short> parentSize) override {
            std::list<std::tuple<short, short, std::shared_ptr<Widget>>> toMeasure;
            for (std::size_t c = 0; c < COLS; c++) {
                for (std::size_t r = 0; r < components.size(); r++) {
                    if (components[r][c]->measure(std::make_pair(-1, -1))) {
                        rowHeight[r] = std::max(rowHeight[r], components[r][c]->getRows());
                        colWidth[c] = std::max(colWidth[c], components[r][c]->getCols());
                    } else {
                        toMeasure.push_back(std::make_tuple(c, r, components[r][c]));
                    }
                }
            }

            for (auto &[c, r, widget]: toMeasure) {
                if (widget->measure(std::make_pair(colWidth[c], rowHeight[r]))) {
                    rowHeight[r] = widget->getRows();
                    colWidth[c] = widget->getCols();
                } else {
                    stub();
                }
            }
            return true;
        }

        [[nodiscard]] short getRows() const override {
            return std::reduce(rowHeight.begin(), rowHeight.end(), 0);
        }

        [[nodiscard]] short getCols() const override {
            return std::reduce(colWidth.begin(), colWidth.end(), 0);
        }

        void draw(Canvas &canvas) override {
            short row = 0;
            for (std::size_t r = 0; r < components.size(); r++) {
                short cols = 0;
                for (std::size_t c = 0; c < COLS; c++) {
                    auto limitedCanvas = canvas.limitCoord(cols, row);
                    components[r][c]->draw(limitedCanvas);
                    cols += colWidth[c];
                }
                row += rowHeight[r];
            }
        }

        void track(WidgetTracker &tracker) override {
            for (auto &r: components) {
                for (auto &w: r) {
                    tracker(w);
                    w->track(tracker);
                }
            }
        }


        ~Table() override = default;
    };

    template<typename  ...T>
    constexpr std::array<std::shared_ptr<Widget>,  sizeof...(T)> tableRow(T... elements) {
        using arr = std::array<std::shared_ptr<Widget>,  sizeof...(T)>;
        arr a = {{elements...}};
        return a;
    }


} // tui
