/*

g++ main.cpp Nodo.cpp ArbolLH.cpp -o code.out
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
	/*
	arbol.agregarHijo(*(arbol.getLP()->getPrimera()->getSiguiente()->getSiguiente()->getEtiqueta()), 5);
	arbol.agregarHijo(*(arbol.getLP()->getPrimera()->getSiguiente()->getSiguiente()), 6);
	
	*/
}