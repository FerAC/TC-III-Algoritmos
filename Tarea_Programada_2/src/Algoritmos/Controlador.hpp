#ifndef CONTROLADOR_ALGORITMOS_GRAFOS
#define CONTROLADOR_ALGORITMOS_GRAFOS

#if defined(MATRIZ)
#include "../MatrizAdyacencia/Grafo.hpp"
#define VERSION_GRAFO "GRAFO REPRESENTADO CON MATRIZ DE ADYACENCIA"
#else
#include "../ListaAdyacencia/Grafo.hpp"
#define VERSION_GRAFO "GRAFO REPRESENTADO CON LISTA DE ADYACENCIA"
#endif

#include "../2/Lista.hpp"
#include <iostream>

class Controlador
{
private:
    // Grafo grafo;

public:
    Controlador() {}

    ~Controlador() {}

    static void Prim()
    {
    }

    static void Kruskal()
    {
    }

    static Lista<{Vertice, int}> *Dijkstra(Grafo grafo, Vertice &inicio)
    {
        Lista<{Vertice, int}> *camino;
        size_t cantidadVertices = grafo.NumVertices();

        Vertice vertice = grafo.PrimerVertice();

        // primero llenamos la lista con la etiqueta de cada elemento y un valor mas cercano al infinito al cual tenemos acceso
        for (size_t i = 0; i < cantidadVertices; ++i)
        {
            if (vertice.getEtiqueta() != inicio.getEtiqueta())
            {
                camino->insertar({vertice.getEtiqueta(), 2147483647});
            }
            vertice = grafo.SiguienteVertice(vertice);
        }

        vertice = grafo.PrimerVerticeAdyacente(inicio);
       //  Vertice verticeNulo;

        // poner el costo de las arista del vertice inicio
        while (vertice.esNulo() != 1)
        {
            // agregar a camino el peso de la arista            

            vertice = grafo.SiguienteVerticeAdyacente(vertice);
        }


        




        return camino;
    }

    static void Floyd()
    {
    }

    static void imprimirGrafo(Grafo grafo)
    {
        #if defined(MATRIZ)
            grafo.ImprimirGrafo();
        #else
            grafo.ImprimirVertices();
            // tambien se deberia imprimir las arristas
        #endif
    }
};
#endif
