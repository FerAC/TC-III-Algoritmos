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
#include <utility>

// arista se usa como el objecto "par" usado en el algoritmo de kruskal
struct arista
{
    Vertice vertice1;
    Vertice vertice2;
};

class ListaDijkstra
{
    friend class Controlador;

public:
    int cantidadElementos = 0;
    int tamanoMax;
    bool *visitado;
    int *pesos;
    char *vertices;
    char *verticeAnterior;

    ListaDijkstra(size_t tamano)
    {
        tamanoMax = tamano;
        pesos = new int[tamano];
        vertices = new char[tamano];
        verticeAnterior = new char[tamano];
        visitado = new bool[tamano];

        size_t contador = 0;
        while (contador < tamano)
        {
            visitado[contador] = false;
            ++contador;
        }
    }

    ~ListaDijkstra()
    {
        delete[] pesos;
        delete[] vertices;
        delete[] verticeAnterior;
        delete[] visitado;
    }

    void agregar(char verticeActual, char elVerticeAnterior, int peso)
    {

        if (cantidadElementos < tamanoMax)
        {

            vertices[cantidadElementos] = verticeActual;
            pesos[cantidadElementos] = peso;
            verticeAnterior[cantidadElementos] = elVerticeAnterior;
            // std::cout<<"se agrego un elemento"<<std::endl;
            ++cantidadElementos;
        }
    }

    void setPeso(char verticeActual, int peso)
    {
        int contador = 0;
        char vertice = vertices[contador];
        while (vertice != verticeActual)
        {
            ++contador;
            vertice = vertices[contador];
        }
        pesos[contador] = peso;
    }

    void setAnterior(char verticeActual, char anterior)
    {
        int contador = 0;
        char vertice = vertices[contador];
        while (vertice != verticeActual)
        {
            ++contador;
            vertice = vertices[contador];
        }
        verticeAnterior[contador] = anterior;
    }

    int getPeso(char verticeActual)
    {
        int contador = 0;
        char vertice = vertices[contador];
        while (vertice != verticeActual)
        {
            ++contador;
            vertice = vertices[contador];
        }
        return pesos[contador];
    }

    int getPesoPorIndice(size_t indice)
    {
        return pesos[indice];
    }

    char getVerticePorIndice(size_t indice)
    {
        return vertices[indice];
    }

    bool esVisitadoPorIndice(size_t indice)
    {
        return visitado[indice];
    }

    void setVisitadorPorIndice(size_t indice)
    {
        visitado[indice] = true;
    }

    void setVisitado(char verticeVisitado)
    {
        int contador = 0;
        char vertice = vertices[contador];
        while (vertice != verticeVisitado)
        {
            ++contador;
            vertice = vertices[contador];
        }
        visitado[contador] = true;
    }

    void imprimirLista()
    {
        size_t contador = 0;
        while (contador < cantidadElementos)
        {
            std::cout << vertices[contador] << "\t" << pesos[contador] << "\t" << verticeAnterior[contador] << std::endl;
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

    static Vertice buscarVertice(Grafo &grafo, char etiqueta)
    {
        const Vertice NULO;
        for (Vertice vertice = grafo.PrimerVertice(); vertice != NULO; vertice = grafo.SiguienteVertice(vertice))
        {
            if (vertice.getEtiqueta() == etiqueta)
            {
                return vertice;
            }
        }
        return NULO;
    }

    static void nVecesDijkstra(Grafo grafo)
    {
        Vertice vertice = grafo.PrimerVertice();
        for (size_t i = 0; i < grafo.NumVertices(); ++i)
        {
            ListaDijkstra camino(grafo.NumVertices());
            std::cout << "dijkstra para el vertice: " << grafo.Etiqueta(vertice) << std::endl;
            Dijkstra(grafo, vertice, camino);
            vertice = grafo.SiguienteVertice(vertice);
            camino.imprimirLista();
            std::cout << std::endl;
        }
    }

    static void colorear(Grafo grafo)
    {
    }

    static bool existeCiclosRecursivo(Grafo &grafo, std::list<std::pair<bool, char>> &visitados, Vertice &verticeActual, Vertice &verticeAnterior)
    {
        bool resultado;
        // set vertice actual in visitado as true
        bool esVisitado = false;
        std::list<std::pair<bool, char>>::iterator iterador = visitados.begin();
        // se guarda el vertice actual como visitado
        while (esVisitado == false)
        {
            if (grafo.Etiqueta(verticeActual) == (*iterador).second)
            {
                // std::cout << "123" << std::endl;
                (*iterador).first = true;
                esVisitado = true;
            }
            else
            {
                ++iterador;
            }
            // std::cout << (*iterador).second << std::endl;
        }

        // std::cout << "AAAAAAAAAAAAAAAAAAAAAAA" << std::endl;

        Vertice verticeAdyacente = grafo.PrimerVerticeAdyacente(verticeActual);

        Vertice verticeNulo;
        size_t contador = 0;
        // se reitera para todos los vertices adyacentes del vertice actual
        // while (verticeAdyacente != verticeNulo)
        while (contador < grafo.NumVertices() - 1)
        {
            // si el adyacente ya es visitado y no es el anterior, entonces return true
            bool adyacenteVisitado;

            std::list<std::pair<bool, char>>::iterator i = visitados.begin();
            while (i != visitados.end())
            {
                // std::cout << "123" << std::endl;
                if ((*i).second == grafo.Etiqueta(verticeAdyacente))
                {
                    if ((*i).first == true)
                    {
                        adyacenteVisitado = true;
                    }
                    else
                    {
                        adyacenteVisitado = false;
                    }
                    i = visitados.end();
                }
                else
                {
                    ++i;
                }
            }

            // return true si se encontro con un elemento ya visitado y que no sea el padre
            if (verticeAdyacente != verticeAnterior && adyacenteVisitado)
            {
                // std::cout << "AAAAAAAAAAAAAAAAAAAAAAA" << std::endl;
                return true;
            }

            bool grafoVisitado = true;
            // i = visitados.begin();
            size_t counter = 0;
            // ciclo para saber si se visito todo el arbol
            // while (i != visitados.end())
            while (counter < visitados.size())
            {
                // std::cout << "zz" << std::endl;
                if ((*i).first == false)
                {
                    // std::cout << "oo" << std::endl;
                    grafoVisitado = false;
                    i = visitados.end();
                }
                ++counter;
                //++i;
            }

            if (grafoVisitado)
            {
                // std::cout << "BBBBBBBBBBBBBBBBBBBBBBB" << std::endl;
                return false;
            }
            else
            {
                // else llamar recursivamente
                // std::cout << "CCCCCCCCCCCCCCCCCCCCCCCCCC" << std::endl;
                resultado = existeCiclosRecursivo(grafo, visitados, verticeAdyacente, verticeActual);
            }

            verticeAdyacente = grafo.SiguienteVerticeAdyacente(verticeActual, verticeAdyacente);
            // std::cout << "BBBBBBBBBBBBBBBBBBBBBBBBB" << std::endl;
            ++contador;
        }
        return resultado;
    }

    static bool existeCiclos(Grafo &grafo)
    {

        // recorrido por profundidad primero -> si hay un arco de retroceso, entonces hay ciclo
        int cantidadVertices = grafo.NumVertices();
        Vertice vertice = grafo.PrimerVertice();

        std::list<std::pair<bool, char>> visitados;
        for (size_t i = 0; i < grafo.NumVertices(); ++i)
        {
            visitados.push_front(std::make_pair(false, grafo.Etiqueta(vertice)));
            vertice = grafo.SiguienteVertice(vertice);
            /// std::cout << "hello there" << std::endl;
        }

        Vertice primerVertice = grafo.PrimerVertice();
        bool esCiclico = existeCiclosRecursivo(grafo, visitados, primerVertice, primerVertice);
        std::cout << esCiclico << std::endl;
        return esCiclico;
    }

    static void Kruskal(Grafo grafo, Grafo &grafoMinimo)
    {
        Vertice vertice = grafo.PrimerVertice();
        Vertice verticeNulo;
        int cantidadAristas = 0;
        int cantidadVertices = grafo.NumVertices();

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

            int pesoMinimo = 2147483647;
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

    static void Dijkstra(Grafo grafo, Vertice &inicio, ListaDijkstra &camino)
    {
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
            int pesoVerticePivote = 2147483647;
            int pesoContador;

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

                int nuevoPeso = grafo.Peso(verticeOptimal, verticeAdyacente) + camino.getPeso(verticeOptimalEtiqueta);

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

    static void imprimirListaDijkstra(ListaDijkstra &camino)
    {
        camino.imprimirLista();
    }
};
#endif
