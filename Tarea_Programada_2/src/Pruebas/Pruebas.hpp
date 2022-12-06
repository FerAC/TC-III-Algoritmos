#ifndef CONTROLADOR
#define CONTROLADOR

#include <iostream>

#include "Algoritmos.hpp"

namespace Controlador {

    void iniciar() {
        Grafo grafo;
        bool continuar;

        do
        {
            std::cout<< "Cual operador basico deseea utilizar?" << std::endl;
            std::cout<< "1- Agregar vertice" << std::endl;
            std::cout<< "2- Eliminar vertice" << std::endl;
            std::cout<< "3- Modificar etiqueta" << std::endl;
            std::cout<< "4- Agregar arista" << std::endl;
            std::cout<< "5- Eliminar arista"<< std::endl;
            std::cout<< "6- Modificar peso" << std::endl;
            std::cout<< "7- Peso" << std::endl;
            std::cout<< "8- Primer vertice" << std::endl;
            std::cout<< "9- Siguiente vertice" << std::endl;
            std::cout<< "10- Primer vertice adyacente" << std::endl;
            std::cout<< "11- Siguiente vertice adyacente" << std::endl;
            std::cout<< "12- Num vertices" << std::endl;
            std::cout<< "13- Destruir Grafo" << std::endl;

            int decision;
            std::cin >> decision;

            switch (decision)
            {
            case 1:
                {
                    std::cout<< "Digite la etiqueta del vertice" << std::endl;
                    char etiqueta;
                    std::cin>> etiqueta;
                    grafo.AgregarVertice(etiqueta);   
                }
                break;
            case 2:
                {
                    std::cout<< "Digite la etiqueta del vertice" << std::endl;
                    char etiqueta;
                    std::cin>> etiqueta;
                    Vertice vertice = Algoritmos::buscarVertice(etiqueta, grafo);
                    grafo.EliminarVertice(vertice); 
                }
                break;
            case 3:
                {
                    std::cout<<"Etiqueta actual" << std::endl;
                    char etiquetaVieja;
                    std::cin>> etiquetaVieja;
                    std::cout<<"Nueva etiqueta" << std::endl;
                    char etiqueta;
                    std::cin>> etiqueta;
                    Vertice vertice =  Algoritmos::buscarVertice(etiquetaVieja, grafo);
                    grafo.ModificarEtiqueta(vertice, etiqueta);
                }
                
                break;
            case 4:
                {
                    std::cout<< "Digite la etiqueta del vertice 1" << std::endl;
                    char etiqueta1;
                    std::cin>> etiqueta1;
                    std::cout<< "Digite la etiqueta del vertice2" << std::endl;
                    char etiqueta2;
                    std::cin>> etiqueta2;
                    std::cout<< "Digite el peso de la arista" << std:: endl;
                    size_t peso;
                    std::cin>>peso;
                    Vertice vertice1 = Algoritmos::buscarVertice(etiqueta1, grafo);
                    Vertice vertice2 = Algoritmos::buscarVertice(etiqueta2, grafo);
                    grafo.AgregarArista(vertice1, vertice2, peso);
                }
                break;
            case 5:
                {
                    std::cout<< "Digite la etiqueta del vertice 1" << std::endl;
                    char etiqueta1;
                    std::cin>> etiqueta1;
                    std::cout<< "Digite la etiqueta del vertice2" << std::endl;
                    char etiqueta2;
                    std::cin>> etiqueta2;
                    Vertice vertice1 = Algoritmos::buscarVertice(etiqueta1, grafo);
                    Vertice vertice2 = Algoritmos::buscarVertice(etiqueta2, grafo);
                    grafo.EliminarArista(vertice1, vertice2);
                }
                break;
            case 6:
                {
                    std::cout<< "Digite la etiqueta del vertice 1" << std::endl;
                    char etiqueta1;
                    std::cin>> etiqueta1;
                    std::cout<< "Digite la etiqueta del vertice2" << std::endl;
                    char etiqueta2;
                    std::cin>> etiqueta2;
                    std::cout<< "Digite el peso de la arista" << std:: endl;
                    size_t peso;
                    std::cin>>peso;
                    Vertice vertice1 = Algoritmos::buscarVertice(etiqueta1, grafo);
                    Vertice vertice2 = Algoritmos::buscarVertice(etiqueta2, grafo);
                    grafo.ModificarPeso(vertice1, vertice2, peso);
                }
                break; 
            case 7:
                {
                    std::cout<< "Digite la etiqueta del vertice 1" << std::endl;
                    char etiqueta1;
                    std::cin>> etiqueta1;
                    std::cout<< "Digite la etiqueta del vertice 2" << std::endl;
                    char etiqueta2;
                    std::cin>> etiqueta2;
                    Vertice vertice1 = Algoritmos::buscarVertice(etiqueta1, grafo);
                    Vertice vertice2 = Algoritmos::buscarVertice(etiqueta2, grafo);
                    int peso = grafo.Peso(vertice1, vertice2);
                    std::cout<< "El peso entre " << etiqueta1 << " y " << etiqueta2 << " es " << peso << std::endl;
                }
                break;
            case 8:
                {
                    Vertice vertice = grafo.PrimerVertice();
                    std::cout<< "La etiqueta del vertice es " << grafo.Etiqueta(vertice);
                }
                break;
            case 9:
                    {
                    std::cout<< "Digite la etiqueta del vertice anteroir" << std::endl;
                    char etiqueta1;
                    Vertice vertice1 = Algoritmos::buscarVertice(etiqueta1, grafo);
                    Vertice vertice = grafo.SiguienteVertice(vertice1); 
                    std::cout<< "La etiqueta del vertice es " << grafo.Etiqueta(vertice);
                    }
                    break;
            case 10:
                    {
                    std::cout<< "Digite la etiqueta del vertice" << std::endl;
                    char etiqueta1;
                    Vertice vertice1 = Algoritmos::buscarVertice(etiqueta1, grafo);
                    Vertice vertice = grafo.PrimerVerticeAdyacente(vertice1); 
                    std::cout<< "La etiqueta del vertice es " << grafo.Etiqueta(vertice);
                    }
                    break; 
            case 11:
                {
                    std::cout<< "Digite la etiqueta del vertice 1" << std::endl;
                    char etiqueta1;
                    std::cin>> etiqueta1;
                    std::cout<< "Digite la etiqueta del anterior adyacente vertice" << std::endl;
                    char etiqueta2;
                    std::cin>> etiqueta2;
                    Vertice vertice1 = Algoritmos::buscarVertice(etiqueta1, grafo);
                    Vertice vertice2 = Algoritmos::buscarVertice(etiqueta2, grafo);
                    Vertice vertice = grafo.SiguienteVerticeAdyacente(vertice1, vertice2); 
                    std::cout<< "La etiqueta del vertice es " << grafo.Etiqueta(vertice);
                }
            case 12:
                {
                    std::cout<<"La cantidad de vertices del grafo es : " <<grafo.NumVertices() <<  std::endl;
                }
                break;
            default:
                std::cout<< "Opcion invalida" << std::endl;
                break;
            }

            std::cout<< "Desea continuar?"<< std::endl;
            std::cin>>continuar;

        } while (continuar);
    }

    void static pruebaDijkstra(Grafo &grafo){
        ListaDijkstra camino(grafo.NumVertices());
        Vertice vertice = grafo.PrimerVertice();
        Algoritmos::Dijkstra(grafo, vertice, camino);
        // pregunta a dijkstra para un vertice random 
                    
    }

    void static pruebaDijkstraN(Grafo &grafo){
        ListaDijkstra camino(grafo.NumVertices());
        Vertice vertice = grafo.PrimerVertice();
        Vertice verticeNulo;
        
        while(vertice != verticeNulo){
            Algoritmos::Dijkstra(grafo, vertice, camino);
            vertice = grafo.SiguienteVertice(vertice);
        }              
    }

    void static pruebaKruskal(Grafo &grafo){
        Grafo grafoMinimo;
        Algoritmos::Kruskal(grafo, grafoMinimo);            
    }

    void static pruebaFloyd(Grafo &grafo){
        Algoritmos::Floyd(grafo);
    }

    void static pruebaPrim(Grafo &grafo){
        Algoritmos::primMetodo(grafo);
    }

    void static pruebaColorear(Grafo &grafo){
        Algoritmos::colorear(grafo);
    }

    Grafo static crearGrafoArana(size_t limite){
        //Las etiquetas van de 33 a limite 
        //Todos se conectan al vertice con la etiqueta 33 (ascii)
        Grafo grafo; 
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
            if(j++%2){ //min conecto con dos de forma aleatoria
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
                    if(!grafo.ExisteArista(i, a)){
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
                        if(!grafo.ExisteArista(i, a)){
                            grafo.AgregarArista(i, a, peso);
                        }
                    }
                } 
            }
            return grafo;
        }
    }

    Grafo static crearGrafoCircular(size_t limite){
        Grafo grafo;
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
    }

    Grafo static crearGrafoMalla(size_t limite){
        Grafo grafo;
        for (size_t i = 33; i < limite; i++)
        {
            char etiqueta = i;
            
        }
        for (size_t i = 33; i < limite; i++)
        {
            char buscado = i;
            Vertice salida = Algoritmos::buscarVertice(i);
            //Cuatro casos posibles +1, -1, +4, -4
            if (i-1 >=33)
            {
                buscado = i-1;
                grafo.AgregarArista(Algoritmos::buscarVertice(buscado-1),salida, 1 + rand() % 1000) ;
            }
            if (i+1 <=limite)
            {
                buscado = i+1;
                grafo.AgregarArista(Algoritmos::buscarVertice(buscado-1),salida, 1 + rand() % 1000) ;
            }
                if (i-4 >=33)
            {
                buscado = i-4;
                grafo.AgregarArista(Algoritmos::buscarVertice(buscado-1),salida, 1 + rand() % 1000) ;
            }
            if (i+4 <=limite)
            {
                buscado = i+4;
                grafo.AgregarArista(Algoritmos::buscarVertice(buscado-1),salida, 1 + rand() % 1000) ;
            }
        } 
    }

};

#endif
