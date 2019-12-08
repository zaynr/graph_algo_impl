//
// Created by 曾锃煜 on 2019/12/7.
//


#pragma once

#include <data_struct.h>

using namespace data::detail;

class Dijkstra {
private:
    Graph graph_;

public:
    Dijkstra(Graph graph)
            : graph_(move(graph)) {
    }
};


