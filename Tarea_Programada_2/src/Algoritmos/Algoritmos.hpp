#ifndef ALGORITMOS_ALGORITMOS_GRAFOS
#define ALGORITMOS_ALGORITMOS_GRAFOS

#ifdef MATRIZ
    // #include "../MatrizAdyacencia/Grafo.hpp"
    #define VERSION_GRAFO "GRAFO REPRESENTADO CON MATRIZ DE ADYACENCIA"
#else
    // #include "../ListaAdyacencia/Grafo.hpp"
    #define VERSION_GRAFO "GRAFO REPRESENTADO CON LISTA DE ADYACENCIA"
#endif

// Decidido en tiempo de compilación gracias al -I de todas las carpetas
// y los header guards que identifican la definición del símbolo MATRIZ
#include "GrafoImplementado.hpp"

#include <list>  // Listas indexadas
#include <set>  // Conjuntos
#include <vector>  // Arreglos

#include "Djikstra/ListaDijkstra.hpp"
#include "Coloreo/PairColoreo.hpp"

namespace Algoritmos {

    // PEQUEÑOS

    Vertice BuscarVertice(const Grafo& grafo, char etiqueta);

    PairColoreo Colorear(const Grafo& grafo);

    // CLÁSICOS

    ListaDijkstra Dijkstra(const Grafo& grafo, Vertice &inicio);

    /* TODO(us): Escoger uno de los dos
    void Kruskal(const Grafo& grafo, Grafo& grafoMinimo);
    */

    void Kruskal(const Grafo& grafo, Grafo& grafoRecipiente);

    void Prim(const Grafo& grafo, Grafo& grafoRecipiente);

    Grafo primMetodo(Grafo& grafo);

    std::vector<std::vector<size_t>>
    Floyd(const Grafo& grafo);

    std::vector<std::vector<size_t>>
    nVecesDijkstra(const Grafo& grafo);

    // CIRCUITO HAMILTON DE MENOR COSTO

    std::vector<Vertice> HamiltonBEP(const Grafo& grafo);

    std::vector<Vertice> HamiltonBERA(const Grafo& grafo);

}

#endif
