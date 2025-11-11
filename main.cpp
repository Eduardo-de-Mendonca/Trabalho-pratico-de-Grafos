#include "Graph.h"
#include <cassert>
#include <iostream>
#include <limits>
#include <chrono>
#include <fstream>
#include <random>

auto time_now() {
    return std::chrono::steady_clock::now();
}

double time_elapsed(std::chrono::steady_clock::time_point start, std::chrono::steady_clock::time_point end) {
    return std::chrono::duration<double>(end - start).count(); // seconds
}

int main() {
    Graph g1("Grafos/grafo_pequeno.txt", false, false);
    Graph g2("Grafos/grafo_pequeno.txt", true, false);
    Graph g3("Grafos/grafo_pequeno2.txt", false, false);
    Graph g4("Grafos/grafo_pequeno2.txt", true, false);

    g1.print();
    g2.print();
    g3.print();
    g4.print();

    return 0;
}
