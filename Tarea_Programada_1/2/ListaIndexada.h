#ifndef ListaIndex
#define ListaIndex

// TODO: LISTA.H YA INCLUYE A CELDA.H
#include "Celda.h"
#include "Lista.h"
#include <stddef.h>

// TODO: PREFERIBLMENTE HEREDAR DE LISTA SIMPLEMENTE ENLAZADA EN VEZ DE COMPONER SOBRE ELLA
class ListaIndexada{
	private:
		size_t contador; 
		Lista<int> listaInterna; 
		Celda<int>* moverse(int);
	
	public:
		// TODO: FALTA VACIAR, VACIA, INICIAR Y DESTRUIR (¿ÚLTIMAS DOS SE PUEDEN TOMAR COMO CONST. Y DESTR?)
		ListaIndexada();
		~ListaIndexada();
		// TODO: INDICES DEBERIAN SER SIZE_T
		// TODO: INSERTAR ES POCO SIGNIFICATIVO (¿DONDE SE INSERTA?). NOMBRE ESTA RESERVADO EN OP. BASICAS
		void insertar(int, int);
		void borrar(int);
		int recuperar(int);
		void modificar(int, int);
		// TODO: NUM ELEM DEBERIA SER SIZE_T
		int numElem();
		// TODO: USAR OPERATOR<< PARA SER MAS VERSATIL
		void imprimir();
};
#endif 