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
		Celda(const T& elemento) {
			this->etiqueta = elemento;
			this->siguiente = nullptr;
			existe = 1;
		}

		Celda() {
			this->siguiente = nullptr;
		}
		
		void setEtiqueta(T valorNuevo){
			this->etiqueta = valorNuevo;
		}

		~Celda() {
			this->siguiente = nullptr;
			//delete &etiqueta;
		}

		int operator==(Celda* celda) {
			return (etiqueta == celda->etiqueta && siguiente == celda->siguiente);
		}

		T * getEtiqueta() {
			return &etiqueta;
		}
		
		T getEtiqueta(int noSeUsa){
			return etiqueta;
		}

		Celda* getSiguiente() {
			return siguiente;
		}

		void setSiguiente(Celda* celdaSiguiente) {
			siguiente = celdaSiguiente;
		}

		// TODO: UTILIZAR OPERATOR<< PARA SER MAS VERSATIL
		void imprimir() {
			std::cout << etiqueta << std::endl;
		}
		
		
		
		void imprimirPunteros(){
			//std::cout<< "Imprimendo lista hijos" << std::endl;
			if(existe){
				//std::cout <<"EXISTO " << std::endl;
				etiqueta->imprimirValor();
			} else{
				std::cout<< "Nodo Vacio" << std::endl;
			}
			
		}
};

#endif
