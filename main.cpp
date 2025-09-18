#include "Graph.h"

int main() {
    Graph g1("Grafos/grafo_pequeno.txt", false);
    g1.print();
    Graph g2("Grafos/grafo_pequeno.txt", true);
    g2.print();

    g1.write_output("vetor_adj.txt");
    g2.write_output("matriz_adj.txt");

    g1.write_bfs(5, "bfs_vetor_adj.txt");
    g2.write_bfs(5, "bfs_matriz_adj.txt");

    g1.write_dfs(5, "dfs_vetor_adj.txt");
    g2.write_dfs(5, "dfs_matriz_adj.txt");
}
