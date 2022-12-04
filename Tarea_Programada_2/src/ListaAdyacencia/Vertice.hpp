#ifndef VERTICE_GRAFO_LISTA_ADYACENCIA
#define VERTICE_GRAFO_LISTA_ADYACENCIA

#include "ListaSimplementeEnlazada/Lista.hpp"

// TODO(Us): Documentar
class Vertice {
    friend class Grafo;

    private:
		// TODO(Us): Documentar
        class Contenedor 
        {
            friend class Grafo;

            private:
				// TODO(Us): Documentar
                size_t peso;
				// TODO(Us): Documentar
                Vertice* VAdyacente;

            public:
				// TODO(Us): Documentar
                Contenedor(Vertice& vertice, size_t pesoN);
                Contenedor(const Contenedor& original);
                Contenedor();

				// TODO(Us): Documentar
                ~Contenedor();

				// TODO(Us): Documentar
                int operator==(const Contenedor& otro);
                int operator!=(const Contenedor& otro);
        };

		// TODO(Us): Documentar
        char etiqueta;
		// TODO(Us): Documentar
		Lista<Contenedor>* listaAdyacencia;

		// TODO(Us): Documentar
        int esNulo();

    public:	
		/// @brief Constructor por omision de la clase nodo
		/// @remarks Requiere que el nodo no este inicializado 
		Vertice();

		/// @brief Destructor por omision de la clase nodo
		/// @remarks Requiere que el nodo este inicializada
		~Vertice();

		/// @brief constructor con parametros de clase nodo
		/// @remarks Requiere que el nodo no este inicializada
		/// @param char et  
		Vertice(char et);

		/// @brief inserta en la lista de hijos de un nodo
		/// @remarks Requiere que el nodo este inicializado y que tenga una lista de hijos inicializada
		/// @param Vertice* otro
        Vertice(Vertice* otro);

		/// @brief Retorna la lista de hijos de un nodo
		/// @remarks Requiere que el nodo este inicializado y tenga una lista de hijos
		/// @return Lista<Vertice*> en caso de no encontralo devuelve un nullptr 
		Lista<Contenedor>* getlistaAdyacencia();

        // TODO(Us): Usar?
		/// @brief imprime la etiqueta de un nodo
		/// @remarks Requiere que el nodo este inicializado
        /*
		void imprimirValor() {
			std::cout<< etiqueta << std::endl;
		}
       */

		/// @brief operador de igualdad de la clase nodo
		/// @remarks Requiere que ambos nodos esten inicializados y que posean etiquetas comparables
		/// @param Vertice 
		/// @return 1 si son iguales, 0 si no
		int operator==(const Vertice& nodo2) const;
       
		/// @brief operador de desigualdad de la clase nodo
		/// @remarks Requiere que ambos nodos esten inicializados y que posean etiquetas comparables
		/// @param Vertice 
		/// @return 0 si son iguales, 1 si no
		int operator!=(const Vertice& nodo2) const;

        // TODO(Us): Documentar
        int operator<(const Vertice& otro) const;

		/// @brief Devuelve la etiqueta de un nodo
		/// @remarks Requiere que el nodo este inicializado
		/// @return char etiqueta
		char getEtiqueta();

		/// @brief modifica la etiqueta de un nodo
		/// @remarks Requiere que el nodo este inicializado
		/// @param char  
		void setEtiqueta(char valorNuevo);
    
};

#endif
