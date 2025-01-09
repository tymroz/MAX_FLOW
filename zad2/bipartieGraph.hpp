#include <iostream>
#include <vector>
#include <random>
#include <limits>
#include <queue>

int INF = std::numeric_limits<int>::max();

class BipartieGraph{
private:
    int k;
    int i;
    int n;
    std::vector<std::vector<int>> edges;
    std::vector<int> pairU, pairV, dist;

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

    bool bfs() {
        std::queue<int> q;
        for (int u = 0; u < n; u++) {
            if (pairU[u] == -1) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = INF;
            }
        }
        dist[-1] = INF;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            if (dist[u] < dist[-1]) {
                for (int v = 0; v < n; v++) {
                    if (edges[u][v] == 1 && dist[pairV[v]] == INF) {
                        dist[pairV[v]] = dist[u] + 1;
                        q.push(pairV[v]);
                    }
                }
            }
        }
        return dist[-1] != INF;
    }

    bool dfs(int u) {
        if (u != -1) {
            for (int v = 0; v < n; v++) {
                if (edges[u][v] == 1 && dist[pairV[v]] == dist[u] + 1) {
                    if (dfs(pairV[v])) {
                        pairV[v] = u;
                        pairU[u] = v;
                        return true;
                    }
                }
            }
            dist[u] = INF;
            return false;
        }
        return true;
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

    int hopcroftKarp() {
        pairU.assign(n, -1);
        pairV.assign(n, -1);
        dist.assign(n + 1, 0);

        int matching = 0;
        while (bfs()) {
            for (int u = 0; u < n; u++) {
                if (pairU[u] == -1 && dfs(u)) {
                    matching++;
                }
            }
        }
        return matching;
    }

    void displayMatching() {
        std::cout << "Krawedzie nalezace do maksymalnego skojarzenia:" << std::endl;
        for (int u = 0; u < n; u++) {
            if (pairU[u] != -1) {
                std::cout << "(" << u << ", " << pairU[u] << ")" << std::endl;
            }
        }
    }
};