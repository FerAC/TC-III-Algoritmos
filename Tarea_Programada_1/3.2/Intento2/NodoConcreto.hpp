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
		
/// @brief Constructor por omision de la clase nodo
/// @remarks Requiere que el nodo no este inicializado 
NodoConcreto(){
	
}
/// @brief Destructor por omision de la clase nodo
/// @remarks Requiere que el nodo este inicializada
~NodoConcreto(){
}
/// @brief constructor con parametros de clase nodo
/// @remarks Requiere que el nodo no este inicializada
/// @param int et  
NodoConcreto(int et){
	etiqueta = et;
}
/// @brief inserta en la lista de hijos de un nodo
/// @remarks Requiere que el nodo este inicializado y que tenga una lista de hijos inicializada
/// @param NodoConcreto*  
void insertarEnLista(NodoConcreto* nodoNuevo){
	
	if(listaHijos->getPrimera()!=nullptr){
		
		listaHijos->insertar(nodoNuevo);
		
	} else{
		
		listaHijos->insertarAlPrincipio(nodoNuevo);
		
	}
	
}

/// @brief Retorna la lista de hijos de un nodo
/// @remarks Requiere que el nodo este inicializado y tenga una lista de hijos
/// @return Lista<NodoConcreto*> en caso de no encontralo devuelve un nullptr 
Lista<NodoConcreto*>* getListaHijos(){
	return listaHijos; 
}
/// @brief imprime la etiqueta de un nodo
/// @remarks Requiere que el nodo este inicializado
void imprimirValor(){
	std::cout<< etiqueta << std::endl;
}

/// @brief operador de igualdad de la clase nodo
/// @remarks Requiere que ambos nodos esten inicializados y que posean etiquetas comparables
/// @param NodoConcreto 
/// @return 1 si son iguales, 0 si no
int operator==(NodoConcreto nodo2){
	if(this->etiqueta == nodo2.getEtiqueta()){
		return 1;
	}
	return 0;
}

/// @brief operador de desigualdad de la clase nodo
/// @remarks Requiere que ambos nodos esten inicializados y que posean etiquetas comparables
/// @param NodoConcreto 
/// @return 0 si son iguales, 1 si no
int operator==(NodoConcreto nodo2){
	if(this->etiqueta != nodo2.getEtiqueta()){
		return 1;
	}
	return 0;
}
/// @brief operador de desigualdad de la clase nodo
/// @remarks Requiere que ambos nodos esten inicializados y que posean etiquetas comparables
/// @param NodoConcreto 
/// @return 0 si son iguales, 1 si no
int getEtiqueta(){
	return etiqueta;
}

void setEtiqueta(int valorNuevo){
	this->etiqueta = valorNuevo;
}

ostream& imprimir(ostream& output){
	output<< "Etiqueta : " << etiqueta << std::endl;
	output<< "Mis hijos son : " << std::endl;
	listaHijos->imprimirPunteros();
	return output;
}
		 
	
};
#endif