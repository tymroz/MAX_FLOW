#include "hyperCube.hpp"

int main(int argc, char* argv[]) {
    int k;
    bool printFlow = false;

    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "--size" && i + 1 < argc) {
            k = atoi(argv[i+1]);
        } else if (std::string(argv[i]) == "--printFlow") {
            printFlow = true;
        }
    }

    Hypercube hypercube(k);
    hypercube.printEdges();

    int maxFlow = hypercube.edmondsKarp(0, (1 << k) - 1);
    int au = hypercube.getAugmentingPathsCount();
    std::cout << "Maksymalny przeplyw: " << maxFlow << std::endl; 
    std::cout << "Liczba sciezek powiekszajacych: " << au << std::endl; 

    if (printFlow) {
        hypercube.printFlow();
    }
    
    return 0;
}