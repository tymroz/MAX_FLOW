#include <iostream>
#include <vector>
#include <bitset>
#include <random>
#include <functional>
#include <queue>
#include <limits>
#include <fstream>
#include <algorithm>

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

    bool bfsLevelGraph(int source, int target, std::vector<int>& level) {
        std::fill(level.begin(), level.end(), -1);
        level[source] = 0;
        std::queue<int> q;
        q.push(source);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : edges[u]) {
                if (level[v] == -1 && capacity[u][v] > flow[u][v]) {
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        return level[target] != -1;
    }

    int dfsFlow(int u, int target, int pushedFlow, std::vector<int>& level, std::vector<int>& ptr) {
        if (u == target) {
            augmentPathCount++;
            return pushedFlow;
        }

        for (int& cid = ptr[u]; cid < edges[u].size(); ++cid) {
            int v = edges[u][cid];

            if (level[u] + 1 == level[v] && capacity[u][v] > flow[u][v]) {
                int flowToPush = std::min(pushedFlow, capacity[u][v] - flow[u][v]);
                int flowPushed = dfsFlow(v, target, flowToPush, level, ptr);

                if (flowPushed > 0) {
                    flow[u][v] += flowPushed;
                    flow[v][u] -= flowPushed;
                    //augmentPathCount++;
                    return flowPushed;
                }
            }
        }
        return 0;
    }

public:
    std::vector<std::vector<int>> edges;
    std::vector<std::vector<int>> capacity;
    std::vector<std::vector<int>> flow;

    Hypercube(int k) : k(k), augmentPathCount(0), n(1 << k) {
        edges.resize(n);
        capacity.assign(n, std::vector<int>(n, 0));
        flow.assign(n, std::vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            int hamming_i = hammingWeight(i);
            for (int j = i + 1; j < n; j++) {
                int hamming_j = hammingWeight(j);
                if (areConnected(i, j) && hamming_i < hamming_j) {
                    int weight = randomWeight(i, j);
                    edges[i].emplace_back(j);
                    edges[j].emplace_back(i); // Dodajemy krawędź w drugą stronę dla przepływu zwrotnego
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

    int dinicAlgorithm(int source, int target) {
        int maxFlow = 0;
        std::vector<int> level(n), ptr(n);

        while (bfsLevelGraph(source, target, level)) {
            std::fill(ptr.begin(), ptr.end(), 0);
            while (int pushed = dfsFlow(source, target, INF, level, ptr)) {
                maxFlow += pushed;
            }
        }
        return maxFlow;
    }

    int getAugmentingPathsCount() const {
        return augmentPathCount;
    }

};
