#ifndef GRAFO_LISTA_ADYACENCIA
#define GRAFO_LISTA_ADYACENCIA

#include "ListaAdyacencia/Vertice.hpp"
#include <iostream>

// TODO(Us): Documentar
class Grafo {
    private:
        // TODO(Us): Documentar
		Lista<Vertice>* listaPrincipal; 
		
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
        void EliminarVertice(Vertice& vertice);

        // TODO(Us): Documentar
        size_t NumVertices() const;

        // TODO(Us): Documentar
        char Etiqueta(Vertice& vertice);

        // TODO(Us): Documentar
        Vertice PrimerVertice();

        // TODO(Us): Documentar
        Vertice SiguienteVertice(Vertice& original);

        // TODO(Us): Documentar
        Vertice PrimerVerticeAdyacente(Vertice& original);

        // TODO(Us): Documentar
        Vertice SiguienteVerticeAdyacente(Vertice& original, Vertice& adyAnterior);

        // TODO(Us): Documentar
        int ExisteArista(Vertice& inicio, Vertice& fin);

        // TODO(Us): Documentar
        void ModificarEtiqueta(Vertice& vertice, char nueva);

        // TODO(Us): Documentar
        void AgregarArista(Vertice& origen, Vertice& destino, size_t peso);

        // TODO(Us): Documentar
        void EliminarArista(Vertice& origen, Vertice& destino);

        // TODO(Us): Documentar
        size_t Peso(const Vertice& origen, const Vertice& destino);

        // TODO(Us): Documentar
        void ModificarPeso(Vertice& origen, Vertice& destino, size_t nuevoPeso);

        // TODO(Us): Documentar
        void ImprimirConexiones(Vertice& vertice);

        // TODO(Us): Documentar
        void ImprimirVertices();
};

#endif