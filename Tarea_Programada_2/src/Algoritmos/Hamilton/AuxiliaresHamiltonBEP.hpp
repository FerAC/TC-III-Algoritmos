#ifndef HAMILTON_BEP
#define HAMILTON_BEP

#include <limits>  // Max de size_t
#include <map>  // Relaciones
#include <vector>  // Arreglos

#include "Grafo.hpp"

struct Datos {
    std::vector<Vertice> solActual;
    std::vector<Vertice> mejorSol;

    size_t costoActual = 0;
    size_t mejorCosto = std::numeric_limits<size_t>::max();
    
    std::map<char, Vertice> diccionario;

    Datos(const Grafo& grafo) 
    : solActual(grafo.NumVertices())
    , mejorSol(grafo.NumVertices()) {
        solActual[0] = grafo.PrimerVertice();
        diccionario.insert(std::pair<char, Vertice>
            (grafo.PrimerVertice().getEtiqueta(), grafo.PrimerVertice()));
    }
};

#endif
