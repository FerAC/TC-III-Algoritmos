#include <map>     // Para listas indexadas
#include <utility> // Para parejas
#include <set>     // Para conjuntos
#include <algorithm>
#include <vector>
#include <iostream>
#include <cassert>
#include "GrafoImplementado.hpp"

void colorearRec(Vertice vertice, std::map<size_t, std::set<Vertice>> &conjuntoOptimal,
                 std::map<size_t, std::set<Vertice>> &conjuntoTemporal, Grafo &grafo)
{
    // std::cout<< "Entre recursividad" << std::endl;
    // std::cout<< "El vertice es " << vertice.getEtiqueta() << std::endl;
    std::set<Vertice> verticesAdyacentesV;
    Vertice adyacente = grafo.PrimerVerticeAdyacente(vertice);
    Vertice verticeNulo;
    assert(vertice != verticeNulo);
    // se llena el conjunto de los vertices adyacentes de vertice
    while (adyacente != verticeNulo)
    {
        verticesAdyacentesV.insert(adyacente);
        adyacente = grafo.SiguienteVerticeAdyacente(vertice, adyacente);
    }

    for (size_t i = 0; i < grafo.NumVertices(); ++i)
    {
        // std::cout<< i << std::endl;
        // checkeo para saber si los conjuntos de adyacentes y de vertices coloreados de color i son disjuntos o no

        auto it = conjuntoTemporal.find(i);
        bool usadoPorPrimeraVez = false;
        if (it == conjuntoTemporal.end())
        { // No agregado el color i
            //std::cout << "se agrego el color " << i << " al conjunto de colores" << std::endl;
            usadoPorPrimeraVez = true;
            std::set<Vertice> conjuntoI;
            conjuntoI.insert(vertice);
            std::pair<size_t, std::set<Vertice>> conjunto(i, conjuntoI);
            conjuntoTemporal.insert(conjunto);
            it = conjuntoTemporal.find(i);
        }
        std::set<Vertice> interseccion;

        std::set_intersection(verticesAdyacentesV.begin(), verticesAdyacentesV.end(), it->second.begin(), it->second.end(), std::inserter(interseccion, interseccion.begin())); // Saca la interseccion
        if (interseccion.empty())
        {
            // Asumo
            if (!usadoPorPrimeraVez)
            {
                it->second.insert(vertice); // Inserto a vertice en el conjunto de color i
            }
            ////////////////////////////////////////

            if (grafo.SiguienteVertice(vertice) == verticeNulo)
            { // Solucion
                //    std::cout<< "Encontre una solucion" << std::endl;
                //std::cout << "Solucion actual " << conjuntoTemporal.size() << std::endl;
                //std::cout << "Solucion mejor  " << conjuntoOptimal.size() << std::endl;
                if (conjuntoOptimal.empty())
                { // Primera vez que se encuentra solucion
                    conjuntoOptimal = conjuntoTemporal;
                }
                else if (conjuntoTemporal.size() < conjuntoOptimal.size())
                { // Ya habia una solucion
                    conjuntoOptimal = conjuntoTemporal;
                }
                //  std::cout<< "Asumi exitosamente la solucion" << std::endl;
            }
            else
            { // sino, hacer llamado recursivo
                colorearRec(grafo.SiguienteVertice(vertice), conjuntoOptimal, conjuntoTemporal, grafo);
            }
            // std::cout<< "Me arrepiento master" << std::endl;
            // Arrepentimiento
            //  assert(!it->second.empty());
            it->second.erase(vertice);

            if (usadoPorPrimeraVez)
            {
                conjuntoTemporal.erase(i);
            }
            /////////////////////
        }
    }
}

namespace Algoritmos
{

    std::map<size_t, std::set<Vertice>> *Colorear(Grafo &grafo)
    {
        Vertice vertice = grafo.PrimerVertice();
        size_t cantidadElementos = 65535;
        std::map<size_t, std::set<Vertice>> *conjuntoOptimal = new std::map<size_t, std::set<Vertice>>();
        conjuntoOptimal->clear();
        std::map<size_t, std::set<Vertice>> *conjuntoTemporal = new std::map<size_t, std::set<Vertice>>();
        colorearRec(vertice, *conjuntoOptimal, *conjuntoTemporal, grafo);
        delete conjuntoTemporal;
        return conjuntoOptimal;
    }
}
