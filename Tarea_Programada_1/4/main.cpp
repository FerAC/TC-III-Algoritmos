// Incluye utilidades auxiliares
#include <cstddef> // Para utilizar contadores en recorrido por niveles
#include "../CDE/Cola.hpp" // Cola dinámica para realizar recorrido por niveles

// Include de la Cola
#include "../1/Cola.hpp"

// Include de la Lista Indexada
#include "../2/ListaIndexada.h"

// Include de los Árboles
// #include "../3.1/3.1.hpp"
// #include "../3.2/3.2.hpp"
// #include "../3.3/3.3.hpp"
// #include "../3.4/3.4.hpp"
#include "../3.5/3.5.hpp"

// Include para I/O estándar
#include <iostream>

/// @brief Permite imprimir el contenido de una árbol dado por parámetro. Recore el árbol en pre-orden
/// @param nodo Nodo Inicial
/// @param arbol Árbol es el arbol recibido por referencia
void imprimirArbol(Arbol &arbol)
{
    const Nodo &NodoNulo = Nodo();

    // Imprimamos la cantidad de nodos presentes en el árbol
    std::cout << "N = " << arbol.NumNodos() << std::endl;

    // Caso 1: El árbol tiene raíz nula (no tiene nodos)
    if (arbol.Raiz() == NodoNulo)
        return;

    // Caso 2: El árbol tiene nodos
    // Realizaremos un recorrido por niveles utilizando una cola de nodos
    Util::Cola<Nodo> colaNodos;

    // Encolemos a la raiz para iniciar el recorrido usándola como punto de partida
    colaNodos.Encolar(arbol.Raiz());

    // Adicionalmente, imprimiremos sus contenidos de primero
    std::cout << '[' << arbol.Etiqueta(arbol.Raiz()) << ']' << std::endl;

    // Adicionalmente, llevaremos cuenta de cuántos nodos corresponden al nivel actual y su correspondiente siguiente
    size_t nodosPendientesNivelActual = 1;
    size_t nodosPendientesNivelSiguiente = 0;

    // Mientras tengamos nodos en la cola, no hemos terminado el recorrido
    // Si resulta que encontramos al padre, escaparemos el recorrido mediante un retorno prematuro
    while (!colaNodos.Vacio())
    {
        // Siempre obtendremos el nodo encolado más antigüamente (de primero)
        Nodo nodoActual = colaNodos.Desencolar();

        // Tras obtener ese nodo, la cantidad de nodos pendientes en el nivel actual disminuye en 1
        --nodosPendientesNivelActual;

        // Tras obtener un nodo, encolaremos cada hijo
        // Para distinguir a cada grupo de hijos, encerraremos la impresión de cada grupo entre llaves
        std::cout << "[";

        for (Nodo hijoActual = arbol.HijoMasIzquierdo(nodoActual); hijoActual != NodoNulo; hijoActual = arbol.HermanoDerecho(hijoActual))
        {
            // Tras obtener un hijo, imprimiremos sus contenidos
            std::cout << arbol.Etiqueta(hijoActual);

            // Si tiene un hermano derecho, dejaremos un espacio entre ellos
            if (arbol.HermanoDerecho(hijoActual) != NodoNulo)
                std::cout << ' ';

            // Luego, tras imprimir sus contenidos, lo encolaremos
            colaNodos.Encolar(hijoActual);

            // Tras encolar un hijo, la cantidad de nodos pendientes en el nivel siguiente aumenta
            ++nodosPendientesNivelSiguiente;
        }
    
        std::cout << "] ";
        
        // Si ya no hay nodos pendientes en este nivel, entonces hemos cambiado de nivel
        if (nodosPendientesNivelActual == 0)
        {
            // La cantidad de nodos pendientes en este nivel corresponden a la cantidad de nodos pendientes para el siguiente
            nodosPendientesNivelActual = nodosPendientesNivelSiguiente;

            // Luego, como cambiamos de nivel, la cantidad de nodos pendientes para el siguiente nivel se asume como 0 de nuevo
            nodosPendientesNivelSiguiente = 0;

            // Adicionalmente podemos realizar un salto de nivel en la impresión
            std::cout << std::endl;
        }
    }
}

/// @brief Devuelve el primer nodo correspondiente a la etiqueta buscada (si existe). Recorre el árbol en pre-orden
/// @param arbol Arbol donde se busca algún nodo con la etiqueta
/// @param etiqueta Etiqueta cuyos contenidos se intentan buscar en el árbol (dentro de un nodo)
/// @return Nodo en el árbol que posee la etiqueta alimentada. Nodo nulo en caso contrario
Nodo buscarEtiqueta(int etiqueta, Arbol &arbol)
{
    const Nodo &NodoNulo = Nodo();

    // Caso 1: El árbol tiene raíz nula (no tiene nodos)
    if (arbol.Raiz() == NodoNulo)
        return NodoNulo;

    // Caso 2: El árbol tiene nodos
    // Realizaremos un recorrido por niveles utilizando una cola de nodos
    Util::Cola<Nodo> colaNodos;

    // Encolemos a la raiz para iniciar el recorrido usándola como punto de partida
    colaNodos.Encolar(arbol.Raiz());

    // Mientras tengamos nodos en la cola, no hemos terminado el recorrido
    // Si resulta que encontramos al nodo, escaparemos el recorrido mediante un retorno prematuro
    while (!colaNodos.Vacio())
    {
        // Siempre obtendremos el nodo encolado más antigüamente (de primero)
        Nodo nodoActual = colaNodos.Desencolar();

        // Si resulta ser un nodo con la etiqueta que buscamos, lo retornaremos
        if (arbol.Etiqueta(nodoActual) == etiqueta)
            return nodoActual;

        // Ahora encolaremos todos sus hijos
        for (Nodo hijoActual = arbol.HijoMasIzquierdo(nodoActual); hijoActual != NodoNulo; hijoActual = arbol.HermanoDerecho(hijoActual))
            colaNodos.Encolar(hijoActual);
    }

    // Si no se encontró un nodo con la etiqueta correspondiente en el árbol, entonces devolveremos nodo nulo
    return NodoNulo;
}

void padre(int elemento, Arbol& arbol)
{
    Nodo nodoHijo = buscarEtiqueta(elemento, arbol);
    Nodo mI = arbol.Padre(nodoHijo);
    std::cout << "Padre de " << elemento << "es " << arbol.Etiqueta(mI) << std::endl;
}

void hermanoDerecho(int etiqueta, Arbol& arbol)
{
    Nodo nodoPadre = buscarEtiqueta(etiqueta, arbol);
    Nodo mI = arbol.HermanoDerecho(nodoPadre);
    std::cout << "Hermano Derecho de " << etiqueta << "es " << arbol.Etiqueta(mI) << std::endl;
}

void hijoMasIzquierdo(int etiqueta, Arbol& arbol)
{
    Nodo nodoPadre = buscarEtiqueta(etiqueta, arbol);
    Nodo mI = arbol.HijoMasIzquierdo(nodoPadre);
    std::cout << "Hijo mas Izquiedo de " << etiqueta << "es " << arbol.Etiqueta(mI) << std::endl;
}

void borrarHoja(int valorBorrado, Arbol& arbol)
{
    Nodo borrado = buscarEtiqueta(valorBorrado, arbol);
    arbol.BorrarHoja(borrado);
    imprimirArbol(arbol);
}

void agregarHijo(int etiqueta, int etiquetaHijo, Arbol& arbol)
{
    Nodo nodoPadre = buscarEtiqueta(etiqueta, arbol);
    arbol.AgregarHijo(etiquetaHijo, nodoPadre);
    imprimirArbol(arbol);
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
                {
                    std::cout << "Cual elemento quiere encolar ?" << std::endl;
                    int elemento;
                    std::cin >> elemento;
                    cola.Encolar(elemento);
                    break;
                }

            case 1: // desencolar
                {
                    int elem = cola.Desencolar();
                    std::cout << "El elemento desencolado es: " << elem << std::endl;
                    break;
                }
                

            case 2: // numElem
                {
                    std::cout << cola.NumElem() << std::endl;
                    break;
                }

            case 3: // vaciar
                {
                    cola.vaciar();
                    std::cout << "se vacio correctamente la cola" << std::endl;
                    break;
                }
                

            case 4: // vacio (devuelve un bool)
                {
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
                }

            case 5: // salir
                {
                    seguir = 0;
                    break;
                }
                

            default:
                break;
            }
        }

        if (respuestaUsuario == 'l')
        {
            std::cout << "\n\n\t ############################# \n"
                      << std::endl;
            std::cout << "Que desea hacer con la lista indexada?" << std::endl;
            std::cout << "0 - insertar etiqueta" << std::endl;
            std::cout << "1 - borrar elemento" << std::endl;
            std::cout << "2 - Modificar indice" << std::endl;
            std::cout << "3 - cantidad de elementos" << std::endl;
            std::cout << "4 - Recuperar" << std::endl;
            std::cout << "5 - Destruir" << std::endl;
            std::cin >> choice;

            ListaIndexada lista;
            switch (choice)
            {
            case 0:
                {
                    std::cout << "Cual valor quiere insertar ?" << std::endl;
                    int valor;
                    std::cin >> valor;
                    std::cout << "A que indice ?" << std::endl;
                    int indice;
                    std::cin >> indice;
                    lista.insertar(valor, indice);
                    break;
                }

            case 1:
                {
                    std::cout << "Cual indice quiere borrar ?" << std::endl;
                    int valor;
                    std::cin >> valor;
                    lista.borrar(valor);
                    break;
                }

            case 2:
                {
                    std::cout << "Cual valor quiere insertar ?" << std::endl;
                    int valor;
                    std::cin >> valor;
                    std::cout << "A que indice ?" << std::endl;
                    int indice;
                    std::cin >> indice;
                    lista.modificar(valor, indice);
                    break;
                }
                

            case 3:
                {
                    std::cout << "Cantidad de elementos" << lista.numElem() << std::endl;
                    break;
                }
               

            case 4:
                {
                    std::cout << "Cual indice quiere recuperar?" << std::endl;
                    int valor;
                    std::cin >> valor;
                    lista.recuperar(valor);
                    break;    
                }

            case 5: // imprimir
                {
                    seguir = 0;
                    break;
                }

            case 6:
                {
                    lista.imprimir();
                    break;
                }

            default:
                break;
            }
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
                imprimirArbol(arbol);
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