#include <limits>  // Max de size_t
#include <queue>  // Cola de prioridad
#include <set>  // Conjunto

#include "GrafoImplementado.hpp"
#include "AuxiliaresHamiltonBERA.hpp"

bool existeCiclos(const Grafo& grafo);

namespace Algoritmos {

    /* TODO(us): Modificar con cola de prioridad, diccionario y contador?
    void Kruskal(const Grafo& grafo, Grafo& grafoMinimo)
    {
        Vertice vertice = grafo.PrimerVertice();
        Vertice verticeNulo;
        size_t cantidadAristas = 0;
        size_t cantidadVertices = grafo.NumVertices();

        // primero llenamos la lista con la etiqueta de cada elemento y un valor mas cercano al infinito al cual tenemos acceso
        while (vertice != verticeNulo)
        {
            std::cout << "a" << std::endl;
            char etiqueta = grafo.Etiqueta(vertice);
            grafoMinimo.AgregarVertice(etiqueta);
            vertice = grafo.SiguienteVertice(vertice);
        }
        // std::cout << "Se termino de insertar los vertices en grafo minimo" << std::endl;

        // se reitera para agregar todos los caminos minimos para que los vertices esten connectados y que no haya ciclos
        while (cantidadAristas != cantidadVertices - 1)
        {
            size_t pesoMinimo = std::numeric_limits<size_t>::max();
            Vertice verticeOptimalPartida = grafo.PrimerVertice();
            Vertice verticePartida = grafo.PrimerVertice();
            Vertice verticeLlegada = grafo.PrimerVerticeAdyacente(verticePartida);
            Vertice verticeOptimalLlegada = grafo.PrimerVerticeAdyacente(verticePartida);

            // std::cout << "a" << std::endl;

            // ciclo para saber cual es el siguiente camino mas corto
            while (verticePartida != verticeNulo)
            {
                // std::cout << "b" << std::endl;
                verticeLlegada = grafo.PrimerVerticeAdyacente(verticePartida);
                while (verticeLlegada != verticeNulo)
                {
                    // std::cout << "c" << std::endl;
                    if (grafo.Peso(verticePartida, verticeLlegada) < pesoMinimo)
                    {
                        // std::cout << "d" << std::endl;
                        pesoMinimo = grafo.Peso(verticePartida, verticeLlegada);
                        verticeOptimalLlegada = verticeLlegada;
                        verticeOptimalPartida = verticePartida;
                    }
                    verticeLlegada = grafo.SiguienteVerticeAdyacente(verticePartida, verticeLlegada);
                    // std::cout << "e" << std::endl;
                }
                verticePartida = grafo.SiguienteVertice(verticePartida);
            }

            // std::cout << "Se encontro el camino mas corto" << std::endl;

            // se borra la arista optimal del Grafo grafo
            grafo.EliminarArista(verticeOptimalPartida, verticeOptimalLlegada);

            // se agrega a grafoMinimo
            grafoMinimo.AgregarArista(verticeOptimalPartida, verticeOptimalLlegada, pesoMinimo);

            if (existeCiclos(grafoMinimo)) // si crea un ciclo en grafoMinimo, entonces se borra la arista de grafoMinimo
            {
                // std::cout << "AAAA" << std::endl;
                grafoMinimo.EliminarArista(verticeOptimalPartida, verticeOptimalLlegada);
            }
            else
            { // sino se incrementa cantidadArista de 1
                ++cantidadAristas;
            }
            // imprimirGrafo(grafoMinimo);
        }
    }
    */

    /// @brief Obtiene el árbol minimal de un grafo fuertemente conexo
    /// @param grafo Grafo fuertemente conexo tomado como para el cual sacar el arbol minimal
    /// @param grafo Grafo vacío donde colocar la respuesta del árbol minimal
    /// @return Arbol minimal del grafo de entrada
    void Kruskal(const Grafo& grafo, Grafo& grafoRecipiente) {

        // Si el árbol está vacío, no hay nada que se pueda hacer
        if (grafo.NumVertices() == 0) {
            return;
        }

        // También llevemos cuenta de una cola de prioridad de aristas, 
        // para sacar las de menor costo cada vez
        std::priority_queue<Arista, std::vector<Arista>, std::greater<Arista>>
        aristasPorSacar;

        // Poblemos esta cola de prioridad con las aristas disponibles en el grafo
        for (Vertice v = grafo.PrimerVertice(); v != Vertice(); v = grafo.SiguienteVertice(v)) {
            for (Vertice w = grafo.PrimerVerticeAdyacente(v);
                w != Vertice(); 
                w = grafo.SiguienteVerticeAdyacente(v, w)) {
                    aristasPorSacar.push(Arista(v, w, grafo.Peso(v, w)));
            }
        }

        // Si no hay aristas que se puedan sacar, no hay nada que se pueda hacer
        if (aristasPorSacar.empty()) {
            return;
        }

        // Llevemos cuenta de los vértices visitados
        std::set<Vertice> verticesVisitados;

        // Y de las aristas que colocaremos en el grafo de ser exitosos
        std::vector<Arista> aristasPorMeter;
        aristasPorMeter.reserve(grafo.NumVertices());

        // Saquemos aristas hasta que se nos acaben, o hayamos llegado 
        // a utilizar n-1 de ellas
        size_t aristasSacadas = 0;
        const size_t n = grafo.NumVertices();
        while (aristasSacadas < n-1 && !aristasPorSacar.empty()) {
            // Saquemos la arista de menor costo hasta ahora
            Arista aristaMenorCosto = aristasPorSacar.top();
            aristasPorSacar.pop();

            // Si al menos uno de los dos vértices de la arista no ha sido
            // visitado todavía, entonces no genera un ciclo
            if (!verticesVisitados.contains(aristaMenorCosto.first)
                || !verticesVisitados.contains(aristaMenorCosto.second)) {
                // Añadamos ambos vértices, si no han sido añadidos previamente
                // al árbol minimal. Además, marquemoslos como visitados
                if (!verticesVisitados.contains(aristaMenorCosto.first)) {
                    verticesVisitados.insert(aristaMenorCosto.first);
                }

                if (!verticesVisitados.contains(aristaMenorCosto.second)) {
                    verticesVisitados.insert(aristaMenorCosto.second);
                }

                // Añadamos esta arista a la lista de aristas por meter al árbol minimal
                aristasPorMeter.push_back(aristaMenorCosto);

                // Y aumentemos el contador de aristas sacadas
                aristasSacadas += 1;
            }
        }

        // Si sacamos menos de n-1 aristas, entonces no existe arbol minimal
        if (aristasSacadas < n-1) {
            return;
        }

        // Como sacamos n-1 aristas, en teoría hemos sacado el árbol minimal
        // Poblemos la respuesta

        // Volveremos a visitar los vértices para añadirlos únicamente si no se
        // han añadido antes
        verticesVisitados.clear();
        for (size_t i = 0; i < n-1; ++i) {
            // Añadamos ambos vértices, si no han sido añadidos previamente
            // al árbol minimal. Además, marquemoslos como visitados
            if (!verticesVisitados.contains(aristasPorMeter[i].first)) {
                grafoRecipiente.AgregarVertice(grafo.Etiqueta(aristasPorMeter[i].first));
                verticesVisitados.insert(aristasPorMeter[i].first);
            }

            if (!verticesVisitados.contains(aristasPorMeter[i].second)) {
                grafoRecipiente.AgregarVertice(grafo.Etiqueta(aristasPorMeter[i].second));
                verticesVisitados.insert(aristasPorMeter[i].second);
            }

            grafoRecipiente.AgregarArista(aristasPorMeter[i].first
                , aristasPorMeter[i].second
                , aristasPorMeter[i].pesoAsociado);
        }

        // Ya terminamos el algoritmo
        return;
    }

}
