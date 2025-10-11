#include "Graph.h"
#include <cassert>
#include <iostream>

template <typename T>
void print_vector(const std::vector<T>& v) {
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n";
}

int main() {
    /*
    Graph g1("Grafos/grafo_pequeno.txt", false);
    Graph g2("Grafos/grafo_pequeno.txt", true);

    g1.print();
    g2.print();
    */

    WeightedGraph wg1("Grafos/grafo_cpesos2.txt", false);
    //WeightedGraph wg2("Grafos/grafo_cpesos2.txt", true);

    int s = 1;
    std::vector<double> dists;
    std::vector<int> parents;
    wg1.dijkstra(s, dists, parents, false);

    std::cout << "dists:\n";
    print_vector(dists);
    std::cout << "parents:\n";
    print_vector(parents);

    print_vector(wg1.reconstruct_path(parents, 1));
    print_vector(wg1.reconstruct_path(parents, 2));
    print_vector(wg1.reconstruct_path(parents, 4));

    return 0;
}