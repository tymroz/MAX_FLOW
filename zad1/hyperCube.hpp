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
    std::vector<std::vector<int>> edges;
    std::vector<std::vector<int>> capacity;

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

public:
    Hypercube(int k) : k(k) {
        edges.resize(1 << k); // 2^k wierzchołków
        capacity.assign(1 << k, std::vector<int>(1 << k, 0));
        flow.assign(1 << k, std::vector<int>(1 << k, 0));
        for (int i = 0; i < (1 << k); ++i) {
            int hamming_i = hammingWeight(i);
            for (int j = i + 1; j < (1 << k); ++j) {
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
        for (int i = 0; i < (1 << k); ++i) {
            std::cout << "Wierzcholek " << i << " (binarne: " << std::bitset<17>(i) << "):\n";
            for (int v : edges[i]) {
                std::cout << "  --> Wierzcholek " << v << " (binarne: " << std::bitset<17>(v) << "), Waga: " << capacity[i][v] << "\n";
            }
        }
    }

    int edmondsKarp(int source, int target) {
        
    }
};
