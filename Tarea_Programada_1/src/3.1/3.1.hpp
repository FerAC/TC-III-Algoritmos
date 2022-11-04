#ifndef ARBOL_1_HPP
#define ARBOL_1_HPP

#include <iostream>

class NodoArbol
{
    friend class ArbolSenalador;

private:
    size_t indicePadre;
    int valor;
    size_t indice;
    int esNulo = 0;

    /**
     * @brief el metodo setIndice permite cambiar el indice del NodoArbol
     * @param nuevoIndice nuevoIndice es el unico parametro del metodo setIndice, es un entero, es el nuevo valor del indice
     * @remark el metodo requiere que el NodoArbol sea inicializado y que el nuevoIndice sea un indice valido
     */
    void setIndice(int nuevoIndice)
    {
        indice = nuevoIndice;
    }

    /**
     * @brief getIndice es un metodo que permite recuperar el indice del NodoArbol
     * @return El metodo devuelve un entero, el indice del NodoArbol
     * @remark El metodo requiere que el NodoArbol sea inicializado y indice tenga un valor
     */
    int getIndice() const
    {
        return indice;
    }

    /**
     * @brief el metodo setValor permite cambiar el valor del NodoArbol
     * @param nuevoValor nuevoValor es el unico parametro del metodo setValor, es un entero
     * @remark el metodo requiere que el NodoArbol sea inicializado
     */
    void setValor(int nuevoValor)
    {
        valor = nuevoValor;
    }

    /**
     * @brief getValor es un metodo que permite recuperar el valor del NodoArbol
     * @return El metodo devuelve un entero, el valor del NodoArbol
     * @remark El metodo requiere que el NodoArbol sea inicializado y valor tenga un valor
     */
    int getValor() const
    {
        return valor;
    }

    /**
     * @brief el metodo setPadre permite cambiar el indicePadre del NodoArbol
     * @param nuevoValor nuevoIndice es el unico parametro del metodo setPadre, es un entero
     * @remark el metodo requiere que el NodoArbol sea inicializado
     */
    void setPadre(int nuevoIndice)
    {
        indicePadre = nuevoIndice;
    }

    /**
     * @brief getIndicePadre es un metodo que permite recuperar el indicePadre del NodoArbol
     * @return El metodo devuelve un entero, el indicePadre del NodoArbol
     * @remark El metodo requiere que el NodoArbol sea inicializado y indicePadre tenga un valor
     */
    int getIndicePadre() const
    {
        return indicePadre;
    }

public:
    /**
     * @brief NodoArbol es el metodo constructor de NodoArbol, permite inicializar un NodoArbol recibiendo un Padre y un valor
     * @param padre padre es un parametro de tipo NodoArbol, es el NodoArbol al cual el NodoArbol "apunta" por medio del indicePadre
     * @param elValor elValor es un parametro de tipo entero, es el valor del NodoArbol
     * @remark El metodo requiere que ambos el padre y elValor sean validos y inicializados
     */
    NodoArbol(NodoArbol padre, int elValor)
    {
        valor = elValor;
        indicePadre = padre.getIndice();
    }

    /**
     * @brief NodoArbol es el metodo constructor por omision de la clase NodoArbol, no recibe parametros
     */
    NodoArbol()
    {
        indicePadre = 0;
        valor = 0;
        indice = 0;
        esNulo = 1;
    }

    /**
     * @brief ~NodoArbol es el metodo destructor de la clase NodoArbol, no recibe parametros
     * @remark El metodo ~NodoArbol requiere que el NodoArbol esta inicializado
     */
    ~NodoArbol() {}

    /**
     * @brief operator == es la sobrecarga del operador basico == ese metodo permite comparar un NodoArbol a un entero
     * @param comparador comparador es el unico parametro del metodo, es el elemento al cual se compara el NodoArbol
     * @return El metodo devuelve un booleano, dependiendo si el NodoArbol es nulo o no
     * @remark El metodo requiere que el NodoArbol este inicializado
     */
    bool operator==(const int &comparador) const
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

    /**
     * @brief operator != es la sobrecarga del operador basico == ese metodo permite comparar un NodoArbol a un entero
     * @param comparador comparador es el unico parametro del metodo, es el elemento al cual se compara el NodoArbol
     * @return El metodo devuelve un booleano, dependiendo si el NodoArbol es nulo o no
     * @remark El metodo requiere que el NodoArbol este inicializado
     */
    bool operator!=(const int &comparador) const
    {
        if (comparador == 0 && indice == 0 && valor == 0 && indicePadre == 0)
        {
            return 0;
        }
        else
        {
            if (comparador == 0)
            {
                return 1;
            }
        }

        if (comparador != 0 && indice != 0 && valor != 0 && indicePadre != 0)
        {
            return 0;
        }
        else
        {
            if (comparador != 0)
            {
                return 1;
            }
        }
        return 0;
    }

    /**
     * @brief operator == es la sobrecarga del operador basico == ese metodo permite comparar un NodoArbol a un otro nodo
     * @param comparador comparador es el unico parametro del metodo, es el elemento al cual se compara el NodoArbol
     * @return El metodo devuelve un booleano, dependiendo si el NodoArbol es nulo o no
     * @remark El metodo requiere que el NodoArbol este inicializado
     */
    bool operator==(const NodoArbol &otroNodo) const
    {
        if (esNulo == 1 && otroNodo.esNulo == 1)
        {
           
            return 1;
        }
        if (esNulo == 1)
        {
            
            return 0;
        }
        if (otroNodo.esNulo == 1)
        {
           
            return 0;
        }

        if(otroNodo.getIndice() == indice && otroNodo.getIndicePadre()==indicePadre && otroNodo.getValor() == valor){
            return 1;
        }else{
            return 0;
        }
    }

    /**
     * @brief operator == es la sobrecarga del operador basico != ese metodo permite comparar un NodoArbol a un otro nodo
     * @param comparador comparador es el unico parametro del metodo, es el elemento al cual se compara el NodoArbol
     * @return El metodo devuelve un booleano, dependiendo si el NodoArbol es nulo o no
     * @remark El metodo requiere que el NodoArbol este inicializado
     */
    bool operator!=(const NodoArbol &otroNodo) const
    {
        return !(*this == otroNodo);
    }
};

class ArbolSenalador
{

public:
    /**
     * @brief El metodo ArbolSenaladores el metodo constructor de la clase ArbolSenaladores
     * @param cantidad cantidad es el unico parametro de la funcion ArbolSenaladores, representa la cantidad maxima de elementos en el arbol
     * @remark el metodo requiere que cantidad sea un tamaño de array valido
     */
    ArbolSenalador(size_t const cantidad)
    {
        arregloArbol = new NodoArbol[cantidad];
        maximo = cantidad;
        actual = 0;
        esVacio = 0;
    }

    /**
     * @brief El metodo ArbolSenaladores el metodo constructor de la clase ArbolSenaladores
     * @param cantidad cantidad es el unico parametro de la funcion ArbolSenaladores, representa la cantidad maxima de elementos en el arbol
     * @remark el metodo requiere que cantidad sea un tamaño de array valido
     */
    ArbolSenalador()
    {
        arregloArbol = new NodoArbol[256];
        maximo = 256;
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
        // delete nodoVacio;
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
        arregloArbol[0].esNulo = 0;
        if (esVacio == 0)
        {
            esVacio = 1;
            ++actual;
        }
    }

    /**
     * @brief AgregarHijo permite agregar un elemento al arbol, y por lo tanto un hijo al NodoArbol dado
     * @param padre padre es de tipo NodoArbol, es el NodoArbol al cual se agrega un hijo
     * @param valorHijo valorHijo es el valor del nuevo NodoArbol agregado al arbol
     * @return El NodoArbol creado como hijo del Padre. Es nulo si no se logro añadir
     * @remark El metodo necesita que el arbol sea inicializado, que tengo por lo menos una raiz incializada, y que el NodoArbol padre exista en el arbol
     */
    NodoArbol AgregarHijo(int valorHijo, NodoArbol padre)
    {
        NodoArbol hijoRetornado;

        if (actual < maximo)
        {
            arregloArbol[actual].setValor(valorHijo);
            arregloArbol[actual].setPadre(padre.getIndice());
            arregloArbol[actual].setIndice(actual);
            arregloArbol[actual].esNulo = 0;

            hijoRetornado = arregloArbol[actual];
            ++actual;
        }

        return hijoRetornado;
    }

    /**
     * @brief AgregarHijoMasDerecho permite agregar un nuevo elemento al Arbol, por medio de un hijo al NodoArbol dado, se agrega el hijo en la posicion mas derecha en comparacion a sus hermanos
     * @param padre padre es de tipo NodoArbol, es el NodoArbol al cual se agrega un hijo
     * @param valorHijo valorHijo es el valor del nuevo NodoArbol agregado al arbol
     * @return El NodoArbol creado como hijo del Padre. Es nulo si no se logro añadir
     * @remark El metodo necesita que el arbol sea inicializado, que tenga por lo menos una raiz incializada, y que el NodoArbol padre exista en el arbol
     */
    NodoArbol AgregarHijoMasDerecho(int valorHijo, NodoArbol padre) // agrega al padre un hijo
    {
        return AgregarHijo(valorHijo, padre);
    }

    /**
     * @brief Raiz permite acceder a la Raiz del arbol, no recibe parametros
     * @return El metodo Raiz devuelve el NodoArbol raiz del arbol
     * @remark El metodo requiere que sea incializado, y que tenga una raiz con valores inicializada
     */
    NodoArbol Raiz()
    {return arregloArbol[0];}

    /**
     * @brief El metodo Padre permite encontrar el Padre de un NodoArbol dado que pertenece al arbol
     * @param hijo hijo es de tipo NodoArbol, es el NodoArbol del cual se quiere encontrar el padre
     * @return El metodo devuelve un NodoArbol, el NodoArbol del arbol que tiene como hijo el NodoArbol NodoArbol hijo
     * @remark El metodo requiere que el arbol este inicializado, el NodoArbol dado por parametro exista en el arbol, sea inicializado y no sea la raiz del arbol
     */
    NodoArbol Padre(NodoArbol hijo)
    {
        return arregloArbol[hijo.getIndicePadre()];
    }

    /**
     * @brief El metodo HijoMasIzquierdo permite encontrar el Hijo mas a la izquierda de un NodoArbol dado
     * @param padre padre es el unico parametro del metodo, es de tipo NodoArbol, es el NodoArbol del cual hay que encontrar el hijo mas izquierdo, si no existe entonces significa que es una hoja
     * @return El metodo devuelve un puntero hacia el NodoArbol hijo, o un nullptr en el caso que no tenga hijos
     * @remark El metodo requiere que el arbol este inicializado, y que el NodoArbol padre dado exista en el arbol
     */
    NodoArbol HijoMasIzquierdo(NodoArbol padre)
    {
        int indice = padre.getIndice() + 1;

        int encontrado = 0;
        while (indice < maximo && arregloArbol[indice].getIndicePadre() != padre.getIndice())
        {
            
            if (arregloArbol[indice].getIndicePadre() == padre.getIndice())
            {
                encontrado = 1;
            }

            ++indice;
        }

        if (indice < maximo && arregloArbol[indice].getIndicePadre() == padre.getIndice())
        {
            encontrado = 1;
        }

        if (encontrado == 1) // caso donde el NodoArbol no es una hoja
        {
            return arregloArbol[indice];
        }
        else // caso donde el NodoArbol es una hoja
        {
            // return nullptr;
            return nodoVacio;
            // return 0;
        }
    }

    /**
     * @brief El metodo HermanoDerecho permite encontrar el NodoArbol mas cercano a la derecha del NodoArbol dado que tengo el mismo padre, si no existe entonces significa que el NodoArbol dado ya es el NodoArbol mas a la derecha
     * @param hermano hermano es el unico parametro del metodo, es el NodoArbol del cual tenemos que buscar el hermano derecho
     * @return El metodo devuelve un puntero hacia el hermano derecho, o un nullptr en el caso que no tengo hermano derecho
     * @remark El metodo requiere que el arbol este inicializado, que el NodoArbol hermano exista en el arbol, y que no sea la raiz
     */
    NodoArbol HermanoDerecho(NodoArbol hermano)
    {
        int indixePadre = hermano.getIndicePadre();
        int indice = hermano.getIndice();

        if (indice != actual - 1)
        {
            ++indice;
            int encontrado = 0;

            // caso donde el hermano derecho es el indice justo despues del hermano
            if(arregloArbol[indice].getIndicePadre() == hermano.getIndicePadre()){
                encontrado = 1;
            }

            // pasamos por todos los nodos del arbol hasta encontrar el primero que tenga el mismo padre
            while(indice < maximo && arregloArbol[indice].getIndicePadre() != hermano.getIndicePadre() && encontrado ==0){
                ++indice;
                if(arregloArbol[indice].getIndicePadre() == hermano.getIndicePadre()){
                encontrado = 1;
                }
            }

            if(encontrado){
                return arregloArbol[indice];
            }else{
                return nodoVacio;
            }

        }else{
            return nodoVacio;
        }
    }

    /**
     * @brief BorrarHoja es un metodo del arbol que permite eliminar una hoja del arbol
     * @param nodoBorrado bodoBorrado es el unico parametro del metodo, es el metodo del arbol que se quiere borrar
     * @remark El metodo occupa que el arbol sea inicializado y el NodoArbol nodoBorrado exista en el arbol y sea una hoja
     */
    void BorrarHoja(NodoArbol nodoBorrado)
    {

        int indiceBorrado = nodoBorrado.getIndice();

        // si el elemento borrado es el ultimo
        // if (indiceBorrado != actual - 1)
        if (nodoBorrado.getValor() != arregloArbol[actual - 1].getValor())
        {
            int indiceBorrado = 0;
            while (arregloArbol[indiceBorrado].getValor() != nodoBorrado.getValor())
            {
                ++indiceBorrado;
            }

            int indice = indiceBorrado;
            // sizeN-2 es el "nuevo" ultimo elemento del array
            while (indice != actual - 1)
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
       arregloArbol[actual-1].esNulo = 1;
       arregloArbol[actual-1].setValor(0); 
       arregloArbol[actual-1].setIndice(0); 
       arregloArbol[actual-1].setPadre(0); 
        --actual;
        
    }

    /**
     * @brief Etiqueta es un metodo del arbol que devuelve la etiqueta, en ese caso un entero, de un NodoArbol dado
     * @param nodo nodo es de tipo NodoArbol, es el NodoArbol del cual queremos extraer le etiqueta
     * @remark El metodo requiere que el arbol sea inicializado, y que el NodoArbol nodo exista en el arbol
     */
    int Etiqueta(NodoArbol nodo)
    {
        return nodo.getValor();
    }

    /**
     * @brief ModificarEtiqueta permite modificar el valor (etiqueta) de un NodoArbol dado
     * @param nodo nodo es de tipo NodoArbol, es el NodoArbol del cual queremos cambiar la etiqueta
     * @param nuevoValor nuevoValor es un entero, una etiqueta, es el nuevo valor de la etiqueta del NodoArbol nodo
     * @remark El metodo requiere que el arbol sea inicializado, y que el NodoArbol nodo existe en el arbol
     */
    void ModificaEtiqueta(int nuevoValor, NodoArbol nodo)
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
    NodoArbol *arregloArbol;
    int maximo;
    int actual;
    int esVacio;
    NodoArbol nodoVacio;
};

typedef NodoArbol Nodo;
typedef ArbolSenalador Arbol;

#endif