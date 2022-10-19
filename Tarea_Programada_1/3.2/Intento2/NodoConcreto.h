#ifndef NODOLH
#define NODOLH
#include "Lista.h"
#include "Celda.h"
#include <iostream>
using namespace std;

class NodoConcreto{
	friend ostream& operator<<(ostream& salida, Nodo p){
			return p.imprimir(salida);  
		}
	private:
		int etiqueta;
		Lista<Nodo*> * listaHijos; 
		
	public:
		Nodo();
		Nodo(int); 
		~Nodo();
		void insertarEnLista(Nodo*);
		Lista<Nodo*>* getListaHijos(); 
		int getEtiqueta();
		void setEtiqueta(int);
		ostream & imprimir(ostream&); 
		void imprimirValor();
		int operator==(Nodo); 
		 
	
};
#endif