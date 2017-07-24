// Path finding algorithms

#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

#include "type.hpp"

class Graph;
struct Vertex;

std::vector<Vertex*> depth_first_search(Vertex& start, Vertex& end);

#endif // PATHFINDER_HPP
