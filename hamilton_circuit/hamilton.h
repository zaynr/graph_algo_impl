//
// Created by 曾锃煜 on 2019/12/6.
//

#pragma once

#include <utility>
#include <set>
#include "data_struct.h"

using namespace data::detail;

class Hamilton {
private:
    Graph graph_;
    set<Vertex> close_set_;

public:
    Hamilton(Graph graph)
        :graph_(std::move(graph)){
        parseGraph();
    }

private:
    void parseGraph();

};
