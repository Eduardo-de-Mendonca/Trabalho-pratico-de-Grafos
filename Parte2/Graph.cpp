#include "Graph.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include <functional>
#include <cassert>
#include <limits>

// Funções ajudantes
namespace{
    /**
    Retorna true <-> a.size() >= b.size().
    O(1)
    */
    bool sort_key(const std::vector<int>& a, const std::vector<int> b) {
        return a.size() >= b.size();
    }

    /**
    Escreve o vetor no final do arquivo. Após cada entrada do vetor, é escrito um espaço (inclusive no final)

    O(writee.size())
    */
    void write_vector(std::ofstream& outfile, const std::vector<int>& writee) {
        for (int i = 0; i < writee.size(); i++) {
            outfile << writee[i] << " ";
        }
    }

    /**
    Lê o arquivo filename e altera n e edges com as informações do arquivo.

    O(n + m)
    */
    void read_file_info(const std::string& filename, int& n, std::vector<std::pair<int, int>>& edges) {
        std::ifstream infile(filename);
        assert(infile);
        
        infile >> n;
        assert(n >= 1);

        edges.resize(0);
        int u, v;
        while (infile >> u >> v) {
            edges.push_back(std::make_pair(u, v));
        }

        return;
    }

    /**
    Lê o arquivo filename (representando um grafo com peso) e altera n e edges com as informações do arquivo.

    O(n + m)
    */
    void read_file_info_weighted(const std::string& filename, int& n, std::vector<std::pair<int, int>>& edges, std::vector<double>& weights) {
        std::ifstream infile(filename);
        assert(infile);
        
        infile >> n;
        assert(n >= 1);

        edges.resize(0);
        weights.resize(0);
        int u, v;
        double w;
        while (infile >> u >> v >> w) {
            edges.push_back(std::make_pair(u, v));
            weights.push_back(w);
        }

        return;
    }

    /**
    Lê o arquivo filename (representando um grafo com peso) e escreve em temp_weights um vetor de adjacências com pares (v, weight), ordenados de acordo com v.

    O(n + m log m)
    */
    void build_weighted_adjacency_vector(const std::string& filename, int& n, std::vector<std::vector<std::pair<int, double>>>& w_adj_vector) {
        std::ifstream infile(filename);
        assert(infile);
        
        infile >> n;
        assert(n >= 1);

        w_adj_vector.assign(n + 1, std::vector<std::pair<int, double>>());
        int u, v;
        double w;
        while (infile >> u >> v >> w) {
            w_adj_vector[u].push_back(std::make_pair(v, w));
            w_adj_vector[v].push_back(std::make_pair(u, w)); // grafo não direcionado
        }

        // Ordenar com base nos vértices (O(m log m))
        for (int i = 1; i <= n; i++) {
            std::sort(w_adj_vector[i].begin(), w_adj_vector[i].end()); // Ordenar com base no primeiro elemento do par (o vértice)
        }
    }

    /**
    Olhando a partir da posição 1, retorna o índice da menor distância dentre os elementos que não foram visitados e cuja distância não é infinita. "double inf = -1" é considerado como distância infinita. Se ninguém for encontrado, retorna -1.

    O(n)
    */
    int nonvis_mindist_idx(const std::vector<double>& dists, const std::vector<bool>& vis) {
        double inf = std::numeric_limits<double>::infinity();

        int result = -1;
        double min = inf;
        for (int v = 1; v < dists.size(); v++) {
            if (vis[v]) continue;
            if (dists[v] == inf) continue;

            if (min >= dists[v]) {
                result = v;
                min = dists[v];
            }
        }

        return result;
    }
}

// Métodos privados
std::vector<int> Graph::neighbors(int v) const {
    return r->neighbors(v);
}

int Graph::max_dist(const std::vector<int>& dists) const {
    assert(dists.size() > 0);
    for (int i = 0; i < dists.size(); i++) assert(dists[i] == -1 || 0 <= dists[i]);

    int max = -2;
    for (int i = 0; i < dists.size(); i++) {
        int x = dists[i];
        if (max == -2 || max < x || x == -1) max = x;
    }

    return max;
}

std::vector<int> Graph::connected_component_vector() const {
    int n = get_n();
    std::vector<int> result(n + 1, -1);

    int i = 1;
    int marker = 0;
    for (int i = 1; i <= n; i++) {
        if (result[i] == -1) {
            bfs_visited(i, result, marker);
            marker++;
        }
    }

    return result;
}

std::vector<std::vector<int>> Graph::connected_components_unsorted() const {
    int n = get_n();

    // Pegar as componentes conexas (O(n + m))
    std::vector<int> components = connected_component_vector();

    // Calcular a componente conexa de maior índice (O(n))
    int max = -1;
    for (int i = 1; i <= n; i++) {
        if (components[i] > max) max = components[i];
    }

    // Mudar a representação (O(n))
    std::vector<std::vector<int>> result(max + 1, std::vector<int>()); // Essa lista é indexada em 0 mesmo, pois não é de vértices, e sim de componentes conexas
    for (int i = 1; i <= n; i++) {
        int c = components[i];
        if (c != -1) {
            result[c].push_back(i); // O(1) amortizado
        }
    }

    return result;
}

// Métodos públicos
Graph::Graph(const std::string& filename, bool use_matrix) {
    int n;
    std::vector<std::pair<int, int>> edges;
    read_file_info(filename, n, edges);
    if (use_matrix) {
        r = std::make_unique<AdjacencyMatrix>(n, edges);
    } else {
        r = std::make_unique<AdjacencyVector>(n, edges);
    }
}

void Graph::print() const {
    r->print();
}

void Graph::write_output(const std::string& filename) const {
    int vertices = get_n();
    int n = get_n();

    // O(n + m) para vetores de adjacências, O(n^2) para matriz de adjacências
    int edges = 0;
    std::vector<int> degrees(n + 1, 0); // Vértice de índice 0 não existe
    for (int i = 1; i <= n; i++) {
        int degree = neighbors(i).size();
        degrees[i] = degree;
        edges += degree;
    }
    edges = edges/2; // Grafo sem direção

    // Calcular coisas com os graus
    int degree_sum = 0;
    int degree_min = -1;
    int degree_max = -1;
    for (int i = 1; i <= n; i++) {
        int degree = degrees[i];
        degree_sum += degree;
        
        if (degree_min == -1 || degree < degree_min) {
            degree_min = degree;;
        }
        if (degree_max == -1 || degree_max < degree) {
            degree_max = degree;
        }
    }
    double degree_avg = (static_cast<double>(degree_sum))/n;

    std::vector<int> real_degrees(degrees.begin() + 1, degrees.end());
    std::sort(real_degrees.begin(), real_degrees.end());
    double degree_median; // Operação O(n log n)
    if (n % 2 != 0) {
        degree_median = real_degrees[n/2];
    }
    else {
        // Pegamos a média dos dois graus centrais
        double sum = real_degrees[n/2 - 1] + real_degrees[n/2];
        degree_median = sum/2;
    }

    // Calcular componentes conexas
    std::vector<std::vector<int>> components = connected_components();

    std::ofstream outfile(filename);
    assert(outfile);

    outfile << "Vértices: " << vertices << "\n";
    outfile << "Arestas: " << edges << "\n";
    outfile << "Grau mínimo: " << degree_min << "\n";
    outfile << "Grau máximo: " << degree_max << "\n";
    outfile << "Grau médio: " << degree_avg << "\n";
    outfile << "Mediana de grau: " << degree_median << "\n";

    outfile << "\n";
    outfile << "Quantidade de componentes conexas: " << components.size() << "\n";
    // Imprimir componentes conexas
    for (int i = 0; i < components.size(); i++) {
        std::vector<int> component = components[i];

        outfile << "Componente " << i << ": tamanho "<< component.size() << "; membros: ";
        write_vector(outfile, component);
        outfile << "\n";
    }
}

void Graph::bfs(int s, std::vector<int>& levels, std::vector<int>& parents) const {
    int n = get_n();
    assert(1 <= s && s <= n); // Garantir que temos um vértice válido
    
    levels.assign(n + 1, -1);
    parents.assign(n + 1, -1);

    std::queue<int> Q;
    levels[s] = 0;
    parents[s] = s;
    Q.push(s);
    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
        std::vector<int> nb = neighbors(v);
        int d = levels[v];
        for (int i = 0; i < nb.size(); i++) {
            int w = nb[i];
            if (levels[w] == -1) {
                levels[w] = d + 1;
                parents[w] = v;
                Q.push(w);
            }
        }
    }
}

void Graph::bfs_visited(int s, std::vector<int>& visited, int marker) const{
    int n = get_n();
    assert(visited.size() == n + 1);

    std::queue<int> Q;
    visited[s] = marker;
    Q.push(s);
    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
        std::vector<int> nb = neighbors(v);
        for (int i = 0; i < nb.size(); i++) {
            int w = nb[i];
            if (visited[w] != marker) {
                visited[w] = marker;
                Q.push(w);
            }
        }
    }
}

void Graph::write_bfs(int s, const std::string& filename) const {
    std::vector<int> dists;
    std::vector<int> parents;
    bfs(s, dists, parents);

    std::ofstream outfile(filename);
    assert(outfile);

    outfile << "Nível -1 significa não descoberto. Nível 0 e pai iguai a si significa raiz da árvore geradora induzida" << "\n";
    outfile << "\n";
    int n = get_n();
    for (int v = 1; v <= n; v++) {
        outfile << "Vértice " << v << ": pai " << parents[v] << " e nível " << dists[v] << "\n";
    }
}

void Graph::dfs(int s, std::vector<int>&levels, std::vector<int>& parents) const {
    int n = get_n();
    assert(1 <= s && s <= n);
    levels.assign(n + 1, -1);
    parents.assign(n + 1, -1);

    std::stack<std::pair<int, int>> P; // A primeira entrada do par é o vértice. A segunda é o cara que o empilhou
    P.push(std::make_pair(s, s));
    while (!P.empty()) {
        std::pair<int, int> p = P.top();
        P.pop();

        int u = p.first;
        int parent = p.second;
        int l = levels[parent];
        if (levels[u] == -1) {
            levels[u] = l + 1;
            parents[u] = parent;
            std::vector<int> nb = neighbors(u);
            for (int i = nb.size() - 1; 0 <= i; i--) { // Empilhamos em ordem contrária para descobrirmos na ordem certa
                int v = nb[i];
                P.push(std::make_pair(v, u));
            }
        }
    }
}

void Graph::write_dfs(int s, const std::string& filename) const {
    std::vector<int> levels;
    std::vector<int> parents;
    dfs(s, levels, parents);

    std::ofstream outfile(filename);
    assert(outfile);

    outfile << "Nível -1 significa não descoberto. Nível 0 e pai igual a si significa raiz da árvore geradora induzida" << "\n";
    outfile << "\n";
    int n = get_n();
    for (int v = 1; v <= n; v++) {
        outfile << "Vértice " << v << ": pai " << parents[v] << " e nível " << levels[v] << "\n";
    }
}

int Graph::dist(int u, int v) const {
    int n = get_n();
    assert(1 <= u && u <= n && 1 <= v && v <= n);
    std::vector<int> dists;
    std::vector<int> parents;

    bfs(u, dists, parents);
    return dists[v];
}

int Graph::diameter() const {
    std::vector<int> dists;
    std::vector<int> parents;

    int max = -2;
    int n = get_n();
    for (int u = 1; u <= n; u++) {
        bfs(u, dists, parents);

        int new_max = max_dist(dists);
        if (new_max == -1) return -1; // Grafo desconexo.
        if (max == -2 || max < new_max) max = new_max;
    }

    return max;
}

int Graph::approx_diameter() const {
    std::vector<int> dists;
    std::vector<int> parents;
    bfs(1, dists, parents);

    int max_v = 0;
    int max = 0;
    int n = get_n();
    for (int v = 1; v <= n; v++) {
        int d = dists[v];
        if (d == -1 || max_v == 0 || max < d) {
            max = d;
            max_v = v;
        }
    }

    if (max == -1) return -1;
    bfs(max_v, dists, parents);
    return max_dist(dists);
}

std::vector<std::vector<int>> Graph::connected_components() const {
    // Pegar as componentes conexas (O(n + m))
    std::vector<std::vector<int>> components = connected_components_unsorted();

    // Ordenar com base no tamanho (O(k log k) <= O(n log n)
    std::sort(components.begin(), components.end(), sort_key);
    return components;
}

void Graph::connected_component_info(int& amount, int& size_largest, int& size_smallest) const {
    // Pegar as componentes conexas (O(n + m))
    std::vector<std::vector<int>> components = connected_components_unsorted();

    // Percorrer para pegar a informação (O(n))
    int max = -1;
    int min = -1;
    for (int i = 0; i < components.size(); i++) {
        int c = components[i].size();
        if (max < c) max = c;
        if (c < min) min = c;
    }

    // Alterar os inteiros (O(1))
    amount = components.size();
    size_largest = max;
    size_smallest = min;
}

int Graph::get_n() const {
    return r->get_n();
}

std::vector<int> Graph::reconstruct_path(const std::vector<int>& parents, int u) const {
    int n = get_n();
    assert(1 <= u && u <= n);

    // Encontrar a raiz - O(n)
    int s = 0;
    for (int i = 1; i < parents.size(); i++) {
        if (parents[i] == i) {
            s = i;
            break;
        }
    }
    if (s == 0) throw std::runtime_error("Árvore parece não ter raiz; ninguém é pai de si próprio");

    // Construir o caminho na ordem contrária. Depois vamos inverter. - O(n)
    std::vector<int> result = {u};
    while (u != s) {
        u = parents[u];
        result.push_back(u);
    }

    // Inverter - O(n)
    std::vector<int> reversed;
    for (int i = result.size() - 1; 0 <= i; i--) {
        reversed.push_back(result[i]);
    }

    return reversed;
}

// Métodos de WeightedGraph
WeightedGraph::WeightedGraph(const std::string& filename, bool use_matrix) {
    std::cout << "Começando a construir o WeightedGraph\n";

    int n;
    std::vector<std::vector<std::pair<int, double>>> temp_weights;

    // O(n + m log m)
    build_weighted_adjacency_vector(filename, n, temp_weights);

    // Copiar os pesos na ordem correta (O(n + m))
    weights.assign(n + 1, std::vector<double>());
    std::vector<std::vector<int>> adj_vector(n + 1, std::vector<int>());
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < temp_weights[i].size(); j++) {
            adj_vector[i].push_back(temp_weights[i][j].first);
            weights[i].push_back(temp_weights[i][j].second);
        }

        // Destruir a linha para liberar memória
        temp_weights[i].clear();
        temp_weights[i].shrink_to_fit();

        if (i % 100'000 == 0) {
            std::cout << "Destruiu a linha " << i << "/" << n << "\n";
        }
    }
    
    if (!use_matrix) {
        r = std::make_unique<AdjacencyVector>(std::move(adj_vector));
    } else {
        r = std::make_unique<AdjacencyMatrix>(std::move(adj_vector));
    }

    std::cout << "Terminou de construir o WeightedGraph\n";
}

void WeightedGraph::print() const {
    int n = get_n();
    std::cout << "Vértices: " << n << "\n";
    std::cout << "Vetor de adjacências com pesos (internamente, pode ser vetor ou matriz):\n";
    for (int u = 1; u <= n; u++) {
        std::vector<int> nb = neighbors(u);
        std::cout << u << ": ";
        for (int i = 0; i < nb.size(); i++) {
            int v = nb[i];
            double weight = weights[u][i];
            std::cout << "(" << v << " com peso " << weight << ") ";
        }
        std::cout << "\n";
    }
}

void WeightedGraph::dijkstra(int s, std::vector<double>& dists, std::vector<int>& parents, bool use_vector_only) const {
    int n = get_n();
    assert(1 <= s && s <= n);

    // Ver se há pesos negativos - O(n + m)
    for (int u = 1; u <= n; u++) {
        for (int i = 0; i < weights[u].size(); i++) {
            double w = weights[u][i];
            if (w < 0) throw std::runtime_error("Encontrou um peso negativo durante a execução do algoritmo de Dijkstra");
        }
    }

    // Inicialização (O(1))
    double inf = std::numeric_limits<double>::infinity();
    std::vector<bool> explored(n + 1, false);
    dists.assign(n + 1, inf);
    dists[s] = 0;
    parents.assign(n + 1, -1);

    // Dists é atualizado no momento que o vértice entra na heap/ é encontrado por um vizinho. parents é atualizado no momento que o vértice é retirado da heap/ é explorado de vez.

    // Usando Heap - O(n + m log m) = O(n + m log n)
    // Repare: nesta implementação, o tamanho da Heap é O(m), e não O(n). Porém, O(log m) = O(log (n^2)) = O(2 log n) = O(log n)
    if (!use_vector_only) {
        // Mais inicialização (O(1))
        // Heap mínima
        std::priority_queue<
            std::tuple<double, int, int>, // dist, vértice e quem encontrou
            std::vector<std::tuple<double, int, int>>,
            std::greater<std::tuple<double, int, int>>
        > H;

        H.push(std::make_tuple(0, s, s)); // s se descobriu com distância 0

        while (!H.empty()) {
            std::tuple<double, int, int> t = H.top();
            H.pop(); // O(m) remoções - complexidade O(m log m) total dessa linha

            int u = std::get<1>(t);
            int parent = std::get<2>(t);

            if (!explored[u]) { // Entramos nesse if O(n) vezes, pois cada vértice é explorado no máximo 1 vez
                explored[u] = true;
                parents[u] = parent;
                std::vector<int> nb = neighbors(u); // Em matriz de adjacências, essa operação é O(n), criando aqui um n^2 que torna a complexidade igual à sem Heap

                for (int i = 0; i < nb.size(); i++) {
                    int v = nb[i];
                    double w = weights[u][i];
                    double ndist = dists[u] + w;

                    if (dists[v] >= ndist) {
                        dists[v] = ndist;
                        std::tuple<double, int, int> newt = std::make_tuple(ndist, v, u);
                        H.push(newt); // O(grau u) inserções na Heap - no total, aqui temos O(m) inserções, com complexidade total O(m log m)
                    }
                }
            }
        }
    }

    // Usando vetor - O(n^2)
    else {
        // Mais inicialização - O(n)
        std::vector<std::pair<double, int>> dist_parent(n + 1);
        for (int i = 0; i < dist_parent.size(); i++) {
            dist_parent[i] = std::make_pair(inf, -1);
        }
        dist_parent[s] = std::make_pair(0, s); // s se descobriu com distância 0

        while (true) {// O(n) iterações (no pior caso, até todos os vértices serem explorados)
            int u = nonvis_mindist_idx(dists, explored); // O(n)
            if (u == -1) break; // Não achou ninguém não-visitado com distância diferente de -1. Parar

            // Olhar os vizinhos - O(grau u)
            int parent = dist_parent[u].second;
            explored[u] = true;
            parents[u] = parent;
            std::vector<int> nb = neighbors(u);

            for (int i = 0; i < nb.size(); i++) {
                int v = nb[i];
                double w = weights[u][i];
                double ndist = dists[u] + w;

                if (dists[v] >= ndist) {
                    dists[v] = ndist;
                    std::pair<double, int> newp = std::make_pair(ndist, u);
                    
                    dist_parent[v] = newp;
                }
            }
        }
    }
}

double WeightedGraph::dist_weighted(int u, int v) const{
    int n = get_n();
    assert(1 <= u && u <= n && 1 <= v && v <= n);
    std::vector<double> dists;
    std::vector<int> parents;

    dijkstra(u, dists, parents, false);
    return dists[v];
}