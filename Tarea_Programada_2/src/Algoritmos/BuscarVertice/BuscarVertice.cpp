#include "GrafoImplementado.hpp"

namespace Algoritmos {

    Vertice BuscarVertice(const Grafo &grafo, char etiqueta)
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
