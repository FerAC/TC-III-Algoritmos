#include <cstddef>  // Size_t
#include <iostream> // DEBUG
#include <vector>   // Arreglos
#include <limits>   // Max de size_t
#include <map>

#include "GrafoImplementado.hpp"

namespace Algoritmos
{

    std::vector<std::vector<size_t>> Floyd(const Grafo &grafo)
    {

        size_t numVertices = grafo.NumVertices();
        const Vertice NULO;
        Vertice listaVertices[numVertices];
        size_t i = 0;

        Vertice vertice;
        for (vertice = grafo.PrimerVertice(); vertice != NULO; vertice = grafo.SiguienteVertice(vertice))
        {
            listaVertices[i] = vertice;
            i++;
        }

        std::vector<std::vector<size_t>> matrizCostos(grafo.NumVertices(),
                                                      std::vector<size_t>(grafo.NumVertices()));

        for (int i = 0; i < numVertices; i++)
        {
            for (int j = 0; j < numVertices; j++)
            {
                if (i != j)
                {
                    if (grafo.ExisteArista(listaVertices[i], listaVertices[j]))
                    {
                       
                        matrizCostos[i][j] = grafo.Peso(listaVertices[i], listaVertices[j]);
                    }
                    else
                    {
                        matrizCostos[i][j] = std::numeric_limits<size_t>::max();
                    }
                }
                else
                {
                     matrizCostos[i][j] = 0;
                }
            }
        }
       
        Vertice matrizVertices[numVertices][numVertices];
     

        // Paso 2
         
        for (size_t iteradorPivotes = 0; iteradorPivotes < numVertices; iteradorPivotes++)
        { // Pivotea
            for (i = 0; i < numVertices; i++)
            {
                for (size_t j = 0; j < numVertices; j++)
                {   
                    
                    if (matrizCostos[i][iteradorPivotes] != std::numeric_limits<size_t>::max())
                    { // Hay camino del actual al pivote
                        if (matrizCostos[i][j] > matrizCostos[i][iteradorPivotes] + matrizCostos[iteradorPivotes][j])
                        {
                            matrizCostos[i][j] = matrizCostos[i][iteradorPivotes] + matrizCostos[iteradorPivotes][j];
                            //matrizCostos[j][i]= matrizCostos[i][iteradorPivotes]+matrizCostos[iteradorPivotes][j];
                        }
                    }
                }
               
            }
        }


        for (size_t i = 0; i < grafo.NumVertices(); ++i)
        {
           for (size_t j = 0; j <= i; ++j)
           {
                matrizCostos[j][i] = matrizCostos[i][j];
           }
           
        }
        
        return matrizCostos;
    }

}
