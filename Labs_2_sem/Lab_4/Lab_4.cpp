/*  Найти в заданном графе количество и состав компонент связности с помощью поиска в глубину*/
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

	void DFS(int v, std::vector<bool>& visited) {
		visited[v] = true;
		std::cout << (v + 1) << ' ';

		for (const auto& edge : adjList[v]) {
			int u = edge.dest;
			if (!visited[u]) {
				DFS(u, visited);
			}
		}
	}

	void findConnectedComponents() {
		std::vector<bool> visited(q_Vert, false);

		for (int v = 0; v < q_Vert; ++v) {
			if (!visited[v]) {
				DFS(v, visited);
				std::cout << std::endl;
			}
		}
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

	std::cout << "Компонент связности при помощи DFS :" << std::endl;
	graph.findConnectedComponents();
	return 0;
}