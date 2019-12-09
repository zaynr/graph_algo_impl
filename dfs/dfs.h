//
// Created by 曾锃煜 on 2019/12/8.
//


#pragma once

#include <data_struct.h>

using namespace data::detail;

class Dfs {
private:
    Graph graph_;
    VertexSet open_set_;
    VertexSet close_set_;
    WeightGraphMap weight_map_;

public:
    Dfs(Graph graph)
            : graph_(move(graph)) {
        parseGraph();
    }

    ~Dfs(){}

    void SearchLongest(const Vertex &src);

    void SearchAllPath(const Vertex &src, size_t len, list<VertexList> &out_list);

private:
    void parseGraph();
};


