#include "ListaDijkstra.hpp"

#include <iostream>  // DEBUG

// CONSTRUCTORES y DESTRUCTORES

ListaDijkstra::ListaDijkstra(size_t tamano) {
    tamanoMax = tamano;
    pesos = new size_t[tamano];
    vertices = new char[tamano];
    verticeAnterior = new char[tamano];
    visitado = new bool[tamano];

    size_t contador = 0;
    while (contador < tamano)
    {
        visitado[contador] = false;
        ++contador;
    }
}

ListaDijkstra::~ListaDijkstra() {
    delete[] pesos;
    delete[] vertices;
    delete[] verticeAnterior;
    delete[] visitado;
}

// SETTERS y GETTERS 

void ListaDijkstra::agregar(char verticeActual, char elVerticeAnterior, size_t peso) {
    if (cantidadElementos < tamanoMax)
    {
        vertices[cantidadElementos] = verticeActual;
        pesos[cantidadElementos] = peso;
        verticeAnterior[cantidadElementos] = elVerticeAnterior;
        // std::cout<<"se agrego un elemento"<<std::endl;
        ++cantidadElementos;
    }
}

void ListaDijkstra::setPeso(char verticeActual, size_t peso) {
    int contador = 0;
    char vertice = vertices[contador];
    while (vertice != verticeActual)
    {
        ++contador;
        vertice = vertices[contador];
    }
    pesos[contador] = peso;
}

size_t ListaDijkstra::getPeso(char verticeActual) {
    int contador = 0;
    char vertice = vertices[contador];
    while (vertice != verticeActual)
    {
        ++contador;
        vertice = vertices[contador];
    }
    return pesos[contador];
}

size_t ListaDijkstra::getPesoPorIndice(size_t indice) {
    return pesos[indice];
}

void ListaDijkstra::setAnterior(char verticeActual, char anterior) {
    int contador = 0;
    char vertice = vertices[contador];
    while (vertice != verticeActual)
    {
        ++contador;
        vertice = vertices[contador];
    }
    verticeAnterior[contador] = anterior;
}

char ListaDijkstra::getVerticePorIndice(size_t indice) {
    return vertices[indice];
}

void ListaDijkstra::setVisitado(char verticeVisitado) {
    int contador = 0;
    char vertice = vertices[contador];
    while (vertice != verticeVisitado)
    {
        ++contador;
        vertice = vertices[contador];
    }
    visitado[contador] = true;
}

void ListaDijkstra::setVisitadoPorIndice(size_t indice) {
    visitado[indice] = true;
}

bool ListaDijkstra::esVisitadoPorIndice(size_t indice) {
    return visitado[indice];
}

// OTROS

void ListaDijkstra::imprimirLista() {
    size_t contador = 0;
    while (contador < cantidadElementos)
    {
        std::cout << vertices[contador] << "\t" << pesos[contador] << "\t" << verticeAnterior[contador] << std::endl;
        ++contador;
    }
}


