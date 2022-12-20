//
// Created by mslxl on 12/13/2022.
//

#include<set>
#include<queue>
#include <map>
#include <sstream>
#include <unistd.h>

#include "bank_map.h"
#include "core/data/struct/graph.h"

#include "tui/Widget.h"
#include "tui/dialog/msgbox.h"

struct route {
    int w;
    int v;
    int parent;

    bool operator<(const route &rhs) const {
        return w < rhs.w;
    }
};

const char* MAP_FILE = "map.csv";

void page::mapPage(tui::Term &term) {
    using namespace tui;
    Graph<int> graph;
    if(access(MAP_FILE,F_OK) == -1){
        auto value = inputbox<char, wchar_t, wchar_t, wchar_t>(term,
                                                               L"无地图信息",
                                                               true,
                                                               L"确定", true,
                                                               L"取消");
        return;
    }
    std::vector<int> endPoint;

    std::string line;
    std::ifstream map_csv(MAP_FILE);
    std::getline(map_csv, line);
    std::getline(map_csv, line);
    while(line[0] != '-'){
        std::istringstream spliter(line);
        std::string id,name,end, open;
        std::getline(spliter, id, ',');
        std::getline(spliter, name, ',');
        std::getline(spliter, end, ',');
        std::getline(spliter, open, ',');
        graph.name[std::stoi(id)] = name;
        if(std::stoi(end) && std::stoi(open)) endPoint.push_back(std::stoi(id));
        std::getline(map_csv, line);
    }
    std::getline(map_csv, line);
    while(std::getline(map_csv, line)){
        int pt[3];
        std::istringstream spliter(line);
        for(int & i : pt){
            std::string cache;
            std::getline(spliter,cache, ',');
            i = std::stoi(cache);
        }
        graph.add_biedge(pt[0], pt[1], pt[2]);
    }

    short curPage = 0;

    auto widget = ui<Center>(
            ui<VListView>(
                    ui<HCenter>(
                            ui<AttrFill>(
                                    color::BG_GREEN | color::FG_COMMON,
                                    ui<Box>(
                                            ui<HListView>(std::make_shared<Struct>(1, 4),
                                                          ui<WText>(
                                                                  L"网点导航"),
                                                          ui<Struct>(1, 4)
                                            )
                                    )
                            )
                    ),
                    ui<Struct>(2, 2),
                    ui<WText>(L"所有网点："),
                    ui<Box>(
                            ui_args<TableBuilder<3, 4, std::vector<int>, int>>(
                                    [](TableBuilder<3, 4, std::vector<int>, int> &table) {
                                        table.setHeader(tableRow(
                                                ui<WText>(L"位置"),
                                                ui<Struct>(1, 1),
                                                ui<WText>(L"编号")
                                        ));
                                    }, curPage, endPoint, [&graph](short index, int target) {
                                        return tableRow(
                                                ui<Text>(graph.name[target]),
                                                ui<Struct>(1, 1),
                                                ui<WText>(std::to_wstring(target) + L" 号网点"));
                                    })
                    ),
                    ui<Struct>(2, 2),
                    ui<HCenter>(
                            ui<HListView>(
                                    ui_args<WTextButton>([&endPoint, &term](WTextButton &t) {
                                        t.setFocusOrder(0);
                                        t.setActionListener([&endPoint, &term]() {
                                            auto value = inputbox<char, wchar_t, wchar_t, wchar_t>(term,
                                                                                                   L"请输入地点",
                                                                                                   true,
                                                                                                   L"确定", true,
                                                                                                   L"取消");

                                            if (value.has_value()) {
                                                auto id = std::stoi(value.value());
                                                if(std::find(endPoint.begin(), endPoint.end(), id) != endPoint.end()){
                                                    std::remove(endPoint.begin(), endPoint.end(), id);
                                                }else{
                                                    endPoint.push_back(id);
                                                }
                                            }
                                        });
                                    }, L"开关网点"),
                                    ui<Struct>(2, 2),
                                    ui_args<WTextButton>([&endPoint, &term, &graph](WTextButton &t) {
                                        t.setFocusOrder(1);
                                        t.setActionListener([&endPoint, &term, &graph]() {
                                                                auto value = inputbox<char, wchar_t, wchar_t, wchar_t>(term,
                                                                                                                       L"请输入出发地点",
                                                                                                                       true, L"确定",
                                                                                                                       true, L"取消");
                                                                if (!value.has_value()) {
                                                                    return;
                                                                }

                                                                int startPoint = std::stoi(value.value());
                                                                std::set<int> endPointSet(endPoint.begin(),
                                                                                          endPoint.end());


                                                                auto result = dijkstra<int>(graph, startPoint, endPointSet);
                                                                auto route = result.first;
                                                                if (route.empty()) {
                                                                    msgbox<char, wchar_t, wchar_t>(term, "无可用路线", true, L"确定",
                                                                                                   false, L"");
                                                                    return;
                                                                }

                                                                std::stringstream ss;
                                                                ss << "最短路径为 ";
                                                                ss << graph.name[route[0]];
                                                                for (int i = 1; i < route.size(); i++) {
                                                                    ss << "->" << graph.name[route[i]];
                                                                }
                                                                ss << "(网点)，全程 " << result.second << " 米";

                                                                msgbox<char, wchar_t, wchar_t>(term, ss.str(), true, L"确定",
                                                                                               false, L"");
                                                            }
                                        );


                                    }, L"导航")
                            )),

                    ui<HCenter>(
                            ui_args<WTextButton>([&term](WTextButton &t) {
                                t.setFocusOrder(2);
                                t.setActionListener([&term]() {
                                    term.pop();
                                });
                            }, L"返回")
                    )
            )
    );
    term.push(widget);
    term.invalidate();
    term.capture();
    term.invalidate();

}
