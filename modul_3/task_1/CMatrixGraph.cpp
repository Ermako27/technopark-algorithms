#include <set>
#include "CMatrixGraph.h"

#include <iostream>
#include <set>
#include "CMatrixGraph.h"


CMatrixGraph::CMatrixGraph(int n)
:   _vertex_count(n) {
	std::vector<int> tmp;
    for (int i = 0; i < n; ++i) {
    	for (int j = 0; j < n; ++j){
    		tmp.push_back(0);
    	}
        _adjency_matrix.push_back(tmp);
    }
}

CMatrixGraph::CMatrixGraph(IGraph *graph) {
    _vertex_count = graph->VerticesCount();
    std::vector<int> tmp;

    for (int i = 0; i < _vertex_count; ++i) {
    	for (int j = 0; j < _vertex_count; ++j){
    		tmp.push_back(0);
    	}
        _adjency_matrix.push_back(tmp);
    }

    for (int i = 0; i < _vertex_count; ++i) {
        std::vector<int> next = graph->GetNextVertices(i);
        for (int j = 0; j < next.size(); ++j) {
            _adjency_matrix[i][next[j]] = 1;
        }
    }
}


CMatrixGraph::~CMatrixGraph() {
    for (int i = 0; i < _vertex_count; ++i) {
        _adjency_matrix[i].clear();
    }
    _adjency_matrix.clear();
}


void CMatrixGraph::AddEdge(int from, int to) {
    _adjency_matrix[from][to] = 1;
}

std::vector<int> CMatrixGraph::GetNextVertices(int vertex) const {
    std::vector<int> answer;
    for (int i = 0; i < _vertex_count; ++i) {
        if ( _adjency_matrix[vertex][i] ) {
            answer.push_back(i);
        }
    }
    return answer;
}

std::vector<int> CMatrixGraph::GetPrevVertices(int vertex) const {
    std::vector <int> answer;
    for (int i = 0; i < _vertex_count; ++i) {
        if ( _adjency_matrix[i][vertex] ) {
            answer.push_back(i);
        }
    }
    return answer;
}

void CMatrixGraph::printMatrix() {
	for (int i = 0; i < _vertex_count; ++i){
		for (int j = 0; j < _vertex_count; ++j){
			std::cout << _adjency_matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
}
