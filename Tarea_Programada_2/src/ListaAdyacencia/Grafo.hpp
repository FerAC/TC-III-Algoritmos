#ifndef GRAFO_LISTA_ADYACENCIA
#define GRAFO_LISTA_ADYACENCIA

#include "ListaAdyacencia/Vertice.hpp"

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
        void AgregarArista(Vertice& origen, Vertice& destino, size_t peso);

        // TODO(Us): Documentar
        void EliminarArista(Vertice& origen, Vertice& destino);

        // TODO(Us): Documentar
        size_t Peso(const Vertice& origen, const Vertice& destino) const;

        // TODO(Us): Documentar
        void ModificarPeso(Vertice& origen, Vertice& destino, size_t nuevoPeso);

        // TODO(Us): Documentar
        void ImprimirConexiones(const Vertice& vertice) const;

        // TODO(Us): Documentar
        void ImprimirVertices() const;
};

#endif
