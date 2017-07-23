#include "graph.hpp"

namespace  {
// Helper to add a directed edge
std::shared_ptr<Edge> create_single_edge(Vertex& start, Vertex& end, double cost);
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
    auto edge = create_single_edge(start, end, cost);
    auto reverse_edge = create_single_edge(end, start, cost);
    edges_.insert(edge);
    edges_.insert(reverse_edge);
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

namespace {
std::shared_ptr<Edge> create_single_edge(Vertex& start, Vertex& end, double cost) {
    auto edge = std::make_shared<Edge>(start, end, cost);
    edge->start.edges.insert(edge.get());
    return edge;
}
}
