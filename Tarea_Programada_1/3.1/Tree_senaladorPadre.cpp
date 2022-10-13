#include "Tree_senaladorPadre.h"

ArbolSenalador::ArbolSenalador(int const quantityElements)
{
    doubleEntryArray = new int *[2];
    doubleEntryArray[0] = new int[quantityElements];
    doubleEntryArray[1] = new int[quantityElements];
    sizeM = quantityElements;
}

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
}

void ArbolSenalador::AgregarHijo(int)
{
}

int ArbolSenalador::getRaiz()
{
    return (doubleEntryArray[0][0]);
}

int ArbolSenalador::getPadre(int value)
{
    int i =0;
    while(doubleEntryArray[i][0]!=value){
        ++i;
    }
    int valueFather = doubleEntryArray[doubleEntryArray[i][1]][0];
    return valueFather;
}

void ArbolSenalador::BorrarHoja()
{
    // borrar nodo, hacer shift para que no haya un hueco
}

void ArbolSenalador::ModificaEtiqueta(int value, int newValue) // change the node with value, to newValue
{
}

int ArbolSenalador::NumNodos()
{
    return 0;
}


    /*
    ArbolSenalador::Node::Node(int newEtiqueta)
    {
        etiqueta = newEtiqueta;
    }

    ArbolSenalador::Node::~Node()
    {
    }*/