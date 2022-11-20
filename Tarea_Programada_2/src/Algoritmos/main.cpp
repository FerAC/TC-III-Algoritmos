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

   




    return 0;


}