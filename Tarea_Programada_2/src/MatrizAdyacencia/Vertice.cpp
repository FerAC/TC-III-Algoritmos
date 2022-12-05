#ifdef MATRIZ

#include "MatrizAdyacencia/Vertice.hpp"

// CONSTRUCTORES y DESTRUCTORES

Vertice::Vertice() {
    indice = 0;
    etiqueta = '0';
    nulo = 1;
}

Vertice::Vertice(size_t indice, char etiqueta) {
    this->indice = indice;
    this->etiqueta = etiqueta;
}

Vertice::~Vertice() {
}

// COMPARADORES

bool Vertice::operator ==(const Vertice& otro) const {
    if (otro.etiqueta == this->etiqueta && otro.indice == this->indice)
        return 1;

    return 0;
}

bool Vertice::operator!=(const Vertice&otro) const {
    return !(*this==otro); 
}

bool Vertice::operator<(const Vertice& otro) const {
    return this->etiqueta < otro.etiqueta;
}

// SETTERS y GETTERS

void Vertice::setPosicion(size_t indice) {
    this->indice = indice;
}

size_t Vertice::getindice() const {
    return indice; 
}

void Vertice::setEtiqueta(char valor) {
    this->etiqueta = valor;
}

char Vertice::getEtiqueta() const {
    return this->etiqueta;
}

// OTROS

int Vertice::esNulo() {
    if (nulo == 1 && etiqueta == '0') {
        return 1;
    }

    return 0;            
}

#endif
