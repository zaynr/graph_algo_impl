//
// Created by 曾锃煜 on 2019/12/6.
//

#pragma once

#include <vector>
#include <list>
#include <set>
#include <map>

using namespace std;

namespace data {
    namespace detail {

        struct Vertex {
            size_t x;
            size_t y;
            size_t index;

            Vertex(const Vertex &rhs) : x(rhs.x), y(rhs.y), index(rhs.index) {}
            Vertex(size_t x, size_t y, size_t index) : x(x), y(y), index(index) {}

            inline bool operator==(const Vertex &rhs) const {
                return this->index == rhs.index;
            }

            inline bool operator<(const Vertex &rhs) const {
                return this->index < rhs.index;
            }
        };
        using VertexList = list<Vertex>;
        using VertexSet = set<Vertex>;

        struct WeightVertex : public Vertex {
            float weight;
            VertexSet successor;

            WeightVertex(const Vertex &rhs, float w) : Vertex(rhs), weight(w) {}

            void SetParent(const Vertex &rhs) {
                this->x = rhs.x;
                this->y = rhs.y;
                this->index = rhs.index;
            }

            inline bool operator<(const WeightVertex &rhs) const {
                if (this->weight == rhs.weight) {
                    return this->index < rhs.index;
                }
                return this->weight < rhs.weight;
            }
        };
        using WeightGraphMap = map<Vertex, WeightVertex>;

        class Graph {
        private:
            size_t width_;
            size_t height_;
            vector<char> data_;

        public:
            explicit Graph(vector<char> &data, const size_t width, const size_t height)
                    : width_(width), height_(height) {
                data_.swap(data);
            }

            Vertex GetCoord(const size_t index) {
                return Vertex{index % width_, index / width_, index};
            }

            Vertex GetCoord(const size_t x, const size_t y) {
                return Vertex{x, y, x + y * width_};
            }

            vector<char> &GetGraphBuffer() {
                return data_;
            }

            void PrintGraph();

            void LeftFootprint(const Vertex &pos) {
                data_[pos.index] = 'A';
            }

            list<Vertex> GetAdjList(const Vertex &pos);
        };

    } // namespace detail
} // namespace data
