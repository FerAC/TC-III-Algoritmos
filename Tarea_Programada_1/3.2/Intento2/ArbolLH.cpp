#include "ArbolLH.h"

ArbolLH::ArbolLH(){
	listaPrincipal = new Lista<Nodo>;
	
}

ArbolLH::~ArbolLH(){
	delete listaPrincipal;									//listaPrincipal->										//listaPrincipal
} 

void ArbolLH::imprimir(){
	//std::cout<< "Raiz: " << listaPrincipal->getPrimera()->getEtiqueta()->getEtiqueta() << std::endl;
	//Celda<Nodo> * actual = listaPrincipal->getPrimera();
	/*
	while(actual!=nullptr){
		//std::cout<< "ELEMENTO : " << actual->getEtiqueta()->getEtiqueta() << std::endl;
		//std::cout<< "Hijos a";
		//actual->getEtiqueta()->getListaHijos()->imprimir();
		actual = actual->getSiguiente();
		//std::cout<< "ELEMENTO : " << actual->getEtiqueta()->getEtiqueta() << std::endl;
	}
	*/
	listaPrincipal->imprimir();
	
}

void ArbolLH::imprimirLP(){
	Celda<Nodo> * actual = listaPrincipal->getPrimera();
	while(actual!=nullptr){
		std::cout<< "ELEMENTO : " << actual->getEtiqueta()->getEtiqueta() << std::endl;
		//std::cout<< "Hijos a";
		//actual->getEtiqueta()->getListaHijos()->imprimir();
		actual = actual->getSiguiente();
		//std::cout<< "ELEMENTO : " << actual->getEtiqueta()->getEtiqueta() << std::endl;
	}
	
}

void ArbolLH::ponerRaiz(Nodo * nuevoNodo){
	listaPrincipal->insertarAlPrincipio(*nuevoNodo);
}
	
void ArbolLH::agregarHijo(Nodo nodoPadre, int etiqueta){
	Nodo * nodoNuevo = new Nodo(etiqueta); 
	listaPrincipal->insertar(*nodoNuevo);
	nodoPadre.insertarEnLista(nodoNuevo); 
	
	
}

void ArbolLH::agregarHijoMasDerecho(Nodo nodoPadre, int etiqueta){
	agregarHijo(nodoPadre, etiqueta);
}

void ArbolLH::borrarHoja(Nodo* borrado){
	
	
	
}	
Lista<Nodo>* ArbolLH::getLP(){
	return listaPrincipal;
}
Celda<Nodo>* ArbolLH::raiz()
{
	return (listaPrincipal->getPrimera()); 
}
	
Nodo* ArbolLH::padre(Nodo * hijo){
	Nodo * a;
	Celda<Nodo> * actual = listaPrincipal->getPrimera();
	if(actual->getEtiqueta() == hijo){ //Caso trivial, raiz
		return nullptr; 
	} else{
		while(actual!=nullptr){
			Celda<Nodo*>* celdaHijos = actual->getEtiqueta()->getListaHijos()->getPrimera();  //Apunta al primer indice de la lista de hijos si es que existe
			while(celdaHijos!=nullptr){
				if(*(celdaHijos->getEtiqueta()) == hijo){ //Significa que encontre a mi padre
					return actual->getEtiqueta();
				} else{ //Sigo avanzando
					celdaHijos = celdaHijos->getSiguiente();
				}
			}
			actual = actual->getSiguiente(); 	
		}
		return nullptr; //Si sali del while principal significa que no encontre padre
	}
	
}

Celda<Nodo*>* hijoMasIzquierdo(Nodo* padre){
	return padre->getListaHijos()->getPrimera();
}

int  etiqueta(Nodo* nodo){
	return nodo->getEtiqueta();
}

void modificaEtiqueta(Nodo* nodo, int valorNuevo){
	nodo->setEtiqueta(valorNuevo);
}

	/*
	
	Celda<int>* hermanoDerecho(Celda<int>*);
	
	
	int numNodos(Celda<int>*);
	*/
	