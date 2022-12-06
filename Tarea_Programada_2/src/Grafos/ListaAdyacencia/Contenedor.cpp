#include "ListaAdyacencia/Grafo.hpp"

// CONSTRUCTORES y DESTRUCTORES

Vertice::Contenedor::Contenedor() {
}

Vertice::Contenedor::Contenedor(const Contenedor& original) {
    VAdyacente = original.VAdyacente;
    peso = original.peso; 
}

Vertice::Contenedor::Contenedor(Vertice& vertice, size_t pesoN) {
    VAdyacente = &vertice;
    peso = pesoN; 
}

Vertice::Contenedor::~Contenedor() {
}

// COMPARADORES

int Vertice::Contenedor::operator==(const Contenedor& otro) {
    if (otro.VAdyacente == this->VAdyacente) {
        return 1;
    }

    return 0;
}

int Vertice::Contenedor::operator!=(const Contenedor& otro) {
    if (otro.VAdyacente == this->VAdyacente) {
        return 0;
    }

    return 1;
}
