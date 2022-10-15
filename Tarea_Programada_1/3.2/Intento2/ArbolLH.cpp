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
			Celda<Nodo*> * celdaHijos = actual->getEtiqueta()->getListaHijos()->getPrimera();  //Apunta al primer indice de la lista de hijos si es que existe
			a = *(celdaHijos->getEtiqueta());
			while(a!=nullptr){
				//std::cout<<"ENTRE WHILE 78 ArbolLH / comparando " << a->getEtiqueta()<<  std::endl;
				if(a->getEtiqueta() == hijo->getEtiqueta()){ //Significa que encontre a mi padre
					//std::cout<< "Encontre tata " << std::endl;
					return actual->getEtiqueta();
				} else{ //Sigo avanzando
					celdaHijos = celdaHijos->getSiguiente();
				}
				a = *(celdaHijos->getEtiqueta());
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

Nodo* ArbolLH::hermanoDerecho(Celda<Nodo>* celdaParam){
	int contador = 0;
	Celda<Nodo*> hermanoDerecho; 
	int terminado = 0;
	Nodo * nodoDer = nullptr;
	int i =0;
	for(Celda<Nodo> * buffer = listaPrincipal->getPrimera(); buffer!=nullptr; buffer = buffer->getSiguiente()){ //Busca a celdaParam en la lista de hijos
		std::cout<< i << std::endl;
		int j =0;
		for(Celda<Nodo*> * buffer2 = buffer->getEtiqueta()->getListaHijos()->getPrimera(); buffer2!=nullptr; buffer2 = buffer2->getSiguiente()){
			std::cout<< j++ << std::endl;
			Nodo* a = (buffer2->getEtiqueta(4));
			
			if( a->getEtiqueta() == celdaParam->getEtiqueta()->getEtiqueta()){
				
				if(buffer2->getSiguiente() != nullptr){
					nodoDer = buffer2->getSiguiente()->getEtiqueta(4);
					std::cout<< "Lo encontre " << std::endl;
					return nodoDer;
				} else{
					return nullptr;
				}
			}
		}
	}
}

int ArbolLH::numNodos(){
	//Celda<Nodo> * buffer = listaPrincipal->getPrimera();
	int contador = 0;
	for(Celda<Nodo> * buffer = listaPrincipal->getPrimera(); buffer!=nullptr; buffer = buffer->getSiguiente()){
		++contador;
	}
	return contador;	
}
	