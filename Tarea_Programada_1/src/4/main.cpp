#include "Controlador.hpp"

/**
 * @brief Contiene el menu principal que permite comunicar con el usuario
 * @return El método devuelve un 0 al final de se ejecución
 */
int main()
{
    // ListaIndexada lista;
    // Cola<int> cola(10000);
    Arbol arbol;

    Controlador controlador;

    std::cout << "Bienvenid@ ! Inserta [i] para inicializar un arbol vacio, sino inserta [q] para salir del programa" << std::endl;
    int seguir = 0;

    char respuestaUsuario;
    while (seguir == 0)
    {
        std::cin >> respuestaUsuario;

        if(respuestaUsuario == 'q')
        {
            std::cout << "Cerrando programa. Bye bye!" << std::endl;
            return 0;
        }

        else if (respuestaUsuario == 'i')
        {
            std::cout << "Abriendo menu" << std::endl;
            seguir = 1;
        }

        else
            std::cout << "Opcion invalida. Por favor ingrese otra" << std::endl;
    }

    int choice;
    while (seguir)
    {
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        std::cout << "Que desea hacer con el arbol n-ario?" << std::endl;
        std::cout << "0 - Cambiar raiz (vital al inicializar el arbol)" << std::endl;
        std::cout << "1 - Agregar hijo" << std::endl;
        std::cout << "2 - Borrar hoja" << std::endl;
        std::cout << "3 - Imprimir el arbol" << std::endl;
        std::cout << "4 - Get raiz" << std::endl;
        std::cout << "5 - Salir y destruir el arbol" << std::endl;
        std::cout << "6 - HijoMasIzquierdo" << std::endl;
        std::cout << "7 - HermanoDerecho" << std::endl;
        std::cout << "8 - Padre" << std::endl;
        std::cout << "9 - Modificar etiqueta" << std::endl;
        std::cout << "10 - NumNodos" << std::endl;
        std::cout << "11 - Listar por niveles" << std::endl;
        std::cout << "12 - Listar por preorden" << std::endl;
        std::cout << "13 - Etiquetas en un nivel" << std::endl;
        std::cout << "14 - Eliminar arbol a partir de un nodo" << std::endl;
        std::cout << "15 - Crear un arbol en base a una lista" << std::endl;
        std::cout << "16 - Verificar si un nodo existe en el árbol" << std::endl;
        std::cout << "17 - Averiguar profundidad de un nodo " << std::endl;
        std::cout << "18 - Averiguar etiquetas repetidas" << std::endl;
        std::cout << "19 - Hermano Izquierdo de un nodo" << std::endl;
        std::cout << "20 - Cantidad de niveles (preorden)" << std::endl;
        std::cout << "21 - Cantidad de niveles (por niveles)" << std::endl;

        std::cin >> choice;

        switch (choice)
        {
        case 0:
            {
                std::cout << "Cual valor quiere poner a la raiz?" << std::endl;
                int valorRaiz;
                std::cin >> valorRaiz;
                arbol.PonerRaiz(valorRaiz);
            }
        break;
        case 1:
            {
                std::cout << "Valor del padre" << std::endl;
                int valorP;
                std::cin >> valorP;
                std::cout << "Valor a insertar" << std::endl;
                int valor;
                std::cin >> valor;
                controlador.agregarHijo(valorP, valor, arbol);
            }
        break;
        case 2:
            {
                std::cout << "Cual valor quiere borrar del arbol?" << std::endl;
                int etiquetaBorrada;
                std::cin >> etiquetaBorrada;
                controlador.borrarHoja(etiquetaBorrada, arbol);
            }
        break;
        case 3:
            {
                controlador.imprimirArbol(arbol);
            }
        break;
        case 4:
            {
                std::cout << arbol.Etiqueta(arbol.Raiz()) << std::endl;
            }
        break;
        case 5:
            {
                seguir = 0;
            }
        break;
        case 6:
            {
                std::cout << "Cual valor del padre?" << std::endl;
                int valor;
                std::cin >> valor;
                controlador.hijoMasIzquierdo(valor, arbol);
            }
        break;
        case 7:
            {
                std::cout << "Cual valor del hermano?" << std::endl;
                int valor;
                std::cin >> valor;
                controlador.hermanoDerecho(valor, arbol);
            }
        break;
        case 8:
            {
                std::cout << "Cual valor del hijo?" << std::endl;
                int valor;
                std::cin >> valor;
                controlador.padre(valor, arbol);
            }
        break;
        case 9:
            {
                std::cout << "Cual valor quiere modificar del arbol?" << std::endl;
                int etiquetaModificada;
                std::cin >> etiquetaModificada;
                std::cout << "Cual es el nuevo valor?" << std::endl;
                int etiqueta;
                std::cin >> etiqueta;
                controlador.modificaEtiqueta(etiquetaModificada, etiqueta, arbol);
            }
        break;
        case 10:
            {
                std::cout << "Num Nodos :" << arbol.NumNodos() << std::endl;
            }
        break;
        case 11:
            {
                controlador.listarPorNiveles(arbol);
            }
        break;
        case 12:
            {
                controlador.listarPorPreorden(arbol, arbol.Raiz());
            }
        break;
        case 13:
            {
                std::cout << "Que nivel desea conocer?" << std::endl;
                int nivel;
                std::cin >> nivel;
                controlador.imprimirNodosEnNivel(arbol, arbol.Raiz(), nivel - 1);
            }
        break;
        case 14:
            {
                std::cout << "A partir de que valor desea borrar?" << std::endl;
                int valor;
                std::cin >> valor;
                Nodo subroot = controlador.buscarEtiqueta(valor, arbol);
                controlador.borrarSubArbol(arbol, subroot);
            }
        break;
        case 15:
            {
                int eleccion;
                std::cout << "Desea general una lista o que esta sea generada automaticamente? \n 1 - Auto \n 2 - Manual " << std::endl;
                std::cin >> eleccion;

                ListaIndexada list;
                int conformidad = 2;
                int i, k, cantidad;
                if (eleccion == 1)
                {
                    std::cout << "Niveles" << std::endl;
                    std::cin >> i;
                    std::cout << "Hijos por nivel" << std::endl;
                    std::cin >> k;
                    cantidad = (pow(k, i) - 1) / (k - 1);

                    for (int j = 0; j < cantidad; j++)
                        list.insertar(j, j);
                    
                    controlador.crearArbol(i, k, list, arbol);
                }
                else
                {
                    do
                    {

                        std::cout << "Niveles" << std::endl;
                        std::cin >> i;
                        std::cout << "Hijos por nivel" << std::endl;
                        std::cin >> k;
                        cantidad = (pow(k, i) - 1) / (k - 1);

                        std::cout << "Para un arbol de " << i << " niveles y " << k << " hijos, debera insertar " << cantidad << " elementos manualmente. \n Esta de acuerdo? \n 1 - Si \n 2 - reingresar valores \n 3 salir del metodo" << std::endl;
                        std::cin >> conformidad;

                    } while (conformidad == 2);
                }
                if (conformidad == 1)
                {

                    for (int j = 0; j < cantidad; j++)
                    {
                        int elemento;
                        std::cout << "Inserte un elemento" << std::endl;
                        std::cin >> elemento;
                        list.insertar(elemento, j);
                    }

                    controlador.crearArbol(i, k, list, arbol);
                }
            }
        break;
        case 16:
            {
                int elemento;
                std::cout << "Inserte un elemento" << std::endl;
                std::cin >> elemento;
                Nodo nodoDondeEtiqueta = controlador.buscarEtiqueta(elemento, arbol);

                if (nodoDondeEtiqueta == Nodo())
                    std::cout << "Nodo NO existe en el árbol" << std::endl;
                else
                    std::cout << "Nodo SÍ existe en el árbol" << std::endl;
            }
        break;
        case 17:
            {
                int elemento;
                std::cout << "Cual es la etiqueta del nodo del cual quiere conocer la profundidad?" << std::endl;
                std::cin >> elemento;
                Nodo nodo = controlador.buscarEtiqueta(elemento, arbol);
                int profundidad = controlador.averiguarProfundidadNodo(arbol, nodo);
                std::cout << "La profundidad de la etiqueta " << elemento << " es de: " << profundidad << std::endl;
            }
        break;
        case 18:
            {
                bool repetidas = controlador.averiguarEtiquetasRepetidas(arbol);

                if (repetidas != 0)
                    std::cout << "Hay etiquetas repetidas en el arbol" << std::endl;
                
                else
                    std::cout << "No hay etiquetas repetidas en el arbol" << std::endl;
            }
        break;
        case 19:
            {
                // Hermano izquierdo
                int elemento;
                std::cout << "Cual es la etiqueta del nodo del cual quiere conocer el hermano izquierdo?" << std::endl;
                std::cin >> elemento;

                Nodo hermanoDerecho = controlador.buscarEtiqueta(elemento, arbol);
                Nodo nodo = controlador.averiguarHermanoIzquierdo(hermanoDerecho, arbol);

                Nodo nodoNulo = Nodo();
                if(nodo != nodoNulo)
                {
                    int etiquetaHermanoIzquierdo = arbol.Etiqueta(nodo);
                    std::cout << "El hermano izquierdo de " << elemento << " es: " << etiquetaHermanoIzquierdo << std::endl;
                }
                else
                    std::cout << "La etiqueta " << elemento << " no tiene hermano izquierdo" << std::endl;
                
            }
        break;
        case 20:
            {
                size_t nivelesPPO = controlador.nivelesArbolRPO(arbol, arbol.Raiz());
                std::cout << "Tras recorrer en preorden, hay " << nivelesPPO << " niveles " << std::endl;
            }
        break;
        case 21:
            {
                size_t nivelesRPN = controlador.nivelesArbolRPN(arbol);
                std::cout << "Tras recorrer en por niveles, hay " << nivelesRPN << " niveles" << std::endl;
            }
        break;
        default:
            {
                std::cout << "Opcion invalida, por favor ingrese otra" << std::endl;
            }
            break;
        }
    }

    return 0;
}
