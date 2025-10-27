#ifndef REPRESENTATION_H
#define REPRESENTATION_H

#include <vector>
#include <string>

class GraphRepresentation {
public:
    // Destrutor virtual vazio, para ser possível deletar uma classe filha a partir de um ponteiro para GraphRepresentaion.
    virtual ~GraphRepresentation() = default;

    /**
    Retorna o número de vértices.

    O(1)
    */
    virtual int get_n() const = 0;

    /**
    Imprime o grafo no console, de acordo com sua representação.

    Vetor de adjacências: O(n + m)
    Matriz de adjacências: O(n^2)
    */
    virtual void print() const = 0;

    /**
    Retorna um vetor com os vizinhos do vértice v (de 1 a n), em ordem crescente. No caso de vetores de adjacências, é simplesmente uma cópia do vetor de adjacências correspondente a v.
    Vetores de adjacências: O(grau(v))
    Matriz de adjacências: O(n)
    */
    virtual std::vector<int> neighbors(int v) const = 0;
};

class AdjacencyVector : public GraphRepresentation {
private:
    std::vector<std::vector<int>> vec;

public:
    /**
    Constrói o vetor de adjacências.
    
    O(n + m log m)
    */
    AdjacencyVector(int n, const std::vector<std::pair<int, int>>& edges);

    /**
    Recebe o vetor de adjacências já pronto.
    
    O(1)
    */
    explicit AdjacencyVector(std::vector<std::vector<int>>&& adj_vector) {
        vec = std::move(adj_vector);
    }

    /**
    Retorna o número de vértices.

    O(1)
    */
    int get_n() const override;

    /**
    Retorna um vetor com os vizinhos, em ordem crescente de índice. 
    
    O(grau(v)) 
    */
    std::vector<int> neighbors(int v) const override;

    /**
    Imprime o vetor de adjacências no console.

    O(n + m)
    */
    void print() const override;
};

class AdjacencyMatrix : public GraphRepresentation {
private:
    std::vector<std::vector<bool>> mat;

public:
    /**
    Constrói a matriz de adjacências.

    O(n^2)
    */
    AdjacencyMatrix(int n, const std::vector<std::pair<int, int>>& edges);
    
    /**
    Retorna o número de vértices.

    O(1)
    */
    int get_n() const override;

    /**
    Retorna um vetor com os vizinhos de v, em ordem crescente de índice.

    O(n) 
    */
    std::vector<int> neighbors(int v) const override;

    /**
    Imprime a matriz de adjacências no console.

    O(n^2)
    */
    void print() const override;
};

#endif