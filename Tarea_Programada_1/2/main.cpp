#include <iostream>
#include "ListaIndexada.h"
int main(){
	ListaIndexada lista;
	
	for(int i=0; i<15; ++i){
		lista.insertar(i,i);
	}
	
	lista.imprimir();
	std::cout<< "Listo" <<std::endl;
	
	lista.insertar(3, 66);
	lista.imprimir();
	std::cout<< "Noice" <<std::endl;
	int a = lista.recuperar(8); 
	lista.insertar(33,0);
	lista.imprimir();
	std::cout<< "soy a " << a << std::endl;
	return 0;
}