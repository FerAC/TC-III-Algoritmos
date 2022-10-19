#ifndef ARBOLLH
#define ARBOLLH
#include "Lista.h"
#include "Celda.h"
#include "Nodo.h"

class ArbolLH{
	private:
		Lista<Nodo> * listaPrincipal; 
		
	public:
		ArbolLH();
		~ArbolLH();
		void ponerRaiz(Nodo*);
		Nodo* agregarHijo(Nodo, int);
		Nodo* agregarHijoMasDerecho(Nodo, int);
		void borrarHoja(Nodo*);
		Nodo* raiz();
		Nodo* padre(Nodo*);
		Nodo* hijoMasIzquierdo(Nodo*);
		Nodo* hermanoDerecho(Nodo*);
		int etiqueta(Nodo*);
		void modificaEtiqueta(Nodo*);
		int numNodos();
		void imprimir();
		Lista<Nodo>* getLP();
		void imprimirLP();
	
};
#endif
