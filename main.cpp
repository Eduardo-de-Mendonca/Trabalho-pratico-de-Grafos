#include "Graph.h"
#include <cassert>
#include <iostream>
#include <limits>
#include <chrono>
#include <fstream>


auto time_now() {
    return std::chrono::steady_clock::now();
}

double time_elapsed(std::chrono::steady_clock::time_point start, std::chrono::steady_clock::time_point end) {
    return std::chrono::duration<double>(end - start).count(); // seconds
}

template <typename T>
void print_vector(std::ofstream& outfile,const std::vector<T>& v) {
    for (int i = 0; i < v.size(); i++) {
        outfile << v[i] << " ";
    }
    outfile<< "\n";
}

void test_dist_path(const std::string& graph_file, const std::string& filename, bool use_vector_only){
    std::ofstream outfile(filename);
    assert(outfile);
    WeightedGraph wg1(graph_file, use_vector_only);
    int s = 10;
    std::vector<double> dists;
    std::vector<int> parents;

    auto start = std::chrono::high_resolution_clock::now();
    wg1.dijkstra(s, dists, parents, false);

    outfile << "dists:\n";
    outfile << "20: ";
    outfile << dists[20];
    outfile << " , ";
    outfile << "30: ";
    outfile << dists[30];
    outfile << " , ";
    outfile << "40: ";
    outfile << dists[40];
    outfile << " , ";
    outfile << "50: ";
    outfile << dists[50];
    outfile << " , ";
    outfile << "60: ";
    outfile << dists[60];
    outfile << "\n";
    
    outfile << "Caminho:\n";
    outfile << "\n";
    print_vector(outfile,wg1.reconstruct_path(parents, 20));
    std::cout << "\n";
    print_vector(outfile,wg1.reconstruct_path(parents, 30));
    std::cout << "\n";
    print_vector(outfile,wg1.reconstruct_path(parents, 40));
    std::cout << "\n";
    print_vector(outfile,wg1.reconstruct_path(parents, 50));
    std::cout << "\n";
    print_vector(outfile,wg1.reconstruct_path(parents, 60));

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = end - start;

    // --- Passo 6: Converta para Unidades Convenientes e Exiba ---
    // Converter para segundos (s) - usando double para frações de segundo
    std::chrono::duration<double> duration_s = duration; // Conversão implícita para segundos com double

    outfile << "\n--- Tempo de Execucao ---" << std::endl;
    outfile<< "Segundos:       " << duration_s.count() << " s" << std::endl;
    outfile << "\n";
}

int main() {
    /*
    Graph g1("Grafos/grafo_pequeno.txt", false);
    Graph g2("Grafos/grafo_pequeno.txt", true);

    g1.print();
    g2.print();
    */
    test_dist_path("TP2 grafos/grafo_W_4.txt","Estudo de caso(1)/grafo4(Vetor).txt",true);
    return 0;
}