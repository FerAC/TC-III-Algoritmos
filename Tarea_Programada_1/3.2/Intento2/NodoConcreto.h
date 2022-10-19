#ifndef NodoConcretoLH
#define NodoConcretoLH
#include "Lista.h"
#include "Celda.h"
#include <iostream>
using namespace std;

class NodoConcreto{
	friend ostream& operator<<(ostream& salida, NodoConcreto p){
			return p.imprimir(salida);  
		}
	private:
		int etiqueta;
		Lista<NodoConcreto*> * listaHijos; 
		
	public:
		NodoConcreto();
		NodoConcreto(int); 
		~NodoConcreto();
		void insertarEnLista(NodoConcreto*);
		Lista<NodoConcreto*>* getListaHijos(); 
		int getEtiqueta();
		void setEtiqueta(int);
		ostream & imprimir(ostream&); 
		void imprimirValor();
		int operator==(NodoConcreto); 
		 
	
};
#endif