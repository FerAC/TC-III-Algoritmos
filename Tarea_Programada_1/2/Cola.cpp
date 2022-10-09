#include "Cola.h"

Cola::Cola(int maxSize)
{
	size = maxSize;
	arrayCircular = new int[size + 1];
	// head = 0;
	// end = size - 1;
	isEmpty = true;
}

Cola::~Cola()
{
	delete[] arrayCircular;
}

/**
 * @brief El metodo Encolar permite hacer un push a la cola, agrega un element al final de la cola
 */
void Cola::Encolar(int newElement)
{

	if (isEmpty == false) // normal add
	{
		if (this->NumElem() != size)
		{
			if (end == size - 1)
			{
				end = 0;
			}
			else
			{
				++end;
			}
			arrayCircular[end] = newElement;
		}
	}
	else // add first elem
	{
		end = 0;
		head = 0;
		arrayCircular[0] = newElement;
		isEmpty = 0;
	}

	// check if the queue is not full
	// if (this->NumElem() != size)
	//{

	//	if (end == size - 1)
	//	{
	//		end = 0;
	//	}
	//	else
	//	{
	//		++end;
	//	}

	//	arrayCircular[end] = newElement;
	//}
	// else
	//{
	// cannot insert element, queue already full
	//}
}

/**
 * @brief El metodo Desencolar permite hacer un pop a la cola, quita el elemento del inicio de la cola
 * @return El metodo devuelve un int que contiene el valor eliminado de la cola
 */
int Cola::Desencolar()
{

	int bufferPop = arrayCircular[head]; // there is no need to clean the current value of the poped element

	if (head == size - 1)
	{
		head = 0;
	}
	else
	{
		++head;
	}
	//++head;
	return bufferPop;
}

/**
 * @brief El metodo NumElem devuelve la cantidad de elemento en el array circular
 */
int Cola::NumElem()
{
	if (isEmpty == true)
	{
		return 0;
	}
	else
	{
		if (end == head)
		{
			return 1;
		}
		else
		{
			if (end > head)
			{
				return (end - head) + 1;
			}
			else
			{
				return (size - head) + end +1;
			}
		}
	}
}
