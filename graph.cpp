#include "graph.hpp"

Vertex::Vertex(int x, int y, double cost, Graph& graph)
    : x{x},
      y{y},
      cost{cost},
      graph_{graph}
{}

bool Vertex::visited()
{
    return (color_ == Color::green || color_ == Color::grey);
}

void Vertex::visit()
{
    setColor(Color::green);
}

void Vertex::reset()
{    
    cost = std::numeric_limits<double>::infinity();
    previous = nullptr; // Vertex comes before this one
    color_ = Color::uncolored;
}

Vertex::Color Vertex::color() const
{
    return color_;
}

void Vertex::setColor(const Color& color)
{
    color_ = color;
}

void Edge::reset()
{
    visited = false;
}


Graph::Graph()
{

}

std::shared_ptr<Vertex> Graph::add_vertex(int x, int y, double cost)
{
    auto vertex = std::make_shared<Vertex>(x, y, cost, *this);
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

const std::set<std::shared_ptr<Vertex>>& Graph::vertices() const
{
    return vertices_;
}

bool operator<(const Index& lhs, const Index& rhs) noexcept {
    return (lhs.y < rhs.y || (lhs.y == rhs.y && lhs.x < rhs.x)) ? true : false;
}

bool operator==(const Index& lhs, const Index& rhs) noexcept {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
