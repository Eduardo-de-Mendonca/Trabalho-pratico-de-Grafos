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
    
    Graph g4 = g2.reverse(false);
    Graph g5 = g1.reverse(false);

    g1.print();
    g2.print();
    g5.print();
    //g3.print();
    //g4.print();

    //std::cout << "g1, g2: " << g1.is_equal(g2) << "\n";
    //std::cout << "g1, g5: " << g1.is_equal(g5) << "\n";
    //std::cout << "g2, g5: " << g2.is_equal(g5) << "\n";
    //std::cout << "g2, g4: " << g2.is_equal(g4) << "\n";

    std::cout << "g1: " << g1.is_undirected() << "\n";
    std::cout << "g2: " << g2.is_undirected() << "\n";
    std::cout << "g4: " << g4.is_undirected() << "\n";
    std::cout << "g5: " << g5.is_undirected() << "\n";

    return 0;
}
