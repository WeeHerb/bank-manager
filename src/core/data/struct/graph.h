//
// Created by mslxl on 12/13/2022.
//


#pragma once

#include<vector>
#include<unordered_map>
#include <string>
#include<set>

// 打 Codeforce 用的模板，直接拿来用了
template<class TData = int>
struct Graph {
    struct node {
        int to{};
        TData data{};
    };
    std::unordered_map<int, std::vector<node>> edges{};
    std::unordered_map<int, std::string> name;

    Graph() = default;

    void add_edge(int u, int v, TData data = TData{}) { edges[u].emplace_back(node{v, data}); }

    void add_biedge(int u, int v, TData data = TData{}) { add_edge(u, v, data), add_edge(v, u, data); }

    void clear() { edges.clear(); }

    std::vector<node> &from(std::size_t idx)  { return (*this)[idx]; }

    std::vector<node> &operator[](std::size_t idx)  { return edges[idx]; }
};

template<typename T>
typename std::enable_if<std::is_integral<T>::value, std::pair<std::vector<int>, int>>::type
dijkstra(Graph<T> &graph, int start, std::set<int> end) {
    std::priority_queue<std::tuple<T, int, std::vector<int>>> que;
    que.push(std::make_tuple(0, start, std::vector<int>({start})));
    std::unordered_map<int, bool> vis;
    while (!que.empty()) {
        auto top = que.top();
        que.pop();
        if (vis[std::get<1>(top)]) continue;
        vis[std::get<1>(top)] = true;
        if (end.count(std::get<1>(top))) {
            return std::make_pair(std::get<2>(top),std::get<0>(top));
        }

        int w = std::get<0>(top);
        std::vector<int> route = std::get<2>(top);
        for (auto node: graph[std::get<1>(top)]) {
            if (vis[node.to]) continue;
            std::vector<int> r = route;
            r.push_back(node.to);
            que.push(std::make_tuple(w + node.data, node.to, r));
        }
    }
    return std::make_pair(std::vector<int>(), -1);
}
