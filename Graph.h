#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

class Graph {
private:
    std::vector<std::vector<int>> adj_vectors;
    std::vector<std::vector<bool>> adj_matrix;
    int n; // Quantidade de vértices

    /**
    Retorna um vetor com os vizinhos do vértice v (de 1 a n), em ordem crescente. No caso de vetores de adjacências, é simplesmente uma cópia do vetor de adjacências correspondente a v.
    Vetores de adjacências: O(grau(v))
    Matriz de adjacências: O(n)
    */
    std::vector<int> neighbors(int v) const;
    
public:
    /**
    Constrói o grafo. A quantidade de vértices deve ser 1 ou mais. O grafo é sempre tratado como não direcionado. Não pode haver duplicatas nas arestas (não pode haver (1,2) e (2,1), nem pode haver (1,2) duas vezes).
    Ordena os vetores de adjacências, para oferecer as ordens de busca corretas.
    Vetores de adjacências: O(n + m log m)
    Matrix de adjacências: O(n^2)
    */
    Graph(const std::string& filename, bool use_matrix);

    /**
    Imprime o grafo no console.
    Vetores de adjacências: O(n + m)
    Matriz de adjacências: O(n^2)
    */
    void print() const;

    /**
    Escreve um arquivo com informações sobre o grafo:
        Número de vértices
        Número de arestas
        Grau mínimo, máximo, médio, mediano
    
    Vetores de adjacências: O(n log(n) + m)
    Matriz de adjacências: O(n^2)
    */
    void write_output(const std::string& filename) const;

    /**
    Altera os vetores dists e parents com informações acerca da bfs a partir do vértice s. No vetor dists, -1 significa "não visitado".
    Vetores de adjacências: O(n + m)
    Matriz de adjacências: O(n^2) 
    */
    void bfs(int s, std::vector<int>& dists, std::vector<int>& parents) const;

    /**
    Chama a bfs a partir de s e escreve um arquivo com as informações encontradas.
    Vetores de adjacências: O(n + m)
    Matriz de adjacências: O(n^2) 
    */
    void write_bfs(int s, const std::string& filename) const;

    /**
    Altera os vetores dists e parents com informações acerca da dfs a partir do vértice s. No vetor levels, -1 significa "não visitado".
    Vetores de adjacências: O(n + m)
    Matriz de adjacências: O(n^2)
    */
    void dfs(int s, std::vector<int>&levels, std::vector<int>& parents) const;

    /**
    Chama a dfs a partir de s e escreve um arquivo com as informações encontradas.
    Vetores de adjacências: O(n + m)
    Matriz de adjacências: O(n^2) 
    */
    void write_dfs(int s, const std::string& filename) const;
};

#endif
