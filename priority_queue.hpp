#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include <algorithm>
#include <stdexcept>
#include <queue>
#include "graph.hpp"

const auto cost_compare = [](Vertex* lhs, Vertex* rhs) {
    return lhs->cost < rhs->cost;
};

// A priority queue that we can change the priority of elements
class Vertex_queue
        : public std::priority_queue<Vertex*,
        std::vector<Vertex*>,
        decltype(cost_compare)> {
public:
    Vertex_queue()
        : std::priority_queue<Vertex*, std::vector<Vertex*>, decltype(cost_compare)> {cost_compare} {}

    void change_cost(Vertex* v, double cost) {
        auto result = std::find(c.begin(), c.end(), v);
        if (result != c.end()) {
            v->cost = cost;
            std::make_heap(c.begin(), c.end(), cost_compare);
        } else {
            throw std::runtime_error {"Cannot find vertex in queue"};
        }
    }
};

#endif // PRIORITY_QUEUE_HPP
