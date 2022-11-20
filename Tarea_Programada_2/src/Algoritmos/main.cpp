//#include "Controlador.hpp"
#include "Prim.hpp"
#include <iostream>




int main(){

    Grafo grafo;
    // se llena el grafo de vertices
    Vertice a = grafo.AgregarVertice('a');
    Vertice b = grafo.AgregarVertice('b');
    Vertice c = grafo.AgregarVertice('c');
    Vertice d = grafo.AgregarVertice('d');

    /*
    Vertice e = grafo.AgregarVertice('e'); 

    // se crean aristas entre los vertices del grafo
    grafo.AgregarArista(a, b, 2);
    grafo.AgregarArista(a, c, 3);
    grafo.AgregarArista(a, d, 10);
    grafo.AgregarArista(d, e, 5);
    grafo.AgregarArista(c, d, 4);

    // TEST DIJKSTRA
    Vertice inicio = grafo.PrimerVertice();
    size_t cantidadVertices = grafo.NumVertices();
    ListaDijkstra listaCaminosMasCortos(cantidadVertices);
    Controlador::Dijkstra(grafo, inicio, listaCaminosMasCortos);
    Controlador::imprimirListaDijkstra(listaCaminosMasCortos);

    // TEST KRUSKAL
    std::list<arista> listaKruskal;
    Controlador::Kruskal(grafo, listaKruskal);
    






    Controlador::imprimirGrafo(grafo);

    std::cout<<"\n"<<std::endl;
    */
    grafo.AgregarArista(a, d, 4);
    grafo.AgregarArista(b, a, 20);
    grafo.AgregarArista(b, d, 3);
    grafo.AgregarArista(c, a, 6);
    grafo.AgregarArista(c, b, 10);
    grafo.AgregarArista(d, c, 5);
    grafo.ImprimirConexiones(a);
    grafo.ImprimirConexiones(b);
    grafo.ImprimirConexiones(c);
    grafo.ImprimirConexiones(d);
    std::cout<< "Ya se creo" << std::endl;
    
    std::cout << grafo.Peso(a, b);
    int** matriz = Prim::Floyd(grafo);  

    for (size_t i = 0; i < grafo.NumVertices(); i++)
    {
        for (size_t j = 0; j < grafo.NumVertices(); j++)
        {
            std::cout << matriz[i][j] << " ";
        }
        std::cout<< "\n";
        
    }
    
    return 0;


}