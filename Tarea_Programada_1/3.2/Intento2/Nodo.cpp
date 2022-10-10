#include "Nodo.h"

Nodo::Nodo(){
	
	
	
}

Nodo::~Nodo(){
	
	
}

Nodo::Nodo(int et){
	etiqueta = et;
	listaHijos = new Lista<Nodo*>();
}

void Nodo::insertarEnLista(Nodo* nodoNuevo){
	
	//std::cout<< "INSERTO A " << "EN LISTA HIJOS " << std::endl;
	if(listaHijos->getPrimera()!=nullptr){
		//std::cout<< "Voy a insertar un hijo NO primero" << std::endl;
		listaHijos->insertar(nodoNuevo);
		//std::cout<< "Inserte un hijo NO primero" << std::endl;
	} else{
		//std::cout<< "Estoy insertando primer hijo " << std::endl;
		listaHijos->insertarAlPrincipio(nodoNuevo);
		//std::cout<< "Inserte primer hijo " << std::endl;
	}
	
}

Lista<Nodo*>* Nodo::getListaHijos(){
	return listaHijos; 
}
void Nodo::imprimirValor(){
	std::cout<< etiqueta << std::endl;
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
}