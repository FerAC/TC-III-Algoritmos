#ifndef NodoArbol32
#define NodoArbol32
#include "NodoConcreto.h"

class Nodo{
	private:
	NodoConcreto* nodoConcreto = nullptr; 
	
	public:
	Nodo(){}
	int operator == (const Nodo& otroNodo){
		if(nodoConcreto == otroNodo.nodoConcreto){
			return 1;
		} 
		return 0;
	}
	Nodo(const Nodo& otroNodo){
		this->nodoConcreto = otroNodo.nodoConcreto;
	}
	
	
};

#endif
