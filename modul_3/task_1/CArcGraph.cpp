#include "CArcGraph.h"

CArcGraph::CArcGraph(int n) :_vertex_count(n) {}

CArcGraph::CArcGraph(IGraph *graph) {
    _vertex_count = graph->VerticesCount();
    for (int i = 0; i < _vertex_count; ++i) {
        std::vector<int> next = graph->GetNextVertices(i);
        for (int j = 0; j < next.size(); ++j) {
            graph_list.push_back( std::make_pair(i, next[j]) );
        }
    }
}

CArcGraph::~CArcGraph() {
    graph_list.clear();
}

void CArcGraph::AddEdge(int from, int to) {
    graph_list.push_back(std::make_pair(from, to));
}

std::vector<int> CArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;
    for (int i = 0; i < graph_list.size(); ++i) {
        if (graph_list[i].first == vertex) {
            result.push_back(graph_list[i].second);
        }
    }
    return result;
}

std::vector<int> CArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    for (int i = 0; i < graph_list.size(); ++i) {
        if (graph_list[i].second == vertex){
            result.push_back(graph_list[i].first);
        }
    }
    return result;
}