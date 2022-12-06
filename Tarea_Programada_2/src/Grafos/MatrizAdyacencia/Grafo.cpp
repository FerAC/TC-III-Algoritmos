#ifdef MATRIZ

#include <iostream>

#include "MatrizAdyacencia/Grafo.hpp"

// CONSTRUCTORES Y DESTRUCTORES

Grafo::Grafo() {
}

Grafo::~Grafo() {
}

// VERTICES

Vertice Grafo::AgregarVertice(char elemento) {
    vector[vertices] = elemento;
    Vertice vertice(vertices++, elemento); 
    // matriz[vertices][vertices] = 1; 
    return vertice; 
}

void Grafo::EliminarVertice(const Vertice &borrado) {
    int encontrado = 0; 
    size_t indiceBorrado; 

    //Vertices es uno mayor al ultimo
    for (size_t i = 0; i < vertices; i++)
    {
        if (encontrado == 0) {
            if (vector[i] == borrado.etiqueta) {
                encontrado = 1;
                indiceBorrado = i;
                vector[i] = vector[i+1];
            }
        } else{
            if (i< vertices -1) {
                vector[i] = vector[i+1];
            } else if (i == vertices -1 ) {
                vector[i] = '0'; //Borrado logico 
            }
        }
    } //Ya lo borre del array

    for (size_t i = indiceBorrado; i < vertices; i++)
    { //Corrimiento de filas
        if (i<vertices-1) {
            for (size_t j = 0; j < vertices; j++)
            {
                matriz[i][j] =matriz[i+1][j]; 
            }
        } else{
            //No se si hacer borrado logico
        }   
    }
    for (size_t i = indiceBorrado; i < vertices; i++)
    { //Corrimiento de filas
        if (i<vertices-1) {
            for (size_t j = 0; j < vertices; j++)
            {
                matriz[j][i] =matriz[j][i+1]; 
            }
        } else{
            //No se si hacer borrado logico
        }
    }
    vertices--;
}

size_t Grafo::NumVertices() const {
    return vertices; 
}

char Grafo::Etiqueta(const Vertice& vertice) const {
    return vertice.etiqueta; 
}

void Grafo::ModificarEtiqueta(Vertice& vertice, char etiqueta) {
    vertice.etiqueta = etiqueta;
    vector[vertice.indice] = etiqueta; 
}

Vertice Grafo::PrimerVertice() const {
    Vertice vertice(0, vector[0]); 
    return vertice; 
}

Vertice Grafo::SiguienteVertice(const Vertice& anterior) const {
    Vertice NULO;

    if (anterior.indice+1 < NumVertices()) {
        Vertice vertice(anterior.indice+1, vector[anterior.indice+1]);
        return vertice;
    }

    return NULO; 
}

Vertice Grafo::PrimerVerticeAdyacente(const Vertice& original) const {
    for (size_t i = 0; i<vertices; i++) {
        if (matriz[original.indice][i]>0) {
            Vertice vertice (i, vector[i]);
            return vertice;
        }
    }

    Vertice vertice;
    return vertice; 
}

Vertice Grafo::SiguienteVerticeAdyacente(const Vertice& original, const Vertice& adyacente) const {
    if (adyacente.indice+1<vertices) {
        for (size_t i = adyacente.indice+1; i < vertices; i++)
        {
            if (matriz[original.indice][i]> 0) {
                Vertice  vertice (i, vector[i]);
                return vertice; 
            }
        }
    } else {
        Vertice NULO;
        return NULO;
    }

    Vertice vertice;
    return vertice; 
}

void Grafo::ImprimirVertices() const {
    for (size_t i = 0; i < vertices; i++) {
        std::cout << vector[i] << " ";
    }
}

// ARISTAS

int Grafo::ExisteArista(const Vertice& inicio, const Vertice& fin) const {
    const Vertice NULO;
    for (Vertice iterador = this->PrimerVerticeAdyacente(inicio);
        iterador != NULO;
        iterador = SiguienteVerticeAdyacente(inicio, iterador)) {
        if (iterador == fin) {
            return 1;
        }
    }

    return 0; 
}

void Grafo::AgregarArista(const Vertice& origen, const Vertice& destino, size_t peso) {
    matriz[origen.indice][destino.indice] = peso;
    matriz[destino.indice][origen.indice] = peso;
}

void Grafo::EliminarArista(const Vertice& origen, const Vertice& destino) {
    matriz[origen.indice][destino.indice] = -1;
    matriz[destino.indice][origen.indice] = -1;
}

size_t Grafo::Peso(const Vertice& origen, const Vertice& destino) const {
    return matriz[origen.indice][destino.indice]; 
}

void Grafo::ModificarPeso(const Vertice& origen, const Vertice& destino, size_t peso) {
    this->AgregarArista(origen, destino, peso);
}

void Grafo::ImprimirGrafo() const {
    for (size_t i = 0; i < vertices; i++)
    {
        for (size_t j = 0; j < vertices; j++) {
            std::cout<< matriz[i][j]<< " "; 
        }

        std::cout<< std::endl;
    }
    
}

#endif
