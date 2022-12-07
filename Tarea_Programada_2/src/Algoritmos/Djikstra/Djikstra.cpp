#include <iostream>  // DEBUG
#include <limits>  // Max de size_t
#include <vector>  // Arreglos

#include "Algoritmos.hpp"

// DIJKSTRA

namespace Algoritmos {

    ListaDijkstra Dijkstra(const Grafo& grafo, const Vertice &inicio)
    {
        ListaDijkstra camino(grafo.NumVertices());

        size_t cantidadVertices = grafo.NumVertices();
        Vertice vertice = grafo.PrimerVertice();

        // primero llenamos la lista con la etiqueta de cada elemento y un valor mas cercano al infinito al cual tenemos acceso
        for (size_t i = 0; i < cantidadVertices; ++i)
        {
            if (grafo.Etiqueta(vertice) != grafo.Etiqueta(inicio)) // si el elemento no es el inicio dado por el usuario
            {
                camino.agregar(grafo.Etiqueta(vertice), grafo.Etiqueta(inicio), 2147483647);
                // std::cout << grafo.Etiqueta(vertice) << std::endl;
            }
            else
            { // si el elemento es el inicio dado por el usuario
                camino.agregar(grafo.Etiqueta(vertice), grafo.Etiqueta(inicio), 0);
                // std::cout << grafo.Etiqueta(vertice) << std::endl;
                camino.setVisitado(grafo.Etiqueta(inicio)); // se guarda el inicio como visitado
            }
            vertice = grafo.SiguienteVertice(vertice);
        }
        // std::cout << "TERMINO DE GUARDAR LAS ETIQUETAS EN CAMINO" << std::endl;

        vertice = grafo.PrimerVerticeAdyacente(inicio);
        Vertice verticeNulo;

        // poner el vertice anterior y el costo de las aristas que salen de inicio
        while (vertice != verticeNulo)
        {
            // std::cout << grafo.Peso(inicio, vertice) << std::endl;
            // std::cout << grafo.Etiqueta(vertice) << std::endl;
            camino.setPeso(grafo.Etiqueta(vertice), grafo.Peso(inicio, vertice));
            vertice = grafo.SiguienteVerticeAdyacente(inicio, vertice);
        }
        // std::cout << "TERMINO DE GUARDAR LOS PESOS DE LOS VERTICES ADYACENTES AL NODO INICIAL" << std::endl;

        size_t contador = 0;

        while (contador < cantidadVertices - 1)
        {
            // std::cout << "se ejecuto el ciclo principal" << std::endl;
            size_t counter = 0; // usado para pasar por cada elemento de camino
            char verticePivote = camino.getVerticePorIndice(counter);
            size_t pesoVerticePivote = std::numeric_limits<size_t>::max();
            size_t pesoContador;

            while (counter < cantidadVertices) // este loop permite encontrar el siguiente vertice que tenemos que estudiar, debe ser el menor que aun no fue visitado
            {

                pesoContador = camino.getPesoPorIndice(counter);
                // std::cout << "b" << std::endl;
                bool esVisitado = camino.esVisitadoPorIndice(counter); // esVisitado es 0 si el counter elemento

                if (!esVisitado) // estas 2 condiciones permiten saber si el elemento en la posicion counter es un elemento pivote valido o no
                {
                    if (pesoVerticePivote > pesoContador)
                    {
                        verticePivote = camino.getVerticePorIndice(counter);
                        pesoVerticePivote = camino.getPesoPorIndice(counter);
                    }
                }
                ++counter;
                // std::cout << "a" << std::endl;
            }
            camino.setVisitado(verticePivote); // se guarda el pivote como visitado

            Vertice verticeOptimal = grafo.PrimerVertice();
            char verticeOptimalEtiqueta = grafo.Etiqueta(verticeOptimal);
            // este loop permite encontrar el vertice del grafo que tiene como etiqueta a verticePivote
            while (verticeOptimalEtiqueta != verticePivote)
            {
                // std::cout << "b" << std::endl;
                verticeOptimal = grafo.SiguienteVertice(verticeOptimal);
                verticeOptimalEtiqueta = grafo.Etiqueta(verticeOptimal);
            }

            Vertice verticeAdyacente = grafo.PrimerVerticeAdyacente(verticeOptimal);
            // este loop permite cambiar en la listaDijkstra camino todos los pesos menores a los ya encontrados
            while (verticeAdyacente != verticeNulo)
            {

                size_t nuevoPeso = grafo.Peso(verticeOptimal, verticeAdyacente) + camino.getPeso(verticeOptimalEtiqueta);

                if (nuevoPeso < camino.getPeso(grafo.Etiqueta(verticeAdyacente)))
                {
                    camino.setPeso(grafo.Etiqueta(verticeAdyacente), nuevoPeso);
                    camino.setAnterior(grafo.Etiqueta(verticeAdyacente), verticePivote);
                }
                verticeAdyacente = grafo.SiguienteVerticeAdyacente(verticeOptimal, verticeAdyacente);
                // std::cout << "c" << std::endl;
            }

            ++contador;
        }
        // std::cout << "se termino el ciclo principal" << std::endl;

        return camino;
    }

    std::vector<std::vector<size_t>> nVecesDijkstra(const Grafo &grafo)
    {
        const size_t numVertices = grafo.NumVertices();
        Vertice vertice = grafo.PrimerVertice();

        std::vector<std::vector<size_t>> matrizCostos(numVertices
            , std::vector<size_t>(numVertices));

        for (size_t  ejeX = 0;  ejeX < numVertices; ++ ejeX)
        {
            ListaDijkstra camino = Dijkstra(grafo, vertice);
            vertice = grafo.SiguienteVertice(vertice);

            for (size_t ejeY = 0; ejeY < numVertices; ++ejeY) {
                matrizCostos[ejeX][ejeY]
                    = camino.getPesoPorIndice(ejeY);
            }
        }

        return matrizCostos;
    }

}
