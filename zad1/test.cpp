#include "hyperCube.hpp"
#include <fstream>
#include <chrono>

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
    //hypercube.printEdges();

    auto start = std::chrono::high_resolution_clock::now();
    int maxFlow = hypercube.edmondsKarp(0, (1 << k) - 1);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    int time = duration.count();
    
    int au = hypercube.getAugmentingPathsCount();

    std::cout << "Maksymalny przeplyw: " << maxFlow << std::endl; 
    if (printFlow) {
        hypercube.printFlow();
    }

    std::cerr << "Liczba sciezek powiekszajacych: " << au << std::endl; 
    std::cerr << "Czas: " << time << std::endl; 

    std::ofstream plik("dane.txt");
    plik << k << std::endl;
    plik << maxFlow << std::endl;
    plik << time << std::endl;
    plik << au << std::endl;

   plik.close();
    
    return 0;
}