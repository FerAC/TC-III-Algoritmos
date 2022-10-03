#include <iostream>
#include "ListaIndexada.h"
using namespace std;

ListaIndexada::ListaIndexada(){
	contador = 0;
	//Lista<int> listaInterna();
}

int ListaIndexada::recuperar(int indice){
	Celda<int>* actual = this->moverse(indice);
	
	return actual->getEtiqueta();
}

void ListaIndexada::insertar(int etiqueta, int indice){
	if(contador==indice){
		listaInterna.insertar(etiqueta); 
	} else if(indice!= 0){
		cout<< "caso 2" <<endl;
		listaInterna.modificarEnlaces(etiqueta, indice);
	} else{
		cout<< "caso 0 " << endl;
		listaInterna.insertarAlPrincipio(etiqueta);
	}
	contador++;
}

void ListaIndexada::modificar(int valorNuevo, int indice){
	Celda<int>* actual = this->moverse(indice); 
	actual->setEtiqueta(valorNuevo);
}

Celda<int>* ListaIndexada::moverse(int indice){
	Celda<int>* actual = listaInterna.getPrimera();
	for(int i=0; i<indice; ++i){
		actual = actual->getSiguiente();
	}
	return actual;
}

int ListaIndexada::numElem(){
	return contador;
}

void ListaIndexada::borrar(int indice){
	Celda<int>* actual = this->moverse(indice); 
	listaInterna.borrar(actual->getEtiqueta());
}

ListaIndexada::~ListaIndexada(){
	
}

void ListaIndexada::imprimir(){
	listaInterna.imprimir();
}