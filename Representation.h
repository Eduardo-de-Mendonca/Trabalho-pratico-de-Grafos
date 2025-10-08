#ifndef REPRESENTATION_H
#define REPRESENTATION_H

#include <vector>
#include <string>

class GraphRepresentation {
public:
    virtual ~GraphRepresentation() = default;

    virtual int get_n() const = 0;
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
    AdjacencyVector(const std::string& filename);

    int get_n() const override;

    /**
    O(grau(v)) 
    */
    std::vector<int> neighbors(int v) const override;
    void print() const override;
};

class AdjacencyMatrix : public GraphRepresentation {
private:
    std::vector<std::vector<bool>> mat;

public:
    AdjacencyMatrix(const std::string& filename);

    int get_n() const override;

    /**
    O(n) 
    */
    std::vector<int> neighbors(int v) const override;
    void print() const override;
};

#endif