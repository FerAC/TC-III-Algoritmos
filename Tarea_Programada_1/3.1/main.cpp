#include "3_1.hpp"
#include <iostream>

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
    arbol.BorrarHoja(*arbol.HijoMasIzquierdo(*arbol.HijoMasIzquierdo(arbol.Raiz())));

    return 0;
}