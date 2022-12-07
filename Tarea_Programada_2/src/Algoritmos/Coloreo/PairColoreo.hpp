#ifndef PAIR_COLOREO
#define PAIR_COLOREO

#include <cstddef>  // Size_t
#include <list>  // Listas
#include <utility>  // Parejas

#include "GrafoImplementado.hpp"

typedef struct {
    std::list<std::pair<size_t, Vertice>> listaColoreada;
    size_t cantidadColores;
} PairColoreo;

#endif
