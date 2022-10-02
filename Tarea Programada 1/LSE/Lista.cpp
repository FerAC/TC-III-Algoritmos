#include "Lista.h"
#include "Celda.h"
#include <iostream>
using namespace std; 

Lista::Lista(){
	primera = 0;
	ultima = 0;
	contador = 0;
}

void Lista::insertar(int valor){
	Celda * celdaNueva =  new Celda (valor);
	if(!primera){
		primera = celdaNueva;
		ultima = celdaNueva;
	} else{
		ultima->setSiguiente(celdaNueva);
		ultima = celdaNueva; 
	}
	++contador; 
}

void Lista::borrar(int elemento){
	int i=0;
	//Veo que no sea el primera
	Celda * temp = primera;
	if(elemento == primera->getEtiqueta()){
		Celda * p = (primera->getSiguiente()); 
		Celda ** siguiente = &p;
		delete primera;
		primera = *siguiente; 
		--contador;
	} else{
		int borrado=0;
		while(i< contador && !borrado){
			 if(temp->getSiguiente()->getEtiqueta() == elemento){
				if(temp->getSiguiente() == ultima){ //O sea, el siguiente es el ultima
					cout<< "Entre" << endl;
					ultima = temp;
					delete temp->getSiguiente();
					ultima->setSiguiente(0);
					borrado = 1; 
					--contador;
				} else{
					Celda *p = (temp->getSiguiente()->getSiguiente());
					Celda ** siguiente = &p;
					delete temp->getSiguiente(); 
					temp->setSiguiente(*siguiente); 
					borrado = 1; 
					--contador;
				} 
			 }else{
				temp = temp->getSiguiente(); 
				++i;
			}
		
		}
	}
}
		
Celda * Lista::buscar(int elemento){
	int encontrado = 0;
	int i = 0;
	cout<< "LLegue 65 " << endl;
	Celda * temp = new Celda();
	temp = primera; 
	cout<< "68 " << endl;
	cout<< "Soy contador " << contador << endl;
	while(i<contador && !encontrado){
		//cout<< "entre " << endl;
		if(temp->getEtiqueta() == elemento){
			encontrado = 1;
		} else if(i+1< contador) {
			cout<< "avanzo " << i << endl;
			temp = temp->getSiguiente();
		}
		++i;
	}
	
	if(!encontrado){
		cout<< "Voy a borrar" <<endl;
		delete temp;
		cout<< "Borre " << endl;
		return 0;
	} else{
		return temp; 
	}
}

Lista::~Lista(){
	Celda ** temp = &primera;
	Celda * tempSiguiente;
	for(int i=0; i<contador; ++i){
		if((**temp).getSiguiente()){
			tempSiguiente = (**temp).getSiguiente();
		}
		delete *temp;
		if(i+1 < contador){
			*temp = tempSiguiente; 
		}
	}
	
}

void Lista::imprimir(){
	if(primera){
		primera->imprimir();
	}
}
