#include "Cola.h"

/**
 * @brief Cola es el metodo constructor de la clase Cola
 * @param maxSize maxSize es de tipo size_t, es el unico parametro del constructor, es el valor "M", el tamaño maximo al cual puede llegar la cola
*/
Cola::Cola(std::size_t maxSize)
{
	size = maxSize;
	arrayCircular = new Cola::elemento[size + 1];
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
void Cola::Encolar(Cola::elemento newElement)
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
}

/**
 * @brief El metodo Desencolar permite hacer un pop a la cola, quita el elemento del inicio de la cola
 * @return El metodo devuelve un int que contiene el valor eliminado de la cola
 * @remarks Solo se puede desencolar de una cola inicializada no vacia
 */
Cola::elemento Cola::Desencolar()
{

	Cola::elemento bufferPop = arrayCircular[head]; // there is no need to clean the current value of the poped element

	if (isEmpty == 0 && head == end)	// en el caso que se retira el ultimo elemento de la cola
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

/**
 * @brief vaciar vacia el contenido de la Cola, para isEmpty a 1 y re-inicializa los valores de head y end
 */
void Cola::vaciar(){
	isEmpty = true;
	head = 0;
	end = 0;
}

/**
 * @brief vacia permite saber si la Cola esta vacia o no
 * @return	vacia devuelve un booleano, devuelve 1 si la Cola esta vacia, sino devuelve un 0
*/
bool Cola::vacia(){
	return this->NumElem()?0:1;
}