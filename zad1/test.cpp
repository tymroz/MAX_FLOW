#include "hyperCube.hpp"

int main() {
    int k;
    std::cout << "Podaj liczbe bitow k: ";
    std::cin >> k;

    Hypercube hypercube(k);
    //std::cout << "1\n";
    hypercube.printEdges();
    //int maxFlow = hypercube.edmondsKarp(0, (1 << k) - 1);
    //std::cout << "Maksymalny przeplyw: " << maxFlow << std::endl; 
    
    return 0;
}