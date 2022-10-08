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
        
    if(end!=head-1 && !(end==size-1 && head==0)){
	/*if(end == size-1){
		end = 0;
	} else {
		++end;
	}*/
	/*
	if(head==size-1){
		head = 0;	
	}else{
		++head;
	}*/
	arrayCircular[end] = newElement;

	if(end==size-1){
		end =0;
	}else{
		++end;
	}
    }else{
	// cannot insert element, queue already full
    }


    /*
    if(end<size){
        ++end;
    } else{
        end = 0;
    }

    if(end!=start){
        arrayCircular[end] = newElement;
    } else{
        // array already full, cannot add any more elements
    }*/
}

// TODO: COMPLETAR
int Cola::Desencolar()
{
}

// TODO: COMPLETAR
int Cola::NumElem()
{
}
