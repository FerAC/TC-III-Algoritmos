#ifndef ListaIndex
#define ListaIndex

#include "Celda.h"
#include "Lista.h"
#include <stddef.h>

class ListaIndexada{
	private:
		size_t contador; 
		Lista<int> listaInterna; 
		Celda<int>* moverse(int);
	
	public:
		ListaIndexada();
		~ListaIndexada();
		void insertar(int, int);
		void borrar(int);
		int recuperar(int);
		void modificar(int, int);
		int numElem();
		void imprimir();
};
#endif 