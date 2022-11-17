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

    static Lista<Vertice>* Dijkstra(Grafo grafo, Vertice &inicio)
    {
        Lista<Vertice> *camino;
        int cantidadVertices = grafo.NumVertices();
        int pesos[cantidadVertices-1]; 
        



        return camino;
    }

    static void Floyd()
    {
    }

    static void imprimirGrafo(Grafo grafo){
        #if defined(MATRIZ)
            grafo.ImprimirGrafo();
        #else
            grafo.ImprimirVertices();
            // tambien se deberia imprimir las arristas
        #endif 
    }
};
#endif
