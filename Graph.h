#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

class Graph {
private:
    std::vector<std::vector<int>> adj_vectors;
    std::vector<std::vector<bool>> adj_matrix;
    int n; // Quantidade de vértices
    
public:
    /**
    Constrói o grafo:
    Vetores de adjacências: O(n + m)
    Matrix de adjacências: O(n^2)
    */
    Graph(const std::string& filename, bool use_matrix);

    /**
    Imprime o grafo no console.
    Vetores de adjacências: O(n + m)
    Matrix de adjacências: O(n^2)
    */
    void print() const;
};

#endif
