#ifndef IGRAPH_CSETGRAPH_H
#define IGRAPH_CSETGRAPH_H

#include "IGraph.h"
#include <vector>
#include <unordered_set>  


class CSetGraph : public IGraph {
public:
    CSetGraph(int n);
    CSetGraph(IGraph* graph);

    ~CSetGraph();

    void AddEdge(int from, int to);

    std::vector <int> GetNextVertices(int vertex) const;
    std::vector <int> GetPrevVertices(int vertex) const;

    int VerticesCount() const { return  _vertex_count; }

    void print_graph();

private:
    int _vertex_count;
    std::vector<std::unordered_set<int>> graph_set;
};


#endif //IGRAPH_CSETGRAPH_H