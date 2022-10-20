#ifndef ARBOL_HPP
#define ARBOL_HPP

#include <exception> // Para las excepciones
#include <cstddef> // Para poder usar size_t

#include <iostream> // Para impresiones en la salida estándar
#include "../CDE/Cola.hpp" // Para realizar recorridos por niveles

namespace Arbol_N_Ario
{
    /// @brief Excepción para cuando se intenta desreferenciar un puntero a elemento nulo (a nivel de nodo concreto)
    class ElementoInvalidoArbol : public std::exception
    {
        public:
            ElementoInvalidoArbol() {}
            ~ElementoInvalidoArbol() {}

            virtual const char* what() const noexcept
            {return "Imposible acceder a elemento. Es nulo";}
    };

    /// @brief Excepción para cuando se intenta desreferenciar un puntero a nodo concreto nulo
    class NodoConcretoInvalido : public std::exception 
    {
        public:
            NodoConcretoInvalido() {}
            ~NodoConcretoInvalido() {}

            virtual const char* what() const noexcept
            {return "Imposible acceder a nodo concreto. Es nulo";}
    };

    /// @brief Excepción para cuando se intenta desreferenciar un puntero a elemento nulo (a nivel de nodo)
    class DereferenciaNodoInvalida : public std::exception 
    {
        public:
            DereferenciaNodoInvalida() {}
            ~DereferenciaNodoInvalida() {}

            virtual const char* what() const noexcept
            {return "Imposible desreferenciar nodo, su elemento es nulo";}
    };

    /// @brief Excepción para cuando se maneja un nodo que debería existir en el árbol, pero no se encontró en él
    class NodoEsForaneo : public std::exception 
    {
        public:
            NodoEsForaneo() {}
            ~NodoEsForaneo() {}

            virtual const char* what() const noexcept
            {return "Nodo deberia existir en el arbol, pero no se encontro";}
    };

    /// @brief Excepción para cuando se maneja un nodo que requiere ser una hoja, pero no lo es
    class NodoNoEsHoja : public std::exception 
    {
        public:
            NodoNoEsHoja() {}
            ~NodoNoEsHoja() {}

            virtual const char* what() const noexcept
            {return "Hoja invalida. Nodo no es hoja";}
    };

    /// @brief Excepción para cuando se intenta inicializar una raíz ya existente
    class RaizPreexistente : public std::exception 
    {
        public:
            RaizPreexistente() {}
            ~RaizPreexistente() {}

            virtual const char* what() const noexcept
            {return "Imposible añadir raiz. Ya existe";}
    };

    /// @brief Excepción para cuando se intenta desreferenciar un puntero a raíz (nodo) nula
    class RaizNula : public std::exception 
    {
        public:
            RaizNula() {}
            ~RaizNula() {}

            virtual const char* what() const noexcept
            {return "Imposible acceder a raiz. Es nula";}
    };

    // Declaraciones adelantadas para resolver dependencias circulares en impresión

    /// @brief Árbol N-Ario implementado con Hijo-Más-Izquierdo, Hermano Derecho y contador
    template <typename Elemento>
    class Arbol;

    /// @brief Imprime los contenidos de un árbol de forma vertical a un flujo de salida
    /// @param salida Flujo de salida para imprimir los contenidos del árbol
    /// @param arbol Arbol N-ario del cual imprimir los contenidos
    /// @return Referencia al flujo de salida utilizado (para encadenar impresiones)
    template <typename Elemento>
    std::ostream& operator<<(std::ostream& salida, const Arbol<Elemento>& arbol);

    /// @brief Árbol N-Ario implementado con Hijo-Más-Izquierdo, Hermano Derecho y contador
    template <typename Elemento>
    class Arbol
    {
        // La función de impresión puede ver las entrañas de un Árbol
        template <typename T>
        friend std::ostream& operator<<(std::ostream&, const Arbol<T>&);

        protected: 
            /// @brief Nodo concreto, poseedor de elementos y poseído por el árbol
            class NodoConcreto
            {
                // Un Árbol pueden manipular las entrañas de un Nodo Concreto, y un Nodo verlas
                friend class Nodo;
                friend class Arbol;

                // La función de impresión puede ver las entrañas de un Nodo Concreto
                template <typename T>
                friend std::ostream& operator<<(std::ostream&, const Arbol<T>&);

                private:
                    /// @brief Elemento en la memoria dinámica apuntado (y poseído) por este nodo concreto
                    Elemento* elemento = nullptr;
                    /// @brief Apuntador al nodo concreto correspondiente al hermano derecho de este nodo concreto
                    NodoConcreto* hermanoDerecho = nullptr;
                    /// @brief Apuntador al nodo concreto correspondiente al hijo más izquierdo de este nodo concreto
                    NodoConcreto* hijoMasIzquierdo = nullptr;
                    /// @brief Bandera para indicar si el hermano derecho al que apunta este nodo es su padre
                    bool apuntaAlPadre = false;

                    /// @brief Inicializa a un nodo concreto apuntando a un nuevo elemento creado por copia
                    /// @param valorElemento Elemento el cual será usado como base para construir una copia
                    /// @remark Requiere que el elemento tenga un constructor por copia válido
                    NodoConcreto(const Elemento& valorElemento)
                    {this->elemento = new Elemento(valorElemento);}

                    /// @brief Libera la memoria del elemento apuntado, si resultase no ser nulo
                    /// @remark Requiere que el elemento tenga un destructor por defecto válido
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
                    /// @param nuevoValor Elemento el cual será usado como base para construir una copia
                    /// @remark Requiere que el elemento tenga un constructor por copia y destructor por defecto válidos
                    void cambiarElemento(const Elemento& nuevoValor)
                    {
                        delete this->elemento;
                        this->elemento = new Elemento(nuevoValor);
                    }
            };
        
        public:
            /// @brief Nodo lógico, interfaz entre nodo concreto y usuario del árbol
            class Nodo 
            {
                // Un Árbol puede ver y manipular las entrañas de un Nodo (lógico)
                friend class Arbol;

                // La función de impresión puede ver las entrañas de un Nodo (lógico)
                template <typename T>
                friend std::ostream& operator<<(std::ostream&, const Arbol<T>&);

                private:

                    /// @brief Nodo concreto apuntado (pero no poseído) por este nodo
                    NodoConcreto* nodoConcreto = nullptr;

                    /// @brief Inicializa a un nodo apuntando a un nodo concreto
                    /// @param nodoConcreto Apuntado a un nodo concreto al cual referenciar mediante este nodo
                    Nodo(NodoConcreto* nodoConcreto)
                    {this->nodoConcreto = nodoConcreto;}

                public:
                    /// @brief Crea un nodo nulo (no apunta a ningún nodo concreto)
                    Nodo() {}

                    /// @brief Clona el apuntador de un nodo concreto hacia este nodo
                    /// @param otroNodo Nodo del cual clonar el apuntador al nodo concreto
                    Nodo(const Nodo& otroNodo)
                    {this->nodoConcreto = otroNodo.nodoConcreto;}

                    /// @brief Limpia a este nodo, mas no al nodo concreto al que apunte (no lo posee, solo lo referencia)
                    virtual ~Nodo() {};

                    /// @brief Obtiene el elemento apuntado por el nodo concreto apuntado por este nodo
                    /// @return Elemento obtenido al desreferenciar el apuntador de elemento del nodo concreto
                    /// @remarks Requiere que el nodo concreto apuntado no sea nulo (existe), ni que ese apunte a un
                    // elemento nulo
                    const Elemento& operator->() const
                    {
                        if (nodoConcreto == nullptr)
                            throw NodoConcretoInvalido();

                        return nodoConcreto->getElemento();
                    }

                    /// @brief Compara si dos nodos apuntan al mismo nodo concreto en el árbol
                    /// @return Verdadero si apuntan al mismo nodo concreto, falso en caso contrario
                    bool operator==(const Nodo& otroNodo) const
                    {return this->nodoConcreto == otroNodo.nodoConcreto;}

                    /// @brief Compara si dos nodos apuntan a distintos nodos concretos en el árbol
                    /// @return Verdadero si apuntan a distintos concretos, falso en caso contrario
                    bool operator!=(const Nodo& otroNodo) const
                    {return this->nodoConcreto != otroNodo.nodoConcreto;}
            };

        protected:
            /// @brief Nodo concreto, inicial del árbol
            NodoConcreto* raiz = nullptr;

        public:

            /// @brief Inicializa a un árbol en un estado por defecto
            Arbol() {}

            /// @brief Elimina los nodos de un árbol
            ~Arbol() noexcept(false)
            {
                // Utilicemos una cola de nodos para realizar un recorrido por niveles
                Util::Cola<Nodo> colaNodos;

                // Encolemos a la raiz para iniciar el recorrido usándola como punto de partida
                colaNodos.Encolar(this->Raiz());

                // Mientras tengamos nodos en la cola, no hemos terminado el recorrido
                while (!colaNodos.Vacio())
                {
                    // Siempre obtendremos el nodo encolado más antigüamente (de primero)
                    Nodo nodoActual = colaNodos.Desencolar();

                    // Tras obtener un nodo, encolaremos todos sus hijos
                    // Para ello tenemos que lidiar con el nodo concreto subyacente
                    NodoConcreto* padreConcreto = nodoActual.nodoConcreto;
                    if (padreConcreto == nullptr)
                        throw NodoConcretoInvalido();

                    // Únicamente podemos citar a los hijos de este nodo si es que tiene hijos
                    if (padreConcreto->hijoMasIzquierdo != nullptr)
                    {
                        for (NodoConcreto* it = padreConcreto->hijoMasIzquierdo; it != padreConcreto; it = it->hermanoDerecho)
                            colaNodos.Encolar(Nodo(it));
                    }

                    // Luego, destruiremos al nodo concreto subyacente del nodo que desencolamos
                    // Esto libera los recursos manejados por el nodo concreto
                    delete padreConcreto;
                }
            }

            /// @brief Coloca un elemento en la raíz del arbol como un nodo
            /// @param valorRaiz Elemento a colocar en la raiz del arbol
            /// @remarks Requiere que no exita raiz previamente
            inline void PonerRaiz(const Elemento& valorRaiz)
            {
                if (this->raiz != nullptr) 
                    throw RaizPreexistente();

                this->raiz = new NodoConcreto(valorRaiz);
            }

            /// @brief Agrega un elemento como un primer hijo de un nodo de un árbol
            /// @param valorHijo Elemento a colocar dentro del nuevo nodo hijo
            /// @param nodoPadre Nodo padre al cual agregarle el hijo
            /// @return Nodo creado como hijo del nodo padre
            /// @remarks Requiere que el nodo padre no sea nulo
            inline Nodo AgregarHijo(const Elemento& valorHijo, const Nodo& nodoPadre)
            {
                if (nodoPadre.nodoConcreto == nullptr)
                    throw NodoConcretoInvalido();
                
                NodoConcreto* previoPrimerHijo = nodoPadre.nodoConcreto->hijoMasIzquierdo;
                NodoConcreto* nuevoPrimerHijo = new NodoConcreto(valorHijo);

                nodoPadre.nodoConcreto->hijoMasIzquierdo = nuevoPrimerHijo;

                // Si no existía primer hijo previamente (es nulo), entonces este nuevo primer hijo debe
                // de tener como hermano derecho a su padre (y así cerrar el camino entre él y su padre)
                if (previoPrimerHijo == nullptr)
                {
                    nuevoPrimerHijo->hermanoDerecho = nodoPadre.nodoConcreto;
                    nuevoPrimerHijo->apuntaAlPadre = true;
                }
                // Sino, entonces su hermano derecho es el previo primer hijo (ahora el segundo hijo)
                else
                    nuevoPrimerHijo->hermanoDerecho = previoPrimerHijo;

                return Nodo(nuevoPrimerHijo);
            }

            /// @brief Agrega un elemento como un último hijo de un nodo de un árbol
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

                // Caso 1: No hay hijos todavía
                if (it == nullptr)
                {
                    nodoPadre.nodoConcreto->hijoMasIzquierdo = nuevoUltimoHijo;

                    // Es necesario que el primer hijo tenga de hermano derecho a su padre, para cerrar el camino
                    // entre él y su padre
                    nuevoUltimoHijo->hermanoDerecho = nodoPadre.nodoConcreto;
                    nuevoUltimoHijo->apuntaAlPadre = true;
                }
                    
                // Caso 2: Sí hay hijos
                else
                {
                    while (!it->apuntaAlPadre)
                        it = it->hermanoDerecho;

                    // El previo último hijo ahora debe tener de hermano derercho al nuevo último hijo, en vez de
                    // tener de hermano derecho a su padre
                    it->hermanoDerecho = nuevoUltimoHijo;
                    it->apuntaAlPadre = false;

                    // Es necesario que el nuevo último hijo tenga de hermano derecho a su padre, para cerrar el camino
                    // entre todos los hermanos y su padre, y tomar el rol que tenía el previo último hijo
                    nuevoUltimoHijo->hermanoDerecho = nodoPadre.nodoConcreto;
                    nuevoUltimoHijo->apuntaAlPadre = true;
                }

                return Nodo(nuevoUltimoHijo);
            }

            /// @brief Elimina un nodo como hoja de un árbol
            /// @param nodoHoja Nodo padre al cual agregarle el hijo
            /// @remarks Requiere que el nodo hoja no sea nulo
            inline void BorrarHoja(const Nodo& nodoHoja)
            {
                if (this->raiz == nullptr)
                    throw RaizNula();

                if (nodoHoja.nodoConcreto == nullptr)
                    throw NodoConcretoInvalido();

                // Para mantener la integridad del árbol, es requerimiento que el nodo parámetro sea una hoja
                if (nodoHoja.nodoConcreto->hijoMasIzquierdo != nullptr)
                    throw NodoNoEsHoja();

                // Naveguemos hasta llegar al último hijo, y luego al padre
                NodoConcreto* padreConcreto = nodoHoja.nodoConcreto;
                while (!padreConcreto->apuntaAlPadre) padreConcreto = padreConcreto->hermanoDerecho; 
                padreConcreto = padreConcreto->hermanoDerecho;

                // Ya que conocemos al padre, podemos borrar al hijo, llevando cuenta de su hermano izquierdo, y si ya borramos
                // a la hoja (para escapar el recorrido)
                NodoConcreto* hermanoIzquierdo = nullptr;
                bool hojaBorrada = false;
                for (NodoConcreto* it = padreConcreto->hijoMasIzquierdo; it != padreConcreto; it = it->hermanoDerecho)
                {
                    // De encontrar a la hoja, debemos eliminarla y cambiar enlaces
                    if (it == nodoHoja.nodoConcreto)
                    {
                        // Caso 1: La hoja es el hijo más izquierdo (no hay hermano izquierdo)
                        if (hermanoIzquierdo == nullptr)
                        {
                            // Caso 1.1: La hoja es el hijo más derecho del árbol (el hermano derecho es el padre)
                            // Como la hoja es simultáneamente el primer y último hijo, debe ser el único hijo, y
                            //  el padre tendrá hijo nulo tras destruir su único hijo
                            if (it->apuntaAlPadre)
                                padreConcreto->hijoMasIzquierdo = nullptr;

                            // Caso 1.2: La hoja no es el hijo más derecho del árbol (el hermano derecho no es el padre)
                            // Como la hoja no es el último hermano, pero sí el primero, entonces el nuevo primer hijo será su hermano
                            else
                                padreConcreto->hijoMasIzquierdo = it->hermanoDerecho;
                        }
                        // Caso 2: La hoja no es el hijo más izquierdo del árbol (sí hay hermano izquierdo)
                        else
                        {
                            // Caso 2.1: La hoja es el hijo más derecho del árbol (el hermano derecho es el padre)
                            // Como la hoja no es el primer hijo, pero sí el último, entonces el hijo anterior debe
                            // apuntar al padre derecho como su hermano derecho
                            if (it->apuntaAlPadre)
                            {
                                hermanoIzquierdo->hermanoDerecho = padreConcreto;
                                hermanoIzquierdo->apuntaAlPadre = true;
                            }

                            // Caso 2.2: La hoja no es el hijo más derecho del árbol (el hermano derecho no es el padre)
                            // Como la hoja no es el primer ni último hijo, entonces el hermano derecho de este nodo será
                            // el nuevo hermano derecho de hermano izquierdo de este nodo
                            else
                                hermanoIzquierdo->hermanoDerecho = it->hermanoDerecho;
                        }

                        // Tras este punto, ya se cambiaron los enlaces de los nodos, y ahora se puede borrar a este nodo
                        delete it;
                        hojaBorrada = true;
                        break;
                    }

                    // Sino, tras esta iteración, el hermano izquierdo pasará a ser el hijo actual presente
                    hermanoIzquierdo = it;
                }

                // Si la hoja no fue borrada tras aquel recorrido, entonces eso significa que la hoja no existía en el árbol en el primer lugar
                if (!hojaBorrada)
                    throw NodoEsForaneo();
            }

            /// @brief Cambia la etiqueta de un nodo de un árbol por otra nueva
            /// @param nodo Nodo al cual sustituirle la etiqueta
            /// @param nuevoValor Elemento con el cual basarse para construir una copia y así reemplazar a la etiqueta
            /// @remarks Requiere que el nodo no sea nulo, y que el elemento tenga un constructor por copia válido
            inline void ModificaEtiqueta(const Elemento& nuevoValor, const Nodo& nodo) const
            {
                if (nodo.nodoConcreto == nullptr)
                    throw NodoConcretoInvalido();

                nodo.nodoConcreto->cambiarElemento(nuevoValor);
            }

            /// @brief Recupera la etiqueta de un nodo de un árbol
            /// @param nodo Nodo del cual recuperar la etiqueta
            /// @return Etiqueta recuperada del nodo
            /// @remarks Requiere que el nodo no sea nulo
            inline const Elemento& Etiqueta(const Nodo& nodo) const
            {
                if (nodo.nodoConcreto == nullptr)
                    throw NodoConcretoInvalido();
                
                return nodo.nodoConcreto->getElemento();
            }
            
            /// @brief Recupera el nodo raiz de un árbol
            /// @return Presunta raiz del arbol. Nodo nulo si resulta no existir (caso árbol vacío)
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
                // Naveguemos hasta llegar al último hijo, y luego al padre
                NodoConcreto* padreConcreto = nodoHijo.nodoConcreto;

                while (!padreConcreto->apuntaAlPadre) padreConcreto = padreConcreto->hermanoDerecho; 
                padreConcreto = padreConcreto->hermanoDerecho;

                return Nodo(padreConcreto);
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
            /// @return Presunto hermano derecho inmediato. Nodo nulo si resulta no tener hermanos (caso hijo único)
            /// @remarks Requiere que el nodo no sea nulo
            inline Nodo HermanoDerecho(const Nodo& nodo) const
            {
                if (nodo.nodoConcreto == nullptr)
                    throw NodoConcretoInvalido();
                
                // Si el nodo actual apunta al padre, se considera que no tiene hermano derecho
                if (nodo.nodoConcreto->apuntaAlPadre)
                    return Nodo();
                
                // Sino, entonces es trivial obtener su hermano derecho
                return Nodo(nodo.nodoConcreto->hermanoDerecho);
            }

            /// @brief Recupera la cantidad de nodos existentes en este arbol
            /// @return Cantidad de nodos existentes en todo el árbol
            inline const size_t NumNodos() const
            {
                // Si la raíz es nula (no hay nodos), entonces hay 0 nodos
                if (this->raiz == nullptr)
                    return 0;

                // Sino, recorreremos a todos los nodos, y llevaremos cuenta de cuántos nodos hemos recorrido
                size_t cantidadNodos = 0;

                // Utilicemos una cola de nodos para realizar un recorrido por niveles
                Util::Cola<Nodo> colaNodos;

                // Encolemos a la raiz para iniciar el recorrido usándola como punto de partida
                colaNodos.Encolar(this->Raiz());

                // Mientras tengamos nodos en la cola, no hemos terminado el recorrido
                while (!colaNodos.Vacio())
                {
                    // Siempre obtendremos el nodo encolado más antigüamente (de primero)
                    Nodo nodoActual = colaNodos.Desencolar();

                    // Tras adquirir ese nodo, tenemos que registrarlo en la cantidad de nodos recorridos
                    ++cantidadNodos;

                    // Luego, tras obtenerlo, encolaremos todos sus hijos
                    // Para ello tenemos que lidiar con el nodo concreto subyacente
                    NodoConcreto* padreConcreto = nodoActual.nodoConcreto;
                    if (padreConcreto == nullptr)
                        throw NodoConcretoInvalido();

                    // Únicamente podemos citar a los hijos de este nodo si es que tiene hijos
                    if (padreConcreto->hijoMasIzquierdo != nullptr)
                    {
                        for (NodoConcreto* it = padreConcreto->hijoMasIzquierdo; it != padreConcreto; it = it->hermanoDerecho)
                            colaNodos.Encolar(Nodo(it));
                    }
                }

                return cantidadNodos;
            }
    };

    template <typename Elemento>
    std::ostream& operator<<(std::ostream& salida, const Arbol<Elemento>& arbol)
    {
        // Imprimamos la cantidad de nodos presentes en el árbol
        salida << "N = " << arbol.NumNodos() << std::endl;

        // Caso 1: El árbol tiene raíz nula (no tiene nodos)
        if (arbol.raiz == nullptr)
            return salida;

        // Caso 2: El árbol tiene nodos
        // Realizaremos un recorrido por niveles utilizando una cola de nodos
        Util::Cola<typename Arbol<Elemento>::Nodo> colaNodos;

        // Encolemos a la raiz para iniciar el recorrido usándola como punto de partida
        colaNodos.Encolar(arbol.Raiz());

        // Adicionalmente, imprimiremos sus contenidos de primero
        salida << '[' << arbol.raiz->getElemento() << ']' << std::endl;

        // Adicionalmente, llevaremos cuenta de cuántos nodos corresponden al nivel actual y su correspondiente siguiente
        size_t nodosPendientesNivelActual = 1;
        size_t nodosPendientesNivelSiguiente = 0;

        // Mientras tengamos nodos en la cola, no hemos terminado el recorrido
        // Si resulta que encontramos al padre, escaparemos el recorrido mediante un retorno prematuro
        while (!colaNodos.Vacio())
        {
            // Siempre obtendremos el nodo encolado más antigüamente (de primero)
            auto nodoActual = colaNodos.Desencolar();

            // Tras obtener ese nodo, la cantidad de nodos pendientes en el nivel actual disminuye en 1
            --nodosPendientesNivelActual;

            // Tras obtener un nodo, encolaremos cada hijo
            // Para distinguir a cada grupo de hijos, encerraremos la impresión de cada grupo entre llaves
            salida << "[";
            auto padreConcreto = nodoActual.nodoConcreto;

            // Únicamente citaremos a sus hijos si es que existen en el primer lugar
            if (padreConcreto->hijoMasIzquierdo != nullptr)
            {
                for (auto it = padreConcreto->hijoMasIzquierdo; it != padreConcreto; it = it->hermanoDerecho)
                {
                    // Tras obtener un hijo, imprimiremos sus contenidos
                    salida << it->getElemento();

                    // Si el hijo tiene un hermano derecho, entonces los separeremos a ambos mediante un espacio
                    if (!it->apuntaAlPadre)
                        salida << ' ';

                    // Luego, tras imprimir sus contenidos, lo encolaremos
                    colaNodos.Encolar(typename Arbol<Elemento>::Nodo(it));

                    // Tras encolar un hijo, la cantidad de nodos pendientes en el nivel siguiente aumenta
                    ++nodosPendientesNivelSiguiente;
                }
            }
            salida << "] ";
            
            // Si ya no hay nodos pendientes en este nivel, entonces hemos cambiado de nivel
            if (nodosPendientesNivelActual == 0)
            {
                // La cantidad de nodos pendientes en este nivel corresponden a la cantidad de nodos pendientes para el siguiente
                nodosPendientesNivelActual = nodosPendientesNivelSiguiente;

                // Luego, como cambiamos de nivel, la cantidad de nodos pendientes para el siguiente nivel se asume como 0 de nuevo
                nodosPendientesNivelSiguiente = 0;

                // Adicionalmente podemos realizar un salto de nivel en la impresión
                salida << std::endl;
            }
        }
        
        return salida;
    }
}

#endif
