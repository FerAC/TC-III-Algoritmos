#ifndef VERTICE_GRAFO_MATRIZ_ADYACENCIA
#define VERTICE_GRAFO_MATRIZ_ADYACENCIA

#include "cstddef"

// TODO(Us): Documentar
class Vertice
{
    friend class Grafo;

    private:
        // TODO(Us): Documentar
        size_t indice; //Posicion en el arreglo
        // TODO(Us): Documentar
        char etiqueta;
        // TODO(Us): Documentar
        int nulo = 0; 

        // TODO(Us): Documentar
        int esNulo();

        // TODO(Us): Documentar
        void setPosicion(size_t indice);

        // TODO(Us): Documentar
        size_t getindice();

        // TODO(Us): Documentar
        void setEtiqueta(char valor);

    public:
        // TODO(Us): Documentar
        Vertice();

        // TODO(Us): Documentar
        Vertice(size_t indice, char etiqueta);
        // TODO(Us): Documentar

        // TODO(Us): Documentar
        ~Vertice();

        // TODO(Us): Documentar
        char getEtiqueta();

        // TODO(Us): Documentar
        bool operator ==(const Vertice& otro) const;

        // TODO(Us): Documentar
        bool operator!=(const Vertice& otro) const;

        // TODO(Us): Documentar
        bool operator<(const Vertice& otro) const;
};

#endif
