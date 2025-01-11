#include "hyperCube.hpp"
#include <fstream>
#include <chrono>

int main(int argc, char* argv[]) {
    int k;
    bool printFlow = false;
    std::string filename = "test.mod";
    bool glpk = false;
    int repetitions = 5;
    std::vector<int> flows;
    std::vector<int> times;
    std::vector<int> augmentingPaths;

    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "--size" && i + 1 < argc) {
            k = atoi(argv[i+1]);
        } else if (std::string(argv[i]) == "--printFlow") {
            printFlow = true;
        } else if (std::string(argv[i]) == "--glpk") {
            filename = argv[i+1];
            glpk = true;
        }
    }

    //Hypercube hypercube(k);
    //hypercube.printEdges();

    for (int rep = 0; rep < repetitions; rep++) {
        Hypercube hypercube(k);
        int s = 0;
        int t = (1 << k) - 1;

        auto start = std::chrono::high_resolution_clock::now();
        int maxFlow = hypercube.dinicAlgorithm(s, t);
        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        int time = duration.count();

        int au = hypercube.getAugmentingPathsCount();

        flows.push_back(maxFlow);
        times.push_back(time);
        augmentingPaths.push_back(au);

        if (printFlow) {
            hypercube.printFlow();
        }
    }

    double avgFlow = 0;
    double avgTime = 0;
    double avgAugmentingPaths = 0;

    for (int i = 0; i < repetitions; ++i) {
        avgFlow += flows[i];
        avgTime += times[i];
        avgAugmentingPaths += augmentingPaths[i];
    }

    avgFlow /= repetitions;
    avgTime /= repetitions;
    avgAugmentingPaths /= repetitions;

    std::ofstream plik("k" + std::to_string(k) + ".txt");
    plik << "k: " << k << std::endl;
    plik << "Sredni maksymalny przeplyw: " << avgFlow << std::endl;
    plik << "Sredni czas dzialania programu [microsec]: " << avgTime << std::endl;
    plik << "Srednia liczba sciezek powiekszajacych: " << avgAugmentingPaths << std::endl;

    plik.close();
    
    return 0;
}