#ifndef MATRIZ

#include <iostream>

#include "ListaAdyacencia/Grafo.hpp"

// CONSTRUCTORES Y DESTRUCTORES

Vertice::Vertice() {
    listaAdyacencia = nullptr;
    etiqueta = 255; 
}

Vertice::Vertice(char et) {
    etiqueta = et;
}

Vertice::Vertice(const Vertice &otro)
: etiqueta(otro.etiqueta) 
, listaAdyacencia(otro.listaAdyacencia) {
}

Vertice::Vertice(Vertice* otro)
: etiqueta(otro->etiqueta) 
, listaAdyacencia(otro->listaAdyacencia) {
}

Vertice::~Vertice() {
}

// COMPARADORES

int Vertice::operator==(const Vertice& nodo2) const {
    if (this->etiqueta== nodo2.etiqueta) {
        return 1;
    }
    return 0;
}

int Vertice::operator!=(const Vertice& nodo2) const {
    if (this->etiqueta == nodo2.etiqueta) {
        return 0;
    }
    return 1;
}

int Vertice::operator<(const Vertice& otro) const {
    return this->etiqueta < otro.etiqueta;
}

// SETTERS y GETTERS

Vertice& Vertice::operator=(const Vertice& otro) {
    this->etiqueta = otro.etiqueta,
    this->listaAdyacencia = otro.listaAdyacencia;

    return *this;
}

char Vertice::getEtiqueta() const {
    return etiqueta;
}

void Vertice::setEtiqueta(char valorNuevo) {
    this->etiqueta = valorNuevo;
}

Lista<Vertice::Contenedor>* Vertice::getlistaAdyacencia() {
    return listaAdyacencia; 
}

// OTROS

int Vertice::esNulo() {
    return 0;
}

#endif
