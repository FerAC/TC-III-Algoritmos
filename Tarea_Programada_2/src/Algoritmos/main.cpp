/**
 * compile:  g++ main.cpp
*/
#include "Controlador.hpp"



int main(){

    Grafo grafo;

    // se llena el grafo de vertices
    Vertice a = grafo.AgregarVertice('a');
    Vertice b = grafo.AgregarVertice('b');
    Vertice c = grafo.AgregarVertice('c');
    Vertice d = grafo.AgregarVertice('d');
    Vertice e = grafo.AgregarVertice('e'); 

    // se crean aristas entre los vertices del grafo
    grafo.AgregarArista(a, b, 2);
    grafo.AgregarArista(a, c, 3);
    grafo.AgregarArista(a, d, 1);
    grafo.AgregarArista(c, d, 4);

    Vertice inicio;
    inicio = grafo.PrimerVertice();
    Controlador::Dijkstra(grafo, inicio);
    Controlador::imprimirGrafo(grafo);


    return 0;


}