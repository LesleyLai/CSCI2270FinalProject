#include "graph.hpp"

bool Vertex::visited()
{
    return (color == Color::green || color == Color::grey);
}

void Vertex::visit()
{
    color = Color::green;
}

void Vertex::reset()
{
    previous = nullptr; // Vertex comes before this one
    color = Color::uncolored;
}

void Edge::reset()
{
    cost = 1; // weight
    visited = false;
}


Graph::Graph()
{

}

std::shared_ptr<Vertex> Graph::add_vertex(int x, int y, double cost)
{
    auto vertex = std::make_shared<Vertex>(x, y, cost);
    vertices_.insert(vertex);
    index_map_[Index{x, y}] = vertex;
    return vertex;
}

const std::shared_ptr<Vertex> Graph::get_vertex(int x, int y) const
{
    auto result = index_map_.find(Index{x, y});
    if (result != index_map_.end()) {
        return result->second;
    } else {
        return nullptr;
    }
}

void Graph::add_edge(Vertex& start, Vertex& end, double cost)
{
    auto edge = std::make_shared<Edge>(start, end, cost);
    edge->start.edges.insert(edge.get());
    edges_.insert(edge);
}

void Graph::reset()
{
    for (auto v : vertices_) {
        v->reset();
    }

    for (auto e : edges_) {
        e->reset();
    }
}

void Graph::clear() {
    vertices_.clear();
    edges_.clear();
    index_map_.clear();
}

bool operator<(const Index& lhs, const Index& rhs) noexcept {
    return (lhs.y < rhs.y || (lhs.y == rhs.y && lhs.x < rhs.x)) ? true : false;
}

bool operator==(const Index& lhs, const Index& rhs) noexcept {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
