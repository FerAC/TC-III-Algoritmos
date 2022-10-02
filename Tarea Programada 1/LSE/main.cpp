#include"Lista.h"
#include "Celda.h"
#include<fstream>
#include<iostream>
using namespace std;

int main(){
   Lista lista;
   for(int i=0; i<15; ++i){
	   lista.insertar(i);
   }
   lista.imprimir();
   cout<< "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"<< endl;
   for(int i=0; i<15; ++i){
	   if(i%2){
		   lista.borrar(i);
	   }
   }
   lista. borrar(0);
   lista.imprimir();
   cout <<"Hola" <<endl;
	Celda *d = lista.buscar(66); 
	cout<< "X" <<endl;
	//cout<< "Soy d " << d->getEtiqueta() << endl;
	return 0;
}