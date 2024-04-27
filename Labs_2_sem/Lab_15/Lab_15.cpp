#include <iostream>
#include <vector>
#include <set>

enum color {
	RED,
	GREEN,
	BLUE,
	WHITE,
	NONE
};

struct Vertex {
	int dest;
	color clr;
	Vertex(int _dest) : dest(_dest), clr(color::NONE) {}
};

template <size_t Rows_Colm>
class Graph {
	int q_Vert;
	std::vector <std::vector<Vertex>> adjList;
	std::vector<bool> visited;

	void addVertex(int src, int dest) {
		adjList[src].emplace_back(Vertex(dest));
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
				if (val != 0)
					graph.addVertex(rowIndx, colmIndx);
				++colmIndx;
			}
			++rowIndx;
		}
		return graph;
	}

	void decorateGraph() {
		std::vector<color> colors(q_Vert, color::WHITE);

		for (int i = 0; i < q_Vert; ++i) {
			std::set<color> neighborColors;

			for (auto v : adjList[i]) {
				if (colors[v.dest] != color::NONE) {
					neighborColors.insert(colors[v.dest]);
				}
			}

			for (int c = 0; c <= 3; ++c) {
				if (!neighborColors.count(static_cast<color>(c))) {
					colors[i] = static_cast<color>(c);
					break;
				}
			}
		}

		for (int i = 0; i < q_Vert; ++i) {
			for (auto& v : adjList[i]) {
				v.clr = colors[v.dest];
			}
		}
	}

	void printGraph() {
		std::vector<std::string> colorNames = { "RED", "GREEN", "BLUE", "WHITE", "NONE" };

		for (int i = 0; i < q_Vert; ++i) {
			std::cout << char('A' + i) << ':' << std::endl;
			for (auto v : adjList[i])
				std::cout << char('A' + v.dest) << " - " << colorNames[static_cast<int>(v.clr)] << std::endl;
		}
	}
};

int main() {
	setlocale(LC_ALL, "ru");

	auto graph = Graph<6>::create({
		//   A  B  C  D  E  F
			{0, 1, 1, 1, 0, 0},//A
			{1, 0, 0, 1, 1, 0},//B
			{1, 0, 0, 1, 0, 1},//C
			{1, 1, 1, 0, 0, 0},//D
			{0, 1, 0, 0, 0, 1},//E
			{0, 0, 1, 0, 1, 0},//F
		});
	graph.decorateGraph();
	graph.printGraph();

	return 0;
}