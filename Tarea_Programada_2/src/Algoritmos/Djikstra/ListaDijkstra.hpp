#ifndef LISTA_DIJKSTA
#define LISTA_DIJKSTA

#include <cstddef>  // Para size_t

class ListaDijkstra
{
    public:

        size_t cantidadElementos = 0;
        size_t tamanoMax;

        bool* visitado;
        size_t* pesos;

        char* vertices;
        char* verticeAnterior;

        ListaDijkstra(size_t tamano);

        ~ListaDijkstra();

        void agregar(char verticeActual, char elVerticeAnterior, size_t peso);

        void setPeso(char verticeActual, size_t peso);

        size_t getPeso(char verticeActual);

        size_t getPesoPorIndice(size_t indice);

        void setAnterior(char verticeActual, char anterior);

        char getVerticePorIndice(size_t indice);

        bool esVisitadoPorIndice(size_t indice);

        void setVisitadoPorIndice(size_t indice);

        void setVisitado(char verticeVisitado);

        void imprimirLista();
};

#endif
