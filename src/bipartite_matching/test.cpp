#include "bipartieGraph.hpp"
#include <chrono>
#include <string>

int main(int argc, char* argv[]) {
    int k;
    int i;
    bool printMatching = false;
    std::string filename;
    bool glpk = false;

    for (int j = 1; j < argc; j++) {
        if (std::string(argv[j]) == "--size" && j + 1 < argc) {
            k = atoi(argv[j+1]);
        } else if (std::string(argv[j]) == "--degree") {
            i = atoi(argv[j+1]);
        } else if (std::string(argv[j]) == "--printMatching") {
            printMatching = true;
        } else if (std::string(argv[j]) == "--glpk") {
            filename = argv[j+1];
            glpk = true;
        }
    }

    BipartieGraph graph(k, i);
    //graph.displayGraph();

    auto start = std::chrono::high_resolution_clock::now();
    int maxMatching = graph.hopcroftKarp();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    int time = duration.count();

    std::cout << "Maksymalne skojarzenie: " << maxMatching << std::endl;
    std::cerr << "Czas: " << time << std::endl;

    if(printMatching){
        graph.displayMatching();
    }

    if(glpk){
        graph.exportToGMPL(filename);
    }
    
    return 0;
}