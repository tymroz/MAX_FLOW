#include <iostream>
#include <vector>
#include <bitset>
#include <random>
#include <functional>
#include <queue>
#include <limits>

int INF = std::numeric_limits<int>::max();

int hammingWeight(int x) {
    return std::bitset<17>(x).count();
}

int zeroCount(int x, int k) {
    return k - hammingWeight(x);
}

class Hypercube {
private:
    int k;
    int n;
    int augmentPathCount;

    bool areConnected(int i, int j) {
        int diff = i ^ j;
        return hammingWeight(diff) == 1; 
    }

    int randomWeight(int i, int j) {
        int hamming_i = hammingWeight(i);
        int zero_i = zeroCount(i, k);
        int hamming_j = hammingWeight(j);
        int zero_j = zeroCount(j, k);
        int l = std::max({hamming_i, zero_i, hamming_j, zero_j});
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, (1 << l));
        return dis(gen);
    }

    bool bfs(int source, int target, std::vector<int>& parent) {
        std::priority_queue<std::pair<int, int>> q;
        std::vector<bool> visited(n);
        q.push({INF, source});
        parent[source] = -2;
        visited[source] = true;

        while (!q.empty()) {
            auto [flowLeft, u] = q.top();
            q.pop();
            for (int v : edges[u]) {
                if (!visited[v] && capacity[u][v] > flow[u][v]) {
                    parent[v] = u;
                    visited[v] = true;
                    int newFlow = std::min(flowLeft, capacity[u][v] - flow[u][v]);
                    q.push({newFlow, v});
                    if (v == target) {
                        augmentPathCount++;
                        return true;
                    }
                }
            }
        }
        return false;
    }

public:
    std::vector<std::vector<int>> edges;
    std::vector<std::vector<int>> capacity;
    std::vector<std::vector<int>> flow;

    Hypercube(int k) : k(k), augmentPathCount(0), n(1 << k) {
        edges.resize(n);
        capacity.assign(n, std::vector<int>(n, 0));
        flow.assign(n, std::vector<int>(n, 0));
        for (int i = 0; i < (n); i++) {
            int hamming_i = hammingWeight(i);
            for (int j = i + 1; j < (n); j++) {
                int hamming_j = hammingWeight(j);
                if (areConnected(i, j) && hamming_i < hamming_j) {
                    int weight = randomWeight(i, j);
                    edges[i].emplace_back(j);
                    capacity[i][j] = weight;
                }
            }
        }
    }

    void printEdges() const {
        for (int i = 0; i < (n); i++) {
            std::cout << "Wierzcholek " << i << " (binarne: " << std::bitset<17>(i) << "):\n";
            for (int v : edges[i]) {
                std::cout << "  --> Wierzcholek " << v << " (binarne: " << std::bitset<17>(v) << "), Waga: " << capacity[i][v] << "\n";
            }
        }
    }

    void printFlow() const {
        std::cout << "Przeplywy:\n";
        for (int i = 0; i < 1 << k; ++i) {
            for (int v : edges[i]) {
                std::cout << i << " -> " << v << ": " << flow[i][v] << "\n";
            }
        }
    }

    int edmondsKarp(int source, int target) {
        int maxFlow = 0;
        std::vector<int> parent(n, -1);

        while (bfs(source, target, parent)) {
            int pathFlow = INF;
            for (int v = target; v != source; v = parent[v]) {
                int u = parent[v];
                pathFlow = std::min(pathFlow, capacity[u][v] - flow[u][v]);
            }

            for (int v = target; v != source; v = parent[v]) {
                int u = parent[v];
                flow[u][v] += pathFlow;
                flow[v][u] -= pathFlow;
            }
            maxFlow += pathFlow;
        }
        return maxFlow;
    }

    int getAugmentingPathsCount() const {
        return augmentPathCount;
    }

};
