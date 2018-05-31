#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <queue>  

#define INF 1000000

class IGraph {
public:
    virtual ~IGraph() {}
    virtual void AddEdge(int from, int to, int weight) = 0;
    virtual int VerticesCount() const  = 0;
    virtual std::vector<std::pair<int, int>> GetNextVertices(int vertex) const = 0;
    virtual std::vector<std::pair<int, int>> GetPrevVertices(int vertex) const = 0;
};


class CListGraph : public IGraph {
public:
    CListGraph(int n);
    CListGraph(IGraph* graph);
    ~CListGraph(){}

    void AddEdge(int from, int to, int weight);

    std::vector<std::pair<int, int>> GetNextVertices(int vertex) const;
    std::vector<std::pair<int, int>> GetPrevVertices(int vertex) const;

    int VerticesCount() const { return  _vertex_count; };

private:
    std::vector<std::list<std::pair<int, int>>> _adjacency;
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
        std::vector<std::pair<int, int>> next = graph->GetNextVertices(i);
        for (int j = 0; j < next.size(); ++j) {
            _adjacency[i].push_front(next[j]);
        }
    }
}


void CListGraph::AddEdge(int from, int to, int weight) {
    _adjacency[from].push_front(std::make_pair(to, weight));
    _adjacency[to].push_front(std::make_pair(from, weight));
}

std::vector<std::pair<int, int>> CListGraph::GetNextVertices(int vertex) const {
    std::vector<std::pair<int, int>> answer;
    for (auto it = _adjacency[vertex].begin(), end = _adjacency[vertex].end(); it != end; ++it) {
        answer.push_back(*it);
    }
    return answer;
}

std::vector<std::pair<int, int>> CListGraph::GetPrevVertices(int vertex) const {
    std::vector<std::pair<int, int>> answer;
    for (int i = 0; i < _adjacency.size(); ++i) {
        for (auto it = _adjacency[i].begin(), end = _adjacency[i].end(); it != end; ++it) {
            if (it->first == vertex) {
                answer.push_back(*it);
                continue;
            }
        }
    }
    return answer;
}

//////////// Алгоритм дейкстры ////////////////////////////////


int deikstra(const IGraph& graph, int from, int to) {
    // содержит длины путей до to
    std::vector<int> path(graph.VerticesCount(), INF);
    path[from] = 0;
    //хранит пары (расстояние, номер вершины)
    std::priority_queue<std::pair<int, int>> queue;
    queue.emplace(std::make_pair(0, from));
    while (!queue.empty()) {
        // получаем вершину с наименьшим расстоянием
        int v = queue.top().second;
        int prev_d = -queue.top().first;
        queue.pop();

        if (prev_d > path[v])  
            continue;

        std::vector<std::pair<int, int>> paths = graph.GetNextVertices(v);
        for (auto c : paths) {
            int t = c.first;
            int len = c.second;
            if (path[t] > path[v] + len) {
                path[t] = path[v] + len;
                queue.emplace(std::make_pair(-path[t], t));
            }
        }
    }
    return path[to];
}

int main() {
    int n = 0;
    int m = 0;
    std::cin >> n >> m;
    CListGraph graph(n);
    for (int i = 0; i < m; i++) {
        int s = 0;
        int t = 0;
        int w = 0;
        std::cin >> s >> t >> w;
        graph.AddEdge(s, t, w);
    }
    int from = 0;
    int to = 0;
    std::cin >> from >> to;

    std::cout << deikstra(graph, from, to);

    return 0;
}

