#ifndef ARBOL_HPP
#define ARBOL_HPP

#include <exception> // Para las excepciones
#include <cstddef> // Para poder usar size_t

#include <iostream> // Para impresiones en la salida estandar
#include "../CDE/Cola.hpp" // Para realizar recorridos por niveles

namespace Arbol_N_Ario
{
    /// @brief Excepcion para cuando se intenta desreferenciar un puntero a elemento nulo (a nivel de nodo concreto)
    class ElementoInvalidoArbol : public std::exception 
    {
        public:
            ElementoInvalidoArbol() {}
            ~ElementoInvalidoArbol() {}

            virtual const char* what() const noexcept
            {return "Imposible acceder a elemento. Es nulo";}
    };

    /// @brief Excepcion para cuando se intenta desreferenciar un puntero a nodo concreto nulo
    class NodoConcretoInvalido : public std::exception 
    {
        public:
            NodoConcretoInvalido() {}
            ~NodoConcretoInvalido() {}

            virtual const char* what() const noexcept
            {return "Imposible acceder a nodo concreto. Es nulo";}
    };

    /// @brief Excepcion para cuando se intenta desreferenciar un puntero a elemento nulo (a nivel de nodo)
    class DereferenciaNodoInvalida : public std::exception 
    {
        public:
            DereferenciaNodoInvalida() {}
            ~DereferenciaNodoInvalida() {}

            virtual const char* what() const noexcept
            {return "Imposible desreferenciar nodo, su elemento es nulo";}
    };

    /// @brief Excepcion para cuando se maneja un nodo que deberia existir en el arbol, pero no se encontro en el
    class NodoEsForaneo : public std::exception 
    {
        public:
            NodoEsForaneo() {}
            ~NodoEsForaneo() {}

            virtual const char* what() const noexcept
            {return "Nodo deberia existir en el arbol, pero no se encontro";}
    };

    /// @brief Excepcion para cuando se maneja un nodo que requiere ser una hoja, pero no lo es
    class NodoNoEsHoja : public std::exception 
    {
        public:
            NodoNoEsHoja() {}
            ~NodoNoEsHoja() {}

            virtual const char* what() const noexcept
            {return "Hoja invalida. Nodo no es hoja";}
    };

    /// @brief Excepcion para cuando se intenta inicializar una raiz ya existente
    class RaizPreexistente : public std::exception 
    {
        public:
            RaizPreexistente() {}
            ~RaizPreexistente() {}

            virtual const char* what() const noexcept
            {return "Imposible añadir raiz. Ya existe";}
    };

    /// @brief Excepcion para cuando se intenta desreferenciar un puntero a raiz (nodo) nula
    class RaizNula : public std::exception 
    {
        public:
            RaizNula() {}
            ~RaizNula() {}

            virtual const char* what() const noexcept
            {return "Imposible acceder a raiz. Es nula";}
    };

    // Declaraciones adelantadas para resolver dependencias circulares en impresion

    /// @brief Arbol N-Ario implementado con Hijo-Mas-Izquierdo, Hermano Derecho y contador
    template <typename Elemento>
    class Arbol;

    /// @brief Imprime los contenidos de un arbol de forma vertical a un flujo de salida
    /// @param salida Flujo de salida para imprimir los contenidos del arbol
    /// @param arbol Arbol N-ario del cual imprimir los contenidos
    /// @return Referencia al flujo de salida utilizado (para encadenar impresiones)
    template <typename Elemento>
    std::ostream& operator<<(std::ostream& salida, const Arbol<Elemento>& arbol);

    /// @brief Arbol N-Ario implementado con Hijo-Mas-Izquierdo, Hermano Derecho y contador
    template <typename Elemento>
    class Arbol
    {
        // La funcion de impresion puede ver las entrañas de un Arbol
        template <typename T>
        friend std::ostream& operator<<(std::ostream&, const Arbol<T>&);

        protected: 
            /// @brief Nodo concreto, poseedor de elementos y poseido por el arbol
            class NodoConcreto
            {
                // Un Arbol pueden manipular las entrañas de un Nodo Concreto, y un Nodo verlas
                friend class Nodo;
                friend class Arbol;

                // La funcion de impresion puede ver las entrañas de un Nodo Concreto
                template <typename T>
                friend std::ostream& operator<<(std::ostream&, const Arbol<T>&);

                private:
                    /// @brief Elemento en la memoria dinamica apuntado (y poseido) por este nodo concreto
                    Elemento* elemento = nullptr;
                    /// @brief Apuntador al nodo concreto correspondiente al hermano derecho de este nodo concreto
                    NodoConcreto* hermanoDerecho = nullptr;
                    /// @brief Apuntador al nodo concreto correspondiente al hijo mas izquierdo de este nodo concreto
                    NodoConcreto* hijoMasIzquierdo = nullptr;

                    /// @brief Inicializa a un nodo concreto apuntando a un nuevo elemento creado por copia
                    /// @param valorElemento Elemento el cual sera usado como base para construir una copia
                    /// @remark Requiere que el elemento tenga un constructor por copia valido
                    NodoConcreto(const Elemento& valorElemento)
                    {this->elemento = new Elemento(valorElemento);}

                    /// @brief Libera la memoria del elemento apuntado, si resultase no ser nulo
                    /// @remark Requiere que el elemento tenga un destructor por defecto valido
                    ~NodoConcreto()
                    {
                        if (this->elemento != nullptr)
                            delete this->elemento;
                    }
            
                    /// @brief Obtiene el elemento apuntado por este nodo concreto
                    /// @return Elemento obtenido al desreferenciar el apuntador de elemento
                    /// @remarks Requiere que el apuntador de elemento nulo no apunte a un elemento nulo
                    const Elemento& getElemento() const
                    {
                        if (this->elemento == nullptr)
                            throw ElementoInvalidoArbol();
                        
                        return *(this->elemento);
                    }
            
                    /// @brief Destruye el elemento apuntado por este nodo concreto para apuntar a otro nuevo
                    /// @param nuevoValor Elemento el cual sera usado como base para construir una copia
                    /// @remark Requiere que el elemento tenga un constructor por copia y destructor por defecto validos
                    void cambiarElemento(const Elemento& nuevoValor)
                    {
                        delete this->elemento;
                        this->elemento = new Elemento(nuevoValor);
                    }
            };
        
        public:
            /// @brief Nodo logico, interfaz entre nodo concreto y usuario del arbol
            class Nodo 
            {
                // Un Arbol puede ver y manipular las entrañas de un Nodo (logico)
                friend class Arbol;

                // La funcion de impresion puede ver las entrañas de un Nodo (logico)
                template <typename T>
                friend std::ostream& operator<<(std::ostream&, const Arbol<T>&);

                private:
                    /// @brief Nodo concreto apuntado (pero no poseido) por este nodo
                    NodoConcreto* nodoConcreto = nullptr;

                    /// @brief Inicializa a un nodo apuntando a un nodo concreto
                    /// @param nodoConcreto Apuntado a un nodo concreto al cual referenciar mediante este nodo
                    Nodo(NodoConcreto* nodoConcreto)
                    {this->nodoConcreto = nodoConcreto;}

                public:
                    /// @brief Crea un nodo nulo (no apunta a ningun nodo concreto)
                    Nodo() {}

                    /// @brief Clona el apuntador de un nodo concreto hacia este nodo
                    /// @param otroNodo Nodo del cual clonar el apuntador al nodo concreto
                    Nodo(const Nodo& otroNodo)
                    {this->nodoConcreto = otroNodo.nodoConcreto;}

                    /// @brief Limpia a este nodo, mas no al nodo concreto al que apunte (no lo posee, solo lo referencia)
                    virtual ~Nodo() {};

                    /// @brief Obtiene el elemento apuntado por el nodo concreto apuntado por este nodo
                    /// @return Elemento obtenido al desreferenciar el apuntador de elemento del nodo concreto
                    /// @remarks Requiere que el nodo concreto apuntado no sea nulo, ni que ese apunte a un elemento nulo
                    const Elemento& operator->() const
                    {
                        if (nodoConcreto == nullptr)
                            throw NodoConcretoInvalido();

                        return nodoConcreto->getElemento();
                    }

                    /// @brief Compara si dos nodos apuntan al mismo nodo concreto en el arbol
                    /// @return Verdadero si apuntan al mismo nodo concreto, falso en caso contrario
                    bool operator==(const Nodo& otroNodo) const
                    {return this->nodoConcreto == otroNodo.nodoConcreto;}

                    /// @brief Compara si dos nodos apuntan a distintos nodos concretos en el arbol
                    /// @return Verdadero si apuntan a distintos concretos, falso en caso contrario
                    bool operator!=(const Nodo& otroNodo) const
                    {return this->nodoConcreto != otroNodo.nodoConcreto;}
            };

        protected:
            /// @brief Nodo concreto, inicial del arbol
            NodoConcreto* raiz = nullptr;
            /// @brief Cantidad de elementos existentes en total en todo el arbol (a partir de la raiz, incluyendola)
            size_t cantidadNodos = 0;

        public:

            /// @brief Inicializa a un arbol en un estado por defecto
            Arbol() {}

            /// @brief Elimina los nodos de un arbol
            ~Arbol() noexcept(false)
            {
                // Si el arbol esta vacio, hay nada que hacer
                if (this->Raiz() == Nodo())
                    return;

                // Sino, utilicemos una cola de nodos para realizar un recorrido por niveles
                Util::Cola<Nodo> colaNodos;

                // Encolemos a la raiz para iniciar el recorrido usandola como punto de partida
                colaNodos.Encolar(this->Raiz());

                // Mientras tengamos nodos en la cola, no hemos terminado el recorrido
                while (!colaNodos.Vacio())
                {
                    // Siempre obtendremos el nodo encolado mas antigüamente (de primero)
                    Nodo nodoActual = colaNodos.Desencolar();

                    // Tras obtener un nodo, encolaremos todos sus hijos
                    // Para ello tenemos que lidiar con el nodo concreto subyacente
                    NodoConcreto* nodoConcreto = nodoActual.nodoConcreto;
                    if (nodoConcreto == nullptr)
                        throw NodoConcretoInvalido();

                    for (NodoConcreto* it = nodoConcreto->hijoMasIzquierdo; it != nullptr; it = it->hermanoDerecho)
                        colaNodos.Encolar(Nodo(it));

                    // Luego, destruiremos al nodo concreto subyacente del nodo que desencolamos
                    // Esto libera los recursos manejados por el nodo concreto
                    delete nodoConcreto;
                }
            }

            /// @brief Coloca un elemento en la raiz del arbol como un nodo
            /// @param valorRaiz Elemento a colocar en la raiz del arbol
            /// @remarks Requiere que no exita raiz previamente
            inline void PonerRaiz(const Elemento& valorRaiz)
            {
                if (this->raiz != nullptr) 
                    throw RaizPreexistente();

                this->raiz = new NodoConcreto(valorRaiz);
                this->cantidadNodos = 1;
            }

            /// @brief Agrega un elemento como un primer hijo de un nodo de un arbol
            /// @param valorHijo Elemento a colocar dentro del nuevo nodo hijo
            /// @param nodoPadre Nodo padre al cual agregarle el hijo
            /// @return Nodo creado como hijo del nodo padre
            /// @remarks Requiere que el nodo padre no sea nulo
            inline Nodo AgregarHijo(const Elemento& valorHijo, const Nodo& nodoPadre)
            {
                if (nodoPadre.nodoConcreto == nullptr)
                    throw NodoConcretoInvalido();
                
                NodoConcreto* viejoPrimerHijo = nodoPadre.nodoConcreto->hijoMasIzquierdo;
                NodoConcreto* nuevoPrimerHijo = new NodoConcreto(valorHijo);

                nodoPadre.nodoConcreto->hijoMasIzquierdo = nuevoPrimerHijo;
                nuevoPrimerHijo->hermanoDerecho = viejoPrimerHijo;

                ++this->cantidadNodos;
                return Nodo(nuevoPrimerHijo);
            }

            /// @brief Agrega un elemento como un ultimo hijo de un nodo de un arbol
            /// @param valorHijo Elemento a colocar dentro del nuevo nodo hijo
            /// @param nodoPadre Nodo padre al cual agregarle el hijo
            /// @return Nodo creado como hijo del nodo padre
            /// @remarks Requiere que el nodo padre no sea nulo
            inline Nodo AgregarHijoMasDerecho(const Elemento& valorHijo, const Nodo& nodoPadre)
            {
                if (nodoPadre.nodoConcreto == nullptr)
                    throw NodoConcretoInvalido();

                NodoConcreto* it = nodoPadre.nodoConcreto->hijoMasIzquierdo;
                NodoConcreto* nuevoUltimoHijo = new NodoConcreto(valorHijo);

                // Caso 1: No hay hijos todavia
                if (it == nullptr)
                    nodoPadre.nodoConcreto->hijoMasIzquierdo = nuevoUltimoHijo;
                // Caso 2: Si hay hijos
                else
                {
                    while (it->hermanoDerecho != nullptr)
                        it = it->hermanoDerecho;

                    it->hermanoDerecho = nuevoUltimoHijo;
                }

                ++this->cantidadNodos;
                return Nodo(nuevoUltimoHijo);
            }

            /// @brief Elimina un nodo como hoja de un arbol
            /// @param nodoHoja Nodo padre al cual agregarle el hijo
            /// @remarks Requiere que el nodo hoja no sea nulo
            inline void BorrarHoja(const Nodo& nodoHoja)
            {
                if (this->raiz == nullptr)
                    throw RaizNula();

                if (nodoHoja.nodoConcreto == nullptr)
                    throw NodoConcretoInvalido();

                // Caso base: La hoja a borrar es la raiz
                if (nodoHoja == this->Raiz())
                {
                    // Si la raiz no es una hoja, entonces no podemos borrarla
                    if (this->raiz->hijoMasIzquierdo != nullptr)
                        throw NodoNoEsHoja();
                    
                    // Sino, podemos borrarla, y nuestra raíz pasara a ser nula
                    delete this->raiz;
                    this->raiz = nullptr;

                    return;
                }

                // Para mantener la integridad del arbol, es requerimiento que el nodo parametro sea una hoja
                if (nodoHoja.nodoConcreto->hijoMasIzquierdo != nullptr)
                    throw NodoNoEsHoja();

                // Es necesario buscar en todo el arbol al padre de este nodo hoja
                // Por eso, realizaremos un recorrido por niveles utilizando una cola de nodos
                Util::Cola<Nodo> colaNodos;

                // Encolemos a la raiz para iniciar el recorrido usandola como punto de partida
                colaNodos.Encolar(this->Raiz());

                // Mientras tengamos nodos en la cola, o no hayamos borrado la hoja todavia, no hemos terminado el recorrido
                bool hojaBorrada = false;
                while (!colaNodos.Vacio() && !hojaBorrada)
                {
                    // Siempre obtendremos el nodo encolado mas antigüamente (de primero)
                    Nodo nodoActual = colaNodos.Desencolar();

                    // Tras obtener un nodo, analizaremos cada hijo y su hermano izquierdo
                    // Para ello tenemos que lidiar con el nodo concreto subyacente
                    NodoConcreto* padreConcreto = nodoActual.nodoConcreto;
                    if (padreConcreto == nullptr)
                        throw NodoConcretoInvalido();

                    NodoConcreto* hermanoIzquierdo = nullptr;
                    for (NodoConcreto* it = padreConcreto->hijoMasIzquierdo; it != nullptr; it = it->hermanoDerecho)
                    {
                        // Si resulta ser distinto que la hoja buscada, lo encolaremos
                        if (it != nodoHoja.nodoConcreto)
                            colaNodos.Encolar(Nodo(it));

                        // Sino, entonces lo borraremos de entre sus hermanos y terminaremos el recorrido
                        else 
                        {
                            // Consideraremos a un hermano derecho hipotetico. No se distingue si es nulo o no
                            NodoConcreto* hermanoDerecho = it->hermanoDerecho;

                            // Caso 1: No hay hermano izquierdo (la hoja esta es el hijo mas izquierdo)
                            if (hermanoIzquierdo == nullptr)
                                padreConcreto->hijoMasIzquierdo = hermanoDerecho;

                            // Caso 2: Si hay hermano izquierdo
                            else 
                                hermanoIzquierdo->hermanoDerecho = hermanoDerecho;

                            // Ya cambiamos los enlaces del arbol. Borremos a la hoja
                            delete it;

                            // Ya borramos la hoja. Dejaremos de encolar hijos y escaparemos el recorrido
                            hojaBorrada = true;
                            break;
                        }

                        // De continuar el ciclo, el hermano izquierdo de la siguiente iteracion seria el hijo de esta
                        hermanoIzquierdo = it;
                    }
                }

                // Para este punto, la hoja ya fue borrada
                --this->cantidadNodos;
            }

            /// @brief Cambia la etiqueta de un nodo de un arbol por otra nueva
            /// @param nodo Nodo al cual sustituirle la etiqueta
            /// @param nuevoValor Elemento con el cual basarse para construir una copia y asi reemplazar a la etiqueta
            /// @remarks Requiere que el nodo no sea nulo, y que el elemento tenga un constructor por copia valido
            inline void ModificaEtiqueta(const Elemento& nuevoValor, const Nodo& nodo) const
            {
                if (nodo.nodoConcreto == nullptr)
                    throw NodoConcretoInvalido();

                nodo.nodoConcreto->cambiarElemento(nuevoValor);
            }

            /// @brief Recupera la etiqueta de un nodo de un arbol
            /// @param nodo Nodo del cual recuperar la etiqueta
            /// @return Etiqueta recuperada del nodo
            /// @remarks Requiere que el nodo no sea nulo
            inline const Elemento& Etiqueta(const Nodo& nodo) const
            {
                if (nodo.nodoConcreto == nullptr)
                    throw NodoConcretoInvalido();
                
                return nodo.nodoConcreto->getElemento();
            }
            
            /// @brief Recupera el nodo raiz de un arbol
            /// @return Presunta raiz del arbol. Nodo nulo si resulta no existir (caso arbol vacio)
            /// @remarks Si el arbol no tiene al menos una raiz, el nodo recuperado es nulo
            inline Nodo Raiz() const
            {return Nodo(this->raiz);}

            /// @brief Recupera el nodo correspondiente al padre de otro nodo
            /// @param nodoHijo Nodo del cual recuperar el nodo padre
            /// @return Presunto padre del nodo. Nodo nulo si resulta no tener padre (caso de la raiz)
            /// @remarks Requiere que el nodo no sea nulo, y que exista una raiz previamente en el arbol
            inline Nodo Padre(const Nodo& nodoHijo) const
            {
                if (nodoHijo.nodoConcreto == nullptr)
                    throw NodoConcretoInvalido();

                if (this->raiz == nullptr)
                    throw RaizNula();

                NodoConcreto* hijoConcreto = nodoHijo.nodoConcreto;

                // Caso 1: El nodo es la raiz (No tiene padre / Tiene padre nulo)
                if (hijoConcreto == this->raiz)
                    return Nodo();

                // Caso 2: El nodo no es la raiz (Debe de tener padre) 
                // Es necesario buscar en todo el arbol al padre de este nodo hoja
                // Por eso, realizaremos un recorrido por niveles utilizando una cola de nodos
                Util::Cola<Nodo> colaNodos;

                // Encolemos a la raiz para iniciar el recorrido usandola como punto de partida
                colaNodos.Encolar(this->Raiz());

                // Mientras tengamos nodos en la cola, no hemos terminado el recorrido
                // Si resulta que encontramos al padre, escaparemos el recorrido mediante un retorno prematuro
                while (!colaNodos.Vacio())
                {
                    // Siempre obtendremos el nodo encolado mas antigüamente (de primero)
                    Nodo nodoActual = colaNodos.Desencolar();

                    // Tras obtener un nodo, analizaremos cada hijo
                    // Para ello tenemos que lidiar con el nodo concreto subyacente
                    NodoConcreto* padreConcreto = nodoActual.nodoConcreto;
                    if (padreConcreto == nullptr)
                        throw NodoConcretoInvalido();

                    for (NodoConcreto* it = padreConcreto->hijoMasIzquierdo; it != nullptr; it = it->hermanoDerecho)
                    {
                        // Si resulta ser distinto que el hijo alimentado, lo encolaremos
                        if (it != hijoConcreto)
                            colaNodos.Encolar(Nodo(it));

                        // Sino, entonces significa que encontramos al padre
                        else 
                            return Nodo(padreConcreto);
                    }
                }

                // Si resulta que no hemos encontrado al padre, entonces este nodo debe ser foraneo a este arbol
                throw NodoEsForaneo();
            }

            /// @brief Recupera el nodo correspondiente al hijo mas izquierdo de otro nodo
            /// @param nodo Nodo del cual recuperar el hijo mas izquierdo
            /// @return Presunto hijo mas izquierdo. Nodo nulo si resulta no tener hijos (caso de las hojas)
            /// @remarks Requiere que el nodo no sea nulo
            inline Nodo HijoMasIzquierdo(const Nodo& nodo) const
            {
                if (nodo.nodoConcreto == nullptr)
                    throw NodoConcretoInvalido();
                
                return Nodo(nodo.nodoConcreto->hijoMasIzquierdo);
            }

            /// @brief Recupera el nodo correspondiente al hermando derecho de otro nodo
            /// @param nodo Nodo del cual recuperar el hermano derecho inmediato
            /// @return Presunto hermano derecho inmediato. Nodo nulo si resulta no tener hermanos (caso hijo unico)
            /// @remarks Requiere que el nodo no sea nulo
            inline Nodo HermanoDerecho(const Nodo& nodo) const
            {
                if (nodo.nodoConcreto == nullptr)
                    throw NodoConcretoInvalido();
                
                return Nodo(nodo.nodoConcreto->hermanoDerecho);
            }

            /// @brief Recupera la cantidad de nodos existentes en este arbol
            /// @return Cantidad de nodos existentes en todo el arbol
            inline const size_t NumNodos() const
            {return this->cantidadNodos;}
    };

    template <typename Elemento>
    std::ostream& operator<<(std::ostream& salida, const Arbol<Elemento>& arbol)
    {
        // Imprimamos la cantidad de nodos presentes en el arbol
        salida << "N = " << arbol.cantidadNodos << std::endl;

        // Caso 1: El arbol tiene raiz nula (no tiene nodos)
        if (arbol.raiz == nullptr)
            return salida;

        // Caso 2: El arbol tiene nodos
        // Realizaremos un recorrido por niveles utilizando una cola de nodos
        Util::Cola<typename Arbol<Elemento>::Nodo> colaNodos;

        // Encolemos a la raiz para iniciar el recorrido usandola como punto de partida
        colaNodos.Encolar(arbol.Raiz());

        // Adicionalmente, imprimiremos sus contenidos de primero
        salida << '[' << arbol.raiz->getElemento() << ']' << std::endl;

        // Adicionalmente, llevaremos cuenta de cuantos nodos corresponden al nivel actual y su correspondiente siguiente
        size_t nodosPendientesNivelActual = 1;
        size_t nodosPendientesNivelSiguiente = 0;

        // Mientras tengamos nodos en la cola, no hemos terminado el recorrido
        // Si resulta que encontramos al padre, escaparemos el recorrido mediante un retorno prematuro
        while (!colaNodos.Vacio())
        {
            // Siempre obtendremos el nodo encolado mas antigüamente (de primero)
            auto nodoActual = colaNodos.Desencolar();

            // Tras obtener ese nodo, la cantidad de nodos pendientes en el nivel actual disminuye en 1
            --nodosPendientesNivelActual;

            // Tras obtener un nodo, encolaremos cada hijo
            // Para distinguir a cada grupo de hijos, encerraremos la impresion de cada grupo entre llaves
            salida << "[";
            auto padreConcreto = nodoActual.nodoConcreto;
            for (auto it = padreConcreto->hijoMasIzquierdo; it != nullptr; it = it->hermanoDerecho)
            {
                // Tras obtener un hijo, imprimiremos sus contenidos
                salida << it->getElemento();

                // Si el hijo tiene un hermano derecho, entonces los separeremos a ambos mediante un espacio
                if (it->hermanoDerecho != nullptr)
                    salida << ' ';

                // Luego, tras imprimir sus contenidos, lo encolaremos
                colaNodos.Encolar(typename Arbol<Elemento>::Nodo(it));

                // Tras encolar un hijo, la cantidad de nodos pendientes en el nivel siguiente aumenta
                ++nodosPendientesNivelSiguiente;
            }
            salida << "] ";
            
            // Si ya no hay nodos pendientes en este nivel, entonces hemos cambiado de nivel
            if (nodosPendientesNivelActual == 0)
            {
                // La cantidad de nodos pendientes en este nivel corresponden a la cantidad de nodos pendientes para el siguiente
                nodosPendientesNivelActual = nodosPendientesNivelSiguiente;

                // Luego, como cambiamos de nivel, la cantidad de nodos pendientes para el siguiente nivel se asume como 0 de nuevo
                nodosPendientesNivelSiguiente = 0;

                // Adicionalmente podemos realizar un salto de nivel en la impresion
                salida << std::endl;
            }
        }
        
        return salida;
    }
};

#endif
