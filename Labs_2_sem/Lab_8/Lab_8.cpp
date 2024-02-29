#include <iostream>
#include <vector>
#include <queue>
#include <limits> 

struct Vertex {
	int dest;
	int weight;
	bool visited;
};

template <size_t Rows_Colm>
class Graph {
	int q_Vert;
	std::vector <std::vector<Vertex>> adjList;
	std::vector<bool> visited;

	void addVertex(int src, int dest, int weight) {
		Vertex vert;
		vert.visited = false;
		vert.dest = dest;
		vert.weight = weight;
		adjList[src].push_back(vert);
	}
public:
	Graph() : q_Vert(Rows_Colm) {
		adjList.resize(q_Vert);
		visited.resize(q_Vert);
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
	void shortestPath_Dijkstra(int start_Vertex) {
		std::vector<int> distance_Vert(q_Vert, std::numeric_limits<int>::max());
		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

		distance_Vert[start_Vertex] = 0;
		pq.push({ 0, start_Vertex });

		while (!pq.empty()) {
			int currentVertex = pq.top().second;
			int currentDistance = pq.top().first;
			pq.pop();

			if (currentDistance > distance_Vert[currentVertex])
				continue;

			for (const auto& adjVertex : adjList[currentVertex]) {
				int newDistance = currentDistance + adjVertex.weight;
				if (newDistance < distance_Vert[adjVertex.dest]) {
					distance_Vert[adjVertex.dest] = newDistance;
					pq.push({ newDistance, adjVertex.dest });
				}
			}
		}
		for (int i = 0; i < q_Vert; ++i) {
			std::cout << "Кратчайшее расстояние до вершины " << i + 1 << ": " << distance_Vert[i] << std::endl;
		}
	}
};


int main() {
	setlocale(LC_ALL, "ru");

	auto graph = Graph<6>::create({
		{0, 1, 6, 0, 0, 0},
		{1, 0, 0, 3, 9, 0},	
		{6, 0, 0, 2, 0, 0},
		{0, 3, 2, 0, 2, 0},
		{0, 9, 0, 2, 0, 3},
		{0, 0, 0, 0, 3, 0},
		});


	graph.printGraph();
	graph.shortestPath_Dijkstra(0);
	return 0;
}