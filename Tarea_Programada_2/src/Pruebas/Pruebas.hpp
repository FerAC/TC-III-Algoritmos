#ifndef PRUEBAS
#define PRUEBAS

#include <iostream>  // DEBUG
#include <cassert>

#include "Algoritmos.hpp"

// TODO(us): Cambiar invocaciones para que compile
namespace Pruebas {

    // ALGORITMOS

    void static pruebaDijkstra(const Grafo &grafo) {
        Vertice vertice = grafo.PrimerVertice();
        Algoritmos::Dijkstra(grafo, vertice);
    }

    void static pruebaDijkstraN(const Grafo &grafo) {
        Algoritmos::nVecesDijkstra(grafo);       
    }

    void static pruebaFloyd(const Grafo &grafo) {
        Algoritmos::Floyd(grafo);
    }

    void static pruebaKruskal(const Grafo &grafo) {
        Grafo recipiente;
        Algoritmos::Kruskal(grafo, recipiente);
    }

    void static pruebaPrim(const Grafo &grafo) {
        Grafo recipiente;
        Algoritmos::Prim(grafo, recipiente);
    }

    void static pruebaColorear(Grafo &grafo) {
        Algoritmos::Colorear(grafo);
    }

    // CREAR GRAFOS

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
            if (j%2) { //min conecto con dos de forma aleatoria
                for (size_t t = 0; t < 2; t++)
                {
                    bool iguales = true; 
                    size_t num = 34 + (double(rand()) / RAND_MAX) * (limite - 34); 
                    while (num==j)
                    {
                        num = 34 + (double(rand()) / RAND_MAX) * (limite - 34); 
                    }
                    size_t peso = 1 + rand() % 1000;
                    std::cout<< "NUM " << num << std::endl; 
                    int noHaceNada;
                    
                    char numAsChar = num; 
                    Vertice v = Algoritmos::BuscarVertice(grafo, numAsChar);
                    if ((!grafo.ExisteArista(i, v)) && i != v) {
                        grafo.AgregarArista(i, v, peso);
                    }
                }
            } else{ //max
                for (size_t t = 34; t < limite-1; t++)
                {
                    if (t != j)
                    {
                        size_t peso = 1 + rand() % 1000;
                        char numAsChar = t; 
                        Vertice c = Algoritmos::BuscarVertice(grafo, numAsChar);

                        if ((!grafo.ExisteArista(i, c)) && (i != c)) {
                            grafo.AgregarArista(i, c, peso);
                        }
                    }
                } 
            }

            j++;
        }
        
        // Ya terminamos de crear el grafo araña
        return;
    }

    void static crearGrafoCircular(size_t limite, Grafo& grafo) {
        char etiqueta = 33;
        Vertice anterior = grafo.AgregarVertice(etiqueta); 
        Vertice primero = anterior; 
        for (size_t i = 34; i <= limite; i++)
        {   
            etiqueta = i;
            Vertice actual = grafo.AgregarVertice(etiqueta);
            size_t peso = 1 + rand() % 1000;
            if(i==limite){
                grafo.AgregarArista(anterior, actual, peso);
                grafo.AgregarArista(primero, actual, peso);
            } else{
                grafo.AgregarArista(anterior, actual, peso);
            }
            anterior = actual; 
        }
        
        // Ya terminamos de crear el grafo circular
        return;
    }

    void static crearGrafoMalla(size_t limite, Grafo& grafo) {

        for (size_t i = 33; i < limite; i++)
        {
            char etiqueta = i;
            grafo.AgregarVertice(etiqueta);
        }
        Vertice salida = grafo.PrimerVertice();
        for (size_t i = 33; i < limite; i++)
        {
            char buscado = i;
           
            //Cuatro casos posibles +1, -1, +4, -4
            if (i-1 >=33)
            {
                buscado = i-1;
                
                
                    if (!grafo.ExisteArista(salida, Algoritmos::BuscarVertice(grafo, buscado)))
                    {
                        grafo.AgregarArista(Algoritmos::BuscarVertice(grafo, buscado),salida, 1 + rand() % 1000) ;
                    
                    }
                
                
            }
            if (i+1 <limite)
            {
                buscado = i+1;
                
                    if (!grafo.ExisteArista(salida, Algoritmos::BuscarVertice(grafo, buscado)))
                    {
                        grafo.AgregarArista(Algoritmos::BuscarVertice(grafo, buscado),salida, 1 + rand() % 1000) ;
                    
                    }
               
            }
            if (i-4 >=33)
            {
                buscado = i-4;
                
                    if (!grafo.ExisteArista(salida, Algoritmos::BuscarVertice(grafo, buscado)))
                    {
                        grafo.AgregarArista(Algoritmos::BuscarVertice(grafo, buscado),salida, 1 + rand() % 1000) ;
                    
                    }
               
                
                 
            }
            if (i+4 <limite)
            {
                buscado = i+4;
               
                    if (!grafo.ExisteArista(salida, Algoritmos::BuscarVertice(grafo, buscado)))
                    {
                        grafo.AgregarArista(Algoritmos::BuscarVertice(grafo, buscado),salida, 1 + rand() % 1000) ;
                    
                    }
                
            }
            salida = grafo.SiguienteVertice(salida);
        } 

        // Ya terminamos de crear el grafo malla
        return;
    }

};

#endif
