#include "HamiltonBERA.hpp"

#include <cstddef>  // Size_t
#include <queue>  // Cola de prioridad
#include <utility>  // Pareja
#include <set>  // Arreglos

class Arista : public std::pair<Vertice, Vertice> {
    public:
        size_t pesoAsociado;

        Arista(const Vertice& origen, const Vertice& destino, size_t peso)
        : std::pair<Vertice, Vertice>(origen, destino)
        , pesoAsociado(peso) {
        }

        Arista& operator=(const Arista& otro) {
            this->first = otro.first;
            this->second = otro.second;
            this->pesoAsociado = otro.pesoAsociado;
        }

        bool operator<(const Arista& otro) const {
            if (this->pesoAsociado < otro.pesoAsociado) {
                return true;
            } else if (otro.pesoAsociado == this->pesoAsociado) {
                if (this->first < otro.first) {
                    return true;
                } else if (this->first == otro.first) {
                    if (this->second < otro.second)
                        return true;
                }
            }

            return false;
        }

        bool operator!=(const Arista& otro) const {
            return (*this < otro) || (otro < *this);
        }
};

static size_t MinimoCostoPosible(const Grafo& grafo
    , const std::set<Arista>& aristasUtilizadas) {
    // Llevemos cuenta del peso estimado al momento
    size_t costoEstimado = 0;

    // Visitemos cada vertice
    for (Vertice v = grafo.PrimerVertice(); v != Vertice(); v = grafo.SiguienteVertice(v)) {

        // Solo debemos considerar dos aristas por vertice
        char aristasConsideradas = 0;
        std::priority_queue<Arista> aristasPorConsiderar;

        // Visitemos cada uno de sus vecinos adyacentes
        for (Vertice w = grafo.PrimerVerticeAdyacente(v); w != Vertice() && aristasConsideradas < 2
        ; w = grafo.SiguienteVerticeAdyacente(v, w)) {

            // Consideremos la arista que hay entre ambos
            Arista aristaActual(v, w, grafo.Peso(v, w));

            // Si definitivamente ya la consideramos, entonces añadámosla al costo estimado
            if (aristasUtilizadas.contains(aristaActual)) {
                costoEstimado += aristaActual.pesoAsociado;
                aristasConsideradas += 1;
            } else {  // Sino, añadamosla a las aristas por considerar
                aristasPorConsiderar.push(aristaActual);
            }
        }

        // Si todavía nos falta 2 aristas por considerar, entonces revisemoslas
        if (aristasConsideradas < 2) {
            // Si podemos revisar 2 aristas, obtengamoslas priorizando el menor costo
            if (aristasPorConsiderar.empty()) {
                continue;
            }

            costoEstimado += aristasPorConsiderar.top().pesoAsociado;
            aristasPorConsiderar.pop();

            if (aristasPorConsiderar.empty()) {
                continue;
            }

            costoEstimado += aristasPorConsiderar.top().pesoAsociado;
            aristasPorConsiderar.pop();
        }
    }

    // Ya el costo está estimado
    return costoEstimado;
}

static bool EsPosiblementeFactible(const Grafo& grafo
    , const Vertice& verticeCola
    , const Vertice& verticeDestino
    , const std::set<Vertice> verticesVisitados) {
    
    // Si el último vértice del recorrido es igual al primero, es posible
    // que hayamos terminado el recorrido, o fracasado en terminarlo
    if (verticeCola == verticeDestino)
    {
        // Si ya visitamos más de un vértice, ya completamos el recorrido
        if (verticesVisitados.size() > 1)
            return true;
        
        // Sino, fracasamos en terminarlo
        return false;
    }
    
    // Sino, debemos revisar conexiones del vértice de la cola
    // Si tiene únicamente de adyacentes a vértices distintos del destino,
    // entonces el recorrido no puede llegar al destino, y no es factible
    char tieneAdyacenteValido = 0;
    for (Vertice verticeAdyacente = grafo.PrimerVerticeAdyacente(verticeCola);
    verticeAdyacente != Vertice() && tieneAdyacenteValido == 0;
    verticeAdyacente = grafo.SiguienteVerticeAdyacente(verticeCola, verticeAdyacente)) {
        if (!verticesVisitados.contains(verticeAdyacente)
            || verticeAdyacente == verticeDestino) {
            tieneAdyacenteValido = 1;
        }
    }

    // Si tiene un vértice adyacente válido, entonces es factible}
    if (tieneAdyacenteValido == 1)
        return true;

    return false;
}

static bool HamiltonBERARecursivo(const Grafo& grafo, const Vertice& partida
    , std::set<Vertice>& verticesVisitados
    , std::set<Arista>& aristasVisitadas
    , std::set<Arista>& aristasDescartadas
    , std::vector<Vertice>& mejorSolucion) {
        
    // Consideraremos el costo sin la conexión añadida
    size_t costoSinAdyacente = MinimoCostoPosible(grafo, aristasVisitadas);

    // Obtendremos al siguiente vértice adyacente sin conexión descartada
    Vertice adyacente = grafo.PrimerVerticeAdyacente(partida);
    Arista conexion(partida, adyacente, grafo.Peso(partida, adyacente));
    while (aristasDescartadas.contains(conexion)) {
        adyacente = grafo.SiguienteVerticeAdyacente(partida, adyacente);

        // Si se nos acabaron los vértices adyacentes sin conexión descartada
        // entonces esta iteración no es factible
        if (adyacente == Vertice()) {
            return false;
        }

        // Sino, obtengamos de candidato a la siguiente conexión
        conexion = Arista(partida, adyacente, grafo.Peso(partida, adyacente));
    }

    // Consideramos el costo con la conexión añadida
    aristasVisitadas.insert(conexion);
    size_t costoConAdyacente = MinimoCostoPosible(grafo, aristasVisitadas);

    // Si la conexión matiene el costo, entonces podemos profundizar por ahí primero
    if (costoConAdyacente == costoSinAdyacente) {
        verticesVisitados.insert(adyacente);

        // Si la solución fue factible, podemos hacer retorno directo
        if (HamiltonBERARecursivo(grafo, adyacente, verticesVisitados
            , aristasVisitadas, aristasDescartadas, mejorSolucion)) {
            mejorSolucion.push_back(adyacente);
            return true;
        }

        // Sino, tenemos que probar con otra iteración, y hacer backtracking
        verticesVisitados.erase(adyacente);
        aristasVisitadas.erase(conexion); aristasDescartadas.insert(conexion);

        // Si la solución alternativa fue factible, podemos hacer retorno directo
        if (HamiltonBERARecursivo(grafo, partida, verticesVisitados
        , aristasVisitadas, aristasDescartadas, mejorSolucion)) {
            return true;
        }

        // Sino, ninguna de las dos soluciones es factible, y tenemos que hacer
        // backtracking todavía más intenso
        aristasDescartadas.erase(conexion);
        return false;
    } else {  // Sino, debemos profundizar por el otro lado (sin arista) primero
        aristasVisitadas.erase(conexion);
        aristasDescartadas.insert(conexion);
    
        // Si la solución alternativa fue factible, podemos hacer retorno directo
        if (HamiltonBERARecursivo(grafo, partida, verticesVisitados
        , aristasVisitadas, aristasDescartadas, mejorSolucion)) {
            return true;
        }

        // Sino, tenemos que probar con otra iteración, y hacer backtracking
        aristasDescartadas.erase(conexion); aristasVisitadas.insert(conexion);
        verticesVisitados.insert(adyacente);

        // Si la solución fue factible, podemos hacer retorno directo
        if (HamiltonBERARecursivo(grafo, adyacente, verticesVisitados
            , aristasVisitadas, aristasDescartadas, mejorSolucion)) {
            mejorSolucion.push_back(adyacente);
            return true;
        }

        // Sino, ninguna de las dos soluciones es factible, y tenemos que hacer
        // backtracking todavía más intenso
        verticesVisitados.erase(adyacente);
        aristasVisitadas.erase(conexion);
        return false;
    }
}

namespace HamiltonBERA {
    static std::vector<Vertice> Hamilton(const Grafo& grafo) {

        // Llevemos cuenta de la cantidad de vertices en el grafo
        const size_t cantidadVertices = grafo.NumVertices();

        // Si no hay vertices, no necesitamos continuar
        if (cantidadVertices == 0) {
            return std::vector<Vertice>();
        }

        // Para el recorrido con BERA necesitaremos de varias E.D auxiliares:
            // Un diccionario de aristas visitadas al momento
            std::set<Arista> aristasVisitadas;
            // Un diccionario de aristas descartadas al momento
            std::set<Arista> aristasDescartadas;
            // Un diccionario de vertices visitados al momento
            std::set<Vertice> verticesVisitados;
            // Una lista de vértices para representar el recorrido
            std::vector<Vertice> recorrido;
            recorrido.reserve(cantidadVertices);
            // Y una referencia al primer vértice del grafo
            const Vertice origenRecorrido = grafo.PrimerVertice();
        
        // Ahora podemos comenzar el recorrido recursivo
        recorrido.push_back(origenRecorrido);
        
        HamiltonBERARecursivo(grafo, origenRecorrido, verticesVisitados, aristasVisitadas, aristasDescartadas, recorrido);

        // Tras terminar el recorrido, podemos devolver el vector con la mejor solución
        return recorrido;
    }
}
