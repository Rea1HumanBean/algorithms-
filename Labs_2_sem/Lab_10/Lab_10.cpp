#include <stack>
#include <iostream>
#include <string>
#include <vector>

class Graph {
    int q_Vert;
    std::vector<std::vector<int>> adjList;

    void addVertex(int src, int dest) {
        adjList[src].push_back(dest);
    }

public:
    Graph(int rows_cols) : q_Vert(rows_cols) {
        adjList.resize(q_Vert);
    }

    static Graph create(std::initializer_list<std::initializer_list<int>> data) {
        int rows_cols = data.size();
        Graph graph(rows_cols);

        int rowIndx = 0;
        for (auto row : data) {
            int colmIndx = 0;
            for (auto val : row) {
                if (val != 0) {
                    graph.addVertex(rowIndx, colmIndx);
                }
                ++colmIndx;
            }
            ++rowIndx;
        }
        return graph;
    }

    std::vector<int> algorithEuler(int startVertex) {
        std::vector<int> eulerVert;

        std::vector<int> vertDegree(q_Vert, 0);

        for (int u = 0; u < q_Vert; ++u) {
            vertDegree[u] = adjList[u].size();
        }

        std::stack<int> path;
        path.push(startVertex);

        while (!path.empty()) {
            int u = path.top();

            if (vertDegree[u] == 0) {
                eulerVert.push_back(u);
                path.pop();
            }
            else {
                bool found = false;

                for (size_t i = 0; i < adjList[u].size(); ++i) {
                    int v = adjList[u][i];

                    if (v != -1) {
                        path.push(v);
                        adjList[u].erase(adjList[u].begin() + i);
                        for (size_t j = 0; j < adjList[v].size(); ++j) {
                            if (adjList[v][j] == u) {
                                adjList[v].erase(adjList[v].begin() + j);
                                break;
                            }
                        }
                        vertDegree[u]--;
                        vertDegree[v]--;
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    path.pop();
                }
            }
        }

        return eulerVert;
    }
};

int main() {
    setlocale(LC_ALL, "ru");

    auto graph = Graph::create({
        //A  B  C  D  E 
         {0, 1, 1, 0, 0},//A
         {1, 0, 1, 0, 0},//B
         {1, 1, 0, 1, 1},//C
         {0, 0, 1, 0, 1},//D
         {0, 0, 1, 1, 0} //E
        });

    std::vector<int> vert = graph.algorithEuler(0);

    for (int c : vert) {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    return 0;
}