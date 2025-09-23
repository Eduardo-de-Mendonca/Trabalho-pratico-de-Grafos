#include "Graph.h"
#include <cassert>

#include <iostream>
#include <fstream>
#include <tuple>

#include <ctime>

double time() {
    return static_cast<double>(std::clock()) / CLOCKS_PER_SEC; // seconds as double
}

void tests() {
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

void test_memory_graph(const std::string& filename, bool use_matrix) {
    Graph g = Graph(filename, use_matrix);
    std::cout << "Carregou: " << filename << ", " << use_matrix << "\n";
    int d = g.dist(1,2); // Só para garantir que ele não desaloca o grafo
    std::string x;
    std::cin >> x;
}

void test_memory() {
    std::string x;
    std::cout << "Sem nenhum grafo\n";
    std::cin >> x;

    test_memory_graph("Grafos/grafo_1.txt", false);
    std::cout << "Descarregou\n";
    std::cin >> x;

    test_memory_graph("Grafos/Grandes/grafo_2.txt", false);
    std::cout << "Descarregou\n";
    std::cin >> x;

    test_memory_graph("Grafos/Grandes/grafo_3.txt", false);
    std::cout << "Descarregou\n";
    std::cin >> x;

    test_memory_graph("Grafos/Grandes/grafo_4.txt", false);
    std::cout << "Descarregou\n";
    std::cin >> x;

    test_memory_graph("Grafos/Grandes/grafo_5.txt", false);
    std::cout << "Descarregou\n";
    std::cin >> x;

    test_memory_graph("Grafos/Grandes/grafo_6.txt", false);
    std::cout << "Descarregou\n";
    std::cin >> x;

    test_memory_graph("Grafos/grafo_1.txt", true);
    std::cout << "Descarregou\n";
    std::cin >> x;

    test_memory_graph("Grafos/Grandes/grafo_2.txt", true);
    std::cout << "Descarregou\n";
    std::cin >> x;

    test_memory_graph("Grafos/Grandes/grafo_3.txt", true);
    std::cout << "Descarregou\n";
    std::cin >> x;

    test_memory_graph("Grafos/Grandes/grafo_4.txt", true);
    std::cout << "Descarregou\n";
    std::cin >> x;

    test_memory_graph("Grafos/Grandes/grafo_5.txt", true);
    std::cout << "Descarregou\n";
    std::cin >> x;

    test_memory_graph("Grafos/Grandes/grafo_6.txt", true);
    std::cout << "Descarregou\n";
    std::cin >> x;
}

void test_performance_graph(const std::string& graph_file, const std::string& filename, bool use_matrix) {
    std::ofstream outfile(filename);
    assert(outfile);

    Graph g(graph_file, use_matrix);

    std::vector<int> dists;
    std::vector<int> parents;

    auto start = time();
    for (int s = 1; s <= 100; s++) {
        g.bfs(s, dists, parents);
    }
    auto end = time();

    double duration = end - start;

    double avg = duration/100;

    outfile << "100 BFS: " << duration << " segundos\n";
    outfile << "Média por BFS: " << avg << "\n";

    // Agora a DFS
    start = time();
    for (int s = 1; s <= 100; s++) {
        g.dfs(s, dists, parents);
    }
    end = time();

    duration = end - start;

    avg = duration/100;

    outfile << "100 DFS: " << duration << " segundos\n";
    outfile << "Média por DFS: " << avg << "\n\n";
}

void test_performance() {
    std::vector<std::tuple<std::string, std::string, bool>> graphs = {
        {"Grafos/grafo_1.txt", "Output/Tempos/grafo_1vetor.txt", false},
        {"Grafos/Grandes/grafo_2.txt", "Output/Tempos/grafo_2vetor.txt", false},
        {"Grafos/Grandes/grafo_3.txt", "Output/Tempos/grafo_3vetor.txt", false},
        {"Grafos/Grandes/grafo_4.txt", "Output/Tempos/grafo_4vetor.txt", false},
        {"Grafos/Grandes/grafo_5.txt", "Output/Tempos/grafo_5vetor.txt", false},
        {"Grafos/Grandes/grafo_6.txt", "Output/Tempos/grafo_6vetor.txt", false},

        {"Grafos/grafo_1.txt", "Output/Tempos/grafo_1matriz.txt", true},
        {"Grafos/Grandes/grafo_2.txt", "Output/Tempos/grafo_2matriz.txt", true},
        {"Grafos/Grandes/grafo_3.txt", "Output/Tempos/grafo_3matriz.txt", true},
        {"Grafos/Grandes/grafo_4.txt", "Output/Tempos/grafo_4matriz.txt", true},
        {"Grafos/Grandes/grafo_5.txt", "Output/Tempos/grafo_5matriz.txt", true},
        {"Grafos/Grandes/grafo_6.txt", "Output/Tempos/grafo_6matriz.txt", true}
    };

    for (auto t : graphs) {
        std::string infile = std::get<0>(t);
        std::string outfile = std::get<1>(t);
        bool use_matrix = std::get<2>(t);
        test_performance_graph(infile, outfile, use_matrix);
    }
}

int main() {
    test_performance();
}
