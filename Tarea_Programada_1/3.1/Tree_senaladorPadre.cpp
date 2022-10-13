#include "Tree_senaladorPadre.h"

/**
 * @brief ArbolSenalador is the constructor method of the class
 */
ArbolSenalador::ArbolSenalador(int const quantityElements)
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
ArbolSenalador::~ArbolSenalador()
{
    delete[] doubleEntryArray[0];
    delete[] doubleEntryArray[1];
    delete[] doubleEntryArray;
}

void ArbolSenalador::PonerRaiz(int root)
{
    doubleEntryArray[0][0] = root;
    doubleEntryArray[0][1] = 0;
    if (isEmpty == 0)
    {
        isEmpty = 1;
        ++sizeN;
    }
}

void ArbolSenalador::AgregarHijo(int padre, int hijo) // agrega al padre un hijo
{
    if (sizeN < sizeM) // while to find the father and it's index, and then ad at the end of the array the son
    {
        int counter = 0;
        int buffer = doubleEntryArray[counter][0];
        while (buffer != padre)
        {
            ++counter;
            buffer = doubleEntryArray[counter][0];
        }
        doubleEntryArray[sizeN][0] = hijo;
        doubleEntryArray[sizeN][1] = counter; // counter is index of father
        ++sizeN;                              // once inserted we add 1 to the size
    }
}

int ArbolSenalador::getRaiz()
{
    return (doubleEntryArray[0][0]);
}

int ArbolSenalador::getPadre(int value)
{
    int i = 0;
    while (doubleEntryArray[i][0] != value)
    {
        ++i;
    }
    int valueFather = doubleEntryArray[doubleEntryArray[i][1]][0];
    return valueFather;
}

void ArbolSenalador::BorrarHoja(int deletedIndex)
{
    --sizeN;
    doubleEntryArray[deletedIndex][0] = doubleEntryArray[sizeN][0];
    doubleEntryArray[deletedIndex][1] = doubleEntryArray[sizeN][1];
    // deleted the element, replace it by the last leaf inserted (last element in the array) and decrement sizeN
}

void ArbolSenalador::ModificaEtiqueta(int value, int newValue) // change the node with value, to newValue
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

int ArbolSenalador::NumNodos()
{
    return 0;
}

int ArbolSenalador::buscar(int target)
{
    int counter = 0;
    int buffer = doubleEntryArray[counter][0];
    int doesExist = 0;
    while ((buffer != target) && (counter != sizeN - 1) && (doesExist == 0))
    {
        ++counter;
        buffer = doubleEntryArray[counter][0];
        if (buffer == target)
        {
            doesExist = 1;
        }
    }

    return doesExist;
}