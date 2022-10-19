#ifndef ARBOLLH
#define ARBOLLH
#include "Lista.h"
#include "Celda.h"
#include "NodoConcreto.h"

class ArbolLH{
	private:
		Lista<NodoConcreto> * listaPrincipal; 
		
	public:
		ArbolLH();
		~ArbolLH();
		void ponerRaiz(NodoConcreto*);
		NodoConcreto* agregarHijo(NodoConcreto, int);
		NodoConcreto* agregarHijoMasDerecho(NodoConcreto, int);
		void borrarHoja(NodoConcreto*);
		NodoConcreto* raiz();
		NodoConcreto* padre(NodoConcreto*);
		NodoConcreto* hijoMasIzquierdo(NodoConcreto*);
		NodoConcreto* hermanoDerecho(NodoConcreto*);
		int etiqueta(NodoConcreto*);
		void modificaEtiqueta(NodoConcreto*);
		int numNodoConcretos();
		void imprimir();
		Lista<NodoConcreto>* getLP();
		void imprimirLP();
	
};
#endif
