// COMANDOS PARA PROBAR SANITIZERS:
// CON (GCC/G++ EN WSL O LINUX)
// asan: g++ *.cpp -g -fsanitize=address -o test
// ubsan: g++ *.cpp -g -fsanitize=undefined -o test
// leaksan: g++ *.cpp -g -fsanitize=leak -o tes
// CON CLANG/CLANG++
// msan: clang++ *.cpp -g -fsanitize=memory -o test

#include <iostream>
#include "ListaIndexada.h"

// TODO: PASAR PRUEBAS DEL TEST
bool test_basico() {
	// Parámetros del experimento
	size_t cantidadElementos = 15;
	int eImposible = cantidadElementos + 1;
	int eInsertadoPrimero = cantidadElementos + 2;
	int eInsertadoSegundo = cantidadElementos + 3;

	// Lista vacía
	ListaIndexada lista;

	std::cout << "Lista vacia" << std::endl;
	lista.imprimir();

	// Lista rellenada
	for(int i=0; i < cantidadElementos; ++i) lista.insertar(i,i);

	std::cout << "Lista rellenada del 0 al 14" << std::endl;
	lista.imprimir();

	// Cantidad de elementos
	std::cout << "Cantidad de elementos esperados" << std::endl;
	std::cout << cantidadElementos << std::endl;

	std::cout << "Cantidad de elementos obtenida" << std::endl;
	std::cout << lista.numElem() << std::endl;

	// // Borrado de lista
	lista.borrar(0);

	std::cout << "Lista tras borrar elemento con valor 0" << std::endl;
	lista.imprimir();

	lista.borrar(eImposible);
	std::cout << "Lista tras borrar elemento con valor " << eImposible << std::endl;
	lista.imprimir();

	// Cantidad de elementos tras borrados
	std::cout << "Cantidad de elementos esperados" << std::endl;
	std::cout << cantidadElementos - 1 << std::endl;

	std::cout << "Cantidad de elementos obtenida" << std::endl;
	std::cout << lista.numElem() << std::endl;

	// Inserción al principio
	lista.insertar(eInsertadoPrimero, 0); 

	std::cout << "Lista tras insertar en indice 0" << std::endl;
	lista.imprimir();

	lista.insertar(eInsertadoSegundo, 1);

	std::cout << "Lista tras insertar en indice 1" << std::endl;
	lista.imprimir();

	return true;
}

int main() {
	test_basico(); return 0;

	// TODO: MODULARIZAR PRUEBAS PARA EVITAR REESCRIBIR CODIGO
	// ListaIndexada lista;
	
	// for(int i=0; i<15; ++i){
	// 	lista.insertar(i,i);
	// }
	
	// lista.imprimir();
	// std::cout<< "Listo" <<std::endl;
	
	// lista.insertar(3, 66);
	// lista.imprimir();
	// std::cout<< "Noice" <<std::endl;
	// int a = lista.recuperar(8); 
	// lista.insertar(33,0);
	// lista.imprimir();
	// std::cout<< "soy a " << a << std::endl;
	// return 0;
}