#include <iostream>  // DEBUG

#include "Controlador.hpp"
#include "Pruebas.hpp"
#include "GrafoImplementado.hpp"

int main()
{
    // Crear
    
    Grafo grafoEntrada;
    /*
    Vertice a = grafoEntrada.AgregarVertice('a');
    Vertice b = grafoEntrada.AgregarVertice('b');
    Vertice c = grafoEntrada.AgregarVertice('c');
    Vertice d = grafoEntrada.AgregarVertice('d');
    Vertice e = grafoEntrada.AgregarVertice('e');
    Vertice f = grafoEntrada.AgregarVertice('f');

    grafoEntrada.AgregarArista(a, b, 2);
    grafoEntrada.AgregarArista(a, c, 8);
    grafoEntrada.AgregarArista(a, d, 6);
    grafoEntrada.AgregarArista(a, e, 7);
    grafoEntrada.AgregarArista(a, f, 3);
    grafoEntrada.AgregarArista(b, c, 3);
    grafoEntrada.AgregarArista(b, d, 9);
    grafoEntrada.AgregarArista(c, e, 1);
    grafoEntrada.AgregarArista(c, f, 6);
    grafoEntrada.AgregarArista(d, f, 9);
    grafoEntrada.AgregarArista(e, f, 4);
    */

    Pruebas::crearGrafoMalla(60, grafoEntrada); 
    // Render
    Controlador::imprimirGrafoCSAcademy(grafoEntrada);

    // Algoritmo
    Grafo respuesta;
    Algoritmos::Kruskal(grafoEntrada, respuesta);
    //auto listaD = Algoritmos::Dijkstra(grafoEntrada, grafoEntrada.PrimerVertice()); 
    //listaD.imprimirLista(); 
    // Render
    std::cout<< "NC = " << grafoEntrada.NumVertices() << std::endl;
    std::cout<< "N = " << respuesta.NumVertices() << std::endl;
    std::cout<< "=============================RESPUESTA===================================" <<std::endl;
    Controlador::imprimirGrafoCSAcademy(respuesta);

    return 0;
}
