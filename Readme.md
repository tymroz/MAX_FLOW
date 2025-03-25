# MAX_FLOW Project

## Project Description
The MAX_FLOW project focuses on the implementation and analysis of flow algorithms in networks. The project includes the implementation of various algorithms, such as Edmonds-Karp and Dinic, as well as experiments on specific graph structures, such as hypercubes and bipartite graphs. The goal of the project is to study the performance of these algorithms depending on graph parameters.

## Project Structure
The project is divided into several tasks, each located in a separate folder:

```
src/
├── hypercube_flow/
│   ├── hyperCube.hpp
│   ├── eksp.cpp
│   ├── test.cpp
├── bipartite_matching/
│   ├── bipartieGraph.hpp
│   ├── eksp.cpp
│   ├── test.cpp
├── dinic_hypercube/
│   ├── hyperCube.hpp
│   ├── eksp.cpp
│   ├── test.cpp
```

### Hypercube Flow
- **Files:** `hyperCube.hpp`, `flow.cpp`, `test.cpp`
- **Description:** Implementation of the Edmonds-Karp algorithm on hypercubes. Experiments include measuring maximum flow, the number of augmenting paths, and the algorithm's runtime.

### Bipartite Matching
- **Files:** `bipartieGraph.hpp`, `matching.cpp`, `test.cpp`
- **Description:** Implementation of the Hopcroft-Karp algorithm for bipartite graphs. Experiments include determining the maximum matching and exporting results to the GMPL format.

### Dinic on Hypercube
- **Files:** `hyperCube.hpp`, `dinic.cpp`, `test.cpp`
- **Description:** Implementation of the Dinic algorithm on hypercubes. Experiments analyze the algorithm's performance under various configurations.

## Requirements
- A compiler compatible with C++11 or later.
- Standard C++ libraries.
- Optionally: GLPK (for exporting data in GMPL format).

## Compilation and Execution
Each task can be compiled and executed separately. Example for the Hypercube Flow task:

```bash
g++ -o flow hypercube_flow/flow.cpp -std=c++11
./flow --size 4 --printFlow
```

## Experiments
Experiments can be run using the `flow.cpp`, `matching.cpp`, or `dinic.cpp` files in each task. Results are saved in text files, e.g., `data.txt` or `k<size>.txt`.
