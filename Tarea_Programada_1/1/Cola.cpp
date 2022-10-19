#include <cstddef>
#include <iostream>

template <class elemento>
class Cola
{
private:
    std::size_t size;
    int cabeza; // first out
    int fin;  // last in
    elemento *arregloCircular;
    bool esVacio;

public:
    /**
     * @brief Cola es el metodo constructor de la clase Cola, inicializa una Cola vacia
     * @param maxSize maxSize es de tipo size_t, es el unico parametro del constructor, es el valor "M", el tamaño maximo al cual puede llegar la cola
     * @remark El metodo requiere un maxSize valido
     */
    Cola(std::size_t maxSize)
    {
        size = maxSize;
        arregloCircular = new elemento[size + 1];
        esVacio = true;
    }

    /**
     * @brief ~Cola es el destructor de la clase Cola, permite destruir la estrucutra de datos y liberar la memoria
     * @remark El metodo requiere que la cola este inicializada
     */
    ~Cola()
    {
        delete[] arregloCircular;
    }

    /**
     * @brief El metodo Encolar permite hacer un push a la cola, agrega un element al final de la cola
     * @param nuevoElemento newElement es el unico parametro del metodo encolar, es el valor que se tiene que agregar a la cola
     * @remarks se requiere que la cola este inicializada y que el nuevoElemento este valido
     */
    void Encolar(elemento nuevoElemento)
    {

        if (esVacio == false) // normal add
        {
            if (this->NumElem() != size)
            {
                if (fin == size - 1)
                {
                    fin = 0;
                }
                else
                {
                    ++fin;
                }
                arregloCircular[fin] = nuevoElemento;
            }
        }
        else // add first elem
        {
            fin = 0;
            cabeza = 0;
            arregloCircular[0] = nuevoElemento;
            esVacio = 0;
        }
    }

    /**
     * @brief El metodo Desencolar permite hacer un pop a la cola, quita el elemento del inicio de la cola
     * @return El metodo devuelve un int que contiene el valor eliminado de la cola
     * @remarks Solo se puede desencolar de una cola inicializada no vacia
     */
    elemento Desencolar()
    {

        elemento bufferPop = arregloCircular[cabeza]; // there is no need to clean the current value of the poped element

        if (esVacio == 0 && cabeza == fin) // en el caso que se retira el ultimo elemento de la cola
        {
            esVacio = 1;
        }
        else
        {
            if (cabeza == size - 1)
            {
                cabeza = 0;
            }
            else
            {
                ++cabeza;
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
        if (esVacio == true)
        {
            return 0;
        }
        else
        {
            if (fin == cabeza)
            {
                return 1;
            }
            else
            {
                if (fin > cabeza)
                {
                    return (fin - cabeza) + 1;
                }
                else
                {
                    return (size - cabeza) + fin + 1;
                }
            }
        }
    }

    /**
     * @brief vaciar vacia el contenido de la Cola, para esVacio a 1 y re-inicializa los valores de cabeza y fin
     * @remark el metodo requiere que la cola este inicializada
     */
    void vaciar()
    {
        esVacio = true;
        cabeza = 0;
        fin = 0;
    }

    /**
     * @brief vacia permite saber si la Cola esta vacia o no
     * @return	vacia devuelve un booleano, devuelve 1 si la Cola esta vacia, sino devuelve un 0
     * @remark el metodo requiere que la cola este inicializada
     */
    bool vacia()
    {
        return this->NumElem() ? 0 : 1;
    }
};

int main()
{
    std::size_t colaMax = 10;
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

    Cola<char> cola(colaMax);
    cola.Encolar('A');
    cola.Encolar('B');
    cola.Encolar('C');
    cola.Encolar('D');

    int cantidadElementos = cola.NumElem();
    std::cout << "Inicial quantity of elements in the queue: " << cola.NumElem() << std::endl;

    int contador = 0;
    while (contador < cantidadElementos)
    {
        // pop and print element
        std::cout << cola.Desencolar() << std::endl;
        ++contador;
    }

    return 0;
}