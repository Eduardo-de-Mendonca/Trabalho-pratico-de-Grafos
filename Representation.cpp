#include "Representation.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <cassert>

AdjacencyVector::AdjacencyVector(int n, const std::vector<std::pair<int, int>>& edges) {
    assert(n >= 1);

    vec.assign(n + 1, std::vector<int>()); // Operação O(n)

    // Operações O(m)
    for (auto edge : edges) {
        int u = edge.first;
        int v = edge.second;
        vec[u].push_back(v);
        vec[v].push_back(u); // grafo não direcionado
    }

    // Operação O(m log m) para vetores de adjacências
    for (int i = 1; i <= n; i++) {
        std::sort(vec[i].begin(), vec[i].end());
    }
}

int AdjacencyVector::get_n() const {
    return vec.size() - 1;
}

std::vector<int> AdjacencyVector::neighbors(int v) const {
    assert(1 <= v && v <= get_n());
    return vec[v];
}

void AdjacencyVector::print() const {
    int n = get_n();
    std::cout << "Vértices: " << n << "\n";
    std::cout << "Vetor de adjacências:\n";
    for (int i = 1; i <= n; i++) {
        std::cout << i << ": ";
        for (int v : vec[i]) {
            std::cout << v << " ";
        }
        std::cout << "\n";
    }
}

AdjacencyMatrix::AdjacencyMatrix(int n, const std::vector<std::pair<int, int>>& edges) {
    assert(n >= 1);

    mat.assign(n + 1, std::vector<bool>(n + 1, false)); // Operação O(n^2)
    // Deixaremos a primeira posição de tudo vazia, pois os vértices começam em 1

    // Operações O(m)
    for (auto edge : edges) {
        int u = edge.first;
        int v = edge.second;
        mat[u][v] = true;
        mat[v][u] = true; // grafo não direcionado
    }
}

AdjacencyMatrix::AdjacencyMatrix(std::vector<std::vector<int>>&& adj_vector) {
    // Destruir adj_vector para ter comportamento consistente com o construtor de AdjacencyVector
    std::vector<std::vector<int>> lvector = std::move(adj_vector);

    int n = lvector.size() - 1;
    mat.assign(n + 1, std::vector<bool>(n + 1, false)); // O(n^2)

    for (int u = 1; u <= n; u++) {
        for (int v : lvector[u]) {
            mat[u][v] = true;
        }
    }
}

int AdjacencyMatrix::get_n() const {
    return mat.size() - 1;
}

std::vector<int> AdjacencyMatrix::neighbors(int v) const {
    std::vector<int> result;
    int n = get_n();
    assert(1 <= v && v <= n);
    for (int j = 1; j <= n; j++) {
        if (mat[v][j]) result.push_back(j);
    }
    return result;
}

void AdjacencyMatrix::print() const {
    int n = get_n();
    std::cout << "Vértices: " << n << "\n";
    std::cout << "Matriz de adjacências:\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << "\n";
    }
}