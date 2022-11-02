#ifndef CONTROLADORTP
#define CONTROLADORTP
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
// #include "../3.2/3.2.hpp"
// #include "../3.3/3.3.hpp"
// #include "../3.4/3.4.hpp"
// #include "../3.5/3.5.hpp"

// Include para I/O estándar
#include <iostream>

class Controlador
{

private:
public:
    /**
     * @brief Encuentra al hermano a la izquierda de un nodo dado. No modifica nada
     * @param nodo Nodo al cual se le buscará el hermano izquierdo.
     * @param arbol Árbol en el cual se buscara al hermano izquierdo del nodo alimentado
     * @remark Tanto el nodo como el árbol deben estar inicializados. El nodo debe pertenecer al árbol
     * @return Devuelve un al hermano izquierdo del nodo, si existe. Sino, devuelve un nodo nulo
     */
    /**
     * @brief Encuentra al hermano a la izquierda de un nodo dado. No modifica nada
     * @param nodo Nodo al cual se le buscará el hermano izquierdo.
     * @param arbol Árbol en el cual se buscara al hermano izquierdo del nodo alimentado
     * @remark Tanto el nodo como el árbol deben estar inicializados. El nodo debe pertenecer al árbol
     * @return Devuelve un al hermano izquierdo del nodo, si existe. Sino, devuelve un nodo nulo
     */
    Nodo averiguarHermanoIzquierdo(Nodo nodo, Arbol &arbol)
    {
        const Nodo &NodoNulo = Nodo();

        // Caso 1: Si el nodo es la raíz. No puede tener hermano izquierdo
        if (nodo == arbol.Raiz())
            return NodoNulo;

        // Caso 2: El nodo no es la raíz
        Nodo nodoPadre = arbol.Padre(nodo);
        Nodo hermanoIzquierdo = arbol.HijoMasIzquierdo(nodoPadre);

        // Subcaso 1: El nodo es el hijo más izquierdo. No tiene hermano izquierdo.
        if (hermanoIzquierdo == nodo)
            return NodoNulo;

        // Subcaso 2: El nodo no es el hijo más izquierdo. Buscaremos un nodo que lo tenga de hermano derecho
        while (arbol.HermanoDerecho(hermanoIzquierdo) != nodo)
            hermanoIzquierdo = arbol.HermanoDerecho(hermanoIzquierdo);

        return hermanoIzquierdo;
    }

    /**
     * @brief Verifica si existe varios nodos con la misma etiqueta en el arbol. No modifica nada
     * @param arbol Árbol donde investigar si existen etiquetas repetidas
     * @remark El árbol debe estar inicializado
     * @return Devuelve true (1) si hay etiquetas repetidas, sino devuelve false (0)
     */
    bool averiguarEtiquetasRepetidas(Arbol &arbol)
    {
        const Nodo &NodoNulo = Nodo();

        // Caso 1: El árbol tiene raíz nula (no tiene nodos)
        if (arbol.Raiz() == NodoNulo)
            return false;

        // Caso 2: El árbol tiene nodos
        // Realizaremos un recorrido por niveles utilizando dos cola de nodos recorridos
        Util::Cola<Nodo> colaNodos;
        Util::Cola<Nodo> colaNodosComparados;

        // Encolemos a la raiz para iniciar el recorrido usándola como punto de partida
        colaNodos.Encolar(arbol.Raiz());

        // Mientras tengamos nodos en la primera cola, no hemos terminado el recorrido
        while (!colaNodos.Vacio())
        {
            // Obtendremos al nodo encolado más antigüamente (de primero) en la primera cola
            Nodo nodoActual = colaNodos.Desencolar();

            // Recorreremos por niveles a todo el árbol en la segunda cola
            colaNodosComparados.Encolar(arbol.Raiz());
            while (!colaNodosComparados.Vacio())
            {
                // Obtendremos al nodo encolado más antigüamente (de primero) en la segunda cola
                Nodo nodoComparado = colaNodosComparados.Desencolar();

                // Si ambos nodos examinados de las dos colas son distintos, pero
                // aún así tienen etiquetas idénticas, entonces encontramos una repetición
                if (arbol.Etiqueta(nodoActual) == arbol.Etiqueta(nodoComparado))
                {
                    if (nodoActual != nodoComparado)
                        return true;
                }

                // Sino, continuaremos encolando nodos para el recorrido en la segunda cola
                for (Nodo hijoActual = arbol.HijoMasIzquierdo(nodoComparado); hijoActual != NodoNulo; hijoActual = arbol.HermanoDerecho(hijoActual))
                    colaNodosComparados.Encolar(hijoActual);
            }

            // Tras haber analizado todo el árbol con el nodo actual, podemos continuar el análisis con el resto
            // Por eso, encolaremos nodos para el recorrido en la primera cola
            for (Nodo hijoActual = arbol.HijoMasIzquierdo(nodoActual); hijoActual != NodoNulo; hijoActual = arbol.HermanoDerecho(hijoActual))
                colaNodos.Encolar(hijoActual);
        }

        // Si no se encontró un nodo con la etiqueta correspondiente en el árbol, entonces devolveremos nodo nulo
        return 0;
    }

    /**
     * @brief Indica cuántos niveles tiene un árbol a partir de cierta subraíz, realizando un recorrido en pre-orden. No modifica nada
     * @param arbol Árbol en el cual transladarse para realizar el recorrido en preoden
     * @param subraiz Nodo raíz del cual partir el recorrido en preorden
     * @remark Tanto el árbol como el nodo debe estar inicializado. El nodo subraíz debe pertencer al árbol, aunque se permite que sea nulo
     * @return Devuelve la cantidad de niveles que tiene el árbol a partir de ese nodo
     * La cantidad de niveles va de 1 a n, siendo n la altura total del árbol
     */
    size_t nivelesArbolRPO(Arbol &arbol, Nodo subraiz)
    {
        const Nodo& NodoNulo = Nodo();

        // Caso base #1: La subraíz es nula (el subárbol está vacío)
        if (subraiz == NodoNulo)
            return 0;

        // Caso recursivo: El nodo sí tiene hijos (no es una hoja)
        // Se va a recorrer el árbol en preorden (recorrer a los hijos del nodo antes de a él mismo)
        // Para la altura del árbol en la subraíz, consideraremos a la mayor altura de los subárboles inmediatos a ésta
        size_t alturaCandidata = 0;  // Asumiremos una altura nula hasta que se pruebe lo contrario
        for (Nodo hijoActual = arbol.HijoMasIzquierdo(subraiz); hijoActual != NodoNulo; hijoActual = arbol.HermanoDerecho(hijoActual))
        {
            size_t alturaSubArbol = nivelesArbolRPO(arbol, hijoActual);

            if (alturaSubArbol > alturaCandidata)
                alturaCandidata = alturaSubArbol;
        }

        // Una vez que ya conocemos la mayor altura entre las de los subárboles inmediatos a la subraíz, entonces es
        // trivial reconocer que la altura a partir de la subraíz considera un nivel adicionaL: el de la subraíz
        return alturaCandidata + 1;
    }

    /**
     * @brief Verifica a cual profundidad (valor entero) se encuentra en el arbol dado un nodo dado. No modifica nada
     * @param arbol Árbol en el cual buscar el nodo, y así encontrar su profundidad
     * @param nodo Nodo para el cual buscamos la profundidad en el árbol.
     * @remark El árbol debe estar inicializado y no vacio. El nodo debe estar inicializado y pertenecer al árbol
     * @return Devuelve un entero que representa la profundidad a la cual se encuentra el nodo
     * La profundidad va de 0 a n-1, siendo n la altura total del árbol
     */
    int averiguarProfundidadNodo(Arbol &arbol, Nodo nodo)
    {
        // Asumiremos una profundidad de 0
        int profundidadNodo = 0;

        // Caso 1: Si el nodo de partida es la raíz del árbol, la profundidad es 0
        if (nodo == arbol.Raiz())
            return profundidadNodo;

        // Caso 2: El nodo de partida no es la raíz del árbol. Es necesario investigar
        ++profundidadNodo;

        // Solicitaremos al padre del nodo, y cada vez al padre de cada uno, hasta llegar a la raíz
        Nodo padre = arbol.Padre(nodo);
        while (padre != arbol.Raiz())
        {
            // Cada vez que solicitamos un padre, la asumción de la profundidad del nodo debe incrementar en 1
            padre = arbol.Padre(padre);
            ++profundidadNodo;
        }

        // Tras haber llegado a la raíz, ya conocemos la profundidad del nodo
        return profundidadNodo;
    }

    /**
     * @brief Imprime por niveles el contenido de una árbol. No modifica nada
     * @param arbol Árbol cuyos contenidos se van a imprimir.
     * @remark El árbol debe estar inicializado.
     */
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

    /**
     * @brief Lista los nodos que existen en el árbol, recorriéndolos por niveles. No modifica nada
     * @param arbol Árbol cuyos contenidos se van a imprimir mediante un recorrerido por niveles
     * @remark El arbol debe estar inicializado.
     */
    void listarPorNiveles(Arbol &arbol)
    {
        const Nodo &NodoNulo = Nodo();

        // Caso 1: El árbol tiene raíz nula (no tiene nodos)
        if (arbol.Raiz() == NodoNulo)
            return;

        // Caso 2: El árbol tiene raíz (al menos un nodo)
        // Realizaremos un recorrido por niveles mediante una cola de nodos pendientes
        Util::Cola<Nodo> colaNodos;
        colaNodos.Encolar(arbol.Raiz());

        // Mientras haya nodos pendientes, seguiremos listando y recolectando nodos para recorrer
        while (!colaNodos.Vacio())
        {
            // Imprimamos el nodo actual
            Nodo nodoActual = colaNodos.Desencolar();
            std::cout << arbol.Etiqueta(nodoActual) << ", ";

            // Encolemos a los hijos de ese nodo
            for (Nodo hijo = arbol.HijoMasIzquierdo(nodoActual); hijo != NodoNulo; hijo = arbol.HermanoDerecho(hijo))
                colaNodos.Encolar(hijo);
        }

        // Si ya no quedan nodos pendientes, ya no hay nada que hacer
        return;
    }

    /**
     * @brief Devuelve el primer nodo correspondiente a la etiqueta buscada (si existe). Recorre el árbol en pre-orden. No modifica nada
     * @param arbol Arbol donde se busca algún nodo con la etiqueta
     * @param etiqueta Etiqueta cuyos contenidos se intentan buscar en el árbol (dentro de un nodo)
     * @remark Tanto el arbol como la etiqueta deben estar inicializados
     * @return Nodo en el árbol que posee la etiqueta alimentada. Nodo nulo en caso contrario
     */
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
     * @brief Imprime el arbol en pre-orden. No modifica nada.
     * @param arbol Árbol del cual imprimir sus contenidos
     * @param nodo Sub-raíz del cual partir para imprimir en preorden
     * @remark Tanto el árbol como el nodo deben estar inicializados. El nodo debe pertenecer al árbol
     */
    void listarPorPreorden(Arbol &arbol, Nodo nodo)
    {
        // Imprime la etiqueta del nodo sub-raíz del cual comenzar
        std::cout << arbol.Etiqueta(nodo) << ", ";

        // Listaremos en preorden a la descendencia de cada hijo directo de la sub-raíz, recursivamente.
        const Nodo &NodoNulo = Nodo();
        for (Nodo nodoTemp = arbol.HijoMasIzquierdo(nodo); nodoTemp != NodoNulo; nodoTemp = arbol.HermanoDerecho(nodoTemp))
            listarPorPreorden(arbol, nodoTemp);
    }

    /**
     * @brief Muestra la etiqueta del nodo padre, partiendo de un nodo que tiene una etiqueta particular. No modifica nada.
     * @param elemento Etiqueta con la cual asociar a un nodo padre.
     * @param arbol Árbol en el cuál buscar la etiqueta del padre
     * @remark Tanto el árbol como la etiqueta deben estar inicializados. Debe existir al menos un nodo con la etiqueta en el árbol.
     */
    void padre(int elemento, Arbol &arbol)
    {
        // Buscamos a un nodo con la etiqueta particular
        Nodo nodoHijo = buscarEtiqueta(elemento, arbol);

        // Luego solicitamos a su padre, y así su etiqueta
        Nodo mI = arbol.Padre(nodoHijo);

        if (mI == Nodo())
            std::cout << "No existe padre para " << elemento << std::endl;
        else
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
     * @brief la función imprimirNodosEnNivel permite saber cuantos nodos existe en un nivel dado del arbol
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
     * @brief borrarSubArbol permite borrar un subarbol que tiene como raiz el Nodo subraiz dado, la función modifica el arbol
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
            // Esta garantizado que el elemento tope del stack es una hoja
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
     * @brief crearArbol permite crear un arbol y despues lo imprime
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
                while (numNodesAdded < numNodesTotal)
                { // Vamos a añadir nodos hijos a todos los niveles menos el ultimo. No hay necesidad de añadirselo al ultimo

                    // El padre al que agregarle un hijo
                    // La cantidad de hijos po padre ya se conoce. Podemos producirla
                    Nodo padre = parentNodesQueue.Desencolar();
                    std::cout << "El desencolado es" << myTree.Etiqueta(padre) << std::endl;
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
                            std::cout << "Encole a " << myTree.Etiqueta(newChild) << std::endl;
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
};
#endif