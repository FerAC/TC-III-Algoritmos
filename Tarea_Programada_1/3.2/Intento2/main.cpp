/*

g++ main.cpp Nodo.cpp ArbolLH.cpp -o code.out
g++ main.cpp Nodo.cpp ArbolLH.cpp -o code.out -g
g++ main.cpp Nodo.cpp ArbolLH.cpp -o code.out -fsanitize=leak
g++ main.cpp Nodo.cpp ArbolLH.cpp -o code.out -fsanitize=undefined

*/

#include "ArbolLH.h"

int main(){
	std::cout<< "Hola Mundo!" << std::endl;
	
	ArbolLH arbol;
	Nodo * nodo = new Nodo(1); 
	arbol.ponerRaiz(nodo);
	//arbol.imprimir();
	
	std::cout<< "**********************MAIN********************" << std::endl;
	std::cout<< "**********************INSERTO 2********************" << std::endl;
	arbol.agregarHijo(*nodo, 2);
	std::cout<< "**********************MAIN********************" << std::endl;
	arbol.agregarHijo(*nodo, 3);
	std::cout<< "**********************MAIN********************" << std::endl;
	
	
	arbol.agregarHijo(*(arbol.getLP()->getPrimera()->getSiguiente()->getSiguiente()->getEtiqueta()), 4);
	arbol.agregarHijo(*(arbol.getLP()->getPrimera()->getSiguiente()->getSiguiente()->getEtiqueta()), 5);
	arbol.agregarHijo(*(arbol.getLP()->getPrimera()->getSiguiente()->getSiguiente()->getEtiqueta()), 6);
	
	std::cout<< "////////////////////LISTA PRINCIPAL////////////////" << std::endl;
	arbol.imprimirLP();
	
	std::cout<< "////////////////////LISTA COMPLETA////////////////////////////////" << std::endl;
	arbol.imprimir();
	
	std::cout<< "Padre de " << arbol.getLP()->getPrimera()->getSiguiente()->getSiguiente()->getEtiqueta()->getEtiqueta() << ": " ;
	Nodo * nodoP = arbol.padre(arbol.getLP()->getPrimera()->getSiguiente()->getSiguiente()->getEtiqueta());
	if(nodoP!=nullptr){
		//std::cout<< "Existe nodoP " << std::endl;
	} else{
		std::cout<< "NO existe nodoP " << std::endl;
	}
	std::cout<< nodoP->getEtiqueta() << std::endl; 
	std::cout<< "Num Nodos " << arbol.numNodos() << std::endl;
	
	Nodo * hermano = arbol.hermanoDerecho(arbol.getLP()->buscar(6));
	Celda<Nodo> * a = arbol.getLP()->buscar(6);
	
	std::cout<< "El hermano der de "<<  a->getEtiqueta()->getEtiqueta() <<" es : ";
	if(hermano!=nullptr){
		std::cout<< hermano->getEtiqueta() << std::endl;
	}
	//std::cout<< "x" << std::endl;
	/*
	arbol.agregarHijo(*(arbol.getLP()->getPrimera()->getSiguiente()->getSiguiente()->getEtiqueta()), 5);
	arbol.agregarHijo(*(arbol.getLP()->getPrimera()->getSiguiente()->getSiguiente()), 6);
	
	*/
	return 0;
}