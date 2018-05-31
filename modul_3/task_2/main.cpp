#include <iostream>
#include <vector>
#include <queue>
#include <list>


class IGraph {
public:
    virtual ~IGraph() {}
    virtual void AddEdge(int from, int to) = 0;
    virtual int VerticesCount() const  = 0;
    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

class CListGraph : public IGraph {
public:
    CListGraph(int n);
    CListGraph(IGraph* graph);
    ~CListGraph(){}

    void AddEdge(int from, int to);

    std::vector<int> GetNextVertices(int vertex) const;
    std::vector<int> GetPrevVertices(int vertex) const;

    int VerticesCount() const { return  _vertex_count; };

private:
    std::vector<std::list<int>> _adjacency;
    int _vertex_count;
};


CListGraph::CListGraph(int n)
        : _vertex_count(n)
{
    _adjacency.resize(n);
    for (int i = 0; i < n; ++i) {
        _adjacency.resize(0);
    }
}

CListGraph::CListGraph(IGraph *graph) {
    _vertex_count = graph->VerticesCount();
    _adjacency.resize(_vertex_count);
    for (int i = 0; i < _vertex_count; ++i) {
        _adjacency.resize(0);
    }
    for (int i = 0; i < _vertex_count; ++i) {
        std::vector <int> next = graph->GetNextVertices(i);
        for (int j = 0; j < next.size(); ++j) {
            _adjacency[i].push_front(next[j]);
        }
    }
}


void CListGraph::AddEdge(int from, int to) {
    _adjacency[from].push_front(to);
    _adjacency[to].push_front(from);
}

std::vector<int> CListGraph::GetNextVertices(int vertex) const {
    std::vector<int> answer;
    for (auto it = _adjacency[vertex].begin(), end = _adjacency[vertex].end(); it != end; ++it) {
        answer.push_back(*it);
    }
    return answer;
}

std::vector<int> CListGraph::GetPrevVertices(int vertex) const {
    std::vector<int> answer;
    for (int i = 0; i < _adjacency.size(); ++i) {
        for (auto it = _adjacency[i].begin(), end = _adjacency[i].end(); it != end; ++it) {
            if (*it == vertex) {
                answer.push_back(i);
                continue;
            }
        }
    }
    return answer;
}



//////////// ПОДСЧЕТ КОЛИЧЕСТВА ПУТЕЙ ///////////////

int countShortestWay(const IGraph& graph, int from, int to){
	std::vector<std::pair<int, int>> states(graph.VerticesCount());
	std::queue<int> queue;

	queue.push(from);
	states[from].second = 1;

	while (!queue.empty()){
		int vert = queue.front();
		queue.pop();

		std::vector<int> nextVert = graph.GetNextVertices(vert);

		for (auto i : nextVert){
			if (!states[i].second){
				queue.push(i);
				states[i].first = states[vert].first + 1;
				states[i].second = states[vert].second;
			}
			else if (states[i].first == states[vert].first + 1){
				states[i].second += states[vert].second;
			}
		}
	}
	return states[to].second;
}


int main()
{
	int v, n;
	std::cin >> v >> n;
	CListGraph graph(v);
	for (int i = 0; i < n; ++i){
		int f, t;
		std::cin >> f >> t;
		graph.AddEdge(f, t);
	}

	int u, w;
	std::cin >> u >> w;

	std::cout << countShortestWay(graph, u, w);
}