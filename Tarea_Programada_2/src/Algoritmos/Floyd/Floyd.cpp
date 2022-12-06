#include <cstddef>  // Size_t
#include <iostream> // DEBUG
#include <vector>  // Arreglos

#include "GrafoImplementado.hpp"

namespace Algoritmos {

    std::vector<std::vector<size_t>> Floyd(const Grafo& grafo) {

        size_t numVertices = grafo.NumVertices();
        std::cout << "Entre floyd" << std::endl;
        const Vertice NULO;
        Vertice listaVertices[numVertices];
        size_t i = 0;
        size_t iteradorPivotes = 0;

        Vertice vertice;
        for (vertice = grafo.PrimerVertice(); vertice != NULO; vertice = grafo.SiguienteVertice(vertice))
        {
            std::cout << "i, primer paso" << i << std::endl;
            listaVertices[i] = vertice;
            i++;
        }

        // Mostrar conexiones
        /*
        std::cout<< "Termino lista" << std::endl;
        for (size_t i = 0; i < grafo.NumVertices(); i++)
        {
            std::cout << i << endl;
            grafo.ImprimirConexiones(listaVertices[i]);
        }
        */

        // Primer paso de inicializacion, ya tengo la lista de vertices
        std::cout << "Primer paso se logro" << std::endl;
        std::cout << "A" << std::endl;
        std::cout << "NUM VERTICES " << numVertices << std::endl;

        std::vector<std::vector<size_t>> matrizCostos(grafo.NumVertices(), 
            std::vector<size_t>(grafo.NumVertices()));

        for (int i = 0; i < numVertices; i++)
        {
            std::cout << "I " << i << std::endl;
            for (int j = 0; j < numVertices; j++)
            {
                std::cout << "J " << j << std::endl;
                if (i != j)
                {
                    if (grafo.ExisteArista(listaVertices[i], listaVertices[j]))
                    {
                        std::cout << "Voy a acceder " << std::endl;
                        std::cout << "Vertice 1 :" << listaVertices[i].getEtiqueta() << std::endl;
                        std::cout << "Vertice 2 :" << listaVertices[j].getEtiqueta() << std::endl;

                        // Vertice vertice1 =
                        // Vertice vertice2 =

                        int miPeso = grafo.Peso(listaVertices[i], listaVertices[j]);
                        std::cout << "Peso  :" << miPeso << std::endl;

                        // std::cout<< "Peso  :" << grafo.Peso(listaVertices[i], listaVertices[j]) << std::endl;
                        matrizCostos[i][j] = grafo.Peso(listaVertices[i], listaVertices[j]);
                    }
                    else
                    {
                        matrizCostos[i][j] = 4;
                    }
                }
                else
                {
                    std::cout << "SON IGUALES " << std::endl;
                    matrizCostos[i][j] = 0;
                }
            }
        }
        std::cout << "Segundo paso se logro" << std::endl;
        // Ya se inicializo la matriz costos
        std::cout << "Voy a imprimir costos" << std::endl;
        for (size_t i = 0; i < numVertices; i++)
        {
            for (size_t j = 0; j < numVertices; j++)
            {
                std::cout << matrizCostos[i][j] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
        Vertice matrizVertices[numVertices][numVertices];
        // Matriz de vertices con basura

        // Paso 2

        for (iteradorPivotes; iteradorPivotes < numVertices; iteradorPivotes++)
        { // Pivotea
            for (i = 0; i < numVertices; i++)
            {
                for (size_t j = 0; j < numVertices; j++)
                {
                    if (i != iteradorPivotes)
                    {
                        if (matrizCostos[i][j] != -1)
                        {
                            if (matrizCostos[iteradorPivotes][j] != -1)
                            {
                                if (grafo.ExisteArista(listaVertices[iteradorPivotes], listaVertices[j]))
                                {
                                    if (matrizCostos[i][j] > matrizCostos[iteradorPivotes][j] + grafo.Peso(listaVertices[iteradorPivotes], listaVertices[j]))
                                    {
                                        matrizCostos[i][j] = matrizCostos[iteradorPivotes][j] + grafo.Peso(listaVertices[iteradorPivotes], listaVertices[j]);
                                        matrizVertices[i][j] = listaVertices[iteradorPivotes];
                                    }
                                }
                            }
                        }
                        else
                        {
                            if (matrizCostos[iteradorPivotes][j] != -1)
                            {
                                if (grafo.ExisteArista(listaVertices[iteradorPivotes], listaVertices[j]))
                                {
                                    matrizCostos[i][j] = matrizCostos[iteradorPivotes][j] + grafo.Peso(listaVertices[iteradorPivotes], listaVertices[j]);
                                    matrizVertices[i][j] = listaVertices[iteradorPivotes];
                                }
                            }
                        }
                    }
                }
            }
        }

        std::cout << "Voy a imprimir costos" << std::endl;
        for (size_t i = 0; i < numVertices; i++)
        {
            for (size_t j = 0; j < numVertices; j++)
            {
                std::cout << matrizCostos[i][j] << " ";
            }
            std::cout << "\n";
        }
        /*
        std::cout << "\n";
        size_t *p[numVertices];
        size_t **q;
        for (int i = 0; i < 4; i++)
            p[i] = matrizCostos[i];
        q = p;
        return q;
        */
        return matrizCostos; 
    }

}