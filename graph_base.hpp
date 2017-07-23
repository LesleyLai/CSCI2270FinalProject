#ifndef GRAPH_BASE_HPP
#define GRAPH_BASE_HPP

#include <memory>
#include <unordered_set>

template<class NodeType, class EdgeType>
class GraphBase {
public:
    /// Creates an empty graph
    GraphBase() {}

    virtual ~GraphBase();

    /// Returns the number of nodes
    size_t size() {return nodes_.size();}

    /// Checks whether a node is empty or not
    bool empty() {return nodes_.empty();}

    void insertNode(std::unique_ptr<NodeType>&& node);

    //std::weak_ptr<NodeType> getNode();

private:
    std::unordered_set<std::shared_ptr<NodeType>> nodes_;
    std::unordered_set<std::shared_ptr<EdgeType>> edges_;
};

template<class NodeType, class EdgeType>
GraphBase<NodeType, EdgeType>::~GraphBase() {}

template<class NodeType, class EdgeType>
void GraphBase<NodeType, EdgeType>::insertNode(std::unique_ptr<NodeType>&& node)
{
    nodes_.push(node);
}

//template<class NodeType, class EdgeType>
//std::weak_ptr<NodeType> GraphBase<NodeType, EdgeType>::getNode()
//{

//}

#endif // GRAPH_BASE_HPP
