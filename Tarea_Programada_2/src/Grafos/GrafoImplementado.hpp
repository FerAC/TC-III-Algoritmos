#ifndef GRAFO_IMPLEMENTADO

    #ifdef MATRIZ
        #include "MatrizAdyacencia/Grafo.hpp"
        #define TIPO_GRAFO "MATRIZ DE ADYACENCIA"
    #else
        #include "ListaAdyacencia/Grafo.hpp"
        #define TIPO_GRAFO "LISTA DE ADYACENCIA"
    #endif

#endif
