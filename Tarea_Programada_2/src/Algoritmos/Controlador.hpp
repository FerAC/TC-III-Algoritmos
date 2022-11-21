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
// #include <map>  // APO de Kruskal
// #include <set>  // conjunto de conjunto de Kruskal
#include <list> // lista de las n-1 aristas del arbol de minimo costa de Kruskal

// arista se usa como el objecto "par" usado en el algoritmo de kruskal
struct arista
{
    Vertice vertice1;
    Vertice vertice2;
};

class ListaDijkstra{
    friend class Controlador;

    public:

    int cantidadElementos = 0;
    int tamanoMax;
    bool *visitado;
    int *pesos;
    char *vertices;
    char *verticeAnterior;

    ListaDijkstra(size_t tamano){
        tamanoMax = tamano;
        pesos = new int[tamano];
        vertices = new char[tamano];
        verticeAnterior = new char[tamano];
        visitado = new bool[tamano];

        size_t contador = 0;
        while (contador<tamano)
        {
            visitado[contador] = false;
            ++contador;
        }
        
    }

    ~ListaDijkstra(){
        delete []pesos;
        delete []vertices;
        delete []verticeAnterior;
        delete []visitado;
    }

    void agregar(char verticeActual, char elVerticeAnterior, int peso){

        if(cantidadElementos < tamanoMax){
           
            vertices[cantidadElementos] = verticeActual;
            pesos[cantidadElementos] = peso;
            verticeAnterior[cantidadElementos] = elVerticeAnterior; 
            // std::cout<<"se agrego un elemento"<<std::endl;
            ++cantidadElementos;
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

    int getPesoPorIndice(size_t indice){
        return pesos[indice];
    }

    char getVerticePorIndice(size_t indice){
        return vertices[indice];
    }

    bool esVisitadoPorIndice(size_t indice){
        return visitado[indice];
    }

    void setVisitadorPorIndice(size_t indice){
        visitado[indice] = true;
    }

    void setVisitado(char verticeVisitado){
        int contador = 0;
        char vertice = vertices[contador];
        while (vertice != verticeVisitado)
        { 
            ++contador;
            vertice = vertices[contador];
        }
        visitado[contador] = true;
    }

    void imprimirLista(){
        size_t contador = 0;
        while (contador < cantidadElementos)
        {
             std::cout << vertices[contador] << "\t" << pesos[contador]  << "\t" << verticeAnterior[contador] << std::endl;          
             ++contador;
        }
        
    }

};

class Controlador
{
private:

public:
    Controlador() {}

    ~Controlador() {}

    static void Prim()
    {
    }


    static bool existeCiclosRecursivo(Grafo &grafo, std::list<bool> &visitados, Vertice &verticeActual){

    }

    static bool existeCiclos(Grafo &grafo){

        // recorrido por profundidad primero -> si hay un arco de retroceso, entonces hay ciclo
        int cantidadVertices = grafo.NumVertices();
        std::list<bool> visitados;
        Vertice primerVertice = grafo.PrimerVertice();
        bool esCiclico = existeCiclosRecursivo(grafo, visitados, primerVertice);
        return esCiclico;
    }

    static void Kruskal(Grafo &grafo, Grafo &grafoMinimo)
    {
        Vertice vertice = grafo.PrimerVertice();
        Vertice verticeNulo;

        // primero llenamos la lista con la etiqueta de cada elemento y un valor mas cercano al infinito al cual tenemos acceso
        while (vertice != verticeNulo)
        {
            char etiqueta = grafo.Etiqueta(vertice);
            grafoMinimo.AgregarVertice(etiqueta);
            vertice = grafo.SiguienteVertice(vertice);
        }

        while (existeCiclos(grafoMinimo) != true)
        {
            /* code */
        }
        
        



    }

    static void Dijkstra(Grafo grafo, Vertice &inicio, ListaDijkstra &camino)
    {
        size_t cantidadVertices = grafo.NumVertices();
        Vertice vertice = grafo.PrimerVertice();

        // primero llenamos la lista con la etiqueta de cada elemento y un valor mas cercano al infinito al cual tenemos acceso
        for (size_t i = 0; i < cantidadVertices; ++i)
        {
            if (grafo.Etiqueta(vertice) != grafo.Etiqueta(inicio))  // si el elemento no es el inicio dado por el usuario
            {
                camino.agregar(grafo.Etiqueta(vertice), grafo.Etiqueta(inicio), 2147483647);
                std::cout<< grafo.Etiqueta(vertice) <<std::endl;
            }else{                                                  // si el elemento es el inicio dado por el usuario
                camino.agregar(grafo.Etiqueta(vertice), grafo.Etiqueta(inicio), 0);
                std::cout<< grafo.Etiqueta(vertice) <<std::endl;
                camino.setVisitado(grafo.Etiqueta(inicio));         // se guarda el inicio como visitado
            }
            vertice = grafo.SiguienteVertice(vertice);
        }
        std::cout<<"TERMINO DE GUARDAR LAS ETIQUETAS EN CAMINO"<<std::endl;

        vertice = grafo.PrimerVerticeAdyacente(inicio);
        Vertice verticeNulo;

        // poner el vertice anterior y el costo de las aristas que salen de inicio 
        while (vertice != verticeNulo)
        {
            std::cout<<grafo.Peso(inicio, vertice)<<std::endl;
            std::cout<<grafo.Etiqueta(vertice)<<std::endl;
            camino.setPeso(grafo.Etiqueta(vertice), grafo.Peso(inicio, vertice));
            vertice = grafo.SiguienteVerticeAdyacente(inicio, vertice);
        }
        std::cout<<"TERMINO DE GUARDAR LOS PESOS DE LOS VERTICES ADYACENTES AL NODO INICIAL"<<std::endl;

        size_t contador = 0;

        while (contador < cantidadVertices-2)
        {
            size_t counter = 0; // usado para pasar por cada elemento de camino
            char verticePivote = camino.getVerticePorIndice(counter);
            int pesoVerticePivote = 2147483647;
            int pesoContador;
            
            while (counter<cantidadVertices-1) // este loop permite encontrar el siguiente vertice que tenemos que estudiar, debe ser el menor que aun no fue visitado
            {
                pesoContador = camino.getPesoPorIndice(counter);
                std::cout<<"b"<<std::endl;
                bool esVisitado = camino.esVisitadoPorIndice(counter); // esVisitado es 0 si el counter elemento 
               
                if (!esVisitado) // estas 2 condiciones permiten saber si el elemento en la posicion counter es un elemento pivote valido o no
                {
                    if (pesoVerticePivote>pesoContador)
                    {
                        verticePivote = camino.getVerticePorIndice(counter);
                        pesoVerticePivote = camino.getPesoPorIndice(counter);
                    }
                }
                ++counter;
            }
            camino.setVisitado(verticePivote); // se guarda el pivote como visitado 

            Vertice verticeOptimal = grafo.PrimerVertice();
            char verticeOptimalEtiqueta = grafo.Etiqueta(verticeOptimal);
            // este loop permite encontrar el vertice del grafo que tiene como etiqueta a verticePivote
            while (verticeOptimalEtiqueta != verticePivote)
            {
                verticeOptimal = grafo.SiguienteVertice(verticeOptimal);
                verticeOptimalEtiqueta = grafo.Etiqueta(verticeOptimal);
            }

            Vertice verticeAdyacente = grafo.PrimerVerticeAdyacente(verticeOptimal);
            // este loop permite cambiar en la listaDijkstra camino todos los pesos menores a los ya encontrados
            while (verticeAdyacente != verticeNulo)
            {
                int nuevoPeso = grafo.Peso(verticeOptimal, verticeAdyacente) + camino.getPeso(verticeOptimalEtiqueta);

                if ( nuevoPeso < camino.getPeso(grafo.Etiqueta(verticeAdyacente)))
                {
                    camino.setPeso(grafo.Etiqueta(verticeAdyacente), nuevoPeso);
                    camino.setAnterior(grafo.Etiqueta(verticeAdyacente), verticePivote);
                }
                verticeAdyacente = grafo.SiguienteVerticeAdyacente(verticeOptimal, verticeAdyacente);
            }

            ++contador;
        }
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

    static void imprimirListaDijkstra(ListaDijkstra &camino){
        camino.imprimirLista();
    }
};
#endif
