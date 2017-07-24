#ifndef TYPE_HPP
#define TYPE_HPP

#include <vector>

// Defines some usful types

struct Index {
    int x;
    int y;
};

enum class Algorithm {
    dfs, // Depth first search
    bfs, // Breath first search
    dijkstra,
    a_star,
};

struct Path {
    std::vector<Index> route;
    double cost;
};

bool operator<(const Index& lhs, const Index& rhs) noexcept;
bool operator==(const Index& lhs, const Index& rhs) noexcept;


#endif // TYPE_HPP
