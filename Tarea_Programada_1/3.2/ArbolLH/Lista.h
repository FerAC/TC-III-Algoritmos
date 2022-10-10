#ifndef ListaSimplementeEnlazada
#define ListaSimplementeEnlazada

#include "Celda.h"
#include <stddef.h>

template <typename T, typename U>
class Lista {
	private:
		Celda<T, U> * primera;
		Celda<T, U> * ultima; 
		size_t contador;
	public:
		Lista() {
			primera = 0;
			ultima = 0;
			contador = 0;
		}

		~Lista() {
			Celda<T, U> ** temp = &primera;
			Celda<T, U> * tempSiguiente;
			for (size_t i=0; i<contador; ++i) {
				if ((**temp).getSiguiente()) {
					tempSiguiente = (**temp).getSiguiente();
				}
				delete *temp;
				if (i+1 < contador) {
					*temp = tempSiguiente; 
				}
			}
		}

		void insertar(const T& elemento) {
			Celda<T, U>* celdaNueva =  new Celda<T, U> (elemento);
			if (!primera) {
				primera = celdaNueva;
				ultima = celdaNueva;
			} else {
				ultima->setSiguiente(celdaNueva);
				ultima = celdaNueva; 
			}
			++contador; 
		}

		void borrar(const T& elemento) {
			Celda<T, U>* match = this->buscar(elemento);

			// Caso trivial: No se encontró
			if (match == nullptr) 
				return;

			// Caso A: Es el primer elemento
			if (match == this->primera) {
				Celda<T, U>* despuesMatch = match->getSiguiente();
				this->primera = despuesMatch;
			}
			// Caso B: Es un elemento después del primero
			else {
				Celda<T, U>* antesMatch = this->primera;
				while (antesMatch->getSiguiente() != match) {
					antesMatch = antesMatch->getSiguiente();
				}
				// Caso 2: Es el último elemento
				if (match == this->ultima) {
					antesMatch->setSiguiente(nullptr);
					this->ultima = antesMatch;	
				}
				// Caso 3: Es un elemento intermedio
				else {
					Celda<T, U>* despuesMatch = match->getSiguiente();
					antesMatch->setSiguiente(despuesMatch);
				}
			}

			// Elemento ha sido borrado
			delete match;
			--contador;
		}

		Celda<T, U> * buscar(const T& elemento) {
			int encontrado = 0;
			size_t i = 0;
			Celda<T, U>* temp = primera;
			while (i < contador && !encontrado) {
				if (temp->getEtiqueta() == elemento) {
					encontrado = 1;
				} else if (i + 1 < contador) {
					temp = temp->getSiguiente();
				}
				++i;
			}
			
			if (!encontrado) {
				return nullptr;
			} else {
				return temp; 
			}
		}

		void imprimir() {
			for (Celda<T, U>* iter = this->primera; iter != nullptr; iter = iter->getSiguiente()) {
				iter->imprimir();
			}
		}
		
		void modificarEnlaces(int indice, int etiqueta){
			Celda<T, U> * nuevaCelda= new Celda<T, U>(etiqueta);
			Celda<T, U> * anterior = primera;
			for(int i=0; i<indice ; ++i){
				anterior = anterior->getSiguiente();
			}
			Celda<T, U> * enlace = anterior->getSiguiente(); 
			nuevaCelda->setSiguiente(enlace);
			anterior->setSiguiente(nuevaCelda);
			
			
		}
};
#endif
