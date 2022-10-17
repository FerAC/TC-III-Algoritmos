//#include "Tree_senaladorPadre.h"
#include <iostream>

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
        //doubleEntryArray[0] = new int[quantityElements];
        //doubleEntryArray[1] = new int[quantityElements];
        maximo = cantidad;
        actual = 0;
        esVacio = 0;
    }

    /**
     * @brief ~ArbolSenalador is the destructor method of the class
     */
    ~ArbolSenalador()
    {
        //delete[] doubleEntryArray[0];
        //delete[] doubleEntryArray[1];
       // delete[] doubleEntryArray;    
       delete[] arregloArbol;
    }

    /**
     * @brief PonerRaiz is a function that change the actual value of the root, or add the first value to the tree
     * @param root root is the new value  of the root
     */
    void PonerRaiz(int root)
    {
       // doubleEntryArray[0]. = root;
        //doubleEntryArray[1][0] = 0;
        arregloArbol[0].setValor(root);
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
    void AgregarHijo(int indicePadre, int valorHijo) // agrega al padre un hijo
    {
        if(actual < maximo){
            arregloArbol[actual].setValor(valorHijo);
            arregloArbol[actual].setPadre(indicePadre);
            ++actual;
        }
       // if (sizeN < sizeM) // while to find the father and it's index, and then ad at the end of the array the son
        //{
          //  doubleEntryArray[0][sizeN] = hijo;
           // doubleEntryArray[1][sizeN] = indexPadre;
           // ++sizeN;
        //}
    }

    /**
     * @brief AgregarHijoMasDerecho add a new element to the tree
     * @param indexPadre indexPadre is the index of the father of the new node
     * @param hijo hijo is the value of the new element inserted in the tree
     */
    void AgregarHijoMasDerecho(int indexPadre, int hijo) // agrega al padre un hijo
    {
        //if (sizeN < sizeM) // while to find the father and it's index, and then ad at the end of the array the son
        //{
          //  doubleEntryArray[0][sizeN] = hijo;
            //doubleEntryArray[1][sizeN] = indexPadre;
            //++sizeN;
        //}
        if(actual < maximo){
            arregloArbol[actual].setValor(valorHijo);
            arregloArbol[actual].setPadre(indicePadre);
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
        // int i = 0;
        //while (i != hijo.getIndicePadre())
        //{
          ///  ++i;
        //}
        return arregloArbol[hijo.getIndicePadre()];
       // return valueFather;
    }

    /**
     * @brief
     * @param
     * @return
     */
    Nodo HijoMasIzquierdo(Nodo padre)
    {
        int i = 0;
        while (arregloArbol[arregloArbol[i].getIndicePadre()].getValor() != padre.getValor())
        {
            ++i;
        }
        return arregloArbol[i];
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
        
        while(arregloArbol[indice].getValor() != hermano.getValor()){
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
    void BorrarHoja(int indiceBorrado)
    {

        // si el elemento borrado es el ultimo
        if (indiceBorrado == sizeN - 1)
        {
            --sizeN;
        }
        else
        {
            // shift todos los elementos a la izquierda, y si el padre es mayor al indiceBorrado entonces dec. indice del padre
            int i = indiceBorrado;
            // sizeN-2 es el "nuevo" ultimo elemento del array
            while (i != sizeN - 2)
            {
                doubleEntryArray[0][i] = doubleEntryArray[0][i + 1];
                doubleEntryArray[1][i] = doubleEntryArray[1][i + 1];
                ++i;
            }
            --sizeN;
        }
    }

    /**
     * @brief
     * @param
     */
    int Etiqueta(int indice)
    {
        return (doubleEntryArray[0][indice]);
    }

    /**
     * @brief
     * @param
     * @param
     */
    void ModificaEtiqueta(int value, int newValue) // change the node with value, to newValue
    {
        int counter = 0;
        int buffer = doubleEntryArray[0][counter];
        while (buffer != value) // find in array the cell with etiqueta
        {
            ++counter;
            buffer = doubleEntryArray[0][counter];
        }
        doubleEntryArray[0][counter] = newValue; // change the actual value to newValue
    }

    /**
     * @brief
     * @return
     */
    int NumNodos()
    {
        return 0;
    }


    /*
    void printTree()
    {
        std::cout << "_______________________\n"
                  << std::endl;
        int counter = 1;
        std::cout << "Root: " << doubleEntryArray[0][0] << " index: 0" << std::endl;
        while (counter != sizeN)
        {
            std::cout << "value: " << doubleEntryArray[0][counter] << ", index: " << counter << ", father's index: " << doubleEntryArray[1][counter] << std::endl;
            ++counter;
        }
    }*/

private:
    Nodo *arregloArbol;
    int maximo;
    int actual;
    int esVacio;
};

class Nodo
{
    friend ArbolSenalador 

private: 
    int indicePadre;
    int valor;

    void setValor(int nuevoValor){
        valor = nuevoValor;
    }

    int getValor(){
        return valor;
    }

    void setPadre(int nuevoIndice){
        indicePadre = nuevoIndice;
    }

    int getIndicePadre(){
        return indicePadre;
    }

  //  void 

    Nodo(int indice, int valor)
    {
        indicePadre = indice;
    }

    ~Nodo() {}
};

Nodo::Nodo(/* args */)
{
}

Nodo::~Nodo()
{
}

int main()
{

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
    tree.printTree();

    std::cout << "_______________________\n"
              << std::endl;

    return 0;
}