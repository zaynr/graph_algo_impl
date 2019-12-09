//
// Created by 曾锃煜 on 2019/12/8.
//

#include <logger.h>
#include <sstream>
#include "dfs.h"

void Dfs::SearchAllPath(const Vertex &src, const size_t len, list<VertexList> &out_list) {
    out_list.clear();

    size_t cur_len = 0;
    VertexList cur_list;
    cur_list.push_back(src);
    out_list.push_back(cur_list);
    list<VertexSet> all_path_set;
    VertexSet path_set;
    path_set.insert(src);
    all_path_set.push_back(path_set);
    while (cur_len != len) {
        ++cur_len;
        list<VertexList> inner_list;
        list<VertexSet> inner_set;
        while (!out_list.empty()) {
            VertexList adj_list = graph_.GetAdjList(*cur_list.rbegin());
            bool empty = true;
            for(const auto &item : adj_list) {
                path_set = *all_path_set.rbegin();
                auto res = path_set.insert(item);
                if(!res.second) {
                    continue;
                }
                empty = false;
                cur_list = *out_list.rbegin();
                cur_list.push_back(item);
                inner_list.push_back(cur_list);
                inner_set.push_back(path_set);
            }
            if (empty) {
                inner_list.push_back(*out_list.rbegin());
                inner_set.push_back(*all_path_set.rbegin());
            }
            out_list.pop_back();
            all_path_set.pop_back();
        }
        out_list.swap(inner_list);
        all_path_set.swap(inner_set);
    }

    LOG("possible path: %u", all_path_set.size());
}

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
