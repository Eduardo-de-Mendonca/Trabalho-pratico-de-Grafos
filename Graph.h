#ifndef GRAPH_H
#define GRAPH_H

#include "Representation.h"
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>

class Graph {
protected:
    std::unique_ptr<GraphRepresentation> r;

    // Construtor vazio para as classes derivadas
    Graph() = default;

    /**
    Retorna um vetor com os vizinhos do vértice v (de 1 a n), em ordem crescente. No caso de vetores de adjacências, é simplesmente uma cópia do vetor de adjacências correspondente a v.
    Vetores de adjacências: O(grau(v))
    Matriz de adjacências: O(n)
    */
    std::vector<int> neighbors(int v) const;

private:

    
    /**
    Retorna o máximo do vetor dists, com a exceção de que -1 é considerado maior que todos os outros inteiros (como se representasse infinito). Poderia ser uma função simples, já que não acessa nenhum atributo do grafo.
    O vetor deve ter apenas inteiros não negativos ou -1. E não pode estar vazio.
    O(tamanho de dists)
    */
    int max_dist(const std::vector<int>& dists) const;

    /**
    Retorna um vector<int> resultante com n + 1 entradas. A entrada 0 é -1. resultante[v] é a componente conexa do vértice v (a primeira componente conexa é 0, e assim por diante). Os índices das componentes conexas não seguem nenhuma ordem em particular.

    Vetores de adjacências: O((n + m))
    Matriz de adjacências: O(n^2) 
    */
    std::vector<int> connected_component_vector() const;

    /**
    Retorna um vector<vector<int>> resultante indexado em 0 mesmo. resultante[i] é um vector<int> com todos os vértices da i-ésima componente conexa. Os índices das componentes conexas não seguem nenhuma ordem em particular.
    
    Vetores de adjacências: O(n + m)
    Matriz de adjacências: O(n^2)
    */
    std::vector<std::vector<int>> connected_components_unsorted() const;

public:
    /**
    Constrói o grafo. A quantidade de vértices deve ser 1 ou mais. O grafo é sempre tratado como não direcionado. Não pode haver duplicatas nas arestas (não pode haver (1,2) e (2,1), nem pode haver (1,2) duas vezes).
    Ordena os vetores de adjacências, para oferecer as ordens de busca corretas.
    Vetores de adjacências: O(n + m log m)
    Matriz de adjacências: O(n^2)
    */
    Graph(const std::string& filename, bool use_matrix);

    /**
    Imprime o grafo no console.
    Vetores de adjacências: O(n + m)
    Matriz de adjacências: O(n^2)
    */
    virtual void print() const;

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

    s deve ser um vértice válido.

    Vetores de adjacências: O(n + m)
    Matriz de adjacências: O(n^2) 
    */
    void bfs(int s, std::vector<int>& levels, std::vector<int>& parents) const;

    /**
    Roda uma bfs, marcando no vetor visited os vértices visitados com o marcador marker.
    Diferentemente do que ocorre com a bfs usual, visited deve ter tamanho n + 1, e não será reinicializado. Assumimos que todos em visited são diferentes de marker quando o método é chamado.

    Vetores de adjacências: O(n + m)
    Matriz de adjacências: O(n^2) 
    */ 
    void bfs_visited(int s, std::vector<int>& visited, int marker) const;

    /**
    Chama a bfs a partir de s e escreve um arquivo com as informações encontradas. Se filename tem um diretório, ele já deve existir (não será criado pelo método).
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
    Chama a dfs a partir de s e escreve um arquivo com as informações encontradas. Se filename tem um diretório, ele já deve existir (não será criado pelo método).
    Vetores de adjacências: O(n + m)
    Matriz de adjacências: O(n^2) 
    */
    void write_dfs(int s, const std::string& filename) const;

    /**
    Retorna a distância no grafo entre u e v. Caso não estejam conectados, retorna -1.
    Vetores de adjacências: O(n + m)
    Matriz de adjacências: O(n^2) 
    */
    virtual int dist(int u, int v) const;

    /**
    Retorna o diâmetro exato do grafo. Retorna -1 caso o grafo não seja conexo.
    Vetores de adjacências: O(n(n + m))
    Matriz de adjacências: O(n^3) 
    */
    virtual int diameter() const;

    /**
    Retorna uma aproximação a do diâmetro d do grafo usando varredura dupla. Se o grafo é uma árvore, a = d. Se o grafo não for conexo, necessariamente retorna -1.

    Vetores de adjacências: O(n + m)
    Matriz de adjacências: O(n^2)
    */
    virtual int approx_diameter() const;

    /**
    Retorna um vector<vector<int>> resultante indexado em 0 mesmo. resultante[i] é um vector<int> com todos os vértices da i-ésima componente conexa. Os índices das componentes seguem ordem decrescente de tamanho
    
    Seja k a quantidade de componentes conexas.
    Vetores de adjacências: O(n + m + k log k) <= O(m + n log n) 
    Matriz de adjacências: O(n^2) 
    */
    std::vector<std::vector<int>> connected_components() const;

    /**
    Altera amount, size_largest e size_smallest com informações sobre as componentes conexas.

    Vetores de adjacências: O(n + m)
    Matriz de adjacências: O(n^2) 
    */
    void connected_component_info(int& amount, int& size_largest, int& size_smallest) const;

    /**
    Retorna a quantidade de vértices do grafo.

    O(1)
    */
    int get_n() const;
};

class WeightedGraph: public Graph {
private:
    /**
    weights[u][i] é o peso da aresta que vai de u para o seu i-ésimo vizinho (em ordem crescente de índice)
    */
    std::vector<std::vector<double>> weights;

public:
    /**
    Constrói o grafo. A quantidade de vértices deve ser 1 ou mais. O grafo é sempre tratado como não direcionado. Não pode haver duplicatas nas arestas (não pode haver (1,2) e (2,1), nem pode haver (1,2) duas vezes).
    Ordena os vetores de adjacências, para oferecer as ordens de busca corretas.

    O(n + m log m) sempre (mesmo com matriz de adjacências, por causa dos pesos)
    */
    WeightedGraph(const std::string& filename, bool use_matrix);

    /**
    Imprime o grafo no console. Imprime sempre no formato de um vetor de adjacências, independetemente de como está internamente representado.

    Vetores de adjacências: O(n + m)
    Matriz de adjacências: O(n^2)
    */
    void print() const override;

    // Declarar Dijkstra (e talvez um novo dist)
    void dijkstra(int s, std::vector<double>& dists, std::vector<int>& parents, bool use_vector_only) const; 

    int dist(int u, int v) const override{
        throw std::runtime_error("Método ainda não implementado");
    };

    // Remover métodos que não são mais necessários
    int diameter() const override{
        throw std::runtime_error("Método não implementado");
    };

    int approx_diameter(){
        throw std::runtime_error("Método não implementado");
    };
};

#endif
