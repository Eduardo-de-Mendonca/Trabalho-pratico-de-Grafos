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

void general_tests() {
    //WeightedGraph wg1("Grafos/Grandes/grafo_W_1.txt", false, false);
    WeightedGraph wg2("Grafos/grafo_cpesos2.txt", false, false);
    
    int t = 2;
    WeightedGraph wg2_rev = wg2.reverse(false);

    std::vector<double> dists;
    std::vector<int> parents;

    wg2_rev.dijkstra(t, dists, parents, false);
    std::cout << "Dijkstra do grafo reverso a partir do vértice " << t << ":\n";
    print_vector(dists);
    print_vector(parents);

    wg2.bellman_ford(t, dists, parents);
    std::cout << "Bellman-Ford do grafo rumo ao vértice " << t << ":\n";
    print_vector(dists);
    print_vector(parents);
}

// Declarar os grafos
std::vector<std::string> graphs = {
    "Grafos/Grandes/grafo_w_1.txt",
    "Grafos/Grandes/grafo_W_2.txt",
    "Grafos/Grandes/grafo_W_3.txt",
    "Grafos/Grandes/grafo_W_4.txt",
    "Grafos/Grandes/grafo_W_5.txt"
};

/**
Escreve em um arquivo quais grafos têm peso negativo.
*/ 
void write_negative_weights() {
    std::ofstream outfile("EstudosDeCaso/analise_preliminar.txt");
    assert(outfile);

    for (int i = 0; i < graphs.size(); i++) {
        int k = i + 1;
        std::string path = graphs[i];
        WeightedGraph wg(path, false, false);
        bool hng = wg.has_negative_weight();

        outfile << "Grafo " << k << "\n";
        outfile << "has_negative_weight(): " << hng << "\n\n";
    }
}

int main() {
    general_tests();

    return 0;
}
