#ifndef CARCGRAPH_H
#define CARCGRAPH_H

#include <vector>
#include <utility>
#include "IGraph.h"

class CArcGraph : public IGraph {
public:
    CArcGraph(int n);
    CArcGraph(IGraph* graph);
    ~CArcGraph();

    void AddEdge(int from, int to);

    int VerticesCount() const { return _vertex_count; };

    std::vector<int> GetNextVertices(int vertex) const;
    std::vector<int> GetPrevVertices(int vertex) const;

private:
    std::vector<std::pair<int, int>> graph_list;
    int _vertex_count;
};


#endif /* CARCGRAPH_H */