#ifndef CONTROLADOR_ALGORITMOS_GRAFOS
#define CONTROLADOR_ALGORITMOS_GRAFOS

#if defined(MATRIZ)
#include "../MatrizAdyacencia/Grafo.hpp"
#define VERSION_GRAFO "GRAFO REPRESENTADO CON MATRIZ DE ADYACENCIA"
#else
#include "../ListaAdyacencia/Grafo.hpp"
#define VERSION_GRAFO "GRAFO REPRESENTADO CON LISTA DE ADYACENCIA"
#endif

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

    static void Dijkstra()
    {
    }

    static void Floyd()
    {
    }

    static void imprimirGrafo(Grafo grafo){
        return;
    }
};
#endif
