
#include <iostream>
#include <string>
#include <vector>
#include <queue>

enum direction {
	direction_NONE = 0,
	direction_AB = 1,
	direction_BOTH = 2,
};

struct Vertex {
	int dest;
	int weight;
	direction Path;
};

template <size_t Rows_Colm>
class Graph {
	int q_Vert;
	std::vector<std::vector<Vertex>> adjList;

	void addVertex(int src, int dest, int weight, direction _Path) {
		Vertex vert;
		vert.dest = dest;
		vert.weight = weight;
		vert.Path = _Path;
		adjList[src].push_back(vert);
	}


public:
	Graph() : q_Vert(Rows_Colm) {
		adjList.resize(q_Vert);
	}

	static Graph<Rows_Colm> create(std::initializer_list<std::initializer_list<std::pair<int, int>>> data) {
		Graph<Rows_Colm> graph;
		int rowIndx = 0;
		for (auto row : data) {
			int colmIndx = 0;
			for (auto val : row) {
				if (val.second != 0)
					graph.addVertex(rowIndx, colmIndx, val.first, static_cast<direction>(val.second));
				++colmIndx;
			}
			++rowIndx;
		}
		return graph;
	}

	void alghoritmBellmanFord(int src) {
		std::vector<int> VertDistance(q_Vert, INT_MAX);
		VertDistance[src] = 0;

		for (int i = 0; i < q_Vert - 1; ++i) {
			for (int j = 0; j < q_Vert; ++j) {
				for (const auto& edge : adjList[j]) {
					int v = edge.dest;
					int weight = edge.weight;
					if (VertDistance[j] != INT_MAX && VertDistance[j] + weight < VertDistance[v]) {
						VertDistance[v] = VertDistance[j] + weight;
					}
				}
			}
		}

		for (int u = 0; u < q_Vert; ++u) {
			for (const auto& edge : adjList[u]) {
				int v = edge.dest;
				int weight = edge.weight;
				if (VertDistance[u] != INT_MAX && VertDistance[u] + weight < VertDistance[v]) {
					std::cout << "Граф содержит отрицательный цикл\n";
					return;
				}
			}
		}

		std::cout << "Кратчайшие расстояния от вершины " << src + 1 << ":\n";
		for (int i = 0; i < q_Vert; ++i) {
			std::cout << "До вершины " << i + 1 << ": " << VertDistance[i] << std::endl;
		}
	}
};

int main() {
	setlocale(LC_ALL, "ru");

	auto graph = Graph<7>::create({
		//	     A       B       C       D       E       F       G
				{{0, 0}, {1, 0}, {1, 1}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},//A
				{{1, 0}, {0, 0}, {2, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},//B
				{{1, 0}, {2, 1}, {0, 0}, {4, 2}, {5,1}, {0, 0}, {0, 0}},//C
				{{0, 0}, {0, 0}, {4, 2}, {0, 0}, {0, 0}, {7, 1}, {14,1}},//D
				{{0, 0}, {0, 0}, {5, 0}, {0, 0}, {0, 0}, {-4,1}, {-5,1}},//E
				{{0, 0}, {0, 0}, {0, 0}, {7, 0}, {-4,0}, {0, 0}, {10,1}},//F
				{{0, 0}, {0, 0}, {0, 0}, {14,0}, {-5,0}, {10,0}, {0, 0}} //G
		});

	graph.alghoritmBellmanFord(0);

	return 0;
}