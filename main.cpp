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
    WeightedGraph wg1("Grafos/grafo_com_pesos.txt", true, false);
    WeightedGraph wg2("Grafos/grafo_com_pesos.txt", false, false);

    wg1.print();
    wg2.print();

    return 0;
}
