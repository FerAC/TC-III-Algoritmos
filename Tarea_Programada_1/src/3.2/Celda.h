#ifndef Celda_Multitool
#define Celda_Multitool

#include <iostream>

template <typename T>
class Celda {
	private:
		T etiqueta;
		Celda * siguiente; 
		int existe;
	public:
/// @brief Constructor de clase celda 
/// @param  elemento Un elemento de tipo T
/// @remarks Requiere que la celda no este inicializada
		Celda(const T& elemento) {
			this->etiqueta = elemento;
			this->siguiente = nullptr;
			existe = 1;
		}
/// @brief Constructor por omision de la celda
/// @remarks Requiere que la celda no este inicializada
		Celda() {
			this->siguiente = nullptr;
		}

/// @brief Cambia la etiqueta en un indice 
/// @param  valorNuevo un elemento de tipo T
/// @remarks Requiere que el valor nuevo sea valido
		void setEtiqueta(T valorNuevo){
			this->etiqueta = valorNuevo;
		}

/// @brief Destructor de la clase Celda
/// @remarks Requiere que la celda este inicializada
		~Celda() {
			this->siguiente = nullptr;
			//delete &etiqueta;
		}

/// @brief Metodo utilizado para comparar celdas
/// @param celda Un puntero a la celda que se quiere comparar
/// @remarks Requiere que ambas celdas esten inicializadas y sean comparables
		int operator==(Celda* celda) {
			return (etiqueta == celda->etiqueta && siguiente == celda->siguiente);
		}

/// @brief Devuelve un puntero a etiqueta
/// @remarks Requiere que la celda este inicializada y que posea una etiqueta
/// @return T* 
		T * getEtiqueta() {
			return &etiqueta;
		}
		
/// @brief Devuelve una etiqueta
/// @remarks Requiere que la celda este inicializada y que posea una etiqueta
/// @return T
		T getEtiqueta(int noSeUsa){
			return etiqueta;
		}
/// @brief Devuelve un puntero a la celda siguiente 
/// @remarks Requiere que la celda este inicializada
/// @return Celda* en caso de no poseer siguiente retorna nullptr 
		Celda* getSiguiente() {
			return siguiente;
		}
/// @brief modifica la celda, especificamente su enlace a siguiente celda
/// @remarks Requiere que la celda este inicializada
		void setSiguiente(Celda* celdaSiguiente) {
			siguiente = celdaSiguiente;
		}

		void imprimir() {
			std::cout << etiqueta << std::endl;
		}
		
		
		
		void imprimirPunteros(){
			
			if(existe){
				
				etiqueta->imprimirValor();
			} else{
				std::cout<< "Nodo Vacio" << std::endl;
			}
			
		}
};

#endif
