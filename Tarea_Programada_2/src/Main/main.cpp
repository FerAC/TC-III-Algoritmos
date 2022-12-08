#include <iostream>  // DEBUG

#include "Controlador.hpp"
#include "Pruebas.hpp"
#include "GrafoImplementado.hpp"
#include "Algoritmos.hpp"
#include <set>
#include <map>

int main()
{
    // CREAR 
    Grafo grafoEntrada;

     //GRAFO MANUAL
     //   Vertice a = grafoEntrada.AgregarVertice('a');
      //  Vertice b = grafoEntrada.AgregarVertice('b');
      //  Vertice c = grafoEntrada.AgregarVertice('c');
        //Vertice d = grafoEntrada.AgregarVertice('d');
        /*
        Vertice e = grafoEntrada.AgregarVertice('e');
        Vertice f = grafoEntrada.AgregarVertice('f');
        */

      //  grafoEntrada.AgregarArista(a, b, 2);
       // grafoEntrada.AgregarArista(a, c, 8);
        //grafoEntrada.AgregarArista(a, d, 6);
       // grafoEntrada.AgregarArista(a, e, 7);
        //grafoEntrada.AgregarArista(a, f, 3);
       // grafoEntrada.AgregarArista(b, c, 3);
        //grafoEntrada.AgregarArista(b, d, 9);
       // grafoEntrada.AgregarArista(c, e, 1);
       // grafoEntrada.AgregarArista(c, f, 6);
       // grafoEntrada.AgregarArista(d, f, 9);
      //  grafoEntrada.AgregarArista(e, f, 4);

    // CREAR GRAFO MALLA
    Pruebas::crearGrafoMalla(40, grafoEntrada);

    // Render
    // Controlador::imprimirGrafoCSAcademy(grafoEntrada);

    // Algoritmo
    //std::vector<std::vector<size_t>> matrizCostos 
    //   = Algoritmos::Floyd(grafoEntrada);
    std::map<size_t, std::set<Vertice>> * coloreo = Algoritmos::Colorear(grafoEntrada);
    std::cout<< "Cant colores : " << std::endl;
    std::cout << coloreo->size() << std::endl;
    delete coloreo; 
    
   //std::cout << coloreo.cantidadColores << std::endl;

    // Render
    // for(size_t i = 0; i < matrizCostos.size(); ++i) {
    //     std::cout << '[';
    //     for(size_t j = 0; j < matrizCostos[i].size(); ++j) {
    //         std::cout << matrizCostos[i][j] << '\t';
    //     }
    //     std::cout << ']' << std::endl;
    // }

    return 0;
}
