#include "CSetGraph.h"

CSetGraph::CSetGraph(int n)
        : _vertex_count(n) {
    graph_set.resize(n);
}

CSetGraph::CSetGraph(IGraph *graph) {
    _vertex_count = graph->VerticesCount();
    graph_set.resize(_vertex_count);
    for (int i = 0; i < _vertex_count; ++i) {
        std::vector<int> next = graph->GetNextVertices(i);
        for (int j = 0; j < next.size(); ++j) {
            graph_set[i].insert( next[j] );
        }
    }
}

CSetGraph::~CSetGraph() {
    for (int i = 0; i < _vertex_count; ++i) {
        graph_set[i].clear();
    }
    graph_set.clear();
}

void CSetGraph::AddEdge(int from, int to) {
    graph_set[from].insert(to);
}

std::vector<int> CSetGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;
    for(auto it = graph_set[vertex].begin(); it != graph_set[vertex].end(); ++it) {
        result.push_back(*it);
    }
    return result;
}

std::vector<int> CSetGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    for (int i = 0; i < graph_set.size(); ++i) {
        if ( graph_set[i].find(vertex) != graph_set[i].end())  {
            result.push_back(i);
        }
    }
    return result;
}