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


class ListaDijkstra{
    friend class Controlador;

    private:

    int cantidadElementos = 0;
    int tamanoMax;
    int *pesos;
    char *vertices;
    char *verticeAnterior;

    ListaDijkstra(size_t tamano){
        tamanoMax = tamano;
        int *pesos = new int[tamano];
        char *vertices = new char[tamano];
        char *verticeAnterior = new char[tamano];
    }

    ~ListaDijkstra(){
        delete []pesos;
        delete []vertices;
        delete []verticeAnterior;
    }

    void agregar(char verticeActual, char elVerticeAnterior, int peso){

        if(cantidadElementos <tamanoMax){
            vertices[cantidadElementos] = verticeActual;
            pesos[cantidadElementos] = peso;
            verticeAnterior[cantidadElementos] = elVerticeAnterior;
            ++ cantidadElementos;
        }
    }

    void setPeso(char verticeActual, int peso){
        int contador = 0;
        char vertice = vertices[contador];
        while (vertice != verticeActual)
        { 
            ++contador;
            vertice = vertices[contador];
        }
        pesos[contador] = peso;
    }

    void setAnterior(char verticeActual, char anterior){
        int contador = 0;
        char vertice = vertices[contador];
        while (vertice != verticeActual)
        { 
            ++contador;
            vertice = vertices[contador];
        }
        verticeAnterior[contador] = anterior;
    }

    int getPeso(char verticeActual){
        int contador = 0;
        char vertice = vertices[contador];
        while (vertice != verticeActual)
        { 
            ++contador;
            vertice = vertices[contador];
        }
        return pesos[contador];
    }

};

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

    static ListaDijkstra* Dijkstra(Grafo grafo, Vertice &inicio)
    {
        size_t cantidadVertices = grafo.NumVertices();
        ListaDijkstra* camino = new ListaDijkstra(cantidadVertices-1);
        Vertice vertice = grafo.PrimerVertice();

        // primero llenamos la lista con la etiqueta de cada elemento y un valor mas cercano al infinito al cual tenemos acceso
        for (size_t i = 0; i < cantidadVertices; ++i)
        {
            if (grafo.Etiqueta(vertice) != grafo.Etiqueta(inicio))
            {
               camino->agregar(grafo.Etiqueta(vertice), grafo.Etiqueta(inicio),2147483647);
            }
            vertice = grafo.SiguienteVertice(vertice);
        }

        vertice = grafo.PrimerVerticeAdyacente(inicio);
       
        Vertice verticeNulo;

        // poner el vertice anterior y el costo de las aristas que salen de inicio 
        while (vertice != verticeNulo)
        {
            camino->setPeso(grafo.Etiqueta(vertice), grafo.Peso(inicio, vertice));
            vertice = grafo.SiguienteVerticeAdyacente(inicio, vertice);
        }

        size_t contador = 0;

        while (contador < cantidadVerces-2)
        {
            
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
