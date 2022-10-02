#include "Celda.h"
#include <iostream>
using namespace std;

Celda:: Celda(int valor){
	this->etiqueta = valor; 
	this->siguiente = 0;
	
}

Celda::getEtiqueta(){
	return etiqueta;
}

Celda* Celda::getSiguiente(){
	return siguiente; 
}

void Celda::setSiguiente(Celda* nuevaCelda){
	siguiente = nuevaCelda; 
}

int Celda::operator ==(Celda* celda){
	if(etiqueta == celda->etiqueta && celda->siguiente == siguiente){
		return 1;
	} 
	return 0; 
}

Celda::Celda(){
	
	
}

Celda::~Celda(){
	
	
}

void Celda::imprimir(){
	cout<< etiqueta << endl;
	if(siguiente){
		siguiente->imprimir();
	}
}