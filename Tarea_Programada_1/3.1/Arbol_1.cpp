//#include "Tree_senaladorPadre.h"
#include <iostream>

class ArbolSenalador
{

public:
    /**
     * @brief ArbolSenalador is the constructor method of the class
     * @param quantityElements quantityElements is a const int, it's the max size of the array
     */
    ArbolSenalador(int const quantityElements)
    {
        doubleEntryArray = new int *[2];
        doubleEntryArray[0] = new int[quantityElements];
        doubleEntryArray[1] = new int[quantityElements];
        sizeM = quantityElements;
        sizeN = 0;
        isEmpty = 0;
    }

    /**
     * @brief ~ArbolSenalador is the destructor method of the class
     */
    ~ArbolSenalador()
    {
        delete[] doubleEntryArray[0];
        delete[] doubleEntryArray[1];
        delete[] doubleEntryArray;
    }

    /**
     * @brief PonerRaiz is a function that change the actual value of the root, or add the first value to the tree
     * @param root root is the new value  of the root
     */
    void PonerRaiz(int root)
    {
        doubleEntryArray[0][0] = root;
        doubleEntryArray[1][0] = 0;
        if (isEmpty == 0)
        {
            isEmpty = 1;
            ++sizeN;
        }
    }

    /**
     * @brief AgregarHijo add a new element to the tree
     * @param indexPadre indexPadre is the index of the father of the new node
     * @param hijo hijo is the value of the new element inserted in the tree
     */
    void AgregarHijo(int indexPadre, int hijo) // agrega al padre un hijo
    {
        if (sizeN < sizeM) // while to find the father and it's index, and then ad at the end of the array the son
        {
            doubleEntryArray[0][sizeN] = hijo;
            doubleEntryArray[1][sizeN] = indexPadre;
            ++sizeN;
        }
    }

    /**
     * @brief AgregarHijoMasDerecho add a new element to the tree
     * @param indexPadre indexPadre is the index of the father of the new node
     * @param hijo hijo is the value of the new element inserted in the tree
     */
    void AgregarHijoMasDerecho(int indexPadre, int hijo) // agrega al padre un hijo
    {
        if (sizeN < sizeM) // while to find the father and it's index, and then ad at the end of the array the son
        {
            doubleEntryArray[0][sizeN] = hijo;
            doubleEntryArray[1][sizeN] = indexPadre;
            ++sizeN;
        }
    }

    /**
     * @brief
     * @return
     */
    int Raiz()
    {
        return (doubleEntryArray[0][0]);
    }

    /**
     * @brief
     * @param
     * @return
     */
    int Padre(int value)
    {
        int i = 0;
        while (doubleEntryArray[i][0] != value)
        {
            ++i;
        }
        int valueFather = doubleEntryArray[doubleEntryArray[i][1]][0];
        return valueFather;
    }

    /**
     * @brief
     * @param
     * @return
     */
    int HijoMasIzquierdo(int indexPadre)
    {
        int i = 0;
        while (doubleEntryArray[i][1] != indexPadre)
        {
            ++i;
        }
        return i;
    }

    /**
     * @brief
     * @param
     * @return
     */
    int HermanoDerecho(int indexHermanoIzquierdo)
    {
        int indexPadre = doubleEntryArray[indexHermanoIzquierdo][1];
        int i = indexHermanoIzquierdo + 1;
        while (doubleEntryArray[i][1] != indexPadre)
        {
            ++i;
        }
        return i;
    }

    /**
     * @brief
     * @param
     */
    void BorrarHoja(int deletedIndex)
    {
        // if it's not the last element in array
        if (deletedIndex != sizeN - 1)
        {
            --sizeN;
            doubleEntryArray[0][deletedIndex] = doubleEntryArray[0][sizeN];
            doubleEntryArray[1][deletedIndex] = doubleEntryArray[1][sizeN];
        }
        else
        { // if it's the last element in array
            --sizeN;
        }
    }

    /**
     * @brief
     * @param
     */
    int Etiqueta(int index){
        return (doubleEntryArray[index][0]);
    }

    /**
     * @brief
     * @param
     * @param
     */
    void ModificaEtiqueta(int value, int newValue) // change the node with value, to newValue
    {
        int counter = 0;
        int buffer = doubleEntryArray[counter][0];
        while (buffer != value) // find in array the cell with etiqueta
        {
            ++counter;
            buffer = doubleEntryArray[counter][0];
        }
        doubleEntryArray[counter][0] = newValue; // change the actual value to newValue
    }

    /**
     * @brief
     * @return
     */
    int NumNodos()
    {
        return 0;
    }

    /**
     * @brief
     */
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
    }

private:
    int **doubleEntryArray;
    int sizeM;
    int sizeN;
    int isEmpty;
};

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
    tree.BorrarHoja(9);
    tree.AgregarHijo(0, 12343); // extra element
    tree.printTree();
    /*
    tree.printTree();

    tree.printTree();

    tree.AgregarHijo(0, 10);
    tree.printTree();

    tree.BorrarHoja(1);
    tree.printTree();


    tree.AgregarHijo(0, 1);
    tree.printTree();
    // tree.BorrarHoja(2);
    tree.printTree();
    */

    std::cout << "_______________________\n"
              << std::endl;

    return 0;
}