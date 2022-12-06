#include <list>  // Listas indexadas

#include "Grafo.hpp"

static bool existeCiclosRecursivo(const Grafo& grafo, std::list<std::pair<bool, char>> &visitados, Vertice &verticeActual, Vertice &verticeAnterior)
{
    bool resultado;
    // set vertice actual in visitado as true
    bool esVisitado = false;
    std::list<std::pair<bool, char>>::iterator iterador = visitados.begin();
    // se guarda el vertice actual como visitado
    while (esVisitado == false)
    {
        if (grafo.Etiqueta(verticeActual) == (*iterador).second)
        {
            // std::cout << "123" << std::endl;
            (*iterador).first = true;
            esVisitado = true;
        }
        else
        {
            ++iterador;
        }
        // std::cout << (*iterador).second << std::endl;
    }

    Vertice verticeAdyacente = grafo.PrimerVerticeAdyacente(verticeActual);

    Vertice verticeNulo;
    size_t contador = 0;
    // se reitera para todos los vertices adyacentes del vertice actual
    // while (verticeAdyacente != verticeNulo)
    while (contador < grafo.NumVertices() - 1)
    {
        // si el adyacente ya es visitado y no es el anterior, entonces return true
        bool adyacenteVisitado;

        std::list<std::pair<bool, char>>::iterator i = visitados.begin();
        while (i != visitados.end())
        {
            // std::cout << "123" << std::endl;
            if ((*i).second == grafo.Etiqueta(verticeAdyacente))
            {
                if ((*i).first == true)
                {
                    adyacenteVisitado = true;
                }
                else
                {
                    adyacenteVisitado = false;
                }
                i = visitados.end();
            }
            else
            {
                ++i;
            }
        }

        // return true si se encontro con un elemento ya visitado y que no sea el padre
        if (verticeAdyacente != verticeAnterior && adyacenteVisitado)
        {
            // std::cout << "AAAAAAAAAAAAAAAAAAAAAAA" << std::endl;
            return true;
        }

        bool grafoVisitado = true;
        // i = visitados.begin();
        size_t counter = 0;
        // ciclo para saber si se visito todo el arbol
        // while (i != visitados.end())
        while (counter < visitados.size())
        {
            // std::cout << "zz" << std::endl;
            if ((*i).first == false)
            {
                // std::cout << "oo" << std::endl;
                grafoVisitado = false;
                i = visitados.end();
            }
            ++counter;
            //++i;
        }

        if (grafoVisitado)
        {
            // std::cout << "BBBBBBBBBBBBBBBBBBBBBBB" << std::endl;
            return false;
        }
        else
        {
            // else llamar recursivamente
            // std::cout << "CCCCCCCCCCCCCCCCCCCCCCCCCC" << std::endl;
            resultado = existeCiclosRecursivo(grafo, visitados, verticeAdyacente, verticeActual);
        }

        verticeAdyacente = grafo.SiguienteVerticeAdyacente(verticeActual, verticeAdyacente);
        // std::cout << "BBBBBBBBBBBBBBBBBBBBBBBBB" << std::endl;
        ++contador;
    }
    return resultado;
}

bool existeCiclos(const Grafo& grafo)
{
    // recorrido por profundidad primero -> si hay un arco de retroceso, entonces hay ciclo
    size_t cantidadVertices = grafo.NumVertices();
    Vertice vertice = grafo.PrimerVertice();

    std::list<std::pair<bool, char>> visitados;
    for (size_t i = 0; i < grafo.NumVertices(); ++i)
    {
        visitados.push_front(std::make_pair(false, grafo.Etiqueta(vertice)));
        vertice = grafo.SiguienteVertice(vertice);
        /// std::cout << "hello there" << std::endl;
    }

    Vertice primerVertice = grafo.PrimerVertice();
    bool esCiclico = existeCiclosRecursivo(grafo, visitados, primerVertice, primerVertice);
    std::cout << esCiclico << std::endl;
    return esCiclico;
}
