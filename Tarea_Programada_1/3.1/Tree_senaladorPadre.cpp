#include "Tree_senaladorPadre.h"


ArbolSenalador::ArbolSenalador(int const quantityElements)
{
    doubleEntryArray = new int*[2];
    doubleEntryArray[0] = new int[quantityElements];
    doubleEntryArray[1] = new int[quantityElements];
}

ArbolSenalador::~ArbolSenalador()
{
    delete[] doubleEntryArray[0];
    delete[] doubleEntryArray[1];
    delete[] doubleEntryArray;
}

void ArbolSenalador::PonerRaiz(int)
{
}

void ArbolSenalador::AgregarHijo(int)
{
}

void ArbolSenalador::AgregarHijoMasDerecho(int)
{
}
void ArbolSenalador::BorrarHoja()
{
}

void ArbolSenalador::ModificaEtiqueta()
{
}

int ArbolSenalador::NumNodos()
{
}

ArbolSenalador::Node::Node(int)
{
}

ArbolSenalador::Node::~Node()
{
}