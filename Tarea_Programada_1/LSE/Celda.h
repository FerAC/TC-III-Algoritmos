#ifndef Celda_Multitool
#define Celda_Multitool

#include <iostream>

template <typename T>
class Celda {
	private:
		T etiqueta;
		Celda * siguiente; 
	public:
		Celda(const T& elemento) {
			this->etiqueta = elemento;
			this->siguiente = 0;
		}

		Celda() {
			this->siguiente = nullptr;
		}

		~Celda() {
			this->siguiente = nullptr;
		}

		int operator==(Celda* celda) {
			return (etiqueta == celda->etiqueta && siguiente == celda->siguiente);
		}

		const T& getEtiqueta() {
			return etiqueta;
		}

		Celda* getSiguiente() {
			return siguiente;
		}

		void setSiguiente(Celda* celdaSiguiente) {
			siguiente = celdaSiguiente;
		}

		void imprimir() {
			std::cout << etiqueta << std::endl;
		}
};

#endif
