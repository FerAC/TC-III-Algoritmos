#ifndef NodoConcretoLH
#define NodoConcretoLH
#include "Lista.h"
#include "Celda.h"
#include "ArbolLH.hpp"
#include <iostream>
using namespace std;

class NodoConcreto{
	friend ostream& operator<<(ostream& salida, NodoConcreto p){
			return p.imprimir(salida);  
		}
	friend class ArbolLH; 
	private:
		int etiqueta;
		Lista<NodoConcreto*> * listaHijos; 
		
	public:
		

NodoConcreto::NodoConcreto(){
	
}

NodoConcreto::~NodoConcreto(){
	///delete listaHijos;
}

NodoConcreto::NodoConcreto(int et){
	etiqueta = et;
	listaHijos = new Lista<NodoConcreto*>();
}

void NodoConcreto::insertarEnLista(NodoConcreto* nodoNuevo){
	
	if(listaHijos->getPrimera()!=nullptr){
		
		listaHijos->insertar(nodoNuevo);
		
	} else{
		
		listaHijos->insertarAlPrincipio(nodoNuevo);
		
	}
	
}

Lista<NodoConcreto*>* NodoConcreto::getListaHijos(){
	return listaHijos; 
}
void NodoConcreto::imprimirValor(){
	std::cout<< etiqueta << std::endl;
}

int NodoConcreto::operator==(NodoConcreto nodo2){
	if(this->etiqueta == nodo2.getEtiqueta()){
		return 1;
	}
	return 0;
}

int NodoConcreto::getEtiqueta(){
	return etiqueta;
}

void NodoConcreto::setEtiqueta(int valorNuevo){
	this->etiqueta = valorNuevo;
}

ostream& NodoConcreto::imprimir(ostream& output){
	output<< "Etiqueta : " << etiqueta << std::endl;
	output<< "Mis hijos son : " << std::endl;
	listaHijos->imprimirPunteros();
	return output;
}
		 
	
};
#endif