#include <iostream>  // DEBUG

#include "Algoritmos.hpp"

// IMPRESION

static void imprimirGrafo(const Grafo& grafo) {

    #ifdef MATRIZ
        grafo.ImprimirGrafo();
    #else
        // Tambien se deberia imprimir las aristas
        grafo.ImprimirVertices();
    #endif
}

static void imprimirGrafoCSAcademy(const Grafo& grafo){
    Vertice NULO;
    for(Vertice vertice = grafo.PrimerVertice();
        vertice!=NULO;
        vertice = grafo.SiguienteVertice(vertice)) {
        std::cout<< grafo.Etiqueta(vertice) << std::endl;
    }

    for(Vertice vertice = grafo.PrimerVertice();
        vertice!=NULO;
        vertice = grafo.SiguienteVertice(vertice)){
        for(Vertice verticeAdy = grafo.PrimerVerticeAdyacente(vertice);
            verticeAdy!=NULO;
            vertice = grafo.SiguienteVerticeAdyacente(vertice, verticeAdy)){
            std::cout
            << grafo.Etiqueta(vertice) << " " 
            << grafo.Etiqueta(verticeAdy) << " " 
            << grafo.Peso(vertice, verticeAdy) 
            << std::endl;
        }
    }
}

// dot -Tsvg < entrada.txt > salida.svg
// dot -Tpng < entrada.txt > salida.svg

static void imprimirGrafoGraphviz(const Grafo& grafo) {
   std::cout 
    << "digraph{" << std::endl
    << "layout=\"circo\";" << std::endl
    << "edge [color=blue]" << std::endl;

    std::set<std::pair<Vertice, Vertice>> paralelasDibujadas;
    for (Vertice v = grafo.PrimerVertice(); v != Vertice(); v = grafo.SiguienteVertice(v)) {
        std::cout << grafo.Etiqueta(v) << std::endl;
    
        for (Vertice w = grafo.PrimerVerticeAdyacente(v); 
            w != Vertice(); 
            w = grafo.SiguienteVerticeAdyacente(v, w)) {

            size_t pesoActual = grafo.Peso(v,w);
            std::pair<Vertice, Vertice> aristaActual = std::make_pair(v,w);

            if (grafo.ExisteArista(w,v) && pesoActual == grafo.Peso(w,v)) {
                if (!paralelasDibujadas.contains(aristaActual)
                && !paralelasDibujadas.contains(std::make_pair(w,v))
                ) {
                    paralelasDibujadas.insert(aristaActual);

                    std::cout << grafo.Etiqueta(v) << " -> " << grafo.Etiqueta(w) 
                    << " [label=" << pesoActual << ", dir=none]" << std::endl;
                }
            } else {
                std::cout << grafo.Etiqueta(v) << " -> " << grafo.Etiqueta(w) 
                << " [label=" << pesoActual << "]" << std::endl;
            }
        }
    }
    std::cout << "}" << std::endl;
}

// CONTROLADOR

namespace Controlador {

    void iniciar() {

        Grafo grafo;
        bool continuar;

        do
        {
            std::cout<< "Cual operador basico deseea utilizar?" << std::endl;
            std::cout<< "1 - Agregar vertice" << std::endl;
            std::cout<< "2 - Eliminar vertice" << std::endl;
            std::cout<< "3 - Modificar etiqueta" << std::endl;
            std::cout<< "4 - Agregar arista" << std::endl;
            std::cout<< "5 - Eliminar arista"<< std::endl;
            std::cout<< "6 - Modificar peso" << std::endl;
            std::cout<< "7 - Peso" << std::endl;
            std::cout<< "8 - Primer vertice" << std::endl;
            std::cout<< "9 - Siguiente vertice" << std::endl;
            std::cout<< "10 - Primer vertice adyacente" << std::endl;
            std::cout<< "11 - Siguiente vertice adyacente" << std::endl;
            std::cout<< "12 - Num vertices" << std::endl;
            std::cout<< "13 - Destruir Grafo" << std::endl;
            std::cout<< "14 - Imprimir Grafo" << std::endl;

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
                        Vertice vertice = Algoritmos::buscarVertice(grafo, etiqueta);
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
                        Vertice vertice =  Algoritmos::buscarVertice(grafo,etiquetaVieja);
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
                        Vertice vertice1 = Algoritmos::buscarVertice(grafo,etiqueta1);
                        Vertice vertice2 = Algoritmos::buscarVertice(grafo, etiqueta2);
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
                        Vertice vertice1 = Algoritmos::buscarVertice(grafo, etiqueta1);
                        Vertice vertice2 = Algoritmos::buscarVertice(grafo, etiqueta2);
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
                        Vertice vertice1 = Algoritmos::buscarVertice(grafo,etiqueta1);
                        Vertice vertice2 = Algoritmos::buscarVertice(grafo,etiqueta2);;
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
                        Vertice vertice1 = Algoritmos::buscarVertice(grafo,etiqueta1);
                        Vertice vertice2 = Algoritmos::buscarVertice(grafo,etiqueta2);;
                        int peso = grafo.Peso(vertice1, vertice2);
                        std::cout<< "El peso entre " << etiqueta1 << " y " << etiqueta2 << " es " << peso << std::endl;
                    }
                break;
                case 8:
                    {
                        Vertice vertice = grafo.PrimerVertice();
                        std::cout<< "La etiqueta del vertice es " << grafo.Etiqueta(vertice) << std::endl;
                    }
                break;
                case 9:
                    {
                        std::cout<< "Digite la etiqueta del vertice anterior" << std::endl;
                        char etiqueta1;
                        Vertice vertice1 = Algoritmos::buscarVertice(grafo,etiqueta1);
                        Vertice vertice = grafo.SiguienteVertice(vertice1); 
                        std::cout<< "La etiqueta del vertice es " << grafo.Etiqueta(vertice) << std::endl;
                    }
                break;
                case 10:
                    {
                        std::cout<< "Digite la etiqueta del vertice" << std::endl;
                        char etiqueta1;
                        Vertice vertice1 = Algoritmos::buscarVertice(grafo,etiqueta1);
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
                        Vertice vertice1 = Algoritmos::buscarVertice(grafo,etiqueta1);
                        Vertice vertice2 = Algoritmos::buscarVertice(grafo,etiqueta2);;
                        Vertice vertice = grafo.SiguienteVerticeAdyacente(vertice1, vertice2); 
                        std::cout<< "La etiqueta del vertice es " << grafo.Etiqueta(vertice) << std::endl;
                    }
                break;
                case 12:
                    {
                        std::cout<<"La cantidad de vertices del grafo es : " <<grafo.NumVertices() <<  std::endl;
                    }
                break;
                // TODO(us): Case 13, Destruir grafo
                case 14:
                    {
                        std::cout<< "Este es el grafo: " << std::endl;
                        imprimirGrafo(grafo); std::cout << std::endl;
                    }
                break;
                default:
                    {
                        std::cout<< "Opcion invalida" << std::endl;
                    }
                break;
            }

            std::cout<< "Desea continuar?"<< std::endl;
            std::cin>>continuar;
        } 
        while (continuar);
    }

};
