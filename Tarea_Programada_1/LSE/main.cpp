#include "Lista.h"
#include "Celda.h"
#include <iostream>
#include <string>

using namespace std;

int main() {

   // Creando lista
   Lista<string> lista;
   for (int i=0; i<15; ++i) {
	   lista.insertar(to_string(i));
   }

   // Imprimiendo lista
   lista.imprimir();
   cout<< "###############################################"<< endl;

   // Eliminando impares de la lista
   for(int i=0; i<15; ++i){
	   if(i%2) {
		   lista.borrar(to_string(i));
	   }
   }
   
   // Borrando elemento "0" de la lista
   lista.borrar(string("0"));

   // Borrando elemento inexistente "8918739" de la lista
   lista.borrar(string("8918739"));

   // Imprimiendo lista
   lista.imprimir();
   cout<< "###############################################"<< endl;

   // Buscar elemento existente "8" de la lista
   Celda<string> *a = lista.buscar("8"); 
	cout<< "a = " << a << endl;
   if(a != nullptr) 
      cout << "*a = " << a->getEtiqueta() << endl;

   // Buscando elemento inexistente "66" de la lista
	Celda<string> *b = lista.buscar("66"); 
	cout<< "b = " << b << endl;
   if(b != nullptr) 
      cout << "*b = " << b->getEtiqueta() << endl;
	
	return 0;
}