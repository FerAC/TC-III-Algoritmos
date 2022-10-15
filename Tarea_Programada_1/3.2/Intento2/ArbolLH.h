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
		void agregarHijo(Nodo, int);
		void agregarHijoMasDerecho(Nodo, int);
		void borrarHoja(Nodo*);
		Celda<Nodo>* raiz();
		Nodo* padre(Nodo*);
		Celda<Nodo*>* hijoMasIzquierdo(Nodo*);
		Nodo* hermanoDerecho(Celda<Nodo>*);
		int etiqueta(Nodo*);
		void modificaEtiqueta(Nodo*);
		int numNodos();
		void imprimir();
		Lista<Nodo>* getLP();
		void imprimirLP();
	
};
#endif
