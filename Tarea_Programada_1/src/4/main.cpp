#include "Controlador.hpp"

/**
 * @brief Muestra la etiqueta del hermano derecho del nodo con cierta etiqueta particular. No modifica nada.
 * @param etiqueta Etiqueta del nodo al cual se le quiere imprimir la etiqueta del hermano derecho
 * @param arbol Árbol en el cuál buscar los nodos
 * @remark Tanto el árbol como la etiqueta deben estar inicializados. Debe existir al menos un nodo con la etiqueta en el árbol.
 */
void hermanoDerecho(int etiqueta, Arbol &arbol)
{
    // Solicitamos al nodo con la etiqueta particular
    Nodo nodoPadre = buscarEtiqueta(etiqueta, arbol);
    Nodo mI = arbol.HermanoDerecho(nodoPadre);

    if(mI!= Nodo()){
        std::cout << "Hermano Derecho de " << etiqueta << "es " << arbol.Etiqueta(mI) << std::endl;
    }else{
        std::cout<< "No tiene hermano derecho" << std::endl;
    }
}

/**
 * @brief Muestra al usuario el hijo mas izquierdo de un nodo cual etiqueta es dada, la función no modifica nada
 * @param etiqueta es de tipo entero, es la etiqueta del nodo del cual queremos conocer el hijo mas izquierdo, la etique debe existir en el arbol
 * @param arbol es el Arbol en el cual debemos buscar el hijo mas izquierdo de la etiqueta dada
 * @remark la función requiere que ambos parametros existan, y que exista un Nodo en el arbol que tenga como etiqueta "etiqueta"
 */
void hijoMasIzquierdo(int etiqueta, Arbol &arbol)
{
    Nodo nodoPadre = buscarEtiqueta(etiqueta, arbol);
    Nodo mI = arbol.HijoMasIzquierdo(nodoPadre);
    std::cout << "Hijo mas Izquiedo de " << etiqueta << "es " << arbol.Etiqueta(mI) << std::endl;
}

/**
 * @brief Borra la hoja del arbol que tengo como etiqueta el entero valorBorrado, la funcion modifica el arbol
 * @param valorBorrado es un entero, es la etiqueta de la hoja que se requiere borrar
 * @param arbol es el Arbol del cual queremos borrar una hoja
 * @remark la función requiere que valorBorrado pertenezca al arbol, y que sea una hoja
 */
void borrarHoja(int valorBorrado, Arbol &arbol)
{
    Nodo borrado = buscarEtiqueta(valorBorrado, arbol);
    arbol.BorrarHoja(borrado);
    imprimirArbol(arbol);
}

/**
 * @brief Agrega un Nodo al arbol con una etiqueta igual a etiquetaHijo y con un padre con la etiqueta "etiqueta", la función modifica el arbol
 * @param etiqueta es un entero, es la etiqueta del Nodo al cual queremos agregar un hijo, la funcion requiere que exista un Nodo en el arbol con esta etiqueta
 * @param etiqueHijo es un entero, es la etique del Nodo que agregamos al arbol
 * @param arbol es de tipo Arbol, se requiere que sea inicializado, y que tenga por lo menos la raiz puesta
 * @remark la función requiere que el arbol tenga una raiz valida (no nula) y que tengo un Nodo con la etiqueta "etiqueta"
 */
void agregarHijo(int etiqueta, int etiquetaHijo, Arbol &arbol)
{
    Nodo nodoPadre = buscarEtiqueta(etiqueta, arbol);
    arbol.AgregarHijo(etiquetaHijo, nodoPadre);
    imprimirArbol(arbol);
}

/**
 * @brief Modifica la etiqueta dada por la nueva etiqueta, la función modifica el arbol
 * @param etiquetaVieja es de tipo entero, es la etiqueta del nodo del cual queremos cambiar la etiqueta
 * @param nuevaEtiqueta es detipo entero, es el nuevo valor de la etiqueta del cual queremos cambiar el valor 
 * @param arbol es de tipo Arbol, debe ser inicializado y no vacio
 * @remark la función requiere que exista un Nodo en el arbol con una etiqueta igual a etiquetaVieja
 */
void modificaEtiqueta(int etiquetaVieja, int nuevaEtiqueta, Arbol &arbol)
{
    Nodo modificado = buscarEtiqueta(etiquetaVieja, arbol);
    arbol.ModificaEtiqueta(nuevaEtiqueta, modificado);
}

/**
 * @brief Muestra cuantos nodos existe en un nivel dado del arbol
 * @param arbol es de tipo Arbol, debe contener al nodo subraiz
 * @param subraiz es de tipo Nodo, cambia para cada llamado recursivo
 * @param level es de tipo entero, sirve como caso base para la recursividad
 * @remark la función requiere que el arbol sea inicializado, y que existe el level dado en el arbol
 * Se indizan a partir de 0 (raíz) a n-1 (con n = altura del árbol)
 */
void imprimirNodosEnNivel(Arbol &arbol, Nodo subraiz, int nivel)
{
    // Caso base: Nivel 0. La sub-raiz. Es el único nodo con su propio nivel
    if (nivel == 0)
    {
        std::cout << arbol.Etiqueta(subraiz);
        return;
    }

    Nodo child = arbol.HijoMasIzquierdo(subraiz);
    const Nodo &NodoNulo = Nodo();

    // Caso base: Nivel 1. La hijos de la sub-raíz. Son los únicos en este nivel (no tienen primos)
    if (nivel == 1)
    { 
        while (child != NodoNulo)
        {
            std::cout << arbol.Etiqueta(child) << ", ";
            child = arbol.HermanoDerecho(child);
        }
    }
    // Caso base: Nivel > 1. Los descendientes de la sub-raiz. Necesitamos considerar a los sub-árboles de los hijos inmediatos a la sub-raíz
    else
    {
        // Sí consideraremos a cada sub-árbol de los hijos inmediatos, pero en cada uno consideraremos una profundidad de un nivel menor
        while (child != NodoNulo)
        {
            imprimirNodosEnNivel(arbol, child, nivel - 1);
            child = arbol.HermanoDerecho(child);
        }
    }
}

/**
 * @brief Borra un subarbol que tiene como raiz el Nodo subraiz dado, la función modifica el arbol
 * @param arbol es de tipo Arbol, debe ser inicializado y no vacio, y debe contener al nodo subraiz
 * @param subraiz es de tipo Nodo, debe existir en el arbol, y ser inicializado
 * @remark la funcion requiere que el Nodo subroot exista en el arbol dado
 */
void borrarSubArbol(Arbol &arbol, Nodo subraiz)
{
    // Vamos a desplazarnos por los nodos de cada nivel usando una cola
    // Cada vez que visitemos un nodo, añadiremos sus hijos a la cola
    // La cola se llena con los nodos hijos de los que hemos visitado
    // Finalmente, cuanto todos los nodos han sido visitados, borramos la cola
    Util::Cola<Nodo> cola;
    
    // Vamos a eliminar los nodos usando una lista como si fuera una "pila"
    // Cada vez que visitamos un nodo, lo añadimos a la "pila"
    // La "pila" se llena en orden inverso al que añadimos los nodos
    // Finalmente, cuando todos los nodos fueron añadidos, los borramos en orden inverso al de agregado
    ListaIndexada pilaBorrado;

    // El desplazamiento del arbol empieza en la raiz
    cola.Encolar(subraiz);

    // Podemos empezar a movernos por el arbol, siempre y cuando haya nodos pendientes por visitar
    while (!cola.Vacio())
    {
        // Vamos a extraer el ultimo nodo de la cola
        Nodo visitedNode = cola.Desencolar();

        // El elemento ha sido vistado, lo añadimos a la pila
        // Siempre tomaremos 0 como el inicio de la "pila"
        pilaBorrado.insertar(arbol.Etiqueta(visitedNode), 0);

        // Consideremos sus hijos para un viaje futuro
        const Nodo &NodoNulo = Nodo();
        for (Nodo visitedChildren = arbol.HijoMasIzquierdo(visitedNode); visitedChildren != NodoNulo; visitedChildren = arbol.HermanoDerecho(visitedChildren))
            cola.Encolar(visitedChildren);

        // Todo esta hecho por esta iteracion 
    }

    // Todo el arbol ha sido visitado y sus nodos puestos en la pila
    // Ahora podemos borrar los nodos en el orden que los agregamos
    int i = 0;
    while (i++ < pilaBorrado.numElem())
    {
        //Esta garantizado que el elemento tope del stack es una hoja
        int valorHojaActual = pilaBorrado.recuperar(0);
        std::cout << "Se va a borrar a " << pilaBorrado.recuperar(0) << std::endl;
        pilaBorrado.borrar(0);
        // Esta garantizado que vamos a borrar el ultimo hijo primero, y luego sus hijos
        // Despues de borrar todos sus hijos, esta garantizado que el padre se vuelve una hoja
        borrarHoja(valorHojaActual, arbol);

        // La ultima hoja del arbol en la pila ha sido borrado
        // Vamos a sacarlo de la pila y llevarlo hasta la siguiente hoja en la proxima iteracion
    }
    // Todo esta hecho
}

/**
 * @brief crea un arbol y despues lo imprime
 * @param i esde tipo entero, debe contener un valor valido
 * @param k es de tipo entero, debe contener un valor valido
 * @param L es de tipo ListaIndexada, debe ser inicializado
 * @param myTree es de tipo Arbol, debe ser inicializado
 * @remark la funcion requiere que i y k sean valores validos, y que la lista y el arbol sean inicializados y validos
 */
void crearArbol(int i, int k, ListaIndexada &L, Arbol &myTree)
{

    // se asuma que el arbol es vacio salvo si especificado de lo contrario

    // Primera condición: por lo menos un nivel y un hijo por nivel
    if (i > 0 && k > 0)
    {
        // ya que el arbol tiene por lo menos un nivel, por lo menos un hijo por nivel, entonces hay una raiz
        myTree.PonerRaiz(L.recuperar(0));

        // Segunda condición: por lo menos 2 niveles
        if (i > 1)
        {
            // Ademas de la primeras condicion, ya que el arbol tiene por lo menos 2 niveles, debemos considerar si sus hijos son padres tambien
            Util::Cola<Nodo> parentNodesQueue;
            parentNodesQueue.Encolar(myTree.Raiz());

            int numNodesTotal = (pow(k, i) - 1) / (k - 1); // La cantidad total de nodos  a agregar en el arbol despues que sea completamente construido
            int numNodesLastLevel = pow(k, i - 1);         // la cantidad de nodos esperados en el ultimo nivel del arbol
            int numNodesAdded = 1;                         // La cantidad de nodos añadidos hasta ahora, la raiz es un nodo asi que llevamos uno 
            std::cout << "Valor de i " << i << std::endl;
            std::cout << "Valor de k " << k << std::endl;
            std::cout << "Valor de Total " << numNodesTotal << std::endl;
            std::cout << "Valor de ultimo nivel " << numNodesLastLevel << std::endl;

            //Vamos a añadir nodos hijos a todos los niveles menos el ultimo. No hay necesidad de añadirselo al ultimo 
            {
                // El padre al que agregarle un hijo 
                // La cantidad de hijos po padre ya se conoce. Podemos producirla 
                Nodo padre = parentNodesQueue.Desencolar();
                for (int numChildAdded = 0; numChildAdded < k; ++numChildAdded)
                {
                    // Es una precondicion de esta funcion en el que se nos garantiza un valor en la lista por cada nodo en el arbol 
                    Nodo newChild = myTree.AgregarHijo(L.recuperar(numNodesAdded), padre);
                    ++numNodesAdded;

                    std::cout << "\tNEW CH = " << myTree.Etiqueta(newChild) << std::endl;
                    // Cada vez que poduzcamos un nuevo hijo, se puede considerar como un padre que valdria la pena visitar despues
                    // Aunque, esta consideracion solo se puede hacer si no hemos alcanzado el ultimo nivel del arbol 
                    if (numNodesTotal - numNodesAdded >= numNodesLastLevel)
                    {
                        parentNodesQueue.Encolar(newChild);
                    }
                }
            }
            // Terminamos de visitar los padres. Ahora podemos liberar la memoria
        }
    }

    // El arbol esta lista, lo podemos imprimir a este punto
    imprimirArbol(myTree);
}

/**
 * @brief Contiene el menu principal que permite comunicar con el usuario
 * @return el metodo devuelve un 0 al final de se ejecución
 */
int main()
{
    //ListaIndexada lista;
    Arbol arbol;
    Controlador controlador; 
    //Cola<int> cola(10000);

    std::cout << "Bienvenid@ ! Inserta [i] para inicializar un arbol vacio, sino inserta [q] para salir del programa" << std::endl;
    char respuestaUsuario;
    std::cin >> respuestaUsuario;

    int choice;
    int seguir = 0;

    if (respuestaUsuario == 'i')
    {
        seguir = 1;
        //std::cout << "Si quiere inicializar una Cola vacia, digita [c] \nSi quiere inicializar una Lista indexada vacia, digita [l] \nSi quiere inicializar un arbol n-ario, digita [a]" << std::endl;
        //std::cin >> respuestaUsuario;
    }

    while (seguir)
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
            std::cout << "6 - HijoMasIzquierdo" << std::endl;
            std::cout << "7 - HermanoDerecho" << std::endl;
            std::cout << "8 - padre" << std::endl;
            std::cout << "9 - modificar etiqueta" << std::endl;
            std::cout << "10 - numNodos" << std::endl;
            std::cout << "11 - Listar por niveles" << std::endl;
            std::cout << "12 - Listar por preorden" << std::endl;
            std::cout << "13 - Etiquetas en un nivel" << std::endl;
            std::cout << "14 - Eliminar arbol a partir de un nodo" << std::endl;
            std::cout << "15 - Crear un arbol en base a una lista" << std::endl;
            std::cout << "16 - Veriricar si un nodo existe en el árbol" << std::endl;
            std::cout << "17 - Averiguar profundidad de un nodo " << std::endl;
            std::cout << "18 - Averiguar etiquetas repetidas" << std::endl;
            std::cout << "19 - Hermano Izquierdo de un nodo" << std::endl;
            std::cout << "20 - Cantidad de niveles (preorden)" << std::endl;
            std::cout << "21 - Cantidad de niveles (por niveles)" << std::endl;
            
            std::cin >> choice;

            switch (choice)
            {
            case 0: // cambiar raiz (vital al inicializar el arbol)
            {
                std::cout << "Cual valor quiere poner a la raiz ?" << std::endl;
                int valorRaiz;
                std::cin >> valorRaiz;
                arbol.PonerRaiz(valorRaiz);
                break;
            }
            case 1: // agregar hijo
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

            case 2: // borrar hoja
            {
                std::cout << "Cual valor quiere borrar del arbol ?" << std::endl;
                int etiquetaBorrada;
                std::cin >> etiquetaBorrada;
                controlador.borrarHoja(etiquetaBorrada, arbol);
                break;
            }
            case 3: // imprimir el arbol
            {
                controlador.imprimirArbol(arbol);
                break;
            }
            case 4: // get raiz
            {
                std::cout << arbol.Etiqueta(arbol.Raiz()) << std::endl;
            }
            break;
            case 5: // salir y destruir arbol
            {
                seguir = 0;
                break;
            }
            case 6: // hijo izq
            {
                std::cout << "Cual valor del padre ?" << std::endl;
                int valor;
                std::cin >> valor;
                controlador.hijoMasIzquierdo(valor, arbol);
                break;
            }

            case 7: // hermano derecho
            {
                std::cout << "Cual valor del hermano ?" << std::endl;
                int valor;
                std::cin >> valor;
                controlador.hermanoDerecho(valor, arbol);
                break;
            }
            case 8: // padre
            {
                std::cout << "Cual valor del hijo ?" << std::endl;
                int valor;
                std::cin >> valor;
                controlador.padre(valor, arbol);
                break;
            }
            case 9:
            {
                std::cout << "Cual valor quiere modificar del arbol ?" << std::endl;
                int etiquetaModificada;
                std::cin >> etiquetaModificada;
                std::cout << "Cual es el nuevo valor ?" << std::endl;
                int etiqueta;
                std::cin >> etiqueta;
                controlador.modificaEtiqueta(etiquetaModificada, etiqueta, arbol);
                break;
            }
            case 10: // num Nodos
            {
                std::cout << "Num Nodos :" << arbol.NumNodos() << std::endl;
                break;
            }
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
                Nodo subroot = buscarEtiqueta(valor, arbol);
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
                int i;
                int k;
                int cantidad;
                if (eleccion == 1)
                {

                    std::cout << "Niveles" << std::endl;
                    std::cin >> i;
                    std::cout << "Hijos por nivel" << std::endl;
                    std::cin >> k;
                    cantidad = (pow(k, i) - 1) / (k - 1);

                    for (int j = 0; j < cantidad; j++)
                    {
                        list.insertar(j, j);
                    }
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
                //averiguarProfundidadNodo
                
            }
            break;
            case 18:
            {
                //averiguarEtiquetasRepetidas
            }
            case 19:
            {
                //Hermano izquierdo
            }
            break;
            case 20:
            {
                //Hermano izquierdo
            }
            break;
            case 21:
            {
                //Hermano izquierdo
            }
            break;
            default:
                break;
            }
            
    }

    return 0;
}