#include <iostream>
#include <string>
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
	std::vector<std::pair<std::string, int>> adjEdge;

	void addVertex(int src, int dest, int weight) {
		Vertex vert;
		vert.dest = dest;
		vert.weight = weight;
		adjList[src].push_back(vert);
	}

	void addEdge(std::string name, int weight) {
		adjEdge.emplace_back(name, weight);
	};

	void removeDuplicates(std::vector<std::pair<std::string, int>>& arr) {
		std::vector<std::pair<std::string, int>> temp;

		for (int i = 0; i < arr.size(); ++i) {
			bool duplicateFound = false;
			for (int j = i + 1; j < arr.size(); ++j) {
				if (arr[i].first.size() == arr[j].first.size() &&
					arr[i].first[0] == arr[j].first[1] &&
					arr[i].first[1] == arr[j].first[0]) {

					duplicateFound = true;
					break;
				}
			}
			if (!duplicateFound) {
				temp.push_back(arr[i]);
			}
		}
		arr = temp;
	};

	void sort(std::vector<std::pair<std::string, int>>& arr) {
		for (int i = 0; i < arr.size() - 1; i++) {
			for (int j = 0; j < arr.size() - 1; j++) {
				if (arr[j].second > arr[j + 1].second) {
					std::pair<std::string, int> bubble{ arr[j] };
					arr[j] = arr[j + 1];
					arr[j + 1] = bubble;
				}
			}
		}
	};

	int findRoot(std::vector<int>& parent, int i) {
		while (parent[i] != i) {
			i = parent[i];
		}
		return i;
	};

	std::vector<std::pair<std::string, int>> kruskal() {
		std::vector<std::pair<std::string, int>> result;
		std::vector<int> parent(q_Vert);

		sort(adjEdge);

		for (int i = 0; i < q_Vert; ++i) {
			parent[i] = i;
		}

		for (const auto& edge : adjEdge) {
			int root1 = findRoot(parent, edge.first[0] - 'A');
			int root2 = findRoot(parent, edge.first[1] - 'A');

			if (root1 != root2) {
				result.push_back(edge);
				parent[root1] = root2;
			}
		}

		return result;
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
				if (val != 0) {
					graph.addVertex(rowIndx, colmIndx, val);
					std::string vert_A(1, 'A' + rowIndx);
					std::string vert_B(1, 'A' + colmIndx);
					graph.addEdge(vert_A + vert_B, val);
				}
				++colmIndx;
			}
			++rowIndx;
		}
		return graph;
	}

	void buildTree() {
		auto result = kruskal();

		for (const auto& edge : result) {
			std::cout << edge.first << ' ' << edge.second << std::endl;
		}
	};

};


int main() {
	setlocale(LC_ALL, "ru");

	auto graph = Graph<9>::create({
		//A  B  C  D  E  F  G  H  I
		 {0, 5, 3, 0, 0, 0, 9, 0, 0},//A
		 {5, 0, 0, 4, 6, 0, 0, 0, 0},//B
		 {3, 0, 0, 7, 0, 0, 0, 0, 0},//C
		 {0, 4, 7, 0, 9, 0, 0, 0, 0},//D
		 {0, 6, 0, 9, 0, 1, 0, 0, 0},//E
		 {0, 0, 0, 0, 1, 0, 4, 0, 0},//F
		 {9, 0, 0, 0, 0, 4, 0, 2, 0},//G
		 {0, 0, 0, 0, 0, 0, 2, 0 ,1},//H
		 {0, 0, 0, 0, 0, 0, 0, 1, 0} //I
		});

	graph.buildTree();

	return 0;
}