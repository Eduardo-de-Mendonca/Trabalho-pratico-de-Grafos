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
    std::cout << "Numero de vertices no reverso: " << wg2_rev.get_n() << std::endl;
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

void Quest_1() {
    std::vector<std::pair<std::string, std::string>> graphs = {
        {"Grafos 3/grafo_W_1.txt", "EstudosDeCaso/Quest_1/grafo_1.txt"},
        {"Grafos 3/grafo_W_2.txt", "EstudosDeCaso/Quest_1/grafo_2.txt"},
        {"Grafos 3/grafo_W_3.txt", "EstudosDeCaso/Quest_1/grafo_3.txt"},
        {"Grafos 3/grafo_W_4.txt", "EstudosDeCaso/Quest_1/grafo_4.txt"},
        {"Grafos 3/grafo_W_5.txt", "EstudosDeCaso/Quest_1/grafo_5.txt"},
    };

    for (auto t : graphs) {
        std::string infile = t.first;
        std::string out_filename = t.second;;

        std::ofstream outfile(out_filename);
        assert(outfile);
        WeightedGraph wg(infile, false,false);
        int s=100;
        std::vector<double> dists;
        std::vector<int> parents;
        double duration;
        auto start = time_now();
        try{
            wg.bellman_ford(s,dists,parents);
        }
        catch(std::runtime_error& e){
            outfile << "Ciclo negativo encontrado.\n";
            continue;
        }
        auto end = time_now();
        duration = time_elapsed(start, end);
        outfile << "Distâncias:\n";
        for (int target : {10,20,30}) {
            outfile << target << ": " << dists[target] << "\n";
        }
        outfile << "Tempo: " << duration << " segundos\n";
    }
}

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

void Quest_2() {
    std::vector<std::pair<std::string, std::string>> graphs = {
        {"Grafos 3/grafo_W_2.txt", "EstudosDeCaso/Quest_2/grafo_2.txt"},
        {"Grafos 3/grafo_W_3.txt", "EstudosDeCaso/Quest_2/grafo_3.txt"},
        {"Grafos 3/grafo_W_4.txt", "EstudosDeCaso/Quest_2/grafo_4.txt"},
        {"Grafos 3/grafo_W_5.txt", "EstudosDeCaso/Quest_2/grafo_5.txt"},
    };

    for (auto t : graphs) {
        std::string infile = t.first;
        std::string out_filename = t.second;;

        std::ofstream outfile(out_filename);
        assert(outfile);
        WeightedGraph wg(infile, false,false);
        int n = wg.get_n();
        std::vector<double> dists;
        std::vector<int> parents;
        double duration,media;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, n);
        std::vector<int> random_starts;
        for (int i = 0; i < 10; i++) {
            random_starts.push_back(dis(gen));
        }
        for (int s : random_starts) {
            outfile << s << " ";
        }
        outfile << "\n";
        auto start = time_now();
        for (int s : random_starts) {
            wg.bellman_ford(s,dists,parents);
        }
        auto end = time_now();
        duration = time_elapsed(start, end);
        media = duration/10;
        outfile << "Duração total das 10 chamadas: " << duration << " segundos\n";
        outfile << "Média por Bellman-Ford: " << media << " segundos\n";
    }
}

void Quest_3() {
    std::vector<std::pair<std::string, std::string>> graphs = {
        {"Grafos 3/grafo_W_2.txt", "EstudosDeCaso/Quest_3//grafo_2.txt"},
        {"Grafos 3/grafo_W_3.txt", "EstudosDeCaso/Quest_3/grafo_3.txt"},
        {"Grafos 3/grafo_W_4.txt", "EstudosDeCaso/Quest_3/grafo_4.txt"},
        {"Grafos 3/grafo_W_5.txt", "EstudosDeCaso/Quest_3/grafo_5.txt"},
    };

    for (auto t : graphs) {
        std::string infile = t.first;
        std::string out_filename = t.second;;
        std::ofstream outfile(out_filename);
        assert(outfile);
        WeightedGraph wg(infile, false,false);
        WeightedGraph wg_rev = wg.reverse(false);
        int n=wg_rev.get_n();
        std::vector<double> dists;
        std::vector<int> parents;
        double duration,media;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, n);
        std::vector<int> random_starts;
        for (int i = 0; i < 10; i++) {
            random_starts.push_back(dis(gen));
        }
        outfile << "\n";
        auto start = time_now();
        for (int t : random_starts) {
            wg_rev.dijkstra(t,dists,parents,false);
        }
        auto end = time_now();
        duration = time_elapsed(start, end);
        media = duration/10;
        outfile << "Duração total das 10 chamadas: " << duration << " segundos\n";
        outfile << "Média por Dyjkstra: " << media << " segundos\n";
        outfile << "Distâncias:\n";
        for (int target : {10,20,30}) {
            outfile << target << ": " << dists[target] << "\n";
        }
    }
}

void Quest_3_Comp() {
    std::vector<std::pair<std::string, std::string>> graphs = {
        {"Grafos 3/grafo_W_2.txt", "EstudosDeCaso/Quest_3/Comp_Dijksttra_Ford/grafo_2.txt"},
        {"Grafos 3/grafo_W_3.txt", "EstudosDeCaso/Quest_3/Comp_Dijksttra_Ford/grafo_3.txt"},
        {"Grafos 3/grafo_W_4.txt", "EstudosDeCaso/Quest_3/Comp_Dijksttra_Ford/grafo_4.txt"},
        {"Grafos 3/grafo_W_5.txt", "EstudosDeCaso/Quest_3/Comp_Dijksttra_Ford/grafo_5.txt"},
    };

    for (auto t : graphs) {
        std::string infile = t.first;
        std::string out_filename = t.second;;

        std::ofstream outfile(out_filename);
        assert(outfile);
        WeightedGraph wg(infile, false,false);
        WeightedGraph wg_rev = wg.reverse(false);
        int s=100;
        std::vector<double> dists;
        std::vector<int> parents;
        double duration;
        auto start = time_now();
        wg_rev.dijkstra(s,dists,parents,false);
        auto end = time_now();
        duration = time_elapsed(start, end);
        outfile << "Distâncias:\n";
        for (int target : {10,20,30}) {
            outfile << target << ": " << dists[target] << "\n";
        }
        outfile << "Tempo: " << duration << " segundos\n";
    }
}


int main() {
    Quest_1();
    return 0;
}
