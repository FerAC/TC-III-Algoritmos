// Incluye utilidades auxiliares
#include <cstddef>         // Para utilizar contadores en recorrido por niveles
#include "../CDE/Cola.hpp" // Cola dinámica para realizar recorrido por niveles
#include <cmath>           // Formula para cantidad de nodos en un nivel

// Include de la Cola
#include "../1/Cola.hpp"

// Include de la Lista Indexada
#include "../2/ListaIndexada.h"

// Include de los Árboles
#include "../3.1/3.1.hpp"
//  #include "../3.2/3.2.hpp"
//  #include "../3.3/3.3.hpp"
// #include "../3.4/3.4.hpp"
// #include "../3.5/3.5.hpp"

// Include para I/O estándar
#include <iostream>

/**
 * @brief la función averiguarHermanoIzquierdo permite encontrar el hermano a la izquierda de un nodo dado, la función no modifica nada
 * @param nodo nodo es de tipo Nodo, es el nodo del cual buscamos el hermano izquierdo, el nodo debe ser inicializado y debe pertenecer al arbol
 * @param arbol arbol es de tipo Arbol, es dado por referencia para economizar memoria, la función requiere que el arbol este inicializado, y que el nodo haga parte del arbol
 * @remark la funcion requiere que ambos parametros sean inicializados y validos
 * @return la función devuelve un Nodo, si existe un hermanoIzquierdo, lo devuelve, sino devuelve NodoNulo
 */
Nodo averiguarHermanoIzquierdo(Nodo nodo, Arbol &arbol)
{
    const Nodo &NodoNulo = Nodo();
    // en ese caso el nodo no tiene hermano izquierdo ya que es la raiz y la raiz no tiene hermano
    if (nodo == arbol.Raiz())
    {
        return NodoNulo;
    }
    
    Nodo nodoPadre = arbol.Padre(nodo);
    Nodo hermanoIzquierdo = arbol.HijoMasIzquierdo(nodoPadre);

    // en ese caso el nodo no tiene hermano izquierdo ya que el mismo es el hijo mas izquierdo
    if(hermanoIzquierdo == nodo){
        return NodoNulo;
    }

    // en ese caso el nodo no es ni el hijo mas izquierdo ni la raiz, por lo tanto tiene un hermano izquierdo
    while (arbol.HermanoDerecho(hermanoIzquierdo) != nodo)
    {
        hermanoIzquierdo = arbol.HermanoDerecho(hermanoIzquierdo);
    }

    return hermanoIzquierdo;
}

/**
 * @brief la función averiguarEtiquetasRepetidas permite verificar si existe varios nodos con la misma etiqueta en el arbol, la funcion crea y modifica al booleano que se devuelve
 * @param arbol arbol es de tipo Arbol, es dado por referencia para economizar memoria, la funcion requiere que el arbol este inicializado
 * @remark la función requiere que el arbol sea inicializado, pero no requiere que el arbol no-este vacio
 * @return la función devuelve 1 si hay etiquetas repetidas, sino devuelve 0
 */
bool averiguarEtiquetasRepetidas(Arbol &arbol)
{

    const Nodo &NodoNulo = Nodo();

    // Caso 1: El árbol tiene raíz nula (no tiene nodos)
    if (arbol.Raiz() == NodoNulo)
        return false;

    // Caso 2: El árbol tiene nodos
    // Realizaremos un recorrido por niveles utilizando una cola de nodos
    Util::Cola<Nodo> colaNodos;
    Util::Cola<Nodo> colaNodosComparados;

    // Encolemos a la raiz para iniciar el recorrido usándola como punto de partida
    colaNodos.Encolar(arbol.Raiz());

    // Nodo nodoComparador = arbol.Raiz();

    // Mientras tengamos nodos en la cola, no hemos terminado el recorrido
    // Si resulta que encontramos al nodo, escaparemos el recorrido mediante un retorno prematuro
    while (!colaNodos.Vacio())
    {
        // Siempre obtendremos el nodo encolado más antigüamente (de primero)
        Nodo nodoActual = colaNodos.Desencolar();
        colaNodosComparados.Encolar(arbol.Raiz());

        // Si resulta ser un nodo con la etiqueta que buscamos, lo retornaremos
        // if (arbol.Etiqueta(nodoActual) == etiqueta)
        while (!colaNodosComparados.Vacio())
        {
            // Siempre obtendremos el nodo encolado más antigüamente (de primero)
            Nodo nodoComparado = colaNodosComparados.Desencolar();

            // si los 2 nodos tienen la misma etiqueta, pero no son el mismo nodo, entonces hay etiqueta(s) repetida(s) en el arbol
            if (arbol.Etiqueta(nodoActual) == arbol.Etiqueta(nodoComparado))
            {
                if (nodoActual != nodoComparado)
                {
                    return 1;
                }
            }

            // Ahora encolaremos todos sus hijos
            for (Nodo hijoActual = arbol.HijoMasIzquierdo(nodoComparado); hijoActual != NodoNulo; hijoActual = arbol.HermanoDerecho(hijoActual))
            {
                colaNodosComparados.Encolar(hijoActual);
            }
        }

        //  return nodoActual;

        // Ahora encolaremos todos sus hijos
        for (Nodo hijoActual = arbol.HijoMasIzquierdo(nodoActual); hijoActual != NodoNulo; hijoActual = arbol.HermanoDerecho(hijoActual))
        {
            colaNodos.Encolar(hijoActual);
        }
    }

    // Si no se encontró un nodo con la etiqueta correspondiente en el árbol, entonces devolveremos nodo nulo
    return 0;
}

/**
 * @brief La función averiguarProfundidadNodo permite verificar a cual profundidad se encuentra en el arbol dado un nodo dado, la función cree y modifica un entero que representa esta profundidad
 * @param arbol arbol es de tipo Arbol, es dado por referencia para economizar memoria, la funcion requiere que el arbol este inicializado y no vacio
 * @param nodo es de tipo Nodo, es el nodo del cual buscamos la profundidad, el nodo debe ser inicializado y debe pertenecer al arbol
 * @remark la función requiere que el arbol sea inicializado, no vacio, y que el nodo sea inicializado y pertenezca al arbol 
 * @return la función devuelve un entero que representa la profundidad a la cual se encuentra el nodo dado en el arbol dado
 */
int averiguarProfundidadNodo(Arbol &arbol, Nodo nodo)
{
    int profundidadNodo = 0;

    // si el nodo dado es la raiz del arbol, entonces profundidadNodo es 0
    if(nodo == arbol.Raiz()){
        return profundidadNodo;
    }

    ++profundidadNodo;

    Nodo padre = arbol.Padre(nodo);

    while (padre != arbol.Raiz())
    {
        padre = arbol.Padre(padre);     
        ++profundidadNodo;   
    }

    return profundidadNodo;
}

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
    {
        std::cout << "RAIZ NULA" << std::endl;
        return;
    }

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

/**
 * @brief
 * @param
 */
void listarPorNiveles(Arbol &arbol)
{
    const Nodo &NodoNulo = Nodo();

    // Caso 1: El árbol tiene raíz nula (no tiene nodos)
    if (arbol.Raiz() == NodoNulo)
        return;
    // Caso 2:
    Util::Cola<Nodo> colaNodos;
    colaNodos.Encolar(arbol.Raiz());
    while (!colaNodos.Vacio())
    {
        Nodo nodoActual = colaNodos.Desencolar();
        std::cout << arbol.Etiqueta(nodoActual) << ", ";
        for (Nodo hijo = arbol.HijoMasIzquierdo(nodoActual); hijo != NodoNulo; hijo = arbol.HermanoDerecho(hijo))
        {
            colaNodos.Encolar(hijo);
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
        {
            std::cout << "ETIQUETA ENCONTRADA = " << etiqueta << std::endl;
            return nodoActual;   
        }
         

        // Ahora encolaremos todos sus hijos
        for (Nodo hijoActual = arbol.HijoMasIzquierdo(nodoActual); hijoActual != NodoNulo; hijoActual = arbol.HermanoDerecho(hijoActual))
            colaNodos.Encolar(hijoActual);
    }

    // Si no se encontró un nodo con la etiqueta correspondiente en el árbol, entonces devolveremos nodo nulo
    return NodoNulo;
}

/**
 * @brief La función listarPorPreorden permite imprimir el arbol dado en pre-orden, la función no modifica nada, usa la libreria de salida estandar
 * @param arbol es de tipo Arbol, requiere que sea inicializado
 * @param nodo es de tipo Nodo, requiere que sea inicializado y pertenezca al arbol
 * @remark la función requiere que  el arbol y el nodo sean inicializados y que el nodo pertenezca al arbol
 */
void listarPorPreorden(Arbol &arbol, Nodo nodo)
{
    std::cout << arbol.Etiqueta(nodo) << ", ";
    const Nodo &NodoNulo = Nodo();
    for (Nodo nodoTemp = arbol.HijoMasIzquierdo(nodo); nodoTemp != NodoNulo; nodoTemp = arbol.HermanoDerecho(nodoTemp))
    {
        listarPorPreorden(arbol, nodoTemp);
    }
}

/**
 * @brief la funcion padre permite mostrar al usuario la etiqueta del nodo padre del nodo que tiene como etiqueta el entero elemento dado
 * @param elemento es la etiqueta dado del cual queremos encontrar el padre, requiere que exista esta etiqueta en el arbol
 * @param arbol arbol es de tipo Arbol, requiere que sea inicializado
 * @remark la funcion requiere que exista el arbol, y que exista un nodo con la etiqueta "elemento"
 */
void padre(int elemento, Arbol &arbol)
{
    Nodo nodoHijo = buscarEtiqueta(elemento, arbol);
    Nodo mI = arbol.Padre(nodoHijo);
    std::cout << "Padre de " << elemento << "es " << arbol.Etiqueta(mI) << std::endl;
}

/**
 * @brief la función hermanoDerecho permite mostrar al usuario la etique del hermano derecho del nodo cual etique es "etiqueta", la funcion no modifica nada
 * @param etique es de tipo entero, el la etique del nodo del cual queremos imprimir la etiqueta del hermano derecho
 * @param arbol arbol es de tipo Arbol, requiere que sea inicializado
 * @remark la función requiere que ambos parametros existan, y que exista en el arbol un nodo cual etiqueta es "etiqueta"
 */
void hermanoDerecho(int etiqueta, Arbol &arbol)
{
    Nodo nodoPadre = buscarEtiqueta(etiqueta, arbol);
    Nodo mI = arbol.HermanoDerecho(nodoPadre);
    std::cout << "Hermano Derecho de " << etiqueta << "es " << arbol.Etiqueta(mI) << std::endl;
}

/**
 * @brief la función hijoMasIzquierdo permite mostrar al usuario el hijo mas izquierdo de un nodo cual etiqueta es dada, la función no modifica nada
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
 * @brief la función borrarHoja permite borrar la hoja del arbol que tengo como etiqueta el entero valorBorrado, la funcion modifica el arbol
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
 * @brief la funcion agregarHijo permite agregar un Nodo al arbol con una etiqueta igual a etiquetaHijo y con un padre con la etiqueta "etiqueta", la función modifica el arbol
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
 * @brief la función modificaEtiqueta permite modificar la etiqueta dada por la nueva etiqueta, la función modifica el arbol
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
 * @brief la función quantityNodesInLevel permite saber cuantos nodos existe en un nivel dado del arbol
 * @param arbol es de tipo arbol, debe contener al nodo subroot
 * @param subroot subroot es de tipo Nodo, cambia para cada llamado recursivo
 * @param level es de tipo entero, sirve como caso base para la recursividad
 * @remark la función requiere que el arbol sea inicializado, y que existe el level dado en el arbol
 */
void quantityNodesInLevel(Arbol &arbol, Nodo subroot, int level)
{ // Revisar

    // Base case: Level 0. The subroot. Its the only node with its own level
    if (level == 0)
    {
        std::cout << arbol.Etiqueta(subroot);
    }
    // Base case: Level 1. The subroot's children. They're the only one on this level (no cousins)
    else if (level == 1)
    {

        int childrenNodes = 0;
        const Nodo &NodoNulo = Nodo();
        Nodo child = arbol.HijoMasIzquierdo(subroot);
        while (child != NodoNulo)
        { // The sum of all ocurrences of children
            std::cout << arbol.Etiqueta(child) << ", ";
            child = arbol.HermanoDerecho(child);
        }

        // return;
    } // Recursive case: Level > 2. The subroot's descendants. We need to consider the children' subtrees quantiies of nodes
    else
    {

        int quantityNodes = 0;
        const Nodo &NodoNulo = Nodo();
        Nodo child = arbol.HijoMasIzquierdo(subroot);
        while (child != NodoNulo)
        { // The sum of all children's subtrees quantities of nodes, with adjusted level (-1)
            quantityNodesInLevel(arbol, child, level - 1);
            child = arbol.HermanoDerecho(child);
        }

        // return;
    }
}

/**
 * @brief borrarSubArbol permite borrar un subarbol que tiene como raiz el Nodo subroot dado, la función modifica el arbol
 * @param tree es de tipo Arbol, debe ser inicializado y no vacio, y debe contener al nodo subroot
 * @param subroot es de tipo Nodo, debe existir en el arbol, y ser inicializado
 * @remark la funcion requiere que el Nodo subroot exista en el arbol dado
 */
void borrarSubArbol(Arbol &tree, Nodo subroot)
{

    // We'll traverse the nodes each level using a queue
    // Each time we visit a node, we'll add its' children to the queue
    // The queue is filled with a node's children after we visited it
    // Then, after all of a node's children have been added, we take it out the queue
    Util::Cola<Nodo> queue;
    // Iniciar(travelQueue)

    // We'll delete the nodes using a stack
    // Each time we visit a node, we'll add it onto the stack
    // The stack is filled on the inverse order we added the nodes
    // Then, after all nodes were added, we delete them in the inverse order we visited them
    ListaIndexada deletionStack;

    // The tree traversion begins on the first node of the subtree: its' root

    queue.Encolar(subroot);

    // We can now begin traversion
    while (!queue.Vacio())
    {

        // Let's extract the last node on the travel queue
        Nodo visitedNode = queue.Desencolar();

        // The element has been visited, let's add it to the top of the stack
        // We'll always take 0 as the top of the stack
        deletionStack.insertar(tree.Etiqueta(visitedNode), 0);

        // Let's consider it's children for future travel
        const Nodo &NodoNulo = Nodo();
        for (Nodo visitedChildren = tree.HijoMasIzquierdo(visitedNode); visitedChildren != NodoNulo; visitedChildren = tree.HermanoDerecho(visitedChildren))
        {
            queue.Encolar(visitedChildren);
        }

        // All is done for this iteration:
        // a) The children will always be visited after their parent => parent -> children
        // b) The siblings will always be visited after the first child => first child -> sibling
        // c) The cousins will also always be visited after the children => children -> cousins
        // d) Due to a, b, and c, the order is as follows: parent -> first child -> siblings -> cousins
    }

    // We no longer need the travel queue. Let's free its memory
    // Destruir(travelQueue)

    // The whole subtree has been visited, and its' nodes placed on the stack in the inverse order they have been visited
    // We can now delete the visited nodes on the order they've been placed on within the stack
    int i = 0;
    while (i++ < deletionStack.numElem())
    {
        // It is guaranteed that the top element of the stack is a leaf
        int currentLeafValue = deletionStack.recuperar(0);
        // Nodo currentLeaf = buscarEtiqueta(currentLeafValue, tree );
        deletionStack.borrar(0);
        // It is guara nteed that we'll first delete the last child, and then its siblings
        // After deleting all siblings, it is guaranteed that its corresponding parent becomes a leaf
        // Therefore, deletion is in this reverse order is always face
        borrarHoja(currentLeafValue, tree);

        // The last leaf of the tree on the stack has been dealt (deleted off of the tree)
        // Let's take it out of the stack and carry on with the next leaf on the following iteration
    }

    // We no longer need the deletion stack. Let's free its memory

    // All is done:
    // a) The whole tree has been visited
    // b) Each node was visited only once
    // c) Each visited node was deleted in inverse order of visit
    // d) The auxiliary data structures were freed after use
}

/**
 * @brief crearArbol permite crear un arbol y despues lo imprime
 * @param i esde tipo entero, debe contener un valor valido
 * @param k es de tipo entero, debe contener un valor valido
 * @param L es de tipo ListaIndexada, debe ser inicializado
 * @param myTree es de tipo Arbol, debe ser inicializado
 * @remark la funcion requiere que i y k sean valores validos, y que la lista y el arbol sean inicializados y validos
 */
void crearArbol(int i, int k, ListaIndexada &L, Arbol &myTree)
{
   

    // The tree is assumed to be empty until noted otherwise

    // First condition: At least one level and one child per level
    if (i > 0 && k > 0)
    {
        // Since the tree has at least one level, and at least one child per level, there must be a root
        myTree.PonerRaiz(L.recuperar(0));

        // Second condition: At least two levels
        if (i > 1)
        {
            // On top of the first condition, since the tree has at least two levels, we must consider if it's children are parents as well
            Util::Cola<Nodo> parentNodesQueue;
            parentNodesQueue.Encolar(myTree.Raiz());

            int numNodesTotal = (pow(k, i) - 1) / (k - 1); // The total amount of nodes to add into the tree after it's fully constructed
            int numNodesLastLevel = pow(k, i - 1);         // The amount of nodes to be expected on the last level of the tree
            int numNodesAdded = 1;                         // The current amount of nodes added so far. The root has been added, therefore it's 1
           

            // We'll add children nodes until before the last level. There's no use in adding children on the last level
            while (numNodesAdded < numNodesTotal)
            {
                // The current parent to add children to
                // The amount of children per parent is already known. We can produce as many.
                Nodo padre = parentNodesQueue.Desencolar();
                for (int numChildAdded = 0; numChildAdded < k; ++numChildAdded)
                {
                    // It is a precondition of this function that we're guaranteed a child on the list for every possible node on the tree
                    Nodo newChild = myTree.AgregarHijo(L.recuperar(numNodesAdded), padre);
                    ++numNodesAdded;
                    // Whenever we produce a new child, it can be considered to be a new parent worth visiting to later on.
                    // However, this consideration may only be made if we haven't reached the last level of the tree
                    if (numNodesTotal - numNodesAdded >= numNodesLastLevel)
                    {
                        parentNodesQueue.Encolar(newChild);
                    }
                }
            }

            // We're done visting parents. We can free the memory allocated by the travel queue
        }
    }

    // Our tree is done! We can return it safely by this point
    imprimirArbol(myTree);
}

/**
 * @brief el metodo main contiene el menu principal que permite comunicar con el usuario
 * @return el metodo devuelve un 0 al final de se ejecución
 */
int main()
{
    ListaIndexada lista;
    Arbol arbol;
    Cola<int> cola(10000);

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
            std::cout << "7 - HijoMasIzquierdo" << std::endl;
            std::cout << "8 - HermanoDerecho" << std::endl;
            std::cout << "9 - padre" << std::endl;
            std::cout << "10 - modificar etiqueta" << std::endl;
            std::cout << "11 - numNodos" << std::endl;
            std::cout << "12 - Listar por niveles" << std::endl;
            std::cout << "13 - Listar por preorden" << std::endl;
            std::cout << "14 - Etiquetas en un nivel" << std::endl;
            std::cout << "15 - Eliminar arbol a partir de un nodo" << std::endl;
            std::cout << "16 - Crear un arbol en base a una lista" << std::endl;
            std::cout << "17 - Veriricar si un nodo existe en el árbol" << std::endl;
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
                agregarHijo(valorP, valor, arbol);
            }
            break;

            case 2: // borrar hoja
            {
                std::cout << "Cual valor quiere borrar del arbol ?" << std::endl;
                int etiquetaBorrada;
                std::cin >> etiquetaBorrada;
                borrarHoja(etiquetaBorrada, arbol);
                break;
            }
            case 3: // imprimir el arbol
            {
                imprimirArbol(arbol);
                break;
            }
            case 4: // get raiz
            {
                std::cout << arbol.Etiqueta(arbol.Raiz()) << std::endl;
            }
            break;

            case 5: // imprimir
            {
                imprimirArbol(arbol);
            }
            break;

            case 6: // salir y destruir arbol
            {
                seguir = 0;
                break;
            }
            case 7: // hijo izq
            {
                std::cout << "Cual valor del padre ?" << std::endl;
                int valor;
                std::cin >> valor;
                hijoMasIzquierdo(valor, arbol);
                break;
            }

            case 8: // hermano derecho
            {
                std::cout << "Cual valor del hermano ?" << std::endl;
                int valor;
                std::cin >> valor;
                hermanoDerecho(valor, arbol);
                break;
            }
            case 9: // padre
            {
                std::cout << "Cual valor del hijo ?" << std::endl;
                int valor;
                std::cin >> valor;
                padre(valor, arbol);
                break;
            }
            case 10:
            {
                std::cout << "Cual valor quiere modificar del arbol ?" << std::endl;
                int etiquetaModificada;
                std::cin >> etiquetaModificada;
                std::cout << "Cual es el nuevo valor ?" << std::endl;
                int etiqueta;
                std::cin >> etiqueta;
                modificaEtiqueta(etiquetaModificada, etiqueta, arbol);
                break;
            }
            case 11: // num Nodos
            {
                std::cout << "Num Nodos :" << arbol.NumNodos() << std::endl;
                break;
            }
            case 12:
            {
                listarPorNiveles(arbol);
            }
            break;
            case 13:
            {
                listarPorPreorden(arbol, arbol.Raiz());
            }
            break;
            case 14:
            {
                std::cout << "Que nivel desea conocer?" << std::endl;
                int nivel;
                std::cin >> nivel;
                quantityNodesInLevel(arbol, arbol.Raiz(), nivel - 1);
            }
            break;
            case 15:
            {
                std::cout << "A partir de que valor desea borrar?" << std::endl;
                int valor;
                std::cin >> valor;
                Nodo subroot = buscarEtiqueta(valor, arbol);
                borrarSubArbol(arbol, subroot);
            }
            break;
            case 16:
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
                    crearArbol(i, k, list, arbol);
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
                    crearArbol(i, k, list, arbol);
                }
            }
            break;
            case 17:
            {
                int elemento;
                std::cout << "Inserte un elemento" << std::endl;
                std::cin >> elemento;
                Nodo nodoDondeEtiqueta = buscarEtiqueta(elemento, arbol);

                if (nodoDondeEtiqueta == Nodo())
                    std::cout << "Nodo NO existe en el árbol" << std::endl;
                else
                    std::cout << "Nodo SÍ existe en el árbol" << std::endl;
            }
            break;
            default:
                break;
            }
        }
    }

    return 0;
}