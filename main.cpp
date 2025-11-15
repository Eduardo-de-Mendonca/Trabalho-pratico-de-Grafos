#include "Graph.h"
#include <cassert>
#include <iostream>
#include <limits>
#include <chrono>
#include <fstream>
#include <random>

template <typename T>
void print_vector(const std::vector<T>& v) {
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n";
}

auto time_now() {
    return std::chrono::steady_clock::now();
}

double time_elapsed(std::chrono::steady_clock::time_point start, std::chrono::steady_clock::time_point end) {
    return std::chrono::duration<double>(end - start).count(); // seconds
}

int main() {
    WeightedGraph wg1("Grafos/grafo_com_pesos.txt", true, false);
    WeightedGraph wg2("Grafos/grafo_com_pesos.txt", false, false);
    WeightedGraph wg3("Grafos/grafo_cpesos2.txt", false, false);

    wg1.print();
    wg2.print();
    wg3.print();

    std::vector<double> dists;
    std::vector<int> parents;

    wg3.dijkstra(1, dists, parents, false);
    print_vector(dists);

    return 0;
}
