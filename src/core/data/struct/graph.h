//
// Created by mslxl on 12/13/2022.
//


#pragma once
#include<vector>
#include<unordered_map>
#include <string>

// 打 Codeforce 用的模板，直接拿来用了
template <class TData = int> struct Graph {
    struct node {
        int to{};
        TData data{};
    };
    std::unordered_map<int, std::vector<node>> edges{};
    std::unordered_map<int, std::string> name;

    Graph()= default;
    void add_edge(int u, int v, TData data = TData{}) {edges[u].emplace_back(node{v,data});}
    void add_biedge(int u, int v, TData data = TData{}) {add_edge(u, v, data),add_edge(v, u, data);}
    void clear() {edges.clear();}
    std::vector<node>& from(std::size_t idx) noexcept{return (*this)[idx];}
    std::vector<node>& operator[](std::size_t idx) noexcept{return edges[idx];}
};