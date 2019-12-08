//
// Created by 曾锃煜 on 2019/12/6.
//

#include "hamilton.h"

void Hamilton::parseGraph() {
    size_t index = 0;
    for(const auto &item : graph_.GetGraphBuffer()) {
        switch(item){
            case 'H':
            case 'A':
            case 'B':
                close_set_.emplace(graph_.GetCoord(index));
                break;
            default:
                break;
        }
        ++index;
    }
}
