#include <list>
#include <map>
#include <stack>
#include <iostream>

#include "Algoritmos.hpp"
#include "Tripleta.hpp"

static Vertice encontrarPivote(Tripleta *lista, std::map<char, Vertice> &mapaVerticesVisitados, const Grafo &grafo)
{
    std::cout << "Estoy en metodo buscar pivote " << std::endl;
    std::cout << "Tamano del mapa : " << mapaVerticesVisitados.size() << std::endl;
    Vertice pivote;
    size_t menorPeso = 0;
    size_t indiceMenor;
    for (size_t i = 0; i < grafo.NumVertices() - 1; i++)
    {
        // Verifico que no haya sido pivoteado antes
        if (mapaVerticesVisitados.empty())
        { // Caso trivial, esta vacio
            std::cout << "Primer pivote " << std::endl;
            if (menorPeso != 0)
            {
                if (lista[i].getPeso() != 0 && lista[i].getPeso() < menorPeso)
                {
                    std::cout << "Primer pivote " << std::endl;
                    indiceMenor = i;
                    menorPeso = lista[indiceMenor].getPeso();
                }
            }
            else
            {
                if (lista[i].getPeso() != 0)
                {
                    std::cout << "Primer pivote " << std::endl;
                    indiceMenor = i;
                    menorPeso = lista[indiceMenor].getPeso();
                }
            }
        }
        else
        {
            if (mapaVerticesVisitados.count(lista[i].getVertice().getEtiqueta()) > 0)
            {
                // Si lo encontro, sigo adelante
                std::cout << "YA SE PIVOTEO CON " << lista[i].getVertice().getEtiqueta() << std::endl;
            }
            else
            {
                std::cout << "No se ha pivoteado con " << lista[i].getVertice().getEtiqueta() << std::endl;
                std::cout << "Su peso es  " << lista[i].getPeso() << std::endl;
                if (menorPeso != 0)
                {
                    if (lista[i].getPeso() != 0 && lista[i].getPeso() < menorPeso)
                    {
                        indiceMenor = i;
                        menorPeso = lista[i].getPeso();
                    }
                }
                else
                {
                    if (lista[i].getPeso() != 0)
                    {
                        indiceMenor = i;
                        menorPeso = lista[i].getPeso();
                    }
                }
            }
        }
    }
    std::cout << "Encontre pivote " << indiceMenor << std::endl;
    std::cout << "Peso menor " << menorPeso << std::endl;
    char a = lista[indiceMenor].getVertice().getEtiqueta();
    std::cout << "Encontre pivote " << a << std::endl;
    Vertice b = lista[indiceMenor].getVertice();
    mapaVerticesVisitados.insert(std::pair<char, Vertice>(a, b));
    return b;
}

namespace Algoritmos {

    Grafo Prim(const Grafo &grafo) {
        // int a = grafo.NumVertices();
        Tripleta lista[grafo.NumVertices() - 1];
        // Inicializacion
        Vertice vInicial = grafo.PrimerVertice();
        const Vertice NULO;
        size_t i = 0;
        std::cout << "Voy a for " << std::endl;
        for (Vertice iterador = grafo.PrimerVertice(); iterador != NULO; iterador = grafo.SiguienteVertice(iterador))
        {
            int peso = 0;
            if (vInicial != iterador)
            {
                std::cout << "No son iguales" << std::endl;
                if (grafo.ExisteArista(vInicial, iterador))
                {
                    peso = grafo.Peso(vInicial, iterador);
                }
                Tripleta tripleta(iterador, peso, vInicial);
                lista[i] = tripleta;
                lista[i].imprimir();
                i++;
            }
        }
        std::cout << std::endl;
        std::cout << "Sali de inicializacion " << std::endl;
        for (size_t i = 0; i < grafo.NumVertices() - 1; i++)
        {
            lista[i].imprimir();
        }

        std::cout << "VOY A PIVOT" << std::endl;
        // Primer pivote
        std::map<char, Vertice> mapaVerticesPivoteados;
        for (size_t j = 0; j < grafo.NumVertices() - 1; j++)
        {
            std::cout << "J " << j << std::endl;
            Vertice pivote = encontrarPivote(lista, mapaVerticesPivoteados, grafo);
            std::cout << "///////////// PIVOTEO CON " << grafo.Etiqueta(pivote) << "///////////" << std::endl;
            for (size_t i = 0; i < grafo.NumVertices() - 1; i++)
            {
                if (lista[i].getVertice() != pivote && mapaVerticesPivoteados.count(lista[i].getVertice().getEtiqueta()) <= 0)
                {
                    if (grafo.Peso(pivote, lista[i].getVertice()) > 0)
                    {
                        if (lista[i].getPeso() > grafo.Peso(pivote, lista[i].getVertice()))
                        {
                            lista[i].setPeso(grafo.Peso(pivote, lista[i].getVertice()));
                            lista[i].setVerticeAnterior(pivote);
                        }
                    }
                }
            }
            std::cout << "+++++++++++++++++++BUCLE EXTERNO ++++++++++++++++++++++" << std::endl;
            for (size_t i = 0; i < grafo.NumVertices() - 1; i++)
            {
                std::cout << "Vertice " << lista[i].getVertice().getEtiqueta() << std::endl;
                std::cout << "Peso " << lista[i].getPeso() << std::endl;
                std::cout << "Vertice Anterior " << lista[i].getVerticeAnterior().getEtiqueta() << std::endl;
            }
            std::cout << "+++++++++++++++++++BUCLE EXTERNO ++++++++++++++++++++++" << std::endl;
        }
        std::cout << "****************************************** " << std::endl;
        for (size_t i = 0; i < grafo.NumVertices() - 1; i++)
        {
            std::cout << "Vertice " << lista[i].getVertice().getEtiqueta() << std::endl;
            std::cout << "Peso " << lista[i].getPeso() << std::endl;
            std::cout << "Vertice Anterior " << lista[i].getVerticeAnterior().getEtiqueta() << std::endl;
        }
        std::cout << "****************************************** " << std::endl;
        Grafo retornado;
        /*
        for (Vertice vertice = grafo.PrimerVertice(); vertice != NULO; vertice = grafo.SiguienteVertice(vertice))
        {
            retornado.AgregarVertice(grafo.Etiqueta(vertice));
        }
         for (Vertice vertice = retornado.PrimerVertice(); vertice != NULO; vertice = retornado.SiguienteVertice(vertice))
        {
            std::cout<< grafo.Etiqueta(vertice) << std::endl;
        }
       */

        for (size_t i = 0; i < grafo.NumVertices() - 1; i++)
        {
            Vertice llegada;
            Vertice salida;
            /*
            llegada = retornado.PrimerVertice();
            salida = retornado.PrimerVertice();
            int bandera = 0;
            while (!bandera)
            {
                if (salida.getEtiqueta() == lista[i].getVerticeAnterior().getEtiqueta())
                {
                    bandera = 1;
                } else{
                    salida = retornado.SiguienteVertice(salida);
                }
            }
            bandera = 0;
              while (!bandera)
            {
                if (llegada.getEtiqueta() == lista[i].getVertice().getEtiqueta())
                {
                    bandera = 1;
                } else{
                    llegada = retornado.SiguienteVertice(llegada);
                }
            }
           */
            // Verifico no haber anadido el vertice anteriormente
            Vertice buscado = buscarVertice(retornado, lista[i].getVertice().getEtiqueta());
            if (buscado == NULO)
            {
                std::cout << "No se ha agregado a " << lista[i].getVertice().getEtiqueta() << std::endl;
                salida = retornado.AgregarVertice(lista[i].getVertice().getEtiqueta());
            }
            else
            {
                std::cout << "Si se ha agregado a " << lista[i].getVertice().getEtiqueta() << std::endl;
                salida = buscado;
            }
            buscado = buscarVertice(retornado, lista[i].getVerticeAnterior().getEtiqueta());
            if (buscado == NULO)
            {
                std::cout << "No se ha agregado a " << lista[i].getVerticeAnterior().getEtiqueta() << std::endl;
                llegada = retornado.AgregarVertice(lista[i].getVerticeAnterior().getEtiqueta());
            }
            else
            {
                std::cout << "Si se ha agregado a " << lista[i].getVerticeAnterior().getEtiqueta() << std::endl;
                llegada = buscado;
            }
            /*
            llegada = buscarVertice(retornado, lista[i].getVertice().getEtiqueta());
            salida = buscarVertice(retornado, lista[i].getVerticeAnterior().getEtiqueta());
           */
            std::cout << "Se va a agregar una arista de peso " << lista[i].getPeso() << ", entre " << llegada.getEtiqueta() << " y " << salida.getEtiqueta() << std::endl;
            retornado.AgregarArista(llegada, salida, lista[i].getPeso());
        }
        Vertice vertice;
        for (size_t i = 0; i < retornado.NumVertices(); i++)
        {
            if (i == 0)
            {
                vertice = retornado.PrimerVertice();
            }
            else
            {
                vertice = retornado.SiguienteVertice(vertice);
            }
            // retornado.ImprimirConexiones(vertice);
        }
        for (size_t i = 0; i < retornado.NumVertices(); i++)
        {
            if (i == 0)
            {
                vertice = grafo.PrimerVertice();
            }
            else
            {
                vertice = grafo.SiguienteVertice(vertice);
            }
            //  grafo.ImprimirConexiones(vertice);
        }
        return retornado;
    }

}
