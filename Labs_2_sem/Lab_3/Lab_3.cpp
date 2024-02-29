#include <iostream>
#include <vector>
#include <queue>
#include <limits> 

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
				if(val != 0)
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
					std::cout  << edge.dest + 1 <<" ";
			}
			std::cout << std::endl;
		}
	}
	void BFS(int start_Vertex, std::vector<bool>& visited) {
		std::queue<int> q;
		q.push(start_Vertex);
		visited[start_Vertex] = true;

		while (!q.empty()) {
			int v = q.front();
			q.pop();
			std::cout << v + 1 << " "; 

			for (const auto& adjVertex : adjList[v]) {
				if (!visited[adjVertex.dest]) {
					q.push(adjVertex.dest);
					visited[adjVertex.dest] = true;
				}
			}
		}
		std::cout << std::endl;
	}

	void findConnectedComponents() {
		std::vector<bool> visited(q_Vert, false);

		std::cout << "Компоненты связности:\n";
		for (int v = 0; v < q_Vert; ++v) {
			if (!visited[v]) {
				BFS(v, visited);
			}
		}
	}
};


int main() {
	setlocale(LC_ALL, "ru");

	auto graph = Graph<9>::create({
		{0, 1, 6, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 3, 9, 0, 0, 0, 0},
		{6, 0, 0, 2, 0, 0, 0, 0, 0},
		{0, 3, 2, 0, 2, 0, 0, 0, 0},
		{0, 9, 0, 2, 0, 3, 0, 0, 0},
		{0, 0, 0, 0, 3, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0 ,5},
		{0, 0, 0, 0, 0, 0, 0, 5, 0}
		});


	graph.printGraph();
	graph.findConnectedComponents();
	return 0;
}
