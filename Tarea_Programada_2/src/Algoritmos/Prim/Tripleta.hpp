#ifndef TRIPLETA_FLOYD
#define TRIPLETA_FLOYD

#include "GrafoImplementado.hpp"

class Tripleta
{
    private:
        Vertice verticeAnterior;
        Vertice vertice;
        size_t peso;

    public:
        Tripleta();
        Tripleta(const Tripleta &otra);
        Tripleta(Vertice &vertice, size_t peso, Vertice &verticeAnterior);

        ~Tripleta();

        void setVertice(Vertice &vertice);
        Vertice getVertice() const;

        void setVerticeAnterior(Vertice &vertice);
        Vertice getVerticeAnterior() const;

        void setPeso(size_t nuevo);
        size_t getPeso() const;

        void imprimir() const;
};

#endif