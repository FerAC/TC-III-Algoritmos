#include <iostream>  // Información de excepciones
#include <stdexcept>  // Manejo de parámetros inválidos

#include "Pruebas.hpp"
#include "Algoritmos.hpp"

// Wrapper para retornar punteros a funciones
typedef struct {
    void (*f) (size_t, Grafo&);
} FuncionCreacionGrafo;


// CREAR ÁRBOL

static void crearGrafoArana(size_t limite, Grafo& grafo) {
        //Las etiquetas van de 33 a limite 
        //Todos se conectan al vertice con la etiqueta 33 (ascii)
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
            if (j%2) { //min conecto con dos de forma aleatoria
                for (size_t t = 0; t < 2; t++)
                {
                    bool iguales = true; 
                    size_t num = 34 + (double(rand()) / RAND_MAX) * (limite - 34); 
                    while (num==j)
                    {
                        num = 34 + (double(rand()) / RAND_MAX) * (limite - 34); 
                    }
                    size_t peso = 1 + rand() % 1000;
                    std::cout<< "NUM " << num << std::endl; 
                    int noHaceNada;
                    
                    char numAsChar = num; 
                    Vertice v = Algoritmos::BuscarVertice(grafo, numAsChar);
                    if ((!grafo.ExisteArista(i, v)) && i != v) {
                        grafo.AgregarArista(i, v, peso);
                    }
                }
            } else{ //max
                for (size_t t = 34; t < limite-1; t++)
                {
                    if (t != j)
                    {
                        size_t peso = 1 + rand() % 1000;
                        char numAsChar = t; 
                        Vertice c = Algoritmos::BuscarVertice(grafo, numAsChar);

                        if ((!grafo.ExisteArista(i, c)) && (i != c)) {
                            grafo.AgregarArista(i, c, peso);
                        }
                    }
                } 
            }

            j++;
        }
        
        // Ya terminamos de crear el grafo araña
        return;
    }

static void crearGrafoCircular(size_t limite, Grafo& grafo) {
        char etiqueta = 33;
        Vertice anterior = grafo.AgregarVertice(etiqueta); 
        Vertice primero = anterior; 
        for (size_t i = 34; i <= limite; i++)
        {   
            etiqueta = i;
            Vertice actual = grafo.AgregarVertice(etiqueta);
            size_t peso = 1 + rand() % 1000;
            if(i==limite){
                grafo.AgregarArista(anterior, actual, peso);
                grafo.AgregarArista(primero, actual, peso);
            } else{
                grafo.AgregarArista(anterior, actual, peso);
            }
            anterior = actual; 
        }
        
        // Ya terminamos de crear el grafo circular
        return;
    }

static void crearGrafoMalla(size_t limite, Grafo& grafo) {

        for (size_t i = 33; i < limite; i++)
        {
            char etiqueta = i;
            grafo.AgregarVertice(etiqueta);
        }
        Vertice salida = grafo.PrimerVertice();
        for (size_t i = 33; i < limite; i++)
        {
            char buscado = i;
           
            //Cuatro casos posibles +1, -1, +4, -4
            if (i-1 >=33)
            {
                buscado = i-1;
                
                
                    if (!grafo.ExisteArista(salida, Algoritmos::BuscarVertice(grafo, buscado)))
                    {
                        grafo.AgregarArista(Algoritmos::BuscarVertice(grafo, buscado),salida, 1 + rand() % 1000) ;
                    
                    }
                
                
            }
            if (i+1 <limite)
            {
                buscado = i+1;
                
                    if (!grafo.ExisteArista(salida, Algoritmos::BuscarVertice(grafo, buscado)))
                    {
                        grafo.AgregarArista(Algoritmos::BuscarVertice(grafo, buscado),salida, 1 + rand() % 1000) ;
                    
                    }
               
            }
            if (i-4 >=33)
            {
                buscado = i-4;
                
                    if (!grafo.ExisteArista(salida, Algoritmos::BuscarVertice(grafo, buscado)))
                    {
                        grafo.AgregarArista(Algoritmos::BuscarVertice(grafo, buscado),salida, 1 + rand() % 1000) ;
                    
                    }
               
                
                 
            }
            if (i+4 <limite)
            {
                buscado = i+4;
               
                    if (!grafo.ExisteArista(salida, Algoritmos::BuscarVertice(grafo, buscado)))
                    {
                        grafo.AgregarArista(Algoritmos::BuscarVertice(grafo, buscado),salida, 1 + rand() % 1000) ;
                    
                    }
                
            }
            salida = grafo.SiguienteVertice(salida);
        } 

        // Ya terminamos de crear el grafo malla
        return;
    }

static FuncionCreacionGrafo comoCrearGrafo (const std::string& nombre) {

    FuncionCreacionGrafo resultado = {nullptr};

    if (nombre == "Arana") {
        resultado = {crearGrafoArana};
    } else if (nombre == "Circular") {
        resultado = {crearGrafoCircular};
    } else if (nombre == "Malla") {
        resultado = {crearGrafoMalla};
    }
    
    return resultado;
}

namespace Pruebas {

    // ARBOLES MINIMALES

    void arbolMinimal(PuntoTiempo& inicio, PuntoTiempo& fin
        , std::tuple<std::string, std::string, size_t> parametros) {

        const std::string& nombreAlgoritmo = std::get<0>(parametros);

        char cualAlgoritmo = 0;
        if (nombreAlgoritmo == std::string("Prim")) {
            cualAlgoritmo = 1;
        } else if (nombreAlgoritmo != std::string("Kruskal")) {
            std::cerr 
            << "[ArbolMinimal] : Algoritmo con nombre " 
            << nombreAlgoritmo << " es invalido" << std::endl;

            throw std::invalid_argument("Algoritmo no reconocido");
        }

        const std::string& tipoGrafo = std::get<1>(parametros);
        FuncionCreacionGrafo funcionCreadora = comoCrearGrafo(tipoGrafo);

        if (funcionCreadora.f == nullptr) {
            std::cerr 
            << "[ArbolMinimal] : Tipo de Grafo " 
            << tipoGrafo << " es invalido" << std::endl;

            throw std::invalid_argument("Grafo no reconocido");
        }

        const size_t tamano = std::get<2>(parametros);

        Grafo grafoEntrada; funcionCreadora.f(tamano, grafoEntrada);
        Grafo grafoSalida = Grafo();

        void (*algoritmo) (const Grafo &, Grafo &) = Algoritmos::Kruskal;
        if (cualAlgoritmo == 1) {
            algoritmo = Algoritmos::Prim;
        }

        inicio = std::chrono::high_resolution_clock::now();
        algoritmo(grafoEntrada, grafoSalida);
        fin = std::chrono::high_resolution_clock::now();

        return;
    }

    // CAMINOS DE MENOR COSTO

    void distanciaCortaUno(PuntoTiempo& inicio, PuntoTiempo& fin
        , std::tuple<std::string, std::string, size_t> parametros) {

        const std::string& nombreAlgoritmo = std::get<0>(parametros);
        if (nombreAlgoritmo != std::string("Djikstra")) {
            std::cerr 
            << "[DistanciaCortaUno] : Algoritmo con nombre " 
            << nombreAlgoritmo << " es invalido (Hint: Debe ser Djikstra)" << std::endl;

            throw std::invalid_argument("Algoritmo no reconocido");
        }

        const std::string& tipoGrafo = std::get<1>(parametros);
        FuncionCreacionGrafo funcionCreadora = comoCrearGrafo(tipoGrafo);

        if (funcionCreadora.f == nullptr) {
            std::cerr 
            << "[DistanciaCortaUno] : Tipo de Grafo " 
            << tipoGrafo << " es invalido" << std::endl;

            throw std::invalid_argument("Grafo no reconocido");
        }

        const size_t tamano = std::get<2>(parametros);

        Grafo grafoEntrada; funcionCreadora.f(tamano, grafoEntrada);

        inicio = std::chrono::high_resolution_clock::now();
        Algoritmos::Dijkstra(grafoEntrada, grafoEntrada.PrimerVertice());
        fin = std::chrono::high_resolution_clock::now();

        return;
    }

    void distanciaCortaTodos(PuntoTiempo& inicio, PuntoTiempo& fin
        , std::tuple<std::string, std::string, size_t> parametros) {

            const std::string& nombreAlgoritmo = std::get<0>(parametros);

        char cualAlgoritmo = 0;
        if (nombreAlgoritmo == std::string("N_Djikstra")) {
            cualAlgoritmo = 1;
        } else if (nombreAlgoritmo != std::string("Floyd")) {
            std::cerr 
            << "[DistanciaCortaTodos] : Algoritmo con nombre " 
            << nombreAlgoritmo << " es invalido" << std::endl;

            throw std::invalid_argument("Algoritmo no reconocido");
        }

        const std::string& tipoGrafo = std::get<1>(parametros);
        FuncionCreacionGrafo funcionCreadora = comoCrearGrafo(tipoGrafo);

        if (funcionCreadora.f == nullptr) {
            std::cerr 
            << "[DistanciaCortaTodos] : Tipo de Grafo " 
            << tipoGrafo << " es invalido" << std::endl;

            throw std::invalid_argument("Grafo no reconocido");
        }

        const size_t tamano = std::get<2>(parametros);

        Grafo grafoEntrada; funcionCreadora.f(tamano, grafoEntrada);

        std::vector<std::vector<size_t>> (*algoritmo) (const Grafo &) = Algoritmos::Floyd;
        if (cualAlgoritmo == 1) {
            algoritmo = Algoritmos::nVecesDijkstra;
        }

        inicio = std::chrono::high_resolution_clock::now();
        algoritmo(grafoEntrada);
        fin = std::chrono::high_resolution_clock::now();

        return;
    }

    // CIRCUITO HAMILTONIANO

    void circuitoHamiltoniano(PuntoTiempo& inicio, PuntoTiempo& fin
        , std::tuple<std::string, std::string, size_t> parametros) {

        const std::string& nombreAlgoritmo = std::get<0>(parametros);

        char cualAlgoritmo = 0;
        if (nombreAlgoritmo == std::string("BERA")) {
            cualAlgoritmo = 1;
        } else if (nombreAlgoritmo != std::string("BEP")) {
            std::cerr 
            << "[CircuitoHamiltoniano] : Algoritmo con nombre " 
            << nombreAlgoritmo << " es invalido" << std::endl;

            throw std::invalid_argument("Algoritmo no reconocido");
        }

        const std::string& tipoGrafo = std::get<1>(parametros);
        FuncionCreacionGrafo funcionCreadora = comoCrearGrafo(tipoGrafo);

        if (funcionCreadora.f == nullptr) {
            std::cerr 
            << "[CircuitoHamiltoniano] : Tipo de Grafo " 
            << tipoGrafo << " es invalido" << std::endl;

            throw std::invalid_argument("Grafo no reconocido");
        }

        const size_t tamano = std::get<2>(parametros);

        Grafo grafoEntrada; funcionCreadora.f(tamano, grafoEntrada);

        std::vector<Vertice> (*algoritmo) (const Grafo &) = Algoritmos::HamiltonBEP;
        if (cualAlgoritmo == 1) {
            algoritmo = Algoritmos::HamiltonBERA;
        }

        inicio = std::chrono::high_resolution_clock::now();
        algoritmo(grafoEntrada);
        fin = std::chrono::high_resolution_clock::now();

        return;
    }

    // COLOREO

    void coloreo(PuntoTiempo& inicio, PuntoTiempo& fin
        , std::tuple<std::string, std::string, size_t> parametros) {
        
        const std::string& nombreAlgoritmo = std::get<0>(parametros);
        if (nombreAlgoritmo != std::string("Coloreo")) {
            std::cerr 
            << "[Coloreo] : Algoritmo con nombre " 
            << nombreAlgoritmo << " es invalido (Hint: Debe ser Coloreo)" << std::endl;

            throw std::invalid_argument("Algoritmo no reconocido");
        }

        const std::string& tipoGrafo = std::get<1>(parametros);
        FuncionCreacionGrafo funcionCreadora = comoCrearGrafo(tipoGrafo);

        if (funcionCreadora.f == nullptr) {
            std::cerr 
            << "[Coloreo] : Tipo de Grafo " 
            << tipoGrafo << " es invalido" << std::endl;

            throw std::invalid_argument("Grafo no reconocido");
        }

        const size_t tamano = std::get<2>(parametros);

        Grafo grafoEntrada; funcionCreadora.f(tamano, grafoEntrada);

        inicio = std::chrono::high_resolution_clock::now();
        auto* mapa = Algoritmos::Colorear(grafoEntrada);
        fin = std::chrono::high_resolution_clock::now();
        delete mapa;

        return;
    }

    // LEER PARÁMETROS

    void leerParametros(std::tuple<std::string, std::string, size_t>& parametros
        , std::istream& entrada) {
        
        entrada >> std::get<0>(parametros);
        entrada >> std::get<1>(parametros);
        entrada >> std::get<2>(parametros);
    }

    void imprimirParametros(const std::tuple<std::string, std::string, size_t>& parametros
        , std::ostream& salida) {
        salida 
        << "Nombre de Algoritmo: " << std::get<0>(parametros) << std::endl
        << "Tipo de Grafo: " << std::get<1>(parametros) << std::endl
        << "N = " << std::get<2>(parametros);
    }

};
