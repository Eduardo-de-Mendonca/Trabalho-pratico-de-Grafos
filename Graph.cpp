#include "Graph.h"
#include <fstream>
#include <iostream>

Graph::Graph(const std::string& filename, bool use_matrix) {
    std::ifstream infile(filename);

    infile >> n;

    if (use_matrix) {
        adj_matrix.resize(n + 1, std::vector<bool>(n + 1, false));
        // Operação O(n^2)
        // Deixaremos a primeira posição de tudo vazia, pois os vértices começam em 1
    } else {
        adj_vectors.resize(n + 1, std::vector<int>());
        // Operação O(n)
    }

    // Operações O(m)
    int u, v;
    while (infile >> u >> v) {
        if (use_matrix) {
            adj_matrix[u][v] = true;
            adj_matrix[v][u] = true; // grafo não direcionado
        } else {
            // As duas operações seguintes são O(1) amortizado
            adj_vectors[u].push_back(v);
            adj_vectors[v].push_back(u);
        }
    }
}

void Graph::print() const {
    std::cout << "Vértices" << n << "\n";
    if (!adj_matrix.empty()) {
        std::cout << "Matriz de adjacências\n";
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                std::cout << adj_matrix[i][j] << " ";
            }
            std::cout << "\n";
        }
    } else {
        std::cout << "Vetores de adjacências\n";
        for (int i = 1; i <= n; i++) {
            std::cout << i << ": ";
            for (int v : adj_vectors[i]) {
                std::cout << v << " ";
            }
            std::cout << "\n";
        }
    }
}
