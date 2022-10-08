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
 * @brief El metodo Encolar permite hacer un push a la cola, agrega un element al final de la pila
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

// TODO: COMPLETAR
int Cola::Desencolar()
{
}

// TODO: COMPLETAR
int Cola::NumElem()
{
}
