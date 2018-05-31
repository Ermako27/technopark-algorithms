#ifndef CMATRIXGRAPH_H
#define CMATRIXGRAPH_H

#include <vector>
#include "IGraph.h"


class CMatrixGraph : public IGraph {
public:
    CMatrixGraph(int n);
    CMatrixGraph(IGraph* graph);
    ~CMatrixGraph();

    void AddEdge(int from, int to);

    std::vector<int> GetNextVertices(int vertex) const;
    std::vector<int> GetPrevVertices(int vertex) const;

    int VerticesCount() const { return  _vertex_count; }

    void printMatrix();

    std::vector<std::vector<int> > _adjency_matrix;
    int _vertex_count;
};



#endif //IGRAPH_CMATRIXGRAPH_H