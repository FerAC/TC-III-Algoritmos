#include "Cola.h"

Cola::Cola(int maxSize)
{
    size = maxSize;
    arrayCircular = new int[size];
    end = 0;
    start = 0;
}

Cola::~Cola()
{
    delete arrayCircular;
}

void Cola::Encolar(int newElement)
{ 
    if(end<size){
        ++end;
    } else{
        end = 0;
    }

    if(end!=start){
        arrayCircular[end] = newElement;
    } else{
        // array already full, cannot add any more elements
    }
}

int Cola::Desencolar()
{
}

int Cola::NumElem()
{
}