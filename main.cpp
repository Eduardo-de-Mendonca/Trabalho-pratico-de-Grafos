#include "Graph.h"
#include <cassert>

int main() {
    Graph g1("Grafos/grafo_pequeno.txt", false);
    Graph g2("Grafos/grafo_pequeno.txt", true);

    g1.print();
    g2.print();

    return 0;
}