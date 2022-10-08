// TODO: MOVER A OTRA CARPETA
#include <iostream>
#include "Cola.h"

int main()
{
	int colaSize = 10;
	Cola cola(colaSize);

	cola.Encolar(0);
	//cola.Encolar(1);
	//cola.Encolar(2);
	//cola.Encolar(3);
	//cola.Encolar(4);
	//cola.Encolar(5);
	// cola.Encolar(6);
	//cola.Encolar(7);
	//cola.Encolar(7);
	//cola.Encolar(8);

	//cola.Desencolar();
	//cola.Desencolar();
	//cola.Encolar(9);
	// cola.Encolar(10);
	// must try case where queue is full

	int quantityElement = cola.NumElem();
	std::cout << "Inicial quantity of elements in the queue: " << cola.NumElem() << std::endl;

	int counter = 0;
	while (counter < quantityElement)
	{
		// pop and print element
		std::cout << cola.Desencolar() << std::endl;
		++counter;
	}

	return 0;
}
