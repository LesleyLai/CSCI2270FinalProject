#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

// Path finding algorithms

#include "type.hpp"

class Graph;
struct Vertex;

std::vector<Vertex*> depth_first_search(Vertex& start, Vertex& end);
std::vector<Vertex*> breath_first_search(Vertex& start, Vertex& end);
std::vector<Vertex*> dijkstras_algorithm(Vertex& start, Vertex& end);


#endif // PATHFINDER_HPP
