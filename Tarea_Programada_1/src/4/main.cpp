#include <chrono>
#include <iomanip>
#include "Controlador.hpp"
#include "Ensayos.hpp"

/**
 * @brief Contiene el menu principal que permite comunicar con el usuario
 * @return El metodo devuelve un 0 al final de se ejecucion
 */
int menu()
{
    // ListaIndexada lista;
    // Cola<int> cola(10000);
    Arbol arbol;

    std::cout << "Bienvenid@ ! Inserta [i] para inicializar un arbol vacio, sino inserta [q] para salir del programa" << std::endl;
    int seguir = 0;

    char respuestaUsuario;
    while (seguir == 0)
    {
        std::cin >> respuestaUsuario;

        if (respuestaUsuario == 'q')
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
        std::cout << "16 - Verificar si un nodo existe en el arbol" << std::endl;
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
            Controlador::agregarHijo(valorP, valor, arbol);
        }
        break;
        case 2:
        {
            std::cout << "Cual valor quiere borrar del arbol?" << std::endl;
            int etiquetaBorrada;
            std::cin >> etiquetaBorrada;
            Controlador::borrarHoja(etiquetaBorrada, arbol);
        }
        break;
        case 3:
        {
            Controlador::imprimirArbol(arbol);
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
            Controlador::hijoMasIzquierdo(valor, arbol);
        }
        break;
        case 7:
        {
            std::cout << "Cual valor del hermano?" << std::endl;
            int valor;
            std::cin >> valor;
            Controlador::hermanoDerecho(valor, arbol);
        }
        break;
        case 8:
        {
            std::cout << "Cual valor del hijo?" << std::endl;
            int valor;
            std::cin >> valor;
            Controlador::padre(valor, arbol);
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
            Controlador::modificaEtiqueta(etiquetaModificada, etiqueta, arbol);
        }
        break;
        case 10:
        {
            std::cout << "Num Nodos :" << arbol.NumNodos() << std::endl;
        }
        break;
        case 11:
        {
            Controlador::listarPorNiveles(arbol);
        }
        break;
        case 12:
        {
            Controlador::listarPorPreorden(arbol, arbol.Raiz());
        }
        break;
        case 13:
        {
            std::cout << "Que nivel desea conocer?" << std::endl;
            int nivel;
            std::cin >> nivel;
            Controlador::imprimirNodosEnNivel(arbol, arbol.Raiz(), nivel - 1);
        }
        break;
        case 14:
        {
            std::cout << "A partir de que valor desea borrar?" << std::endl;
            int valor;
            std::cin >> valor;
            Nodo subroot = Controlador::buscarEtiqueta(valor, arbol);
            Controlador::borrarSubArbol(arbol, subroot);
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

                Controlador::crearArbol(i, k, list, arbol);
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

                Controlador::crearArbol(i, k, list, arbol);
            }
        }
        break;
        case 16:
        {
            int elemento;
            std::cout << "Inserte un elemento" << std::endl;
            std::cin >> elemento;
            Nodo nodoDondeEtiqueta = Controlador::buscarEtiqueta(elemento, arbol);

            if (nodoDondeEtiqueta == Nodo())
                std::cout << "Nodo NO existe en el arbol" << std::endl;
            else
                std::cout << "Nodo SI existe en el arbol" << std::endl;
        }
        break;
        case 17:
        {
            int elemento;
            std::cout << "Cual es la etiqueta del nodo del cual quiere conocer la profundidad?" << std::endl;
            std::cin >> elemento;
            Nodo nodo = Controlador::buscarEtiqueta(elemento, arbol);
            int profundidad = Controlador::averiguarProfundidadNodo(arbol, nodo);
            std::cout << "La profundidad de la etiqueta " << elemento << " es de: " << profundidad << std::endl;
        }
        break;
        case 18:
        {
            bool repetidas = Controlador::averiguarEtiquetasRepetidas(arbol);

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

            Nodo hermanoDerecho = Controlador::buscarEtiqueta(elemento, arbol);
            Nodo nodo = Controlador::averiguarHermanoIzquierdo(hermanoDerecho, arbol);

            Nodo nodoNulo = Nodo();
            if (nodo != nodoNulo)
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
            size_t nivelesPPO = Controlador::nivelesArbolRPO(arbol, arbol.Raiz());
            std::cout << "Tras recorrer en preorden, hay " << nivelesPPO << " niveles " << std::endl;
        }
        break;
        case 21:
        {
            size_t nivelesRPN = Controlador::nivelesArbolRPN(arbol);
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

int viejo()
{
    // Arbol
    Arbol arbol = Arbol();
    size_t cantidadNiveles = 4;
    size_t anchoPorNivel = 2;
    size_t cantidadNodos = (pow(anchoPorNivel, cantidadNiveles) - 1) / (anchoPorNivel - 1);
    size_t cantidadHijosRaiz = 5; // para crearArbolHijoCortoHijoLargo
    size_t cantidadNodosHijoCortoHijoLargo = 100;

    std::cout << "~~~~~~~~~~~~~~PARAMETROS~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "Nodos = " << cantidadNodos << std::endl;
    std::cout << "Niveles = " << cantidadNiveles << std::endl;
    std::cout << "Anchura por nivel = " << anchoPorNivel << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

    // Reloj
    std::chrono::high_resolution_clock clock;

    // Lista de nodos
    ListaIndexada lista;
    for (size_t j = 0; j < cantidadNodos; j++)
        lista.insertar(j, j);

    // Medir duración
    auto start = clock.now();                                               // Iniciar reloj
    //Controlador::crearArbolHijoCortoHijoLargo(cantidadNodosHijoCortoHijoLargo, cantidadHijosRaiz, arbol); // Codigo que queremos medir
    auto finish = clock.now();                                             // Terminar reloj

    // Calcular duración
    auto duracionNano = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);
    auto duracionMicro = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
    auto duracionMili = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    auto duracionSeg = std::chrono::duration_cast<std::chrono::seconds>(finish - start);
    auto duracionMin = std::chrono::duration_cast<std::chrono::minutes>(finish - start);

    //  Anunciar duración
    std::cout << "~~~~~~~~~~~~~~~~DURACION~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "Duracion (nanosegundos):\t" << std::setprecision(5) << std::scientific << (double) duracionNano.count() << std::endl;
    std::cout << "Duracion (microsegundos):\t" << std::setprecision(5) << std::scientific << (double) duracionMicro.count() << std::endl;
    std::cout << "Duracion (milisegundos):\t" << std::setprecision(5) << std::scientific << (double) duracionMili.count() << std::endl;
    std::cout << "Duracion (segundos):\t" << std::setprecision(5) << std::scientific << (double) duracionSeg.count() << std::endl;
    std::cout << "Duracion (minutos):\t" << std::setprecision(5) << std::scientific << (double) duracionMin.count() << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

    // Visualizar árbol
    std::cout << "~~~~~~~~~~~~~~~~~~ARBOL~~~~~~~~~~~~~~~~~~" << std::endl;
    Controlador::imprimirArbol(arbol);
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

    // Ordenes de duración sugeridos por Fer
    // 960800 7 8      1398101  4 11             //Orden 1M          -39200      +398101
    // 97656 5 8       111111   10 6            //Orden 100k         -2344       +11111
    // 9841 3 9                                 //Orden 10k           -159       

    return 0;
}

int main()
{
    // Asociar funciones con hileras de texto
    std::map<std::string, FuncionPrueba> funciones;
    funciones["Crear Hijo Corto Hijo Largo"] = Ensayos::crearArbolHijoCortoHijoLargo;
    funciones["Crear Altura Extrema"] = Ensayos::crearArbolAlturaExtrema;
    funciones["Crear Anchura Extrema"] = Ensayos::crearArbolAnchuraExtrema;
   // funciones["Crear Normal"] = Ensayos::crearArbol;
    funciones["Borrar Sub"] = Ensayos::borrarSubarbol;

    // Generar pruebas en el ensayo
    Ensayos miniEnsayo(funciones, std::cin);

    // Ejecutar pruebas
    miniEnsayo.ejecutarPruebas();

    // Imprimir pruebas
    miniEnsayo.imprimirPruebas();

    return 0;
}