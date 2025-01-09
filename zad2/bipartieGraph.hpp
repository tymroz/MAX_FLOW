#include <iostream>
#include <vector>
#include <random>

class BipartieGraph{
private:
    int k;
    int i;
    int n;
    std::vector<std::vector<int>> edges;

    void generateEdges() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, n - 1);

        for (int v = 0; v < n; v++) {
            for (int j = 0; j < i; j++) {
                int u;
                do {
                    u = dis(gen);
                } 
                while (edges[v][u] == 1);
                edges[v][u] = 1;
            }
        }
    }

public:
    BipartieGraph(int k, int i) : k(k), i(i), n(1 << k) {
        edges.assign(n, std::vector<int>(n, 0));
        generateEdges();
    }

    void displayGraph() {
        std::cout << "Wierzcholki V1: ";
        for (int v = 0; v < n; v++) {
            std::cout << v << " ";
        }
        std::cout << std::endl;

        std::cout << "Wierzcholki V2: ";
        for (int v = 0; v < n; v++) {
            std::cout << v << " ";
        }
        std::cout << std::endl;

        std::cout << "Krawedzie:" << std::endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++){
                if(edges[i][j] == 1){
                    std::cout << "(" << i << ", " << j << ")" << std::endl;
                }
            }
        }
    }
};