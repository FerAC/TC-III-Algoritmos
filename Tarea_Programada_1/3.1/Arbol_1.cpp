#include <iostream>

class Nodo
{
    friend class ArbolSenalador;

private:
    int indicePadre;
    int valor;
    int indice;

    /**
     * @brief el metodo setIndice permite cambiar el indice del Nodo
     * @param nuevoIndice nuevoIndice es el unico parametro del metodo setIndice, es un entero, es el nuevo valor del indice
     * @remark el metodo requiere que el Nodo sea inicializado y que el nuevoIndice sea un indice valido
     */
    void setIndice(int nuevoIndice)
    {
        indice = nuevoIndice;
    }

    /**
     * @brief getIndice es un metodo que permite recuperar el indice del Nodo
     * @return El metodo devuelve un entero, el indice del nodo
     * @remark El metodo requiere que el Nodo sea inicializado y indice tenga un valor
     */
    int getIndice()
    {
        return indice;
    }

    /**
     * @brief el metodo setValor permite cambiar el valor del Nodo
     * @param nuevoValor nuevoValor es el unico parametro del metodo setValor, es un entero
     * @remark el metodo requiere que el Nodo sea inicializado
     */
    void setValor(int nuevoValor)
    {
        valor = nuevoValor;
    }

    /**
     * @brief getValor es un metodo que permite recuperar el valor del Nodo
     * @return El metodo devuelve un entero, el valor del nodo
     * @remark El metodo requiere que el Nodo sea inicializado y valor tenga un valor
     */
    int getValor()
    {
        return valor;
    }

    /**
     * @brief el metodo setPadre permite cambiar el indicePadre del Nodo
     * @param nuevoValor nuevoIndice es el unico parametro del metodo setPadre, es un entero
     * @remark el metodo requiere que el Nodo sea inicializado
     */
    void setPadre(int nuevoIndice)
    {
        indicePadre = nuevoIndice;
    }

    /**
     * @brief getIndicePadre es un metodo que permite recuperar el indicePadre del Nodo
     * @return El metodo devuelve un entero, el indicePadre del nodo
     * @remark El metodo requiere que el Nodo sea inicializado y indicePadre tenga un valor
     */
    int getIndicePadre()
    {
        return indicePadre;
    }

public:
    /**
     * @brief Nodo es el metodo constructor de Nodo, permite inicializar un Nodo recibiendo un Padre y un valor
     * @param padre padre es un parametro de tipo Nodo, es el Nodo al cual el Nodo "apunta" por medio del indicePadre
     * @param elValor elValor es un parametro de tipo entero, es el valor del Nodo
     * @remark El metodo requiere que ambos el padre y elValor sean validos y inicializados
     */
    Nodo(Nodo padre, int elValor)
    {
        valor = elValor;
        indicePadre = padre.getIndice();
    }

    /**
     * @brief Nodo es el metodo constructor por omision de la clase Nodo, no recibe parametros
     */
    Nodo()
    {
        indicePadre = 0;
        valor = 0;
        indice = 0;
    }

    /**
     * @brief ~Nodo es el metodo destructor de la clase Nodo, no recibe parametros
     * @remark El metodo ~Nodo requiere que el Nodo esta inicializado
     */
    ~Nodo() {}

    bool operator==(const int comparador)
    {
        if (comparador == 0 && indice == 0 && valor == 0 && indicePadre == 0)
        {
            return 1;
        }
        else
        {
            if (comparador == 0)
            {
                return 0;
            }
        }

        if (comparador != 0 && indice != 0 && valor != 0 && indicePadre != 0)
        {
            return 1;
        }
        else
        {
            if (comparador != 0)
            {
                return 0;
            }
        }
        return 0;
    }
};

class ArbolSenalador
{

public:
    /**
     * @brief ArbolSenalador is the constructor method of the class
     * @param quantityElements quantityElements is a const int, it's the max size of the array
     */
    ArbolSenalador(int const cantidad)
    {
        arregloArbol = new Nodo[cantidad];
        maximo = cantidad;
        actual = 0;
        esVacio = 0;
    }

    /**
     * @brief ~ArbolSenalador is the destructor method of the class
     * @remark El metodo requiere que el Arbol
     */
    ~ArbolSenalador()
    {
        delete[] arregloArbol;
    }

    /**
     * @brief PonerRaiz is a function that change the actual value of the root, or add the first value to the tree
     * @param root root is the new value  of the root
     */
    void PonerRaiz(int root)
    {
        arregloArbol[0].setValor(root);
        arregloArbol[0].setIndice(0);
        if (esVacio == 0)
        {
            esVacio = 1;
            ++actual;
        }
    }

    /**
     * @brief AgregarHijo add a new element to the tree
     * @param indexPadre indexPadre is the index of the father of the new node
     * @param hijo hijo is the value of the new element inserted in the tree
     */
    void AgregarHijo(int valorHijo, Nodo padre) // agrega al padre un hijo
    {
        int indice = 0;

        while (arregloArbol[indice].getValor() != padre.getValor())
        {
            ++indice;
        }

        if (actual < maximo)
        {
            arregloArbol[actual].setValor(valorHijo);
            arregloArbol[actual].setPadre(indice);
            arregloArbol[actual].setIndice(actual);
            ++actual;
        }
    }

    /**
     * @brief AgregarHijoMasDerecho add a new element to the tree
     * @param indexPadre indexPadre is the index of the father of the new node
     * @param hijo hijo is the value of the new element inserted in the tree
     */
    void AgregarHijoMasDerecho(int valorHijo, Nodo padre) // agrega al padre un hijo
    {
        int indice = 0;

        while (arregloArbol[indice].getValor() != padre.getValor())
        {
            ++indice;
        }

        if (actual < maximo)
        {
            arregloArbol[actual].setValor(valorHijo);
            arregloArbol[actual].setPadre(indice);
            arregloArbol[actual].setIndice(actual);
            ++actual;
        }
    }

    /**
     * @brief Raiz permite acceder a la Raiz del arbol
     * @return el metodo Raiz devuelve el Nodo raiz del arbol
     */
    Nodo Raiz()
    {
        return arregloArbol[0];
    }

    /**
     * @brief
     * @param
     * @return
     */
    Nodo Padre(Nodo hijo)
    {
        return arregloArbol[hijo.getIndicePadre()];
    }

    /**
     * @brief
     * @param
     * @return
     */
    Nodo *HijoMasIzquierdo(Nodo padre)
    {
        int indice = padre.getIndice() + 1;

        int encontrado = 0;
        while (arregloArbol[indice].getIndicePadre() != padre.getIndice())
        {
            ++indice;
            if (arregloArbol[indice].getIndicePadre() == padre.getIndice())
            {
                encontrado = 1;
            }
        }

        if (arregloArbol[indice].getIndicePadre() == padre.getIndice())
        {
            encontrado = 1;
        }

        if (encontrado == 1) // caso donde el Nodo no es una hoja
        {
            return &arregloArbol[indice];
        }
        else // caso donde el Nodo es una hoja
        {
            // Nodo nodoNulo();
            // return nodoNulo;
            return nullptr;
        }
    }

    /**
     * @brief
     * @param
     * @return
     */
    Nodo *HermanoDerecho(Nodo hermano)
    {
        int indixePadre = hermano.getIndicePadre();
        int indice = 0;

        while (arregloArbol[indice].getValor() != hermano.getValor())
        {
            ++indice;
        }

        ++indice;
        int encontrado = 0;

        while (arregloArbol[indice].getIndicePadre() != hermano.getIndicePadre())
        {
            ++indice;
            if (arregloArbol[indice].getIndicePadre() == hermano.getIndicePadre())
            {
                encontrado = 1;
            }
        }

        if (arregloArbol[indice].getIndicePadre() == hermano.getIndicePadre())
        {
            encontrado = 1;
        }

        if (encontrado == 1) // caso donde el Nodo no es el hermano mas derecho
        {
            return &arregloArbol[indice];
        }
        else // caso donde el Nodo es el hermano mas derecho
        {
            // Nodo nodoNulo;
            // return nodoNulo;
            return nullptr;
        }
    }

    /**
     * @brief
     * @param
     */
    void BorrarHoja(Nodo nodoBorrado)
    {

        // si el elemento borrado es el ultimo
        if (nodoBorrado.getValor() != arregloArbol[actual - 1].getValor())
        {
            int indiceBorrado = 0;
            while (arregloArbol[indiceBorrado].getValor() != nodoBorrado.getValor())
            {
                ++indiceBorrado;
            }

            int indice = indiceBorrado;
            // sizeN-2 es el "nuevo" ultimo elemento del array
            while (indice != actual - 2)
            {
                if (arregloArbol[indice + 1].getIndicePadre() > indiceBorrado)
                {
                    arregloArbol[indice] = arregloArbol[indice + 1];
                    arregloArbol[indice].setPadre(arregloArbol[indice + 1].getIndicePadre() - 1);
                    arregloArbol[indice].setIndice(indice);
                    // hay que decrementarlo de 1
                }
                else
                { // solo hacer shift, no se occupa decrementar el indice del padre
                    arregloArbol[indice] = arregloArbol[indice + 1];
                    arregloArbol[indice].setIndice(indice);
                }
                ++indice;
            }
        }
        --actual;
    }

    /**
     * @brief
     * @param
     */
    int Etiqueta(Nodo nodo)
    {
        return nodo.getValor();
    }

    /**
     * @brief
     * @param
     * @param
     */
    void ModificaEtiqueta(Nodo nodo, int nuevoValor) // change the node with value, to newValue
    {
        int indice = 0;
        while (arregloArbol[indice].getValor() != nodo.getValor())
        {
            ++indice;
        }
        arregloArbol[indice].setValor(nuevoValor);
    }

    /**
     * @brief
     * @return
     */
    int NumNodos()
    {
        return actual;
    }

private:
    Nodo *arregloArbol;
    int maximo;
    int actual;
    int esVacio;
    // Nodo nodoNulo();
};

int main()
{
    ArbolSenalador arbol(10);
    arbol.PonerRaiz(100);
    arbol.AgregarHijo(123, arbol.Raiz());
    arbol.AgregarHijo(22, arbol.Raiz());
    // arbol.AgregarHijoMasDerecho(13, arbol.Raiz());
    arbol.AgregarHijoMasDerecho(1, *arbol.HijoMasIzquierdo(arbol.Raiz()));
    std::cout << arbol.Etiqueta(arbol.Raiz()) << std::endl;
    std::cout << arbol.Etiqueta(*arbol.HijoMasIzquierdo(arbol.Raiz())) << std::endl;
    std::cout << arbol.Etiqueta(*arbol.HermanoDerecho(*arbol.HijoMasIzquierdo(arbol.Raiz()))) << std::endl;

    try
    {
        std::cout << arbol.Etiqueta(*arbol.HijoMasIzquierdo(*arbol.HijoMasIzquierdo(arbol.Raiz()))) << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "nodo vacio" << std::endl;
    }

    //}

    // std::cout << arbol.Etiqueta(*arbol.HijoMasIzquierdo(*arbol.HijoMasIzquierdo(arbol.Raiz()))) << std::endl;
    arbol.BorrarHoja(*arbol.HijoMasIzquierdo(*arbol.HijoMasIzquierdo(arbol.Raiz())));

    return 0;
}