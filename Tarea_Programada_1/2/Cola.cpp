#include "Cola.h"

Cola::Cola(int maxSize)
{
    size = maxSize;
    arrayCircular = new int[size];
    head = 0
    end = 0;	
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
    if(end!=head-1 && !(end==size-1 && head==0)){
	arrayCircular[end] = newElement;

	if(end==size-1){
		end =0;
	}else{
		++end;
	}
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
	if(end!=head){
		int bufferPop = arrayCircular[head];	// there is no need to "clean" the current value of the poped element
		
		//ifelse to change head value
		
		return bufferPop;
	} else{
		return 0;
	}
}

// TODO: COMPLETAR
int Cola::NumElem()
{
}
