#include <cstddef>
#include <iostream>

template <class elemento>
class Cola
{
private:
    std::size_t size;
    int head; // first out
    int end;  // last in
    elemento *arrayCircular;
    bool isEmpty;

public:
    /**
     * @brief Cola es el metodo constructor de la clase Cola
     * @param maxSize maxSize es de tipo size_t, es el unico parametro del constructor, es el valor "M", el tamaño maximo al cual puede llegar la cola
     */
    Cola(std::size_t maxSize)
    {
        size = maxSize;
        arrayCircular = new elemento[size + 1];
        isEmpty = true;
    }

    /**
     * @brief ~Cola es el destructor de la clase Cola, permite destruir la estrucutra de datos y liberar la memoria
     */
    ~Cola()
    {
        delete[] arrayCircular;
    }

    /**
     * @brief El metodo Encolar permite hacer un push a la cola, agrega un element al final de la cola
     * @param newElement newElement es el unico parametro del metodo encolar, es el valor que se tiene que agregar a la cola
     * @remarks se requiere que la cola este inicializada
     */
    void Encolar(elemento newElement)
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
    elemento Desencolar()
    {

        elemento bufferPop = arrayCircular[head]; // there is no need to clean the current value of the poped element

        if (isEmpty == 0 && head == end) // en el caso que se retira el ultimo elemento de la cola
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
    int NumElem()
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
    void vaciar()
    {
        isEmpty = true;
        head = 0;
        end = 0;
    }

    /**
     * @brief vacia permite saber si la Cola esta vacia o no
     * @return	vacia devuelve un booleano, devuelve 1 si la Cola esta vacia, sino devuelve un 0
     */
    bool vacia()
    {
        return this->NumElem() ? 0 : 1;
    }
};

int main()
{
    std::size_t colaSize = 10;
    /*
        Cola<int> cola(colaSize);
        cola.Encolar(0);
        cola.Encolar(1);
        cola.Desencolar();
        cola.Desencolar();
        cola.Encolar(0);
        cola.Encolar(1);
        cola.Encolar(2);
        cola.Encolar(3);
        cola.Encolar(4);
        cola.Encolar(5);
        cola.Encolar(6);
        cola.Encolar(7);
        cola.Encolar(7);
        cola.Encolar(8);
        */

    Cola<char> cola(colaSize);
    cola.Encolar('A');
    cola.Encolar('B');
    cola.Encolar('C');
    cola.Encolar('D');

    int quantityElement = cola.NumElem();
    std::cout << "Inicial quantity of elements in the queue: " << cola.NumElem() << std::endl;

    int counter = 0;
    while (counter < quantityElement)
    {
        // pop and print element
        std::cout << cola.Desencolar() << std::endl;
        ++counter;
    }

    return 0;
}