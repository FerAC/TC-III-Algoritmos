#ifndef PRUEBAS
#define PRUEBAS

#include <iostream>  // DEBUG

#include "Algoritmos.hpp"

// TODO(us): Cambiar invocaciones para que compile
namespace Pruebas {

    // ALGORITMOS

    void static pruebaDijkstra(Grafo &grafo) {
        Vertice vertice = grafo.PrimerVertice();
        Algoritmos::Dijkstra(grafo, vertice);
    }

    void static pruebaDijkstraN(Grafo &grafo) {
        ListaDijkstra camino(grafo.NumVertices());
        Vertice vertice = grafo.PrimerVertice();
        Vertice verticeNulo;
        Algoritmos::nVecesDijkstra(grafo);
        
    // while (vertice != verticeNulo) {
        //   Algoritmos::Dijkstra(grafo, vertice, camino);
        // vertice = grafo.SiguienteVertice(vertice);
        //}              
    }

    void static pruebaFloyd(Grafo &grafo) {
        Algoritmos::Floyd(grafo);
    }

    void static pruebaKruskal(Grafo &grafo) {
        Grafo recipiente;
        Algoritmos::Kruskal(grafo, recipiente);
    }

    void static pruebaPrim(Grafo &grafo) {
        Grafo recipiente;
        Algoritmos::Prim(grafo, recipiente);
    }

    void static pruebaColorear(Grafo &grafo) {
        Algoritmos::colorear(grafo);
    }

    // CREAR GRAFOS

    // TODO(us): Devuelven una copia, pero no tenemos un constructor por copia, ni asignamiento, de grafo
    void static crearGrafoArana(size_t limite, Grafo& grafo) {
        //Las etiquetas van de 33 a limite 
        //Todos se conectan al vertice con la etiqueta 33 (ascii)

        Vertice verticeEnComun = grafo.AgregarVertice('!'); 
        srand(time(NULL));
        
        for (size_t i = 34; i < limite; i++)
        {
            size_t num = 1 + rand() % 1000;
            char etiqueta = i;
            Vertice a = grafo.AgregarVertice(etiqueta);
            grafo.AgregarArista(a,verticeEnComun, num); 
        }
        const Vertice NULO;
        size_t j = 34;
        for (Vertice i = grafo.PrimerVertice(); i!=NULO; i = grafo.SiguienteVertice(i))
        {
            if (j++%2) { //min conecto con dos de forma aleatoria
                for (size_t t = 0; i < 2; t++)
                {
                    bool iguales = true; 
                    size_t num; 
                    while (iguales)
                    {
                        num = 1 + rand() % limite;
                        if (num!=j)
                        {
                            iguales = false; 
                        }
                        
                    }
                    size_t peso = 1 + rand() % 1000;
                    Vertice a = Algoritmos::buscarVertice(grafo, num);
                    if (!grafo.ExisteArista(i, a)) {
                        grafo.AgregarArista(i, a, peso);
                    }
                }
            } else{ //max
                for (size_t t = 34; i < limite-1; t++)
                {
                    if (t != j)
                    {
                        bool iguales = true; 
                        size_t peso = 1 + rand() % 1000;
                        Vertice a = Algoritmos::buscarVertice(grafo, t);
                        if (!grafo.ExisteArista(i, a)) {
                            grafo.AgregarArista(i, a, peso);
                        }
                    }
                } 
            }

            // Ya terminamos de crear el grafo araña
            return;
        }
    }

    void static crearGrafoCircular(size_t limite, Grafo& grafo) {
        char etiqueta = 33;
        Vertice anterior = grafo.AgregarVertice(etiqueta); 
        for (size_t i = 34; i < limite; i++)
        {   
            etiqueta = i;
            Vertice actual = grafo.AgregarVertice(etiqueta);
            size_t peso = 1 + rand() % 1000;
            grafo.AgregarArista(anterior, actual, peso);
            anterior = actual; 
        }

        // Ya terminamos de crear el grafo circular
        return;
    }

    void static crearGrafoMalla(size_t limite, Grafo& grafo) {

        for (size_t i = 33; i < limite; i++)
        {
            char etiqueta = i;
            // TODO(us): Aqui se agregan las etiquetas?
        }
        for (size_t i = 33; i < limite; i++)
        {
            char buscado = i;
            Vertice salida = Algoritmos::buscarVertice(grafo, i);
            //Cuatro casos posibles +1, -1, +4, -4
            if (i-1 >=33)
            {
                buscado = i-1;
                grafo.AgregarArista(Algoritmos::buscarVertice(grafo, buscado-1),salida, 1 + rand() % 1000) ;
            }
            if (i+1 <=limite)
            {
                buscado = i+1;
                grafo.AgregarArista(Algoritmos::buscarVertice(grafo, buscado-1),salida, 1 + rand() % 1000) ;
            }
                if (i-4 >=33)
            {
                buscado = i-4;
                grafo.AgregarArista(Algoritmos::buscarVertice(grafo, buscado-1),salida, 1 + rand() % 1000) ;
            }
            if (i+4 <=limite)
            {
                buscado = i+4;
                grafo.AgregarArista(Algoritmos::buscarVertice(grafo, buscado-1),salida, 1 + rand() % 1000) ;
            }
        } 

        // Ya terminamos de crear el grafo malla
        return;
    }

};

#endif
