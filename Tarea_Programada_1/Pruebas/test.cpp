#include <iostream>
#include <cstddef>

#include "src/4/Controlador.hpp"

#define ITERACIONES 1000000

size_t nivelesArbolRPO(Arbol &arbol, Nodo subraiz, size_t& contadorRecursividad)
{
    contadorRecursividad += 1;
    std::cout << "CAPA = " << contadorRecursividad << std::endl;

    const Nodo& NodoNulo = Nodo();

    if (subraiz == NodoNulo)
        return 0;

    size_t alturaCandidata = 0;
    for (Nodo hijoActual = arbol.HijoMasIzquierdo(subraiz); hijoActual != NodoNulo; hijoActual = arbol.HermanoDerecho(hijoActual))
    {
        size_t alturaSubArbol = nivelesArbolRPO(arbol, hijoActual, contadorRecursividad);

        if (alturaSubArbol > alturaCandidata)
            alturaCandidata = alturaSubArbol;
    }

    contadorRecursividad -= 1;
    return alturaCandidata + 1;
}

int main()
{
    Controlador controlador;
    size_t iterContador = 0;

    Arbol arbol; arbol.PonerRaiz(0); 
    Nodo nodoBuff = arbol.Raiz(); const Nodo& NodoNulo = Nodo();

    for (size_t i = 1; i < ITERACIONES; ++i)
        nodoBuff = arbol.AgregarHijo(i, nodoBuff);

    size_t niveles = nivelesArbolRPO(arbol, arbol.Raiz(), iterContador);
    std::cout << "TERMINADO! NIVELES = " << niveles << std::endl;
}

