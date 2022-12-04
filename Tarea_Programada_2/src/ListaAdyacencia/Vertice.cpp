#include "ListaAdyacencia/Grafo.hpp"

// CONSTRUCTORES Y DESTRUCTORES

Vertice::Vertice() {
    listaAdyacencia = nullptr;
    etiqueta = '@'; 
}

Vertice::Vertice(char et) {
    etiqueta = et;
}

Vertice::Vertice(Vertice* otro) {
    this->listaAdyacencia = otro->listaAdyacencia;
    this->etiqueta = otro->etiqueta; 
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

char Vertice::getEtiqueta() {
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
