#include "Grafo.hpp"

#include <iostream>

int main(){
    Grafo grafo;
    Vertice a = grafo.AgregarVertice('a');
    Vertice b = grafo.AgregarVertice('b');
    Vertice c = grafo.AgregarVertice('c');
    Vertice d = grafo.AgregarVertice('d');
    Vertice e = grafo.AgregarVertice('e'); 
    grafo.ImprimirVertices(); 
    std::cout<< "\n";
    grafo.AgregarArista(a, b, 2);
    grafo.AgregarArista(a, c, 3);
    grafo.AgregarArista(a, d, 1);
    grafo.AgregarArista(c, d, 4);
    grafo.ImprimirGrafo();
    std::cout<<"\n"; 
    grafo.EliminarArista(a, b);
    grafo.ImprimirGrafo();
    std::cout<<"\n"; 
    grafo.EliminarVertice(b); 
    std::cout<< "Num Vertices" << grafo.NumVertices() << std::endl;
    grafo.ImprimirVertices(); 
    std::cout<< "\n";
    grafo.ImprimirGrafo();
    std::cout<< "Num Vertices" << grafo.NumVertices() << std::endl;
    grafo.EliminarVertice(e); 
    grafo.ImprimirGrafo();
    return 0; 
}