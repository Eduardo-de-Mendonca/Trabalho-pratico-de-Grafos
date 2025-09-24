#include "Graph.h"
#include <cassert>

#include <iostream>
#include <fstream>
#include <tuple>

#include <chrono>

auto time_now() {
    return std::chrono::steady_clock::now();
}

double time_elapsed(std::chrono::steady_clock::time_point start, std::chrono::steady_clock::time_point end) {
    return std::chrono::duration<double>(end - start).count(); // seconds
}

/*
double time() {
    return static_cast<double>(std::clock()) / CLOCKS_PER_SEC; // seconds as double
}
*/

void print_vector(const std::vector<int>& v) {
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n";
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

void test_performance_bfs(const std::string& graph_file, const std::string& filename, bool use_matrix) {
    std::ofstream outfile(filename);
    assert(outfile);
    int no_optimization = 0;

    Graph g(graph_file, use_matrix);

    std::vector<int> dists(g.get_n() + 1);
    std::vector<int> parents(g.get_n() + 1);
    double duration, avg;

    auto start = time_now();
    for (int s = 1; s <= 100; s++) {
        g.bfs(s, dists, parents);
        no_optimization += dists[1]; // Só para garantir que ele não otimize a chamada
    }
    auto end = time_now();

    duration = time_elapsed(start, end);
    avg = duration/100;

    outfile << "100 BFS: " << duration << " segundos\n";
    outfile << "Média por BFS: " << avg << "\n\n";
    std::cout << no_optimization << "\n";
}

void test_performance_dfs(const std::string& graph_file, const std::string& filename, bool use_matrix) {
    std::ofstream outfile(filename);
    assert(outfile);
    int no_optimization = 0;

    Graph g(graph_file, use_matrix);

    std::vector<int> levels(g.get_n() + 1);
    std::vector<int> parents(g.get_n() + 1);
    double duration, avg;

    auto start = time_now();
    for (int s = 1; s <= 100; s++) {
        g.dfs(s, levels, parents);
        no_optimization += levels[1]; // Só para garantir que ele não otimize a chamada
    }
    auto end = time_now();

    duration = time_elapsed(start, end);
    avg = duration/100;

    outfile << "100 DFS: " << duration << " segundos\n";
    outfile << "Média por DFS: " << avg << "\n\n";
    std::cout << no_optimization << "\n";
}

void test_performance() {
    std::vector<std::tuple<std::string, std::string, bool>> graphs = {
        {"Grafos/grafo_1.txt", "Output/Tempos/grafo_1vetor", false},
        {"Grafos/Grandes/grafo_2.txt", "Output/Tempos/grafo_2vetor", false},
        {"Grafos/Grandes/grafo_3.txt", "Output/Tempos/grafo_3vetor", false},
        {"Grafos/Grandes/grafo_4.txt", "Output/Tempos/grafo_4vetor", false},
        {"Grafos/Grandes/grafo_5.txt", "Output/Tempos/grafo_5vetor", false},
        {"Grafos/Grandes/grafo_6.txt", "Output/Tempos/grafo_6vetor", false},

        {"Grafos/grafo_1.txt", "Output/Tempos/grafo_1matriz", true},
        {"Grafos/Grandes/grafo_2.txt", "Output/Tempos/grafo_2matriz", true},
        {"Grafos/Grandes/grafo_3.txt", "Output/Tempos/grafo_3matriz", true},
        {"Grafos/Grandes/grafo_4.txt", "Output/Tempos/grafo_4matriz", true},
        {"Grafos/Grandes/grafo_5.txt", "Output/Tempos/grafo_5matriz", true},
        {"Grafos/Grandes/grafo_6.txt", "Output/Tempos/grafo_6matriz", true}
    };

    for (auto t : graphs) {
        std::string infile = std::get<0>(t);
        std::string outfile = std::get<1>(t);
        bool use_matrix = std::get<2>(t);

        std::string bfs = "_bfs.txt";
        std::string dfs = "_dfs.txt";
        test_performance_bfs(infile, outfile + bfs, use_matrix);
        test_performance_dfs(infile, outfile + dfs, use_matrix);
    }
}

void write_parents_graph(Graph g, const std::string& filename, bool use_dfs) {
    std::ofstream outfile(filename);
    assert(outfile);

    std::vector<int> dists;
    std::vector<int> parents;
    for (int s = 1; s <= 3; s++) {
        if (use_dfs) g.dfs(s, dists, parents);
        else g.bfs(s, dists, parents);

        outfile << "Raiz: " << s << "\n";
        for (int descendant = 10; descendant <= 30; descendant += 10) {
            outfile << "Pai de " << descendant << ": " << parents[descendant] << "\n";
        }

        outfile << "\n";
    }
}

void write_parents() {
    std::vector<std::tuple<std::string, std::string>> graphs = {
        {"Grafos/grafo_1.txt", "Output/Pais/grafo_1"},
        {"Grafos/Grandes/grafo_2.txt", "Output/Pais/grafo_2"},
        {"Grafos/Grandes/grafo_3.txt", "Output/Pais/grafo_3"},
        {"Grafos/Grandes/grafo_4.txt", "Output/Pais/grafo_4"},
        {"Grafos/Grandes/grafo_5.txt", "Output/Pais/grafo_5"},
        {"Grafos/Grandes/grafo_6.txt", "Output/Pais/grafo_6"},
    };

    for (auto t : graphs) {
        std::string infile = std::get<0>(t);
        std::string outfile = std::get<1>(t);

        Graph g(infile, false);

        std::string bfs = "_bfs.txt";
        std::string dfs = "_dfs.txt";
        write_parents_graph(g, outfile + bfs, false);
        write_parents_graph(g, outfile + dfs, true);
    }
}

void write_distances_graph(Graph g, const std::string& filename) {
    std::ofstream outfile(filename);
    assert(outfile);

    std::vector<int> dists10;
    std::vector<int> dists20;
    std::vector<int> parents;
    g.bfs(10, dists10, parents);
    g.bfs(20, dists20, parents);

    outfile << "Distância (10, 20): " << dists10[20] << "\n";
    outfile << "Distância (10, 30): " << dists10[30] << "\n";
    outfile << "Distância (20, 30): " << dists20[30] << "\n";
    outfile << "\n";    
}

void write_distances() {
    std::vector<std::tuple<std::string, std::string>> graphs = {
        {"Grafos/grafo_1.txt", "Output/Distancias/grafo_1.txt"},
        {"Grafos/Grandes/grafo_2.txt", "Output/Distancias/grafo_2.txt"},
        {"Grafos/Grandes/grafo_3.txt", "Output/Distancias/grafo_3.txt"},
        {"Grafos/Grandes/grafo_4.txt", "Output/Distancias/grafo_4.txt"},
        {"Grafos/Grandes/grafo_5.txt", "Output/Distancias/grafo_5.txt"},
        {"Grafos/Grandes/grafo_6.txt", "Output/Distancias/grafo_6.txt"},
    };

    for (auto t : graphs) {
        std::string infile = std::get<0>(t);
        std::string outfile = std::get<1>(t);

        Graph g(infile, false);
        write_distances_graph(g, outfile);
    }
}

void write_info() {
    std::vector<std::tuple<std::string, std::string>> graphs = {
        {"Grafos/grafo_1.txt", "Output/ComponentesConexas/grafo_1.txt"},
        {"Grafos/Grandes/grafo_2.txt", "Output/ComponentesConexas/grafo_2.txt"},
        {"Grafos/Grandes/grafo_3.txt", "Output/ComponentesConexas/grafo_3.txt"},
        {"Grafos/Grandes/grafo_4.txt", "Output/ComponentesConexas/grafo_4.txt"},
        {"Grafos/Grandes/grafo_5.txt", "Output/ComponentesConexas/grafo_5.txt"},
        {"Grafos/Grandes/grafo_6.txt", "Output/ComponentesConexas/grafo_6.txt"},
    };

    for (auto t : graphs) {
        std::string infile = std::get<0>(t);
        std::string outfile = std::get<1>(t);

        Graph g(infile, false);
        g.write_output(outfile);
    }
}

std::vector<std::tuple<std::string, std::string>> get_filenames() {
    return {
        {"Grafos/grafo_1.txt", "Output/grafo_1.txt"},
        {"Grafos/Grandes/grafo_2.txt", "Output/grafo_2.txt"},
        {"Grafos/Grandes/grafo_3.txt", "Output/grafo_3.txt"},
        {"Grafos/Grandes/grafo_4.txt", "Output/grafo_4.txt"},
        {"Grafos/Grandes/grafo_5.txt", "Output/grafo_5.txt"},
        {"Grafos/Grandes/grafo_6.txt", "Output/grafo_6.txt"},
    };
}

void write_diameters() {
    std::vector<std::tuple<std::string, std::string>> graphs = get_filenames();

    for (auto t : graphs) {
        std::string infile = std::get<0>(t);
        std::string outfile = std::get<1>(t);

        Graph g(infile, false);
        std::ofstream out(outfile);
        assert(out);

        out << "Diâmetro exato: " << g.diameter() << "\n";
    }
}

int main() {
    write_diameters();
}