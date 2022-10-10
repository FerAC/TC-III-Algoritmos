#include "ArbolLH.h"
#include <iostream>
using namespace std;

ArbolLH::ArbolLH(){
	
}

ArbolLH::~ArbolLH(){
	
}

void ArbolLH::ponerRaiz(Nodo*){
	
	Lista<Nodo* , int> * listaHijos = new Lista(); 
	
	listaPrincipal.insertar(listaHijos);
	
}

/*
	void agregarHijo(Celda*, int);
	void agregarHijoMasDerecho(Celda*, int);
	void borrarHoja(Celda*);
	Celda* raiz();
	Celda* padre(Celda*);
	Celda* hijoMasIzquierdo(Celda*);
	Celda* hermanoDerecho(Celda*);
	Celda* etiqueta(Celda*);
	void modificaEtiqueta(Celda*, int);
	int numNodos(Celda*);
	*/
	
	// RECORDAR CREAR UN CONTENEDOR QUE GUARDE LAS DOS COSAS, LA LISTA DE HIJOS Y EL ELEMENTO, ALIMENTARLO A LA LISTA EN VEZ DE HACER UN EMPLANTILLADO CON DOS PARAMS 