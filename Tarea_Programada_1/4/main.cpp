//#include "Tree_senaladorPadre.h"          // 3.1
#include "3.1.hpp"
//#include "ArbolLH.h"                      // 3.2
//#include "Arbol.cpp"                      // 3.3
//#include "treePunteroPadreNoContador.h"   // 3.4
//#include "tree5.h"                        // 3.5
#include <iostream>

/// @brief Metodo imprimirArbol, permite imprimir el contenido de una arbol dado por parametro, recoge el arbol en pre-orden
/// @param nodo nodo
/// @param arbol arbol es el arbol recibido por referencia
void imprimirArbol(Nodo nodo, Arbol &arbol)
{
    const Nodo &NodoNulo = Nodo();
    if (nodo == NodoNulo)
    {
        return;
    }

    std::cout << arbol.Etiqueta(nodo) << std::endl;

    //
    // ciclo para explorar cada

    Nodo hijo = arbol.HijoMasIzquierdo(nodo);
    // std::cout << "aaa" << std::endl;
    while (hijo != NodoNulo)
    {
        imprimirArbol(hijo, arbol);
        hijo = arbol.HermanoDerecho(hijo);
    }
}

/// @brief Metodo buscarArbol, permite buscar si un valor esta en el arbol, recoge el arbol en pre-orden
/// @param
void imprimirArbol(Nodo nodo, Arbol &arbol)
{
    const Nodo &NodoNulo = Nodo();
    if (nodo == NodoNulo)
    {
        return;
    }

    std::cout << arbol.Etiqueta(nodo) << std::endl;

    //
    // ciclo para explorar cada

    Nodo hijo = arbol.HijoMasIzquierdo(nodo);
    // std::cout << "aaa" << std::endl;
    while (hijo != NodoNulo)
    {
        imprimirArbol(hijo, arbol);
        hijo = arbol.HermanoDerecho(hijo);
    }
}

void borrarHoja(int valorBorrado)
{
    Nodo borrado = buscarEtiqueta(etiquetaPadre);
    arbol.BorrarHoja(borrado);
    imprimirArbol(arbol.Raiz(), arbol);
}

void hijoMasIzquierdo(int etiqueta)
{
    Nodo nodoPadre = buscarEtiqueta(etiquetaPadre);
    arbol.HijoMasIzquierdo(nodoPadre);
    imprimirArbol(arbol.Raiz(), arbol);
}

void hijoMasIzquierdo(int etiqueta)
{
    Nodo nodoPadre = buscarEtiqueta(etiquetaPadre);
    Nodo mI = arbol.HijoMasIzquierdo(nodoPadre);
    std::cout << "Hijo mas Izquiedo de " << etiqueta << "es " << arbol.Etiqueta(mI) << std::endl;
}

void hermanoDerecho(int etiqueta)
{
    Nodo nodoPadre = buscarEtiqueta(etiquetaPadre);
    Nodo mI = arbol.HermanoDerecho(nodoPadre);
    std::cout << "Hermano Derecho de " << etiqueta << "es " << arbol.Etiqueta(mI) << std::endl;
}

int main()
{
    std::cout << "Bienvenid@ ! Inserta [i] para inicializar un modelo vacio, sino inserta [q] para salir del programa" << std::endl;
    char respuestaUsuario;
    std::cin >> respuestaUsuario;

    int choice;
    int seguir = 0;

    if (respuestaUsuario == 'i')
    {
        seguir = 1;
        std::cout << "Si quiere inicializar una Cola vacia, digita [c] \nSi quiere inicializar una Lista indexada vacia, digita [l] \nSi quiere inicializar un arbol n-ario, digita [a]" << std::endl;
        std::cin >> respuestaUsuario;
    }

    while (seguir)
    {
        if (respuestaUsuario == 'c')
        {
            std::cout << "Cuantos elementos maximo quiere tener en la cola ?" << std::endl;
            int maximo;
            std::cin >> maximo;
            Cola<int> cola(maximo);
            std::cout << "Que desea hacer con la cola?" << std::endl;
            std::cout << "0 - encolar elemento" << std::endl;
            std::cout << "1 - desencolar elemento" << std::endl;
            std::cout << "2 - numElem " << std::endl;
            std::cout << "3 - vaciar " << std::endl;
            std::cout << "4 - vacio " << std::endl;
            std::cout << "5 - salir y destruir la cola" << std::endl;
            std::cin >> choice;

            switch (choice)
            {
            case 0: // encolar
                std::cout << "Cual elemento quiere encolar ?" << std::endl;
                int elemento;
                std::cin >> elemento;
                cola.Encolar(elemento);
                break;

            case 1: // desencolar
                int elem = cola.Desencolar();
                std::cout << "El elemento desencolado es: " << elem << std::endl;
                break;

            case 2: // numElem
                std::cout << cola.NumElem() << std::endl;
                break;

            case 3: // vaciar
                cola.vaciar();
                std::cout << "se vacio correctamente la cola" << std::endl;
                break;

            case 4: // vacio (devuelve un bool)
                int esVacio = cola.vacia();
                if (esVacio)
                {
                    std::cout << "La cola es vacia" << std::endl;
                }
                else
                {
                    std::cout << "La cola no es vacia" << std::endl;
                }
                break;

            case 5: // salir
                seguir = 0;
                break;

            default:
                break;
            }
        }

        if (respuestaUsuario == 'l')
        {
        }

        if (respuestaUsuario == 'a')
        {

            Arbol arbol;

            std::cout << "\n\n\t ############################# \n"
                      << std::endl;
            std::cout << "Que desea hacer con el arbol n-ario?" << std::endl;
            std::cout << "0 - cambiar raiz (vital al inicializar el arbol)" << std::endl;
            std::cout << "1 - agregar hijo" << std::endl;
            std::cout << "2 - borrar hoja" << std::endl;
            std::cout << "3 - imprimir el arbol" << std::endl;
            std::cout << "4 - get raiz" << std::endl;
            std::cout << "5 - imprimir arbol" << std::endl;
            std::cout << "6 - salir y destruir el arbol" << std::endl;
            std::cin >> choice;

            switch (choice)
            {
            case 0: // cambiar raiz (vital al inicializar el arbol)
                std::cout << "Cual valor quiere poner a la raiz ?" << std::endl;
                int valorRaiz;
                std::cin >> valorRaiz;
                arbol.PonerRaiz(valorRaiz);
                break;

            case 1: // agregar hijo

                break;

            case 2: // borrar hoja
                std::cout << "Cual valor quiere borrar del arbol ?" << std::endl;
                int etiquetaBorrada;
                std::cin >> etiquetaBorrada;

                break;

            case 3: // imprimir el arbol
                imprimirArbol(arbol.Raiz(), arbol);
                break;

            case 4: // get raiz
                /* code */
                break;

            case 5: // imprimir
                // imprimir
                break;

            case 6: // salir y destruir arbol
                seguir = 0;
                break;

            default:
                break;
            }
        }
    }

    return 0;
}