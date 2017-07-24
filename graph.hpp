#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <memory>
#include <set>
#include <map>
#include <ostream>

#include "type.hpp"

struct Vertex;
struct Edge;

struct Vertex {
    enum class Color {
        uncolored, // Unvisited
        green, // visited
        grey, // dead end
    };

    const int x;
    const int y;
    const double cost; // Cost to achieve this vertex, inf means not achievable
    std::set<Edge*> edges;
    Vertex* previous = nullptr; // Vertex comes before this one
    Color color = Color::uncolored;

    Vertex(int x, int y, double cost)
        : x{x},
          y{y},
          cost{cost} {}

    friend std::ostream& operator<<(std::ostream& out, const Vertex& v) {
        out << "Vertex(" << v.x << ',' << v.y << ")";
        return out;
    }

    bool visited();
    void visit();

    void reset();
};

struct Edge {
    Vertex& start;
    Vertex& end;
    double cost = 1; // weight
    bool visited = false; // whether this edge has been visited before

    Edge(Vertex& start, Vertex& end, double cost = 1)
        : start{start},
          end{end},
          cost{cost} {}

    void reset();
};

// An undirected graph
class Graph
{
public:
    Graph();

    // Copy and moves
    Graph(const Graph& graph) = default;
    Graph& operator=(const Graph& graph) = default;
    Graph(Graph&& graph) = default;
    Graph& operator=(Graph&& graph) = default;

    // Add a vertex to the graph and return a reference to it
    std::shared_ptr<Vertex> add_vertex(int x, int y, double cost);

    // Return a pointer to vertex at specific position
    const std::shared_ptr<Vertex> get_vertex(int x, int y) const;

    void add_edge(Vertex& start, Vertex& end, double cost = 1);

    void reset();
    void clear();

private:
    std::set<std::shared_ptr<Vertex>> vertices_;
    std::set<std::shared_ptr<Edge>> edges_;
    std::map<Index, std::shared_ptr<Vertex>> index_map_; // A map from index to vertex
};

#endif // GRAPH_HPP
