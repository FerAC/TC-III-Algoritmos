#include "Grafo.hpp"

namespace Algoritmos {

    Vertice buscarVertice(const Grafo &grafo, char etiqueta)
    {
        const Vertice NULO;
        for (Vertice vertice = grafo.PrimerVertice(); vertice != NULO; vertice = grafo.SiguienteVertice(vertice))
        {
            if (vertice.getEtiqueta() == etiqueta) {
                return vertice;
            }
        }
        return NULO;
    }

};
