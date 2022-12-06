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

namespace Algoritmos {

    // PEQUEÑOS

    Vertice buscarVertice(const Grafo& grafo, char etiqueta);

    std::pair<std::list<std::pair<size_t, Vertice>>, size_t> 
    colorear(const Grafo& grafo);

    // CLÁSICOS

    ListaDijkstra Dijkstra(const Grafo& grafo, Vertice &inicio);

    /* TODO(us): Escoger uno de los dos
    void Kruskal(const Grafo& grafo, Grafo& grafoMinimo);
    */

    Grafo Kruskal(const Grafo& grafo);

    Grafo Prim(const Grafo& grafo);

    std::vector<std::vector<size_t>>
    Floyd(const Grafo& grafo);

    std::vector<std::vector<size_t>>
    nVecesDijkstra(const Grafo& grafo);

    // CIRCUITO HAMILTON DE MENOR COSTO

    std::vector<Vertice> HamiltonBEP(const Grafo& grafo);

    std::vector<Vertice> HamiltonBERA(const Grafo& grafo);

}

#endif
