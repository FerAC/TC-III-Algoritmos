#include "Cola.h"

/**
 * @brief Cola es el metodo constructor de la clase Cola
 * @param maxSize maxSize esel unico parametro del constructor, es el valor "M", el tamaño maximo al cual puede llegar la cola
*/
Cola::Cola(int maxSize)
{
	size = maxSize;
	arrayCircular = new int[size + 1];
	// head = 0;
	// end = size - 1;
	isEmpty = true;
}

/**
 * @brief ~Cola es el destructor de la clase Cola, permite destruir la estrucutra de datos y liberar la memoria
*/
Cola::~Cola()
{
	delete[] arrayCircular;
}

/**
 * @brief El metodo Encolar permite hacer un push a la cola, agrega un element al final de la cola
 * @param newElement newElement es el unico parametro del metodo encolar, es el valor que se tiene que agregar a la cola
 * @remarks se requiere que la cola este inicializada
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
 * @remarks Solo se puede desencolar de una cola inicializada no vacia
 */
int Cola::Desencolar()
{

	int bufferPop = arrayCircular[head]; // there is no need to clean the current value of the poped element

	if (isEmpty == 0 && head == end)
	{
		isEmpty = 1;
	}
	else
	{
		if (head == size - 1)
		{
			head = 0;
		}
		else
		{
			++head;
		}
	}
	//++head;
	return bufferPop;
}

/**
 * @brief El metodo NumElem devuelve la cantidad de elemento en el array circular
 * @return El metodo devuelve un entero que contiene la cantidad de elementos en la cola
 * @remarks el metodo requiere tener una cola inicializada, que sea vacia o no
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
				return (size - head) + end + 1;
			}
		}
	}
}
