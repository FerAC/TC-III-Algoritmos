#include "Cola.h"

Cola::Cola(int maxSize)
{
    size = maxSize;
    arrayCircular = new int[size];
    head = 0;
    end = size-1;	
}

Cola::~Cola()
{
    delete arrayCircular;
}

/**
 * @brief El metodo Encolar permite hacer un push a la cola, agrega un element al final de la cola
 */
void Cola::Encolar(int newElement)
{ 
    // check if the queue is not full
    if(this->NumElem() != size){ 

	if(end==size-1){
		end =0;
	}else{
		++end;
	}

	arrayCircular[end] = newElement;
    }else{
	// cannot insert element, queue already full
    }
}

/**
 * @brief El metodo Desencolar permite hacer un pop a la cola, quita el elemento del inicio de la cola
 * @return El metodo devuelve un int que contiene el valor eliminado de la cola
 */
int Cola::Desencolar()
{
		int bufferPop = arrayCircular[head]; // there is no need to clean the current value of the poped element
		
		if(head==size-1){
			head = 0;
		}else{
			++head;
		}
		return bufferPop;
}

/*
 * @brief El metodo NumElem devuelve la cantidad de elemento en el array circular
 */
int Cola::NumElem()
{	
	if(head==end){
		return 0;
	}
	if(end>head){
		return (end-head); 
	} else{
		return (size-(size-head)+end);
	}
	// if end es mayor a head, entonces end-head elementos
	// else es size-(size-head) + end 
}
