#ifndef HAMILTON_BERA
#define HAMILTON_BERA

#include <cstddef>  // Size_t
#include <limits>  // Max de size_t
#include <utility>  // Pareja
#include <vector>  // Arreglos
#include <set>  // Conjuntos

#include "Grafo.hpp"

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

            return *this;
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

        bool operator>(const Arista& otro) const {
            return otro < *this;
        }

        bool operator!=(const Arista& otro) const {
            return (*this < otro) || (otro < *this);
        }
};

struct Estado {
    std::set<Vertice> verticesRecorridos;
    std::set<Arista> aristasAceptadas;
    std::set<Arista> aristasDescartadas;
};

struct Soluciones {
    std::vector<Vertice> solucionActual;
    std::vector<Vertice> mejorSolucion;
    size_t costoSolucionActual = std::numeric_limits<size_t>::max();
    size_t costoMejorSolucion = std::numeric_limits<size_t>::max();
};

#endif
