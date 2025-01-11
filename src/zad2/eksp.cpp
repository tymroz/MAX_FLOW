    #include "bipartieGraph.hpp"
    #include <chrono>
    #include <string>

    int main(int argc, char* argv[]) {
        int k;
        int i;

        for (int j = 1; j < argc; j++) {
            if (std::string(argv[j]) == "--size" && j + 1 < argc) {
                k = atoi(argv[j+1]);
            } else if (std::string(argv[j]) == "--degree" && j + 1 < argc) {
                i = atoi(argv[j+1]);
            }
        }

        BipartieGraph graph(k, i);

        auto start = std::chrono::high_resolution_clock::now();
        int maxMatching = graph.hopcroftKarp();
        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        int time = duration.count();

        std::ofstream plik("k" + std::to_string(k) + "i" + std::to_string(i) + ".txt");
        plik << k << std::endl;
        plik << i << std::endl;
        plik << maxMatching << std::endl;
        plik << time << std::endl;

        plik.close();
        
        return 0;
    }