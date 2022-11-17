#ifndef ListaIndex
#define ListaIndex

#include "Celda.hpp"
#include "Lista.hpp"
#include <stddef.h>

class ListaIndexada{
	private:
		size_t contador; 
		Lista<int> listaInterna;
	
	public:
		/// @brief Inicializa la lista indexada
		/// @remarks Requiere que el arbol este inicializado y padre no nulo 	
		ListaIndexada(){
			contador = 0;
		}

		/// @brief Devuelve el valor en un indice de la lista
		/// @param  Una lista inicializada y un entero indice
		/// @remarks Requiere que el indice sea valido (entre 0 y el valor tamano maximo de la lista)	
		int recuperar(int indice){
			Celda<int>* actual = this->moverse(indice);
			return actual->getEtiqueta();
		}

		/// @brief Agrega un valor nuevo a la lista
		/// @param  Un entero con la etiqueta a insertar y un entero indice donde se insertara el valor nuevo
		/// @remarks Requiere que la lista este inicializada, que la etiqueta no este en la lista y que el indice sea menor o igual al tamano actual de la lista+1
		void insertar(int etiqueta, int indice){
			if(contador==indice){
				listaInterna.insertar(etiqueta); 
			} else if(indice!= 0){
				listaInterna.modificarEnlaces(etiqueta, indice);
			} else{
				listaInterna.insertarAlPrincipio(etiqueta);
			}
			contador++;
		}

		/// @brief Cambia la etiqueta en un indice 
		/// @param  Un entero con el valor nuevo de la etiquet y un entero con el indice a modificar
		/// @remarks Requiere que la lista este inicializada, que el valor nuevo no pertenezca a la lista y que el indice sea valido (entre 0 y el tamano maximo de la lista)
		void modificar(int valorNuevo, int indice){
			Celda<int>* actual = this->moverse(indice); 
			actual->setEtiqueta(valorNuevo);
		}

		Celda<int>* moverse(int indice){
			Celda<int>* actual = listaInterna.getPrimera();
			for(int i=0; i<indice; ++i){
				actual = actual->getSiguiente();
			}
			return actual;
		}

		/// @brief Devuelve la cantidad de elementos de la lista
		/// @remarks Requiere que la lista este inicializada 	
		int numElem(){
			return contador;
		}

		/// @brief Borra un elemento de la lista 
		/// @param un entero asociado a un indice
		/// @remarks Requiere que la lista este inicializada y que el indice sea valido (entre 0 y el tamano maximo de la lista)	
		void borrar(int indice){
			
			listaInterna.borrar(recuperar(indice));
		}

		/// @brief Borra la lista 
		/// @remarks Requiere que la lista este inicializada 	
		~ListaIndexada(){
		}

		void imprimir(){
			listaInterna.imprimir();
		}
};
#endif 