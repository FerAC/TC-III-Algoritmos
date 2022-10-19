#ifndef ARBOL_1_HPP
#define ARBOL_1_HPP

// #include <iostream>

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

    /**
     * @brief operator == es la sobrecarga del operador basico == ese metodo permite comparar un Nodo a un entero
     * @param comparador comparador es el unico parametro del metodo, es el elemento al cual se compara el Nodo
     * @return El metodo devuelve un booleano, dependiendo si el Nodo es nulo o no
     * @remark El metodo requiere que el Nodo este inicializado
     */
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
     * @brief El metodo ArbolSenaladores el metodo constructor de la clase ArbolSenaladores
     * @param cantidad cantidad es el unico parametro de la función ArbolSenaladores, representa la cantidad maxima de elementos en el arbol
     * @remark el metodo requiere que cantidad sea un tamaño de array valido
     */
    ArbolSenalador(int const cantidad)
    {
        arregloArbol = new Nodo[cantidad];
        maximo = cantidad;
        actual = 0;
        esVacio = 0;
    }

    /**
     * @brief ~ArbolSenalador es el metodo destructor de la clase ArbolSenalador
     * @remark El metodo requiere que el Arbol sea inicializado
     */
    ~ArbolSenalador()
    {
        delete[] arregloArbol;
    }

    /**
     * @brief PonerRaiz es un metodo que permite cambiar el valor actual de la raiz del arbol
     * @param raiz raiz es el nuevo valor de la raiz
     * @remark el metodo requiere que el arbol este inicializado y la el valor de la raiz valida
     */
    void PonerRaiz(int raiz)
    {
        arregloArbol[0].setValor(raiz);
        arregloArbol[0].setIndice(0);
        if (esVacio == 0)
        {
            esVacio = 1;
            ++actual;
        }
    }

    /**
     * @brief AgregarHijo permite agregar un elemento al arbol, y por lo tanto un hijo al Nodo dado
     * @param padre padre es de tipo Nodo, es el Nodo al cual se agrega un hijo
     * @param valorHijo valorHijo es el valor del nuevo Nodo agregado al arbol
     * @remark El metodo necesita que el arbol sea inicializado, que tengo por lo menos una raiz incializada, y que el Nodo padre exista en el arbol
     */
    void AgregarHijo(int valorHijo, Nodo padre)
    {
        // int indice = 0;

        // while (arregloArbol[indice].getValor() != padre.getValor())
        //{
        //   ++indice;
        //}

        if (actual < maximo)
        {
            arregloArbol[actual].setValor(valorHijo);
            // arregloArbol[actual].setPadre(indice);
            arregloArbol[actual].setPadre(padre.getIndice());
            arregloArbol[actual].setIndice(actual);
            ++actual;
        }
    }

    /**
     * @brief AgregarHijoMasDerecho permite agregar un nuevo elemento al Arbol, por medio de un hijo al Nodo dado, se agrega el hijo en la posicion mas derecha en comparacion a sus hermanos
     * @param padre padre es de tipo Nodo, es el Nodo al cual se agrega un hijo
     * @param valorHijo valorHijo es el valor del nuevo Nodo agregado al arbol
     * @remark El metodo necesita que el arbol sea inicializado, que tenga por lo menos una raiz incializada, y que el Nodo padre exista en el arbol
     */
    void AgregarHijoMasDerecho(int valorHijo, Nodo padre) // agrega al padre un hijo
    {
        // int indice = 0;

        // while (arregloArbol[indice].getValor() != padre.getValor())
        //{
        //     ++indice;
        // }

        if (actual < maximo)
        {
            arregloArbol[actual].setValor(valorHijo);
            // arregloArbol[actual].setPadre(indice);
            arregloArbol[actual].setPadre(padre.getIndice());
            arregloArbol[actual].setIndice(actual);
            ++actual;
        }
    }

    /**
     * @brief Raiz permite acceder a la Raiz del arbol, no recibe parametros
     * @return El metodo Raiz devuelve el Nodo raiz del arbol
     * @remark El metodo requiere que sea incializado, y que tenga una raiz con valores inicializada
     */
    Nodo Raiz()
    {
        return arregloArbol[0];
    }

    /**
     * @brief El metodo Padre permite encontrar el Padre de un nodo dado que pertenece al arbol
     * @param hijo hijo es de tipo Nodo, es el Nodo del cual se quiere encontrar el padre
     * @return El metodo devuelve un Nodo, el nodo del arbol que tiene como hijo el nodo Nodo hijo
     * @remark El metodo requiere que el arbol este inicializado, el nodo dado por parametro exista en el arbol, sea inicializado y no sea la raiz del arbol
     */
    Nodo Padre(Nodo hijo)
    {
        return arregloArbol[hijo.getIndicePadre()];
    }

    /**
     * @brief El metodo HijoMasIzquierdo permite encontrar el Hijo mas a la izquierda de un Nodo dado
     * @param padre padre es el unico parametro del metodo, es de tipo Nodo, es el nodo del cual hay que encontrar el hijo mas izquierdo, si no existe entonces significa que es una hoja
     * @return El metodo devuelve un puntero hacia el nodo hijo, o un nullptr en el caso que no tenga hijos
     * @remark El metodo requiere que el arbol este inicializado, y que el Nodo padre dado exista en el arbol
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
            return nullptr;
        }
    }

    /**
     * @brief El metodo HermanoDerecho permite encontrar el nodo mas cercano a la derecha del nodo dado que tengo el mismo padre, si no existe entonces significa que el nodo dado ya es el nodo mas a la derecha
     * @param hermano hermano es el unico parametro del metodo, es el nodo del cual tenemos que buscar el hermano derecho
     * @return El metodo devuelve un puntero hacia el hermano derecho, o un nullptr en el caso que no tengo hermano derecho
     * @remark El metodo requiere que el arbol este inicializado, que el Nodo hermano exista en el arbol, y que no sea la raiz
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
            return nullptr;
        }
    }

    /**
     * @brief BorrarHoja es un metodo del arbol que permite eliminar una hoja del arbol
     * @param nodoBorrado bodoBorrado es el unico parametro del metodo, es el metodo del arbol que se quiere borrar
     * @remark El metodo occupa que el arbol sea inicializado y el Nodo nodoBorrado exista en el arbol y sea una hoja
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
     * @brief Etiqueta es un metodo del arbol que devuelve la etiqueta, en ese caso un entero, de un Nodo dado
     * @param nodo nodo es de tipo Nodo, es el Nodo del cual queremos extraer le etiqueta
     * @remark El metodo requiere que el arbol sea inicializado, y que el Nodo nodo exista en el arbol
     */
    int Etiqueta(Nodo nodo)
    {
        return nodo.getValor();
    }

    /**
     * @brief ModificarEtiqueta permite modificar el valor (etiqueta) de un nodo dado
     * @param nodo nodo es de tipo Nodo, es el Nodo del cual queremos cambiar la etiqueta
     * @param nuevoValor nuevoValor es un entero, una etiqueta, es el nuevo valor de la etiqueta del Nodo nodo
     * @remark El metodo requiere que el arbol sea inicializado, y que el Nodo nodo existe en el arbol
     */
    void ModificaEtiqueta(Nodo nodo, int nuevoValor)
    {
        int indice = 0;
        while (arregloArbol[indice].getValor() != nodo.getValor())
        {
            ++indice;
        }
        arregloArbol[indice].setValor(nuevoValor);
    }

    /**
     * @brief NumNodos permite al usuario conocer la cantidad actual de elementos en el arbol
     * @return El metodo devuelve el parametro "actual" que representa la cantidad actual de elementos en el arbol
     * @remark El metodo requiere que el arbol este inicializado
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
};

#endif