#ifndef Grafo_Matriz_Adyacencia
#define Grafo_Matriz_Adyacencia

#include "MatrizAdyacencia/Vertice.hpp"

// TODO(Us): Documentar
class Grafo {
    private:
        // TODO(Us): Documentar
        size_t vertices = 0;
        // TODO(Us): Documentar
        int matriz[100][100];
        // TODO(Us): Documentar
        char vector[100];

    public:
        /// @brief Crea un nuevo Arbol e inicializa su lista principal
        /// @remarks Requiere que el arbol no este inicializado 
        Grafo();

        /// @brief Elimina al arbol y su lista principal
        /// @remarks Requiere que el arbol este inicializado
        ~Grafo();

        // TODO(Us): Documentar
        Vertice AgregarVertice(char etiqueta);

        // TODO(Us): Documentar
        void EliminarVertice(const Vertice& vertice);

        // TODO(Us): Documentar
        size_t NumVertices() const;

        // TODO(Us): Documentar
        char Etiqueta(const Vertice& vertice) const;

        // TODO(Us): Documentar
        Vertice PrimerVertice() const;

        // TODO(Us): Documentar
        Vertice SiguienteVertice(const Vertice& original) const;

        // TODO(Us): Documentar
        Vertice PrimerVerticeAdyacente(const Vertice& original) const;

        // TODO(Us): Documentar
        Vertice SiguienteVerticeAdyacente(const Vertice& original, const Vertice& adyAnterior) const;

        // TODO(Us): Documentar
        int ExisteArista(const Vertice& inicio, const Vertice& fin) const;

        // TODO(Us): Documentar
        void ModificarEtiqueta(Vertice& vertice, char nueva);

        // TODO(Us): Documentar
        void AgregarArista(const Vertice& origen, const Vertice& destino, size_t peso);

        // TODO(Us): Documentar
        void EliminarArista(const Vertice& origen, const Vertice& destino);

        // TODO(Us): Documentar
        size_t Peso(const Vertice& origen, const Vertice& destino) const;

        // TODO(Us): Documentar
        void ModificarPeso(const Vertice& origen, const Vertice& destino, size_t nuevoPeso);

        // TODO(Us): Documentar
        void ImprimirVertices() const;

        // TODO(Us): Documentar
        void ImprimirGrafo() const;
};

#endif