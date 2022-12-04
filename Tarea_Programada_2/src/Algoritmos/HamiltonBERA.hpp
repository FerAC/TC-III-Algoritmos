#ifndef HAMILTON_BERA
#define HAMILTON_BERA

#include <vector>

#ifdef MATRIZ
    #include "../MatrizAdyacencia/Grafo.hpp"
#else
    #include "../ListaAdyacencia/Grafo.hpp"
#endif

namespace HamiltonBERA {
    static std::vector<Vertice> Hamilton(const Grafo& grafo);
}

#endif