//
// Created by mslxl on 12/13/2022.
//

#include<set>
#include<queue>
#include <map>
#include <sstream>

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


void page::mapPage(tui::Term &term) {
    using namespace tui;
    Graph<int> graph;
    graph.add_biedge(0, 1, 5);
    graph.add_biedge(1, 2, 5);
    graph.add_biedge(2, 3, 2);
    graph.add_biedge(0, 4, 9);
    graph.add_biedge(2, 3, 2);
    graph.add_biedge(2, 3, 8);
    graph.add_biedge(2, 5, 2);
    graph.add_biedge(1, 3, 6);

    std::vector<int> endPoint{4, 5};
    graph.name[0] = "下北泽路";
    graph.name[1] = "A路";
    graph.name[2] = "B路";
    graph.name[3] = "C路";
    graph.name[4] = "D路";
    graph.name[5] = "E路";

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
                    ui<Struct>(2,2),
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
                                                endPoint.push_back(std::stoi(value.value()));
                                            }
                                        });
                                    }, L"填加网点"),
                                    ui<Struct>(2, 2),
                                    ui_args<WTextButton>([&endPoint, &term, &graph](WTextButton &t) {
                                        t.setFocusOrder(1);
                                        t.setActionListener([&endPoint, &term, &graph]() {
                                                                auto value = inputbox<char, wchar_t, wchar_t, wchar_t>(term,
                                                                                                                       L"请输入地点",
                                                                                                                       true, L"确定",
                                                                                                                       true, L"取消");
                                                                if (!value.has_value()) {
                                                                    return;
                                                                }

                                                                int startPoint = std::stoi(value.value());
                                                                std::set<int> endPointSet(endPoint.begin(),
                                                                                          endPoint.end());


                                                                std::map<int, int> parent;
                                                                std::map<int, bool> vis;
                                                                std::priority_queue<route, std::vector<route>> queue;
                                                                queue.push(route{0, startPoint, 0});
                                                                int reachPoint = -1;
                                                                int weight = 0;

                                                                while (!queue.empty()) {
                                                                    auto w = queue.top().w, u = queue.top().v, p = queue.top().parent;
                                                                    if(!vis[u]) parent[u] = p;
                                                                    vis[u] = true;
                                                                    queue.pop();
                                                                    for (auto e: graph[u]) {
                                                                        if (endPointSet.count(e.to)) {
                                                                            reachPoint = e.to;
                                                                            weight = e.data + w;
                                                                            goto end; //my fault :(
                                                                        }
                                                                        if (vis[e.to]) continue;
                                                                        queue.push(route{e.data + w, e.to, u});
                                                                    }
                                                                }
                                                                end:
                                                                if (reachPoint == -1) {
                                                                    msgbox<wchar_t, wchar_t, wchar_t>(term, L"找不到路径", true, L"确定",
                                                                                                      false, L"");
                                                                    return;
                                                                }

                                                                std::stack<std::string> route;
                                                                int pt = reachPoint;
                                                                while (pt != startPoint) {
                                                                    route.push(graph.name[pt]);
                                                                    pt = parent[pt];
                                                                }

                                                                std::stringstream ss;
                                                                ss << "最短路径为 ";
                                                                while (!route.empty()) {
                                                                    ss << route.top() << "->";
                                                                }
                                                                ss << "网点";

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
