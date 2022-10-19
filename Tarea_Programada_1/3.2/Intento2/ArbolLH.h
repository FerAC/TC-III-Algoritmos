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
		void PonerRaiz(int);
		NodoConcreto* AgregarHijo(int, NodoConcreto*);
		NodoConcreto* AgregarHijoMasDerecho(int, NodoConcreto*);
		void BorrarHoja(NodoConcreto*);
		NodoConcreto* Raiz();
		NodoConcreto* Padre(NodoConcreto*);
		NodoConcreto* HijoMasIzquierdo(NodoConcreto*);
		NodoConcreto* HermanoDerecho(NodoConcreto*);
		int Etiqueta(NodoConcreto*);
		void ModificaEtiqueta(int, NodoConcreto*);
		int NumNodoConcretos();
		void Imprimir();
		Lista<NodoConcreto>* GetLP();
		void ImprimirLP();
	
};
#endif
