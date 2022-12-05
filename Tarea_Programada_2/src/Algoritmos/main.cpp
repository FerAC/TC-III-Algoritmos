#include "Controlador.hpp"
#include "Prim.hpp"
#include "HamiltonBERA.hpp"
#include <iostream>

int main()
{
    Grafo grafo;
    
    char lista[] = {'a','b','c','d','e','f'}; 
    for (int i = 0; i < 6; i++)
    {
        grafo.AgregarVertice(lista[i]);
    }

    Vertice a = Controlador::buscarVertice(grafo, 'a'); 
    Vertice b = Controlador::buscarVertice(grafo, 'b');
    Vertice c = Controlador::buscarVertice(grafo, 'c');
    Vertice d = Controlador::buscarVertice(grafo, 'd');
    Vertice e = Controlador::buscarVertice(grafo, 'e');
    Vertice f = Controlador::buscarVertice(grafo, 'f');

    grafo.AgregarArista(a, b, 2);
    grafo.AgregarArista(a, c, 3);
    grafo.AgregarArista(a, d, 10);
    grafo.AgregarArista(a, e, 5);
    grafo.AgregarArista(a, f, 5);
    grafo.AgregarArista(b, c, 4);
    grafo.AgregarArista(b, d, 1);
    grafo.AgregarArista(b, e, 3);
    grafo.AgregarArista(b, f, 8);
    grafo.AgregarArista(c, d, 10);
    grafo.AgregarArista(c, e, 7);
    grafo.AgregarArista(c, f, 8);
    grafo.AgregarArista(d, e, 2);
    grafo.AgregarArista(d, f, 2);
    grafo.AgregarArista(e, f, 9);


    ListaDijkstra listaDijkstra(grafo.NumVertices());
    Controlador::Dijkstra(grafo, f, listaDijkstra);
    listaDijkstra.imprimirLista();
    std::cout << std::endl;
    //Controlador::nVecesDijkstra(grafo);
    
    /* TEST HAMILTON BERA 
    */

    std::vector<Vertice> solucionHamiltonBera = HamiltonBERA::Hamilton(grafo);
    for (size_t it = 0; it < solucionHamiltonBera.size(); ++it) {
        std::cout << "[" << it << "]\t" << solucionHamiltonBera[it].getEtiqueta() << std:: endl;
    }

    // TEST DIJKSTRA

    // TEST KRUSKAL
    /*
    Grafo grafoMinimo;
    Controlador::Kruskal(grafo, grafoMinimo);
    Controlador::imprimirGrafo(grafo);
    Controlador::imprimirGrafo(grafoMinimo);

    std::cout<<"\n"<<std::endl;
    //*/
    // char listaA[] = {'a','a','a','a','a','b','b', 'b','c', 'c', 'e', 'f'}; 
    // char listaB[] = {'b','c','d','e','f','c','d','f','e', 'f', 'f', 'd'};
    // int listaP[] = {2, 8, 6, 7, 3, 3, 9, 5, 1, 6, 4, 9};
    // Vertice x = Controlador::buscarVertice(grafo, listaA[0]);
    // Vertice y = Controlador::buscarVertice(grafo, listaB[0]);
    // std::cout << "Se va a agregar una arista entre " << x.getEtiqueta() << " y "<< y.getEtiqueta() << " con peso " << listaP[0] << std::endl;
    // grafo.AgregarArista(x, y, listaP[0]); 
    // for (int i = 1; i < 12; i++)
    // {
    //     x = Controlador::buscarVertice(grafo, listaA[i]);
    //     y = Controlador::buscarVertice(grafo, listaB[i]);
    //     std::cout << "Se va a agregar una arista entre " << x.getEtiqueta() << " y " << y.getEtiqueta() << " con peso " << listaP[i] << std::endl;
    //     grafo.AgregarArista(x, y, listaP[i]);
    // }
    // std::cout<<"B"<< std::endl;
    // Vertice NULO;

    // for (Vertice v = grafo.PrimerVertice(); v!=NULO; v= grafo.SiguienteVertice(v)) {
    //     grafo.ImprimirConexiones(v); 
    // }

    // TEST DIJKSTRA N VECES
    // Controlador::nVecesDijkstra(grafo);
   
    /*
    grafo.AgregarArista(a, d, 4);
    grafo.AgregarArista(b, a, 20);
    grafo.AgregarArista(b, d, 3);
    grafo.AgregarArista(c, a, 6);
    grafo.AgregarArista(c, b, 10);
    grafo.AgregarArista(d, c, 5);
    // int miPeso = grafo.Peso(a, d);
    // std::cout<< "Peso  :" << miPeso << std::endl;
   */
//    Vertice a = buscarVertice(grafo, 'a'); 
//    Vertice b = buscarVertice(grafo, 'b');
//    Vertice c = buscarVertice(grafo, 'c');
//    Vertice d = buscarVertice(grafo, 'd');
   
   /*
     grafo.ImprimirConexiones(a);
     grafo.ImprimirConexiones(b);
     grafo.ImprimirConexiones(c);
     grafo.ImprimirConexiones(d);
*/

    // std::cout<<"*********************************"<< std::endl;
    // Vertice inicio = grafo.PrimerVertice();\
    // std::cout<<"*******************AAAA***********"<< std::endl;
    // size_t cantidadVertices = grafo.NumVertices();
    // std::cout<<"*****************BBB***********"<< std::endl;
    // ListaDijkstra listaCaminosMasCortos(cantidadVertices);
    // std::cout<<"*****************CCC***********"<< std::endl;
    // Controlador::Dijkstra(grafo, inicio, listaCaminosMasCortos);
    // std::cout<<"*****************DDD***********"<< std::endl;
    // Controlador::imprimirListaDijkstra(listaCaminosMasCortos);

    
    
   //grafo.ImprimirGrafo();
   // std::cout<< "Ya se creo" << std::endl;
    
    // std::cout << grafo.Peso(a, b);
    /*
    size_t** matriz = Prim::Floyd(grafo);

    for (size_t i = 0; i < grafo.NumVertices(); i++)
    {
        for (size_t j = 0; j < grafo.NumVertices(); j++)
        {
            std::cout << matriz[i][j] << " ";
        }
        std::cout<< "\n";

    }
   */
   
   /*
    std::cout<< "VOY A EJECUTAR PRIM" << std::endl;
    Grafo grafoPrim = Prim::primMetodo(grafo); 
    Vertice vertice;
    
    //std::cout<< "Termine Prim" << std::endl;
    
    for (size_t i = 0; i < grafoPrim.NumVertices(); i++)
    {
        if (i == 0) {
            vertice = grafoPrim.PrimerVertice();
        } else{
            vertice = grafoPrim.SiguienteVertice(vertice); 
        }
        grafoPrim.ImprimirConexiones(vertice);  
    }
    

   */

    return 0;
}