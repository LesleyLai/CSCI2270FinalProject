#include "adpter.hpp"

constexpr double sqrt2 = 1.41421356237;

// Add neighbor vertex from a vertex at (x, y)
void add_edges_to_neighbors(const Grid<double>& grid, Graph& graph,
                            int x, int y) {
    auto v = graph.get_vertex(x, y);
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            const int nx = x + dx;
            const int ny = y + dy;
            if ((dx == 0 && dy == 0) || !grid.inBounds(nx, ny)) continue;
            auto neighbor = graph.get_vertex(nx, ny);
            auto multiplier = (dx == 0 || dy == 0) ? 1 : sqrt2;
            auto cost = multiplier * std::abs(v->cost - neighbor->cost);
            if (!isnan(cost) && !isinf(cost)) {
                graph.add_edge(*v, *neighbor, cost);
            }
        }
    }
}

Graph graph_from_grid(const Grid<double>& grid)
{
    Graph graph;

    const int width = grid.width();
    const int height = grid.height();

    // Adds vertices
    for (int x = 0; x != width; ++x) {
        for (int y = 0; y != height; ++y) {
            graph.add_vertex(x, y, grid.at(x, y));
        }
    }

    // Adds edges
    for (int x = 0; x != width; ++x) {
        for (int y = 0; y != height; ++y) {
            add_edges_to_neighbors(grid, graph, x, y);
        }
    }

    return graph;
}
