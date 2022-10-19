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
		

Nodo::Nodo(){
	
	
	
}

Nodo::~Nodo(){
	///delete listaHijos;
}

Nodo::Nodo(int et){
	etiqueta = et;
	listaHijos = new Lista<Nodo*>();
}

void Nodo::insertarEnLista(Nodo* nodoNuevo){
	
	if(listaHijos->getPrimera()!=nullptr){
		
		listaHijos->insertar(nodoNuevo);
		
	} else{
		
		listaHijos->insertarAlPrincipio(nodoNuevo);
		
	}
	
}

Lista<Nodo*>* Nodo::getListaHijos(){
	return listaHijos; 
}
void Nodo::imprimirValor(){
	std::cout<< etiqueta << std::endl;
}

int Nodo::operator==(Nodo nodo2){
	if(this->etiqueta == nodo2.getEtiqueta()){
		return 1;
	}
	return 0;
}

int Nodo::getEtiqueta(){
	return etiqueta;
}

void Nodo::setEtiqueta(int valorNuevo){
	this->etiqueta = valorNuevo;
}

ostream& Nodo::imprimir(ostream& output){
	output<< "Etiqueta : " << etiqueta << std::endl;
	output<< "Mis hijos son : " << std::endl;
	listaHijos->imprimirPunteros();
	return output;
}
		 
	
};
#endif