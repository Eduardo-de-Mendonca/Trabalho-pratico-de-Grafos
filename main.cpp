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

template <typename T>
void write_vector(std::ofstream& outfile,const std::vector<T>& v) {
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
    write_vector(outfile,wg1.reconstruct_path(parents, 20));
    std::cout << "\n";
    write_vector(outfile,wg1.reconstruct_path(parents, 30));
    std::cout << "\n";
    write_vector(outfile,wg1.reconstruct_path(parents, 40));
    std::cout << "\n";
    write_vector(outfile,wg1.reconstruct_path(parents, 50));
    std::cout << "\n";
    write_vector(outfile,wg1.reconstruct_path(parents, 60));

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = end - start;

    // --- Passo 6: Converta para Unidades Convenientes e Exiba ---
    // Converter para segundos (s) - usando double para frações de segundo
    std::chrono::duration<double> duration_s = duration; // Conversão implícita para segundos com double

    outfile << "\n--- Tempo de Execucao ---" << std::endl;
    outfile<< "Segundos:       " << duration_s.count() << " s" << std::endl;
    outfile << "\n";
}

/**
Escreve a distância de 10 para 20, 30, 40, 50, 60 em todos os grafos usando vetor de adjacências e heap (mais rápido), sem registrar tempo de execução. 
*/
void question_1() {
    std::vector<std::pair<std::string, std::string>> graphs = {
        //{"Grafos/Grandes/grafo_W_1.txt", "EstudosDeCaso/Questao1/grafo_1.txt"},
        //{"Grafos/Grandes/grafo_W_2.txt", "EstudosDeCaso/Questao1/grafo_2.txt"},
        //{"Grafos/Grandes/grafo_W_3.txt", "EstudosDeCaso/Questao1/grafo_3.txt"},
        {"Grafos/Grandes/grafo_W_4.txt", "EstudosDeCaso/Questao1/grafo_4.txt"},
        {"Grafos/Grandes/grafo_W_5.txt", "EstudosDeCaso/Questao1/grafo_5.txt"},
        {"Grafos/Grandes/grafo_W_6.txt", "EstudosDeCaso/Questao1/grafo_6.txt"},
    };

    for (auto t : graphs) {
        std::string infile = t.first;
        std::string out_filename = t.second;;

        std::ofstream outfile(out_filename);
        assert(outfile);

        std::cout << "Vai construir o grafo\n";
        WeightedGraph wg(infile, false);
        std::cout << "Fez o grafo\n";
        int s = 10;
        std::vector<double> dists;
        std::vector<int> parents;

        wg.dijkstra(s, dists, parents, false);

        outfile << "Distâncias:\n";
        for (int target : {20, 30, 40, 50, 60}) {
            outfile << target << ": " << dists[target] << "\n";
        }
        
        outfile << "\nCaminhos:\n";
        for (int target : {20, 30, 40, 50, 60}) {
            outfile << target << ": ";
            write_vector(outfile, wg.reconstruct_path(parents, target));
        }
    }
}

void test_performance_dijkstra(const std::string& graph_file, const std::string& filename, bool use_vector_only) {
    std::ofstream outfile(filename);
    assert(outfile);
    int no_optimization = 0;

    WeightedGraph wg(graph_file, false);

    int n = wg.get_n();
    std::vector<double> dists(n + 1);
    std::vector<int> parents(n + 1);
    double duration, avg;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, n);
    std::vector<int> random_starts;
    for (int i = 0; i < 100; i++) {
        random_starts.push_back(dis(gen));
    }

    outfile << "100 Dikstra(use_vector_only=" << (use_vector_only ? "true" : "false") << ")\n";
    outfile << "Vértices de início: ";
    for (int s : random_starts) {
        outfile << s << " ";
    }
    outfile << "\n";

    auto start = time_now();
    for (int s : random_starts) {
        wg.dijkstra(s, dists, parents, use_vector_only);
        no_optimization += static_cast<int>(dists[1]); // Só para garantir que ele não otimize a chamada
    }
    auto end = time_now();

    duration = time_elapsed(start, end);
    avg = duration/100;

    outfile << "\nDuração total das 100 chamadas: " << duration << " segundos\n";
    outfile << "Média por Dijkstra: " << avg << " segundos\n";
    outfile << "\n";

    std::cout << no_optimization << "\n";
}

void question_2() {
    std::vector<std::tuple<std::string, std::string, bool>> graphs = {
        {"Grafos/Grandes/grafo_W_1.txt", "EstudosDeCaso/Questao2/grafo_1_heap.txt", false},
        {"Grafos/Grandes/grafo_W_2.txt", "EstudosDeCaso/Questao2/grafo_2_heap.txt", false},
        {"Grafos/Grandes/grafo_W_3.txt", "EstudosDeCaso/Questao2/grafo_3_heap.txt", false},
        {"Grafos/Grandes/grafo_W_4.txt", "EstudosDeCaso/Questao2/grafo_4_heap.txt", false},
        {"Grafos/Grandes/grafo_W_5.txt", "EstudosDeCaso/Questao2/grafo_5_heap.txt", false},

        {"Grafos/Grandes/grafo_W_1.txt", "EstudosDeCaso/Questao2/grafo_1_vector_only.txt", true},        
        {"Grafos/Grandes/grafo_W_2.txt", "EstudosDeCaso/Questao2/grafo_2_vector_only.txt", true},
        {"Grafos/Grandes/grafo_W_3.txt", "EstudosDeCaso/Questao2/grafo_3_vector_only.txt", true},
        {"Grafos/Grandes/grafo_W_4.txt", "EstudosDeCaso/Questao2/grafo_4_vector_only.txt", true},
        {"Grafos/Grandes/grafo_W_5.txt", "EstudosDeCaso/Questao2/grafo_5_vector_only.txt", true},
        
    };

    for (auto t : graphs) {
        std::string infile = std::get<0>(t);
        std::string outfile = std::get<1>(t);
        bool vector_only = std::get<2>(t);

        test_performance_dijkstra(infile, outfile, vector_only);
    }
}

int main() {
    question_2();

    return 0;
}