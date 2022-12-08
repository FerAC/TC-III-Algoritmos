#include <map>     // Para listas indexadas
#include <utility> // Para parejas
#include <set>     // Para conjuntos
#include <algorithm>
#include <vector>
#include <iostream>
#include <cassert>

//#include "PairColoreo.hpp"

#include "GrafoImplementado.hpp"

// static void colorearRec(const Grafo &grafo,
//                         Vertice vertice,
//                         std::list<std::pair<size_t, Vertice>> &mejorMapeo,
//                         std::list<std::pair<size_t, Vertice>> &mapeo,
//                         size_t &mejorCantidadColor,
//                         size_t &cantidadColorLocal,
//                         std::set<size_t> &colorUsados)
// {
//     std::set<Vertice> verticesAdyacentesV;
//     std::set<Vertice> verticesColorC;
//     Vertice adyacente = grafo.PrimerVerticeAdyacente(vertice);
//     Vertice verticeNulo;
//     bool primeraVezUsado = false;

//     while (adyacente != verticeNulo)
//     {
//         verticesAdyacentesV.insert(adyacente);
//         adyacente = grafo.SiguienteVerticeAdyacente(vertice, adyacente);
//     }

//     // para cada color disponible
//     for (size_t i = 1; i < grafo.NumVertices(); ++i)
//     {
//         verticesColorC.clear();
//         // llena el conjunto verticesColorC con todos los elementos del color C
//         for (std::list<std::pair<size_t, Vertice>>::iterator j = mapeo.begin(); j != mapeo.end(); ++j)
//         {
//             // if element char is equal to iColor
//             if (std::get<0>(*j) == i)
//             {
//                 verticesColorC.insert(std::get<1>(*j));
//             }
//         }

//         std::vector<Vertice> common_data;   // verificar si los conjuntos son disjuntos
//         std::set_intersection(verticesAdyacentesV.begin(), verticesAdyacentesV.end(), verticesColorC.begin(), verticesColorC.end(), std::back_inserter(common_data));
//         bool conjuntosDisjuntos = (common_data.empty()) ? true : false;

//         // si el conjunto verticesAdyacnetesC y verticesColorC son
//         if (!conjuntosDisjuntos)
//         {
//             // guarda en mapeo "vertice" del color i
//             std::pair<size_t, Vertice> parActual = {i, vertice};
//             mapeo.push_front(parActual);

//             if (colorUsados.find(i) == colorUsados.end())
//             {
//                 primeraVezUsado = true;
//                 colorUsados.insert(i);
//                 ++cantidadColorLocal;
//             }

//             Vertice ultimoVertice = grafo.PrimerVertice();
//             while (grafo.SiguienteVertice(ultimoVertice) != verticeNulo)
//             {
//                 ultimoVertice = grafo.SiguienteVertice(ultimoVertice);
//             }

//             if (vertice == ultimoVertice)
//             {
//                 if (mejorCantidadColor < cantidadColorLocal)
//                 {
//                     mejorCantidadColor = cantidadColorLocal;
//                     mejorMapeo = mapeo;
//                 }
//             }
//             else
//             {
//                 colorearRec(grafo,
//                             grafo.SiguienteVertice(vertice),
//                             mejorMapeo,
//                             mapeo,
//                             mejorCantidadColor,
//                             cantidadColorLocal,
//                             colorUsados);
//             }

//             if (primeraVezUsado)
//             {
//                 colorUsados.erase(i);
//             }
//             mapeo.pop_front(); // para quitar el vertice que se acaba de agregar
//             --cantidadColorLocal;
//         }
//     }
// }

void colorearRec(Vertice vertice, std::map<size_t, std::set<Vertice>> &conjuntoOptimal,
                 std::map<size_t, std::set<Vertice>>& conjuntoTemporal, Grafo &grafo)
{
    //std::cout<< "Entre recursividad" << std::endl;
    //std::cout<< "El vertice es " << vertice.getEtiqueta() << std::endl;
    std::set<Vertice> verticesAdyacentesV;
    Vertice adyacente = grafo.PrimerVerticeAdyacente(vertice);
    Vertice verticeNulo;
    assert(vertice!=verticeNulo); 
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
            std::cout<< "se agrego el color " << i << " al conjunto de colores" << std::endl;
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
            if(!usadoPorPrimeraVez){
                it->second.insert(vertice); // Inserto a vertice en el conjunto de color i
            }
        }
        if (grafo.SiguienteVertice(vertice) == verticeNulo){ //Solucion
        //    std::cout<< "Encontre una solucion" << std::endl;
            std::cout<< "Solucion actual " << conjuntoTemporal.size() << std::endl;
            std::cout<< "Solucion mejor  " << conjuntoOptimal.size() << std::endl;
            if(conjuntoOptimal.empty()){ //Primera vez que se encuentra solucion
                conjuntoOptimal = conjuntoTemporal; 
            } else
            if(conjuntoTemporal.size() < conjuntoOptimal.size()){ //Ya habia una solucion
                 conjuntoOptimal = conjuntoTemporal;       
            }
          //  std::cout<< "Asumi exitosamente la solucion" << std::endl;
        }else{  // sino, hacer llamado recursivo
            colorearRec(grafo.SiguienteVertice(vertice), conjuntoOptimal, conjuntoTemporal, grafo);
        }
        //std::cout<< "Me arrepiento master" << std::endl;
        //Arrepentimiento
        // assert(!it->second.empty());
        it->second.erase(vertice); 
        
        if(usadoPorPrimeraVez){
            conjuntoTemporal.erase(i); 
        }
        
    }
}

namespace Algoritmos
{

    std::map<size_t, std::set<Vertice>> * Colorear(Grafo &grafo)
    {
        Vertice vertice = grafo.PrimerVertice();
        size_t cantidadElementos =  65535;
        std::cout<< "ASAAAAAAAAAAAAAAAAAAAAA" << std::endl;
        std::map<size_t, std::set<Vertice>> * conjuntoOptimal = new std::map<size_t, std::set<Vertice>>();
        conjuntoOptimal->clear();
        std::map<size_t, std::set<Vertice>> * conjuntoTemporal = new std::map<size_t, std::set<Vertice>>();
        colorearRec(vertice, *conjuntoOptimal, *conjuntoTemporal, grafo);
        //std::cout<< "oh lala" << std::endl;
        // PairColoreo par;
        std::cout<< "oh lala1" << std::endl;
        delete conjuntoTemporal; 
        return conjuntoOptimal;
    }
}
