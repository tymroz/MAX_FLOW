#include "bipartieGraph.hpp"

int main(int argc, char* argv[]) {
    int k;
    int i;
    bool printMatching = false;

    for (int j = 1; j < argc; j++) {
        if (std::string(argv[j]) == "--size" && j + 1 < argc) {
            k = atoi(argv[j+1]);
        } else if (std::string(argv[j]) == "--degree") {
            i = atoi(argv[j+1]);
        } else if (std::string(argv[j]) == "--printMatching") {
            printMatching = true;
        }
    }

    BipartieGraph graph(k, i);
    graph.displayGraph();
    
    return 0;
}