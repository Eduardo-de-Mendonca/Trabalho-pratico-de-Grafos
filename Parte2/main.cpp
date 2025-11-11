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
        //{"Grafos/Grandes/grafo_W_4.txt", "EstudosDeCaso/Questao1/grafo_4.txt"},
        {"Grafos/Grandes/grafo_W_5.txt", "EstudosDeCaso/Questao1/grafo_5.txt"},
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

void test_performance_dijkstra(const std::string& graph_file, const std::string& filename, bool use_vector_only, int dijkstra_count) {
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
    for (int i = 0; i < dijkstra_count; i++) {
        random_starts.push_back(dis(gen));
    }

    outfile << dijkstra_count << " Dikstra(use_vector_only=" << (use_vector_only ? "true" : "false") << ")\n";
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
    avg = duration/dijkstra_count;

    outfile << "\nDuração total das " << dijkstra_count << " chamadas: " << duration << " segundos\n";
    outfile << "Média por Dijkstra: " << avg << " segundos\n";
    outfile << "\n";

    std::cout << no_optimization << "\n";
}

void question_2() {
    std::vector<std::tuple<std::string, std::string, bool, int>> graphs = {
        //{"Grafos/Grandes/grafo_W_1.txt", "EstudosDeCaso/Questao2/grafo_1_heap.txt", false, 100},
        //{"Grafos/Grandes/grafo_W_2.txt", "EstudosDeCaso/Questao2/grafo_2_heap.txt", false, 100},
        //{"Grafos/Grandes/grafo_W_3.txt", "EstudosDeCaso/Questao2/grafo_3_heap.txt", false, 100},
        //{"Grafos/Grandes/grafo_W_4.txt", "EstudosDeCaso/Questao2/grafo_4_heap.txt", false, 100},
        //{"Grafos/Grandes/grafo_W_5.txt", "EstudosDeCaso/Questao2/grafo_5_heap.txt", false, 100},

        //{"Grafos/Grandes/grafo_W_1.txt", "EstudosDeCaso/Questao2/grafo_1_vector_only.txt", true, 100},        
        //{"Grafos/Grandes/grafo_W_2.txt", "EstudosDeCaso/Questao2/grafo_2_vector_only.txt", true, 100},
        {"Grafos/Grandes/grafo_W_3.txt", "EstudosDeCaso/Questao2/new_grafo_3_vector_only.txt", true, 100},
        {"Grafos/Grandes/grafo_W_4.txt", "EstudosDeCaso/Questao2/grafo_4_vector_only.txt", true, 1},
        {"Grafos/Grandes/grafo_W_5.txt", "EstudosDeCaso/Questao2/grafo_5_vector_only.txt", true, 1},
        
    };

    for (auto t : graphs) {
        std::string infile = std::get<0>(t);
        std::string outfile = std::get<1>(t);
        bool vector_only = std::get<2>(t);
        int dijkstra_count = std::get<3>(t);

        test_performance_dijkstra(infile, outfile, vector_only, dijkstra_count);
    }
}

// Parte referente a questão 3
std::string removeQuotes(const std::string& str) {
    size_t firstQuote = str.find('"');
    size_t lastQuote = str.rfind('"');
    if (firstQuote == std::string::npos || lastQuote == std::string::npos || firstQuote >= lastQuote) {
        return str;
    }
    // Evita erro se as aspas estiverem coladas ""
    if (lastQuote == firstQuote + 1) return "";
    return str.substr(firstQuote + 1, lastQuote - firstQuote - 1);
}

// Função para escrever vetor de nomes em um arquivo outfile
void write_name_vector_to_file(std::ofstream& outfile, const std::vector<std::string>& v) {
    if (!outfile.is_open()) {
        std::cerr << "Erro: Tentando escrever em um arquivo que nao esta aberto!" << std::endl;
        return;
    }
    if (v.empty()) {
        outfile << "(Nenhum caminho encontrado ou erro na reconstrucao)";
        return;
    }
    for (size_t i = 0; i < v.size(); ++i) {
        outfile << "'" << v[i] << "'" << (i == v.size() - 1 ? "" : " -> ");
    }
    // Não adiciona std::endl aqui, permite mais controle na função chamadora
}


// --- Função de Tradução Modificada ---
// Recebe o mapa pré-carregado
std::vector<std::string> translateIdsToNames(
    const std::vector<int>& ids_to_translate,
    const std::vector<std::string>& id_to_name_map) // Recebe o mapa pré-carregado
{
    std::vector<std::string> resulting_names;
    resulting_names.reserve(ids_to_translate.size()); // Otimização

    for (int current_id : ids_to_translate) {
        // Verifica se o ID é um índice válido e se há um nome mapeado
        if (current_id > 0 && static_cast<size_t>(current_id) < id_to_name_map.size() && !id_to_name_map[current_id].empty()) {
            resulting_names.push_back(id_to_name_map[current_id]);
        } else {
            // Adiciona uma string indicando erro se o ID for inválido ou não mapeado
            resulting_names.push_back("<<ID INVALIDO/AUSENTE: " + std::to_string(current_id) + ">>");
            // Aviso opcional no console
            // std::cerr << "Aviso: ID " << current_id << " do caminho e invalido ou nao encontrado no mapeamento." << std::endl;
        }
    }
    return resulting_names;
}

// --- Função da Questão 3 (Corrigida) ---
void questao_3(const std::string& filename){
    std::ofstream outfile(filename);
    if (!outfile.is_open()) { // Verifica se abriu antes de usar assert
         std::cerr << "Erro fatal ao criar/abrir o arquivo de saida: " << filename << std::endl;
         return;
    }
    assert(outfile.is_open());

    // IDs dos pesquisadores
    int Dijkstra = 2722;
    int Turing = 11365;
    int Kruskal = 471365;
    int Kleinberg = 5709;
    int Tardos = 11386;
    int Ratton = 343930; // Certifique-se que este ID existe no arquivo de vértices

    std::vector<int> conexoes = {Turing, Kruskal, Kleinberg, Tardos, Ratton};
    std::string arquivo_mapeamento = "TP2 grafos/rede_colaboracao_vertices.txt";
    std::string arquivo_grafo = "TP2 grafos/rede_colaboracao.txt"; // Deve ter pesos!

    // --- CARREGUE O MAPA UMA VEZ AQUI ---
    std::vector<std::string> id_to_name_map;
    std::cout << "Carregando mapeamento de nomes de '" << arquivo_mapeamento << "'..." << std::endl; // Progresso no console
    std::ifstream mapping_file(arquivo_mapeamento);
    if (!mapping_file.is_open()) {
         std::cerr << "Erro fatal ao abrir o arquivo de mapeamento: " << arquivo_mapeamento << std::endl;
         outfile << "Erro fatal ao abrir o arquivo de mapeamento: " << arquivo_mapeamento << std::endl;
         outfile.close();
         return;
    }

    std::string line;
    int max_id = 0;
    // Descobre max_id
    while (std::getline(mapping_file, line)) {
        std::stringstream ss_check(line);
        int id_check;
        // Ignora linhas vazias ou que não comecem com número
        if (ss_check >> id_check) {
            if (id_check > max_id) {
                max_id = id_check;
            }
        }
    }

    // Validação básica do max_id encontrado
    if (max_id <= 0) {
        std::cerr << "Erro: Nao foi possivel encontrar IDs validos ou max_id invalido no arquivo de mapeamento." << std::endl;
        outfile << "Erro: Nao foi possivel encontrar IDs validos ou max_id invalido no arquivo de mapeamento." << std::endl;
        mapping_file.close();
        outfile.close();
        return;
    }
    id_to_name_map.resize(max_id + 1, "<<NOME AUSENTE>>"); // Redimensiona e inicializa com placeholder

    // Retorna ao início do arquivo para ler os nomes
    mapping_file.clear();
    mapping_file.seekg(0, std::ios::beg);

    // Preenche o vetor de mapeamento
    while (std::getline(mapping_file, line)) {
        std::stringstream ss(line);
        int id;
        std::string name_part;
        if (ss >> id) {
             std::getline(ss, name_part); // Pega o resto da linha
             std::string name = removeQuotes(name_part); // Tira aspas
             // Tira espaços iniciais
             size_t first_char = name.find_first_not_of(" \t");
             if(first_char != std::string::npos) {
                 name = name.substr(first_char);
             }

            if (id > 0 && id < id_to_name_map.size()) {
                id_to_name_map[id] = name; // Armazena o nome
            }
        }
    }
    mapping_file.close();
    std::cout << "Mapeamento carregado (Maior ID encontrado: " << max_id << ")." << std::endl;
    // --- FIM DO CARREGAMENTO DO MAPA ---

    // --- Carregar o Grafo ---
    std::cout << "Carregando grafo de '"<< arquivo_grafo << "'..." << std::endl;
    WeightedGraph wg3(arquivo_grafo, false);

    // Validações adicionais de IDs
    if (Dijkstra <= 0 || static_cast<size_t>(Dijkstra) >= id_to_name_map.size() || id_to_name_map[Dijkstra] == "<<NOME AUSENTE>>") {
        std::cerr << "Erro: ID de Dijkstra (" << Dijkstra << ") invalido ou nao encontrado no mapeamento." << std::endl;
        outfile << "Erro: ID de Dijkstra (" << Dijkstra << ") invalido ou nao encontrado no mapeamento." << std::endl;
        outfile.close(); return;
    }
    if (wg3.get_n() < Dijkstra) {
         std::cerr << "Erro: ID de Dijkstra (" << Dijkstra << ") eh maior que o numero de vertices no grafo (" << wg3.get_n() << ")." << std::endl;
        outfile << "Erro: ID de Dijkstra (" << Dijkstra << ") eh maior que o numero de vertices no grafo (" << wg3.get_n() << ")." << std::endl;
        outfile.close(); return;
    }


    std::vector<double> dists;
    std::vector<int> parents;

    // --- Executar Dijkstra ---
    std::cout << "Executando Dijkstra a partir de '" << id_to_name_map[Dijkstra] << "' (ID: " << Dijkstra << ")..." << std::endl;
    try {
        wg3.dijkstra(Dijkstra, dists, parents, false); // false = usar Heap
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Erro fatal: Memoria insuficiente durante o Dijkstra (std::bad_alloc)." << std::endl;
        outfile << "Erro fatal: Memoria insuficiente durante o Dijkstra (std::bad_alloc)." << std::endl;
        outfile.close();
        return;
    } catch (const std::exception& e) {
        std::cerr << "Erro durante a execucao do Dijkstra: " << e.what() << std::endl;
        outfile << "Erro durante a execucao do Dijkstra: " << e.what() << std::endl;
        outfile.close();
        return;
    }
    std::cout << "Dijkstra concluido." << std::endl;

    // --- Escrever Resultados no Arquivo ---
    outfile << "Caminhos a partir de '" << id_to_name_map[Dijkstra] << "' (ID: " << Dijkstra << "):\n";
    outfile << "-------------------------------------------\n";

    for (int target : conexoes) {
         // Validações do ID alvo
         if (target <= 0 || static_cast<size_t>(target) >= id_to_name_map.size() || id_to_name_map[target] == "<<NOME AUSENTE>>") {
             outfile << "ID Alvo " << target << ": Nome invalido ou nao encontrado no mapeamento.\n\n";
             continue;
         }
          if (wg3.get_n() < target) {
             outfile << "Para: '" << id_to_name_map[target] << "' (ID: " << target << ")\n";
             outfile << "Erro: ID Alvo eh maior que o numero de vertices no grafo.\n\n";
             continue;
         }

         outfile << "Para: '" << id_to_name_map[target] << "' (ID: " << target << ")\n";
         outfile << "Distancia: ";
         // Verifica se o vetor de distâncias tem tamanho suficiente
         if (static_cast<size_t>(target) >= dists.size()) {
             outfile << "Erro: Vetor de distancias pequeno demais para o ID alvo.\n\n";
             continue;
         }

         if(dists[target] == std::numeric_limits<double>::infinity()){
            outfile << "Infinita (sem caminho)\n";
            outfile << "Caminho: N/A\n\n";
         } else {
            outfile << dists[target] << "\n";
            outfile << "Caminho: ";
            // Chama reconstruct_path e a translateIdsToNames modificada
            std::vector<std::string> nomes_do_caminho;
            try {
                 // Verifica se o target foi alcançado antes de reconstruir
                 if (parents[target] != -1 || target == Dijkstra) {
                     nomes_do_caminho = translateIdsToNames(
                         wg3.reconstruct_path(parents, target), // Pode lançar erro se parents for inválido
                         id_to_name_map // Passa o mapa carregado
                     );
                 } else {
                      outfile << "(Destino inalcancavel)"; // Não tenta reconstruir
                 }
            } catch (const std::exception& e) {
                 outfile << "<<ERRO NA RECONSTRUCAO: " << e.what() << ">>";
                 std::cerr << "Erro ao reconstruir/traduzir caminho para " << target << ": " << e.what() << std::endl;
            }

            // Chama a função correta para escrever nomes
            write_name_vector_to_file(outfile, nomes_do_caminho);
            outfile << "\n\n"; // Adiciona espaço entre os alvos
         }
    }
    outfile.close();
    std::cout << "Resultados escritos em '" << filename << "'" << std::endl;
}

int main() {
    question_2();
    questao_3("EstudoDeCaso/Questao3.txt");
    return 0;
}
