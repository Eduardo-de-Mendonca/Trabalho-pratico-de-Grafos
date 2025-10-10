#include "Graph.h"
#include <cassert>

int main() {
    /*
    Graph g1("Grafos/grafo_pequeno.txt", false);
    Graph g2("Grafos/grafo_pequeno.txt", true);

    g1.print();
    g2.print();
    */

    WeightedGraph wg1("Grafos/grafo_com_pesos.txt", false);
    WeightedGraph wg2("Grafos/grafo_com_pesos.txt", true);

    wg1.print();
    wg2.print();

    return 0;
}