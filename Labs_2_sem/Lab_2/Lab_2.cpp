#include <iostream>
#include <vector>
#include <queue>

struct Vertex {
	int dest;
	int weight;
};

template <size_t Rows_Colm>
class Graph {
	int q_Vert;
	std::vector <std::vector<Vertex>> adjList;

	void addVertex(int src, int dest, int weight) {
		Vertex vert;
		vert.dest = dest;
		vert.weight = weight;
		adjList[src].push_back(vert);
	}
public:
	Graph() : q_Vert(Rows_Colm) {
		adjList.resize(q_Vert);
	}

	static Graph<Rows_Colm> create(std::initializer_list<std::initializer_list<int>> data) {
		Graph <Rows_Colm> graph;
		int rowIndx = 0;
		for (auto row : data) {
			int colmIndx = 0;
			for (auto val : row) {
				if (val != 0)
					graph.addVertex(rowIndx, colmIndx, val);
				++colmIndx;
			}
			++rowIndx;
		}
		return graph;
	}

	void printGraph() {
		for (int i = 0; i < q_Vert; i++) {
			std::cout << "Список смежности вершины " << i + 1 << ": ";
			for (const auto& edge : adjList[i]) {
				std::cout << edge.dest + 1 << " ";
			}
			std::cout << std::endl;
		}
	}

	std::vector<int> findShortestPath(int _numberVert) {
		std::vector<bool> visited(q_Vert, false);
		std::vector<int> path(q_Vert, INT_MAX);
		std::queue<int> q;

		q.push(_numberVert);
		path[_numberVert] = 0;
		visited[_numberVert] = true;

		while (!q.empty()) {
			int v = q.front();
			q.pop();

			for (const auto& adjVertex : adjList[v]) {
				if (!visited[adjVertex.dest]) {
					q.push(adjVertex.dest);
					visited[adjVertex.dest] = true;
					path[adjVertex.dest] = path[v] + 1;
				}
			}
		}
		return path;
	}
};


int main() {
	setlocale(LC_ALL, "ru");

	auto graph = Graph<9>::create({
		{0, 1, 1, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 1, 1, 0, 0, 0, 0},
		{1, 0, 0, 1, 0, 0, 0, 0, 0},
		{0, 1, 1, 0, 1, 0, 0, 0, 0},
		{0, 1, 0, 1, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0 ,1},
		{0, 0, 0, 0, 0, 0, 0, 1, 0}
		});

	int nv = 0;
	std::vector<int> path = graph.findShortestPath(nv);
	for (int i = 0; i < path.size(); i++) {
		if (path[i] != nv && path[i] != INT_MAX)
			std::cout << "Кратчайщий путь от " << nv << " до " << (i + 1) << " составляет " << path[i] << std::endl;
	}
	return 0;
}