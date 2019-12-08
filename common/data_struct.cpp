//
// Created by 曾锃煜 on 2019/12/6.
//

#include <string>
#include "data_struct.h"
#include "logger.h"

using namespace data::detail;

list<Vertex> Graph::GetAdjList(const data::detail::Vertex &pos) {
    list<Vertex> ret;
    if (pos.x + 1 < width_) {
        ret.emplace_back(pos.x + 1, pos.y, pos.index + 1);
    }
    if (pos.x > 0) {
        ret.emplace_back(pos.x - 1, pos.y, pos.index - 1);
    }
    if (pos.y + 1 < height_) {
        ret.emplace_back(pos.x, pos.y + 1, pos.index + width_);
    }
    if (pos.y > 0) {
        ret.emplace_back(pos.x, pos.y - 1, pos.index - width_);
    }
    return ret;
}

void Graph::PrintGraph() {
    size_t index = 0;
    string line;
    for (const auto &item : data_) {
        ++index;
        line.push_back(item);
        if (index % width_ != 0) {
            continue;
        }
        LOG("%u\t%s", index / width_ - 1, line.c_str());
        line.clear();
    }
}
