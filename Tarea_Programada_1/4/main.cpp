//#include "Tree_senaladorPadre.h"          // 3.1
//#include "ArbolLH.h"                      // 3.2
//#include "Arbol.cpp"                      // 3.3
//#include "treePunteroPadreNoContador.h"   // 3.4
//#include "tree5.h"                        // 3.5
#include <iostream>

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
            // switch de cola
        }

        if (respuestaUsuario == 'l')
        {
        }

        if (respuestaUsuario == 'a')
        {
            std::cout << "\n\n\t ############################# \n"
                      << std::endl;
            std::cout << "Que desea hacer con el arbol n-ario?" << std::endl;
            std::cout << "0 - cambiar raiz (vital al inicializar el arbol)" << std::endl;
            std::cout << "1 - agregar hijo" << std::endl;
            std::cout << "2 - borrar hoja" << std::endl;
            std::cout << "3 - imprimir el arbol" << std::endl;
            std::cout << "4 - get raiz" << std::endl;
            std::cout << "5 - salir y destruir el arbol" << std::endl;
            std::cin >> choice;

            switch (choice)
            {
            case 0: // cambiar raiz (vital al inicializar el arbol)
                /* code */
                break;

            case 1: // agregar hijo
                /* code */
                break;

            case 2: // borrar hoja
                /* code */
                break;

            case 3: // imprimir el arbol
                /* code */
                break;

            case 4: // get raiz
                /* code */
                break;

            case 5: // salir y destruir arbol
                seguir = 0;
                break;

            default:
                break;
            }
        }
    }

    return 0;
}