#ifndef CLISTGRAPH_H
#define CLISTGRAPH_H


#include "IGraph.h"
#include <list>
#include <vector>

using namespace std;

class CListGraph : public IGraph {
public:
    CListGraph(int n);
    CListGraph(IGraph* graph);
    ~CListGraph();

    void AddEdge(int from, int to);

    vector<int> GetNextVertices(int vertex) const;
    vector<int> GetPrevVertices(int vertex) const;

    int VerticesCount() const { return  _vertex_count; };

private:
    vector <list<int>> _adjacency;
    int _vertex_count;
};


#endif /* CLISTGRAPH_H */