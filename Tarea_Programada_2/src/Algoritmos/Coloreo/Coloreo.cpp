#include <list>  // Para listas indexadas
#include <utility> // Para parejas
#include <set> // Para conjuntos

#include "GrafoImplementado.hpp"

static void colorearRec(const Grafo& grafo,
    Vertice vertice,
    std::list<std::pair<size_t, Vertice>> &mejorMapeo,
    std::list<std::pair<size_t, Vertice>> &mapeo,
    size_t mejorCantidadColor,
    size_t cantidadColorLocal,
    std::set<size_t>& colorUsados)
{
    std::set<Vertice> verticesAdyacentesV;
    std::set<Vertice> verticesColorC;
    Vertice adyacente = grafo.PrimerVerticeAdyacente(vertice);
    Vertice verticeNulo;
    bool primeraVezUsado = false;

    // std::list<std::pair<size_t, Vertice>> mapeoLocal = mejorMapeo;
    // size_t cantidadColorLocal = mejorCantidadColor;

    while (adyacente != verticeNulo)
    {
        verticesAdyacentesV.insert(adyacente);
        adyacente = grafo.SiguienteVerticeAdyacente(vertice, adyacente);
    }

    // para cada color disponible
    for (size_t i = 1; i < grafo.NumVertices(); ++i)
    {
        verticesColorC.clear();
        for (std::list<std::pair<size_t, Vertice>>::iterator j = mapeo.begin(); j != mapeo.end(); ++j)
        {
            // if element char is equal to iColor
            if (std::get<0>(*j) == i)
            {
                verticesColorC.insert(std::get<1>(*j));
            }
        }

        bool conjuntosDisjuntos = false;

        // ciclo para saber si existen elementos en comun en ambos conjuntos, permite saber si son disjuntos o no
        for (std::set<Vertice>::iterator j = verticesAdyacentesV.begin(); j != verticesAdyacentesV.end(); ++j)
        {
            for (std::set<Vertice>::iterator k = verticesColorC.begin(); k != verticesColorC.end(); ++k)
            {
                if (j == k)
                {
                    conjuntosDisjuntos = true;
                }
            }
        }

        // si el conjunto verticesAdyacnetesC y verticesColorC son
        if (!conjuntosDisjuntos)
        {
            // guarda en mapeo "vertice" del color i
            std::pair<size_t, Vertice> parActual = {i, vertice};
            mapeo.push_front(parActual);

            if (colorUsados.find(i) == colorUsados.end())
            {
                primeraVezUsado = true;
                colorUsados.insert(i);
                ++cantidadColorLocal;
            }

            Vertice ultimoVertice = grafo.PrimerVertice();
            while (grafo.SiguienteVertice(ultimoVertice) != verticeNulo)
            {
                ultimoVertice = grafo.SiguienteVertice(ultimoVertice);
            }

            if (vertice == ultimoVertice)
            {
                if (mejorCantidadColor < cantidadColorLocal)
                {
                    mejorCantidadColor = cantidadColorLocal;
                    mejorMapeo = mapeo;
                }
            }
            else
            {
                colorearRec(grafo,
                grafo.SiguienteVertice(vertice),
                mejorMapeo,
                mapeo,
                mejorCantidadColor,
                cantidadColorLocal,
                colorUsados);
            }

            if (primeraVezUsado) {
                colorUsados.erase(i);
            }
            mapeo.pop_front(); // para quitar el vertice que se acaba de agregar
        }
    }
}

namespace Algoritmos {

    std::pair<std::list<std::pair<size_t, Vertice>>, size_t>
    colorear(const Grafo& grafo)
    {
        std::list<std::pair<size_t, Vertice>> mapeo;
        std::list<std::pair<size_t, Vertice>> mejorMapeo;
        size_t cantidadColor = 0;
        size_t mejorCantidadColor = grafo.NumVertices();
        Vertice vertice = grafo.PrimerVertice();
        std::set<size_t> coloresUsados;

        colorearRec(grafo, vertice, mejorMapeo, mapeo, mejorCantidadColor, cantidadColor, coloresUsados);
        // colorearRecursivo(grafo, primerVertice, mapeoColor, cantidadColor, coloresUsados);

        std::pair<std::list<std::pair<size_t, Vertice>>, size_t> miPar{mejorMapeo, mejorCantidadColor};
        return miPar;
    }
}
