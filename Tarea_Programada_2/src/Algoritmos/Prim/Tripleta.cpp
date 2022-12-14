#include "Tripleta.hpp"

#include <iostream>  // DEBUG

// CONSTRUCTORES y DESTRUCTORES

Tripleta::Tripleta() {
}

Tripleta::Tripleta(Vertice vertice, size_t peso, Vertice &verticeAnterior)
{
    this->vertice = vertice;
    this->peso = peso;
    this->verticeAnterior = verticeAnterior;
}

Tripleta::Tripleta(const Tripleta& otra) 
: verticeAnterior(otra.verticeAnterior)
, vertice(otra.vertice)
, peso(otra.peso)  {
}

Tripleta::~Tripleta() {
}

// SETTERS y GETTERS

Tripleta& Tripleta::operator=(const Tripleta& otra) {
    this->vertice = otra.vertice;
    this->verticeAnterior = otra.verticeAnterior;
    this->peso = otra.peso;

    return *this;
}

void Tripleta::setPeso(size_t nuevo) {
    this->peso = nuevo;
}

size_t Tripleta::getPeso() const {
    return peso;
}

void Tripleta::setVertice(Vertice &vertice) {
    this->vertice = vertice;
}

Vertice Tripleta::getVertice() const {
    return vertice;
}

void Tripleta::setVerticeAnterior(Vertice &vertice) {
    this->verticeAnterior = vertice;
}

Vertice Tripleta::getVerticeAnterior() const {
    return verticeAnterior;
}

// OTROS

void Tripleta::imprimir() const
{
    std::cout << "Etiqueta: " << vertice.getEtiqueta() << std::endl;
    std::cout << "Etiqueta vieja: " << this->verticeAnterior.getEtiqueta() << std::endl;
    std::cout << "Peso: " << this->peso << std::endl;
}
