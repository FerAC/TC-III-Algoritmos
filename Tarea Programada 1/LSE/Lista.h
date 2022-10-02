#ifndef ListaSimplementeEnlazada
#define ListaSimplementeEnlazada
#include "Celda.h"

class Lista{
	private:
		Celda * primera;
		Celda * ultima; 
		int contador;
	public:
		Lista();
		~Lista();
		void insertar(int);
		void borrar(int);
		Celda * buscar(int); 
		void imprimir(); 
	
	
	
	
	
	
	
	
};
#endif
