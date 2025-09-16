#include "Graph.h"

int main() {
    Graph g1("Enunciado/grafo_1.txt", false);
    g1.print();

    Graph g2("Enunciado/grafo_1.txt", true);
    g2.print();
}
