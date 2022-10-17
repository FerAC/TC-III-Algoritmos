#include <iostream>

class Nodo
{
    friend class ArbolSenalador;

private:
    int indicePadre;
    int valor;
    int indice;

    void setIndice(int nuevoIndice)
    {
        indice = nuevoIndice;
    }

    int getIndice()
    {
        return indice;
    }

    void setValor(int nuevoValor)
    {
        valor = nuevoValor;
    }

    int getValor()
    {
        return valor;
    }

    void setPadre(int nuevoIndice)
    {
        indicePadre = nuevoIndice;
    }

    int getIndicePadre()
    {
        return indicePadre;
    }

public:
    Nodo(Nodo padre, int elValor)
    {
        valor = elValor;
        indicePadre = padre.getIndice();
    }

    Nodo() {}

    ~Nodo() {}
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
    Nodo HijoMasIzquierdo(Nodo padre)
    {
        //int i = 0;
        //while (arregloArbol[arregloArbol[i].getIndicePadre()].getValor() != padre.getValor())
        //{
        //    ++i;
        //}

        //int indice = 0;
       // while(arregloArbol[indice].getIndicePadre() != i){
       //     ++indice;
        //}

        //return arregloArbol[indice];
        int indice = padre.getIndice() + 1;
        while(arregloArbol[indice].getIndicePadre() != padre.getIndice()){
            ++indice;
        }
        return arregloArbol[indice];
    }

    /**
     * @brief
     * @param
     * @return
     */
    Nodo HermanoDerecho(Nodo hermano)
    {
        int indixePadre = hermano.getIndicePadre();
        int indice = 0;

        while (arregloArbol[indice].getValor() != hermano.getValor())
        {
            ++indice;
        }

        ++indice;

        while (arregloArbol[indice].getIndicePadre() != hermano.getIndicePadre())
        {
            ++indice;
        }
        return arregloArbol[indice];
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
};

int main()
{
    
    /*
        ArbolSenalador tree(10);
        tree.PonerRaiz(5);
        tree.AgregarHijo(0, 2);
        tree.AgregarHijo(1, 3);
        tree.AgregarHijo(1, 125);
        // tree.PonerRaiz(1000);

        tree.AgregarHijo(0, 25);
        tree.AgregarHijo(4, 12);
        tree.AgregarHijo(3, 7);
        tree.AgregarHijo(1, 76);
        tree.AgregarHijo(2, 0);
        tree.AgregarHijo(3, 65);
        tree.BorrarHoja(7);
        tree.BorrarHoja(8);
        tree.AgregarHijo(0, 12343); // extra element
        tree.ModificaEtiqueta(12343, 999);

        std::cout << tree.Etiqueta(2) << std::endl;
        std::cout << tree.Padre(2) << std::endl;

        */
    // tree.printTree();

    ArbolSenalador arbol(10);
    arbol.PonerRaiz(100);
    //std::cout << arbol.Etiqueta(arbol.Raiz()) << std::endl;

    arbol.AgregarHijo(123, arbol.Raiz());
    arbol.AgregarHijo(22, arbol.Raiz());
    arbol.AgregarHijoMasDerecho(1, arbol.HijoMasIzquierdo(arbol.Raiz()));


    std::cout<<arbol.Etiqueta(arbol.Raiz())<<std::endl;
    std::cout<<arbol.Etiqueta(arbol.HijoMasIzquierdo(arbol.Raiz()))<<std::endl;
    std::cout<<arbol.Etiqueta(arbol.HermanoDerecho(arbol.HijoMasIzquierdo(arbol.Raiz())))<<std::endl;
    std::cout<<arbol.Etiqueta(arbol.HijoMasIzquierdo(arbol.HijoMasIzquierdo(arbol.Raiz())))<<std::endl;
    arbol.BorrarHoja(arbol.HijoMasIzquierdo(arbol.HijoMasIzquierdo(arbol.Raiz())));
    
    std::cout << "_______________________\n"
              << std::endl;

    return 0;
}