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
    //grafo.AgregarArista(b, d, 5); 
   // grafo.ImprimirGrafo();
    std::cout<<"\n"; 
    grafo.ImprimirConexiones(a); 
    grafo.EliminarArista(a, b);
    
    //grafo.ImprimirGrafo();
    std::cout<<"\n"; 
    //grafo.EliminarVertice(b); 
    std::cout<< "Num Vertices" << grafo.NumVertices() << std::endl;
   // grafo.ImprimirVertices(); 
    std::cout<< "\n";
   // grafo.ImprimirGrafo();
   grafo.ImprimirConexiones(a); 
   grafo.ImprimirConexiones(b); 
    grafo.EliminarVertice(e); 
    std::cout<< "Num Vertices" << grafo.NumVertices() << std::endl;
   // grafo.ImprimirGrafo();
   return 0;
}