#ifndef ListaSimplementeEnlazada
#define ListaSimplementeEnlazada

#include "Celda.h"
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

		// TODO: INSERTAR DEBERIA SER POR INDICE Y VALOR, NO SOLO POR VALOR
		// TODO: INSERTAR ES POCO SIGNIFICATIVO (¿DONDE SE INSERTA?). NOMBRE ESTA RESERVADO EN OP. BASICAS
		void insertar(const T& elemento) {
			Celda<T>* celdaNueva =  new Celda<T> (elemento);
			if (!primera) {
				//std::cout<< "*******************LISTA*****************" << std::endl;
				//std::cout<< "PRIMER H" << std::endl;
				primera = celdaNueva;
				ultima = celdaNueva;
			} else {
				/*
				//std::cout<< "*******************LISTA*****************" << std::endl;
				//std::cout<< "NO PRIMER H" << std::endl;
				*/
				//std::cout<< "Estoy insertando un hijo no primero" << std::endl;
				if(!ultima){
					//std::cout << "NO HAY ULTIMA " << std::endl;
				}
				ultima->setSiguiente(celdaNueva);
				//std::cout<< "NICE" << std::endl;
				ultima = celdaNueva; 
				//std::cout<< "SE LOGRO " <<std::endl;
			}
			++contador; 
		}
		
		void insertarAlPrincipio(const T& elemento){
			Celda<T> * celdaNueva = new Celda<T> (elemento);  
			celdaNueva->setSiguiente(primera); 
			primera = celdaNueva;
			if(!ultima){
				ultima = celdaNueva;
			}
			contador++;
			// TODO: FALTA ACTUALIZAR CONTADOR
		}

		// TODO: BORRADO DEBERIA SER POR INDICE, NO POR VALOR
		void borrar(const T& elemento) {
			Celda<T>* match = this->buscar(elemento);

			// Caso trivial: No se encontró
			if (match == nullptr) 
				return;

			// Caso A: Es el primer elemento
			if (match == this->primera) {
				Celda<T>* despuesMatch = match->getSiguiente();
				this->primera = despuesMatch;
			}
			// Caso B: Es un elemento después del primero
			else {
				Celda<T>* antesMatch = this->primera;
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
					Celda<T>* despuesMatch = match->getSiguiente();
					antesMatch->setSiguiente(despuesMatch);
				}
			}

			// Elemento ha sido borrado
			delete match;
			--contador;
		}

		Celda<T> * buscar(const T& elemento) {
			int encontrado = 0;
			size_t i = 0;
			Celda<T>* temp = primera;
			// TODO: MAS FACIL MODULARIZAR EN FOR
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
		void imprimirPunteros(){
			////std::cout<<"Llegue a imprimir punteros " << std::endl;
			if(primera){
				//std::cout << "Hay primera " << std::endl;
			} else{
				//std::cout << "No hay primera " << std::endl;
			}
			int i =0;
			for (Celda<T>* iter = this->primera; iter != nullptr; iter = iter->getSiguiente()) {
				//std::cout<< "SOY ITER " << i++ << std::endl;
				iter->imprimirPunteros();
			}
			std::cout << "";
		}
		// TODO: INDICE DEBERIA SER SIZE_T,
		void modificarEnlaces(size_t indice, int etiqueta){
			Celda<T> * nuevaCelda= new Celda<T>(etiqueta);
			++contador;
			Celda<T> * anterior = primera;
			for(int i=0; i<indice-1 ; ++i){  //Lego al indice donde quiero insertar
				anterior = anterior->getSiguiente();
			}
			nuevaCelda->setSiguiente(anterior->getSiguiente());
			anterior->setSiguiente(nuevaCelda);
		}
		
		// TODO: USAR OPERATOR<< PARA SER MAS VERSATIL
		Celda<T>* getPrimera(){
			return primera;
			
		}
};
#endif
