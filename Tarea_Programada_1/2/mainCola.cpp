// TODO: MOVER A OTRA CARPETA
#include <iostream>
#include "Cola.h"

int main(){
	int colaSize = 10;
     	Cola cola(colaSize);

     	//cola.Encolar(0);
	cola.Encolar(1);
	cola.Encolar(2);	

	int quantityElement = cola.NumElem();
	std::cout << "Inicial quantity of elements in the queue: " << cola.NumElem() << std::endl;

	int counter = 0;
	while(counter<quantityElement){
		// pop and print element
		std::cout << cola.Desencolar() << std::endl;
		++counter;
	}


    	 return 0;
}
