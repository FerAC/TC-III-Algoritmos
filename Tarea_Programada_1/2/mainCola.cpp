// TODO: MOVER A OTRA CARPETA
// asan: g++ mainCola.cpp Cola.cpp -g -fsanitize=address -o code0.out
// ubsan: g++ mainCola.cpp Cola.cpp -g -fsanitize=undefined -o code1.out
// leaksan: g++ mainCola.cpp Cola.cpp -g -fsanitize=leak -o code2.out
#include <iostream>
#include "Cola.h"

int main()
{
	int colaSize = 10;
	Cola cola(colaSize);

	cola.Encolar(0);
	cola.Encolar(1);
	//cola.Encolar(1);
	cola.Encolar(2);
	cola.Encolar(3);
	cola.Encolar(4);
	cola.Encolar(5);
	cola.Encolar(6);
	cola.Encolar(7);
	// cola.Encolar(7);
	cola.Encolar(8);

	cola.Desencolar();
	cola.Desencolar();
	cola.Encolar(9);
	cola.Encolar(10);
	cola.Encolar(11);
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
