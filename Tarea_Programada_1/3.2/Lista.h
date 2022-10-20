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
/// @brief Constructor por omision de la clase lista
/// @remarks Requiere que la lista no este inicializada 
		Lista() {
			primera = nullptr;
			ultima = nullptr;
			contador = 0;
		}
/// @brief Destructor de la clase lista
/// @remarks Requiere que la celda este inicializada
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
/// @brief inserta un elemento en la lista
/// @remarks Requiere que la lista este inicializada
		void insertar(const T& elemento) {
			Celda<T>* celdaNueva =  new Celda<T> (elemento);
			if (!primera) {
				
				primera = celdaNueva;
				ultima = celdaNueva;
			} else {
				
				if(!ultima){
					
				}
				ultima->setSiguiente(celdaNueva);
				
				ultima = celdaNueva; 
				
			}
			++contador; 
		}
		
/// @brief inserta un elemento al principio de la lista
/// @remarks Requiere que la lista este inicializada
		void insertarAlPrincipio(const T& elemento){
			Celda<T> * celdaNueva = new Celda<T> (elemento);  
			celdaNueva->setSiguiente(primera); 
			primera = celdaNueva;
			if(!ultima){
				ultima = celdaNueva;
			}
			contador++;
		}
/// @brief Elimina a un elemento de la lista
/// @remarks Requiere que la celda este inicializada 
/// @return int en caso de lograr el borrado devuelve 1, si no 0
		int borrar(const T& elemento) {
			Celda<T>* match = this->buscar(elemento);
			int validez = 0;
			// Caso trivial: No se encontró
			if (match == nullptr) {
				
				return validez;
			}

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

			return 1;
		}

/// @brief Devuelve la celda asociada a una etiqueta en especifico
/// @remarks Requiere que la lista este inicializada y que posea una etiqueta
/// @param T elemento
/// @return Celda<T> en caso de no encontralo devuelve un nullptr 
		Celda<T> * buscar(const T& elemento) {
			int encontrado = 0;
			size_t i = 0;
			if(this->primera == nullptr)
				return nullptr;
			
			Celda<T>* temp = primera;
			// TODO: MAS FACIL MODULARIZAR EN FOR
			
			while (i < contador && !encontrado) {
				if (temp->getEtiqueta(4) == elemento) {
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
/// @brief Devuelve la celda asociada a un entero en especifico
/// @remarks Requiere que la lista este inicializada y que posea una etiqueta
/// @return Celda<T> en caso de no encontralo devuelve un nullptr
/// @param int elemento 
		Celda<T> * buscar(int elemento){
			int encontrado = 0;
			size_t i = 0;
			Celda<T>* temp = primera;
			
			while (i < contador && !encontrado) {
				if (temp->getEtiqueta()->getEtiqueta() == elemento) {
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
			
			if(primera){
				
			} else{
				
			}
			int i =0;
			for (Celda<T>* iter = this->primera; iter != nullptr; iter = iter->getSiguiente()) {
				
				iter->imprimirPunteros();
			}
			
		}
		// TODO: INDICE DEBERIA SER SIZE_T,
/// @brief inserta una lista en una posicion en especifico de la lista, por lo que debe modificar los enlaces
/// @remarks Requiere que la lista este inicializada y que posea una etiqueta
/// @param size_t indice, int etiqueta 
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
		
/// @brief Retorna la primera celda de la lista
/// @remarks Requiere que la celda este inicializada
/// @return Celda<T> en caso de no encontralo devuelve un nullptr 
		Celda<T>* getPrimera(){
			return primera;
			
		}
/// @brief Retorna la ultima celda de la lista
/// @remarks Requiere que la celda este inicializada
/// @return Celda<T> en caso de no encontralo devuelve un nullptr 
		Celda<T>* getUltima(){
			return ultima;
			
		}
};
#endif
