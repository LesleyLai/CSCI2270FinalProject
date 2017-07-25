#include <algorithm>
#include <iostream>
#include <queue>
#include <limits>

#include "priority_queue.hpp"
#include "pathfinder.hpp"
#include "graph.hpp"

namespace {
void enqueue_vertex(Vertex_queue &queue, Vertex* v, Vertex* previous, double cost);

std::vector<Vertex*> generate_path(Vertex* end, Vertex* start);
}

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
            cursor->setColor(Vertex::Color::grey);
            cursor = cursor->previous;
        }
    }
}

std::vector<Vertex*> breath_first_search(Vertex& start, Vertex& end)
{
    std::vector<Vertex*> path;
    Vertex_queue queue;
    start.cost = std::numeric_limits<double>::infinity();
    queue.push(&start);
    double cost; // Cache cost

    while (!queue.empty()) {
        Vertex* cursor = queue.top();
        std::cout << *cursor << " " << cursor->visited() << std::endl;
        queue.pop();
        if (!cursor->visited()) cursor->visit();
        if (cursor == &end) {
            return generate_path(&end, &start);
        }

        for (auto edge : cursor->edges) {
            cost = edge->cost;
            if (!edge->end.visited() && cost < edge->end.cost) {
                edge->visited = true;
                enqueue_vertex(queue, &edge->end, cursor, cost);
            }
        }
    }

    return path;
}

namespace {
// Enqueues a new vertex if the vertex are not exist in the queue
void enqueue_vertex(Vertex_queue &queue, Vertex* v, Vertex* previous, double cost) {
    v->previous = previous;
    if (v->color() != Vertex::Color::purple) {
        v->setColor(Vertex::Color::purple);
        v->cost = cost;
        queue.push(v);
    } else {
        queue.change_cost(v, v->cost);
    }
}

std::vector<Vertex*> generate_path(Vertex* end, Vertex* start) {
    std::vector<Vertex*> result;
    auto cursor = end;
    while (cursor != start) {
        std::cout << *cursor << std::endl;
        result.push_back(cursor);
        cursor = cursor->previous;
    }
    result.push_back(start);
    std::reverse(result.begin(), result.end());
    return result;
}


}
