#ifndef CONTROLADORTP
#define CONTROLADORTP
// Incluye utilidades auxiliares
#include <cstddef>         // Para utilizar contadores en recorrido por niveles
#include "../CDE/Cola.hpp" // Cola dinámica para realizar recorrido por niveles
#include <cmath>           // Formula para cantidad de nodos en un nivel

// Include de la Cola
#include "../1/Cola.hpp"

// Include de la Lista Indexada
#include "../2/ListaIndexada.hpp"

// Include de los Árboles
#if defined(ARBOL_3_1)
#include "../3.1/3.1.hpp"
#elif defined(ARBOL_3_2)
#include "../3.2/3.2.hpp"
#elif defined(ARBOL_3_3)
#include "../3.3/3.3.hpp"
#elif defined(ARBOL_3_4)
#include "../3.4/3.4.hpp"
#elif defined(ARBOL_3_5)
#include "../3.5/3.5.hpp"
#else
#include "../3.1/3.1.hpp"
#endif

// Include para I/O estándar
#include <iostream>

/// @brief Clase encapsuladora de métodos para cada algoritmo o función del problema.
class Controlador
{
    public:
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
         * La cantidad de niveles va de 0 a n, siendo n la altura total del árbol
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
         * @brief Indica cuántos niveles tiene un árbol realizando un recorrido por niveles. No modifica nada
         * @param arbol Árbol para el cual averiguar la cantidad de niveles
         * @remark El árbol debe estar inicializado.
         * @return Devuelve la cantidad de niveles que tiene el árbol (comienza en 0). Un valor de 0 niveles representa un árbol vacío
         */
        size_t nivelesArbolRPN(Arbol &arbol)
        {
            const Nodo &NodoNulo = Nodo();

            // Caso 1: El árbol tiene raíz nula (no tiene nodos)
            if (arbol.Raiz() == NodoNulo)
                return 0;

            // Caso 2: El árbol tiene nodos
            // Realizaremos un recorrido por niveles utilizando una cola de nodos
            Util::Cola<Nodo> colaNodos;

            // Encolemos a la raiz para iniciar el recorrido usándola como punto de partida
            colaNodos.Encolar(arbol.Raiz());

            // Adicionalmente, llevaremos cuenta de cuántos nodos corresponden al nivel actual y su correspondiente siguiente
            size_t nodosPendientesNivelActual = 1;
            size_t nodosPendientesNivelSiguiente = 0;

            // Asimismo, llevaremos cuenta de cuántos niveles hemos recorrido hasta ahora
            size_t nivelesRecorridos = 0;  // Nos falta recorrer el primer nivel todavía, por eso comenzamos en 0

            // Mientras tengamos nodos en la cola, no hemos terminado el recorrido
            while (!colaNodos.Vacio())
            {
                // Siempre obtendremos el nodo encolado más antigüamente (de primero)
                Nodo nodoActual = colaNodos.Desencolar();

                // Tras obtener ese nodo, la cantidad de nodos pendientes en el nivel actual disminuye en 1
                --nodosPendientesNivelActual;

                // Tras obtener un nodo, encolaremos cada hijo
                for (Nodo hijoActual = arbol.HijoMasIzquierdo(nodoActual); hijoActual != NodoNulo; hijoActual = arbol.HermanoDerecho(hijoActual))
                {
                    colaNodos.Encolar(hijoActual);

                    // Tras encolar un hijo, la cantidad de nodos pendientes en el nivel siguiente aumenta
                    ++nodosPendientesNivelSiguiente;
                }

                // Si ya no hay nodos pendientes en este nivel, entonces hemos cambiado de nivel
                if (nodosPendientesNivelActual == 0)
                {
                    // La cantidad de nodos pendientes en este nivel corresponden a la cantidad de nodos pendientes para el siguiente
                    nodosPendientesNivelActual = nodosPendientesNivelSiguiente;

                    // Luego, como cambiamos de nivel, la cantidad de nodos pendientes para el siguiente nivel se asume como 0 de nuevo
                    nodosPendientesNivelSiguiente = 0;

                    // Como estamos seguros que cambiamos de nivel podemos aumentar el contador de niveles
                    nivelesRecorridos += 1;
                }
            }

            // Ya terminamos de recorrer por niveles todo el árbol
            // La cantidad de niveles recorridos debería corresponder con la altura de éste.
            return nivelesRecorridos;
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
                    return nodoActual;

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
                std::cout << "Padre de " << elemento << " es " << arbol.Etiqueta(mI) << std::endl;
        }

        /**
         * @brief Muestra la etiqueta del hermano derecho de un nodo con otra etiqueta particular. No modifica nada
         * @param etiqueta La etiqueta del nodo del cual queremos imprimir la etiqueta del hermano derecho
         * @param arbol Arbol donde se encuentran ambos nodos (nodo con la etiqueta particular y su hermano, si existen)
         * @remark Tanto la etiqueta como el árbol deben estar incializados. Debe existir al menos un nodo con esa etiqueta en el árbol.
         */
        void hermanoDerecho(int etiqueta, Arbol &arbol)
        {
            Nodo nodoPadre = buscarEtiqueta(etiqueta, arbol);
            Nodo mI = arbol.HermanoDerecho(nodoPadre);
            std::cout << "Hermano Derecho de " << etiqueta << "es " << arbol.Etiqueta(mI) << std::endl;
        }

        /**
         * @brief Muestra la etiqueta del nodo hijo mas izquierdo de un nodo con otra etiqueta particular. No modifica nada
         * @param etiqueta La etiqueta del nodo del cual queremos conocer el hijo mas izquierdo
         * @param arbol Arbol donde se encuentra el nodo con la etiqueta particular, y su hipotético hijo más izquierdo (si existe)
         * @remark Tanto la etiqueta como el árbol deben estar incializados. Debe existir al menos un nodo con esa etiqueta en el árbol.
         */
        void hijoMasIzquierdo(int etiqueta, Arbol &arbol)
        {
            Nodo nodoPadre = buscarEtiqueta(etiqueta, arbol);
            Nodo mI = arbol.HijoMasIzquierdo(nodoPadre);
            std::cout << "Hijo mas Izquierdo de " << etiqueta << " es " << arbol.Etiqueta(mI) << std::endl;
        }

        /**
         * @brief Borra la hoja del arbol que tenga una etiqueta particular. El árbol perderá esa hoja.
         * @param valorBorrado La etiqueta del nodo hoja que se planea quitar
         * @param arbol El árbol cual queremos borrar una hoja
         * @remark Tanto el árbol como la etiqueta deben estar inicializados. La etiqueta debe existir en una hoja en el árbol
         */
        void borrarHoja(int valorBorrado, Arbol &arbol)
        {
            Nodo borrado = buscarEtiqueta(valorBorrado, arbol);
            arbol.BorrarHoja(borrado);
            imprimirArbol(arbol);
        }

        /**
         * @brief Agrega un nodo como hoja, con una etiqueta asignada, a otro nodo como padre, identificado mediante otra etiqueta particular. El árbol obtendrá un hijo.
         * @param etiqueta La etiqueta del nodo al cual le queremos asignar un nodo hoja
         * @param etiquetaHijo La etiqueta que le asignaremos al nodo hoja creado como hijo del nodo padre
         * @param arbol Árbol donde reside el nodo padre, y donde residirá la hoja creada
         * @remark Ambas etiquetas y el árbol deben estar inicializados. La etiqueta identificadora del nodo padre debe existir en un nodo del árbol.
         */
        void agregarHijo(int etiqueta, int etiquetaHijo, Arbol &arbol)
        {
            Nodo nodoPadre = buscarEtiqueta(etiqueta, arbol);
            arbol.AgregarHijo(etiquetaHijo, nodoPadre);
        }

        /**
         * @brief Sustituye la etiqueta dada de un nodo identificado por una etiqueta, por otra etiqueta particular. La etiqueta de ese nodo se verá modificada.
         * @param etiquetaVieja La etiqueta que identifica al nodo del nodo del cual queremos cambiar la etiqueta
         * @param nuevaEtiqueta La etiqueta que sustituirá a la otra etiqueta que ayudó a identificar el nodo víctima
         * @param arbol Arbol donde reside el nodo cuya etiqueta se planea modificarks
         * @remark Ambas etiquetas y el árbol deben estar inicializados. La etiqueta identificadora del nodo padre debe existir en un nodo del árbol.
         */
        void modificaEtiqueta(int etiquetaVieja, int nuevaEtiqueta, Arbol &arbol)
        {
            Nodo modificado = buscarEtiqueta(etiquetaVieja, arbol);
            arbol.ModificaEtiqueta(nuevaEtiqueta, modificado);
        }

        /**
         * @brief Indica cuantos nodos existe en un nivel dado del arbol. No modifica nada.
         * @param arbol Arbol cuyos a partir de cierto sub-árbol nodos en cierto nivel (relativo al sub-árbol) se planean imprimir
         * @param subraiz Raíz del sub-árbol (sub-raíz) del cual se parte para recorrer los nodos en cierto nivel
         * @param nivel Nivel (relativo al sub-árbol) del cual se le quiere imprimir los nodos del sub-árbol
         * @remark El árbol, sub-raíz y nivel deben estar inicializados. La subraíz debe existir debe existir en el árbol. El nivel no puede ser negativo
         * Los niveles se indizan a partir de 0 (raíz) a n-1 (con n = altura total del árbol)
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
         * @brief Borra todos los nodos de un sub-árbol particular del árbol más grande. Todos los nodos de ese sub-árbol dejarán de existir en el árbol.
         * @param arbol Árbol del cual se planean borrar los nodos pertenecientes a un sub-árbol suyo
         * @param subraiz Nodo denotando la raíz del sub-árbol cuyos nodos se planean quitar del árbol más grande.
         * @remark Tanto el árbol como el nodo deben estar inicializados. La subraíz debe existir en el árbol.
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
         * @brief Crea un arbol, poblandolo a partir de una lista de elementos, una cantidad de niveles y una cantidad de hijos por nivel. 
         * El árbol termina teniendo ((k^i)-1) / (k-1) nodos en total, copiados 1:1 de principio a fin de la lista, mediante un recorrido por niveles.
         * @param i La cantidad de niveles que se desea tener en este árbol
         * @param k La cantidad de hijos por cada nodo en todo nivel (excepto el último)
         * @param lista Lista de etiquetas que serán tomadas para poblar el árbol con nodos (cuyas etiquetas serán esas).
         * @param arbol Arbol a poblar con los nodos producidos a partir de las etiquetas en la lista
         * @remark Tanto k, i. la lista indexada y el árbol deben estar incializados. El árbol debe estar vacío. La lista tener suficientes elementos
         * etiquetas como para poblar todo el árbol con un elemento distinto (no necesariamente una etiqueta única) cada vez
         */
        void crearArbol(int i, int k, ListaIndexada &lista, Arbol &arbol)
        {
            // Primera condición: por lo menos un nivel y un hijo por nivel
            if (i > 0 && k > 0)
            {
                // Ya que el arbol tiene por lo menos un nivel, por lo menos un hijo por nivel, entonces hay una raiz
                arbol.PonerRaiz(lista.recuperar(0));

                // Segunda condición: por lo menos 2 niveles
                if (i > 1)
                {
                    // Ademas de la primeras condicion, ya que el arbol tiene por lo menos 2 niveles, debemos considerar si sus hijos son padres tambien
                    Util::Cola<Nodo> parentNodesQueue;
                    parentNodesQueue.Encolar(arbol.Raiz());

                    int numNodesTotal = (pow(k, i) - 1) / (k - 1); // La cantidad total de nodos a agregar en el arbol despues que sea completamente construido
                    int numNodesLastLevel = pow(k, i - 1);         // la cantidad de nodos esperados en el ultimo nivel del arbol
                    int numNodesAdded = 1;                         // La cantidad de nodos añadidos hasta ahora, la raiz es un nodo asi que llevamos uno
                
                    // Vamos a añadir nodos hijos a todos los niveles menos el ultimo. No hay necesidad de añadirselo al ultimo
                    while (numNodesAdded < numNodesTotal)
                    {
                        // El padre al que agregarle un hijo
                        // La cantidad de hijos po padre ya se conoce. Podemos producirla
                        Nodo padre = parentNodesQueue.Desencolar();
                    
                        for (int numChildAdded = 0; numChildAdded < k; ++numChildAdded)
                        {
                            // Es una precondicion de esta funcion en el que se nos garantiza un valor en la lista por cada nodo en el arbol
                            Nodo newChild = arbol.AgregarHijo(lista.recuperar(numNodesAdded), padre);
                            ++numNodesAdded;

                            // Cada vez que poduzcamos un nuevo hijo, se puede considerar como un padre que valdria la pena visitar despues
                            // Aunque, esta consideracion solo se puede hacer si no hemos alcanzado el ultimo nivel del arbol
                            if (numNodesTotal - numNodesAdded >= numNodesLastLevel)
                                parentNodesQueue.Encolar(newChild);
                        }
                    }
                }
            }
        }
};
#endif