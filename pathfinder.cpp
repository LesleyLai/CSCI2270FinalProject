#include "pathfinder.hpp"
#include "graph.hpp"

std::vector<Vertex*> depth_first_search(Vertex& start, Vertex& end)
{
    Vertex* cursor = &start;
    std::vector<Vertex*> path;
    while (true) {
        if (!cursor->visited()) {
            cursor->visit();
            path.push_back(cursor);
        }

        if (cursor == &end) return path;

        bool new_vertex = false; // true when cursor move to a new vertex

        // if find any unvisited neighbor, jump to it
        for (auto edge : cursor->edges) {
            Vertex& next = edge->end;
            if (!next.visited()) {
                next.previous = cursor;
                cursor = &next;
                new_vertex = true;
                break;
            }
        }
        // dead end node (no unvisited neighbir)
        if (!new_vertex) {
            if (cursor == &start) {
                path.clear();
                return path; // fail to find path
            }
            // jump back to previous one
            path.pop_back();
            cursor->color = Vertex::Color::grey;
            cursor = cursor->previous;
        }
    }
}
