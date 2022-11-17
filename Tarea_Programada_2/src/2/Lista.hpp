#ifndef ListaSimplementeEnlazada
#define ListaSimplementeEnlazada

#include "Celda.hpp"
#include <stddef.h>

template <typename T>
class Lista {
	private:
		Celda<T> * primera;
		Celda<T> * ultima; 
		size_t contador;
	public:
		Lista() {
			primera = nullptr;
			ultima = nullptr;
			contador = 0;
		}

		~Lista() {
			
			if(primera!=nullptr){
				Celda<T> ** temp = &primera;
				Celda<T> * tempSiguiente;
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
		}

		void insertar(const T& elemento) {
			Celda<T>* celdaNueva =  new Celda<T> (elemento);
			
			if (!primera) {
				this->ultima = celdaNueva; 
				this->primera = celdaNueva;
			} else {
				ultima->setSiguiente(celdaNueva);
				ultima = celdaNueva; 
			}
			++contador; 
		}
		
		void insertarAlPrincipio(const T& elemento){
			Celda<T> * celdaNueva = new Celda<T> (elemento);  
			celdaNueva->setSiguiente(primera); 
			primera = celdaNueva;
			ultima = celdaNueva;
			++contador;
		}

		int borrar(T elemento) {
			
			Celda<T>* match = this->buscar(elemento);

			// Caso trivial: No se encontro
			if (match == nullptr){
				return 0;
				
			}
			// Caso A: Es el primer elemento
			if (match == this->primera) {
				
				Celda<T>* despuesMatch = match->getSiguiente();
				this->primera = despuesMatch;
			}
			// Caso B: Es un elemento despues del primero
			else {
				Celda<T>* antesMatch = this->primera;
				while (antesMatch->getSiguiente() != match) {
					antesMatch = antesMatch->getSiguiente();
				}
				// Caso 2: Es el ultimo elemento
				if (match == this->ultima) {
					antesMatch->setSiguiente(nullptr);
					this->ultima = antesMatch;	
				}
				// Caso 3: Es un elemento intermedio
				else {
					Celda<T>* despuesMatch = match->getSiguiente();
					antesMatch->setSiguiente(despuesMatch);
				}
			}

			// Elemento ha sido borrado
			delete match;
			--contador;
			return 1;
		}

		Celda<T> * buscar( T elemento) {
			
			int encontrado = 0;
			size_t i = 0;
			Celda<T>* temp = primera;
			if(primera->getEtiqueta()==elemento)
				return primera;
			
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
			for (Celda<T>* iter = this->primera; iter != nullptr; iter = iter->getSiguiente()) {
				iter->imprimir();
			}
		}

		void modificarEnlaces(int indice, int etiqueta){
			Celda<T> * nuevaCelda= new Celda<T>(etiqueta);
			++contador;
			Celda<T> * anterior = primera;
			for(int i=0; i<indice-1 ; ++i){  //Lego al indice donde quiero insertar
				anterior = anterior->getSiguiente();
			}
			nuevaCelda->setSiguiente(anterior->getSiguiente());
			anterior->setSiguiente(nuevaCelda);
		}
		
		Celda<T>* getPrimera(){
			return primera;
		}

		Celda<T>* getUltima(){
			return ultima;
		}

		int getContador(){
			return contador;
		}

};
#endif
