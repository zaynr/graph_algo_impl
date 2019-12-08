//
// Created by 曾锃煜 on 2019/12/8.
//

#include <logger.h>
#include "dfs.h"

void Dfs::SearchLongest(const Vertex &src) {
    open_set_.insert(src);

    size_t loop = 0;
    while (!open_set_.empty()) {
        ++loop;
        Vertex vertex = *open_set_.begin();
        open_set_.erase(vertex);
        //LOG("start: %u, %u, size: %u", vertex.x, vertex.y, open_set_.size());

        auto witor = weight_map_.find(vertex);
        auto weight = witor->second.weight;
        VertexList adj_list = graph_.GetAdjList(vertex);
        for (const auto &item : adj_list) {
            if (close_set_.count(item) != 0) {
                continue;
            }
            if (witor->second.successor.count(item) == 0) {
                open_set_.insert(item);
            } else {
                continue;
            }

            auto itor = weight_map_.find(item);
            auto cur_weight = weight + 1;

            if (itor->second.weight < cur_weight
                || itor->second.weight == 0) {
                itor->second.weight = cur_weight;
                itor->second.successor.insert(vertex);
                itor->second.SetParent(vertex);
            }
        }
    }
    LOG("looped: %u", loop);

    // trace path
    graph_.LeftFootprint(src);
    auto max_w = 0.0f;
    auto find_itor = weight_map_.begin();
    for (auto witor = weight_map_.begin(); witor != weight_map_.end(); ++witor) {
        if (max_w < witor->second.weight) {
            max_w = witor->second.weight;
            find_itor = witor;
        }
    }
    LOG("path len: %f, dst: %u, %u", max_w, find_itor->first.x, find_itor->first.y);
    while (find_itor->second.index != find_itor->first.index) {
        graph_.LeftFootprint(find_itor->first);
        find_itor = weight_map_.find(Vertex(find_itor->second.x, find_itor->second.y, find_itor->second.index));
    }
    graph_.PrintGraph();
}

void Dfs::parseGraph() {
    size_t index = 0;
    for (const auto &item : graph_.GetGraphBuffer()) {
        switch (item) {
            case 'H':
            case 'A':
            case 'B':
                close_set_.emplace(graph_.GetCoord(index));
                break;
            default:
                weight_map_.emplace(make_pair(graph_.GetCoord(index),
                                              WeightVertex(graph_.GetCoord(index), 0)));
                break;
        }
        ++index;
    }
}
