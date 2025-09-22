#include "Graph.h"
#include <iostream>

int main() {
    Graph g1("Grafos/grafo_pequeno.txt", false);
    g1.print();
    Graph g2("Grafos/grafo_pequeno2.txt", true);
    g2.print();

    g1.write_output("Output/g1.txt");
    g2.write_output("Output/g2.txt");

    g1.write_bfs(5, "Output/bfs_g1.txt");
    g2.write_bfs(5, "Output/bfs_g2.txt");

    g1.write_dfs(5, "Output/dfs_g1.txt");
    g2.write_dfs(5, "Output/dfs_g2.txt");

    //std::cout << g1.diameter() << "\n";
    //std::cout << g2.diameter() << "\n";
}
