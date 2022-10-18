#include <exception> // Para las excepciones
#include <cstddef> // Para poder usar size_t

#include <iostream> // Para impresiones en la salida estándar
#include <queue> // Para probar recorrido por niveles usando la cola STL de placeholder

/// @brief Excepción para cuando se intenta desreferenciar un puntero a elemento nulo (a nivel de nodo concreto)
class ElementoInvalido : public std::exception 
{
    public:
        ElementoInvalido() {}
        ~ElementoInvalido() {}

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
    // TODO: Migrar de la cola STL a la cola de Archi

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
                /// @brief Apuntador al nodo concreto correspondiente al hermano izquierdo de este nodo concreto
                NodoConcreto* hermanoIzquierdo = nullptr;
                /// @brief Apuntador al nodo concreto correspondiente al padre de este nodo concreto
                NodoConcreto* padre = nullptr;
                /// @brief Apuntador al nodo concreto correspondiente al hijo más izquierdo de este nodo concreto
                NodoConcreto* hijoMasIzquierdo = nullptr;

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
                        throw ElementoInvalido();
                    
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
                Nodo(NodoConcreto* nodoConcreto = nullptr)
                {this->nodoConcreto = nodoConcreto;}

            public:
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
            std::queue<Nodo> colaNodos;

            // Encolemos a la raiz para iniciar el recorrido usándola como punto de partida
            colaNodos.push(this->Raiz());

            // Mientras tengamos nodos en la cola, no hemos terminado el recorrido
            while (!colaNodos.empty())
            {
                // Siempre obtendremos el nodo encolado más antigüamente (de primero)
                Nodo nodoActual = colaNodos.front();
                colaNodos.pop();

                // Tras obtener un nodo, encolaremos todos sus hijos
                // Para ello tenemos que lidiar con el nodo concreto subyacente
                NodoConcreto* padreConcreto = nodoActual.nodoConcreto;
                if (padreConcreto == nullptr)
                    throw NodoConcretoInvalido();

                // Únicamente podemos citar a los hijos de este nodo si es que tiene hijos
                if (padreConcreto->hijoMasIzquierdo != nullptr)
                {
                    for (NodoConcreto* it = padreConcreto->hijoMasIzquierdo; it != nullptr; it = it->hermanoDerecho)
                        colaNodos.push(Nodo(it));
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

            // Primero hay que establecer los señaladores entre padre e hijo
            nodoPadre.nodoConcreto->hijoMasIzquierdo = nuevoPrimerHijo;
            nuevoPrimerHijo->padre = nodoPadre.nodoConcreto;

            // Segundo, hay que establecer los señaladores entre hermanos
            nuevoPrimerHijo->hermanoDerecho = previoPrimerHijo;

            // Si existía un previo primer hijo (no es nulo), entonces su hermano izquierdo será el nuevo primer hijo
            if (previoPrimerHijo != nullptr)
                previoPrimerHijo->hermanoIzquierdo = nuevoPrimerHijo;

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

            // Obtengamos al nodo padre e hijo, concretos, para realizar señaladores
            NodoConcreto* it = nodoPadre.nodoConcreto->hijoMasIzquierdo;
            NodoConcreto* nuevoUltimoHijo = new NodoConcreto(valorHijo);

            // Primero hay que establecer los señaladores entre padre e hijo
            nuevoUltimoHijo->padre = nodoPadre.nodoConcreto;

            // Caso 1: No hay hijos todavía
            if (it == nullptr)
                nodoPadre.nodoConcreto->hijoMasIzquierdo = nuevoUltimoHijo;

            // Caso 2: Sí hay hijos
            else
            {
                // Naveguemos al hermano más derecho entre los hijos
                while (it->hermanoDerecho != nullptr)
                    it = it->hermanoDerecho;

                // Segundo, establezcamos los señaladores entre hermanos
                it->hermanoDerecho = nuevoUltimoHijo;
                nuevoUltimoHijo->hermanoIzquierdo = it;
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

            // Obtengamos al padre
            NodoConcreto* padreConcreto = nodoHoja.nodoConcreto->padre;

            // Ya que conocemos al padre, podemos borrar al hijo, considerando si ya borramos
            // a la hoja (para escapar el recorrido)
            bool hojaBorrada = false;
            for (NodoConcreto* it = padreConcreto->hijoMasIzquierdo; it != nullptr; it = it->hermanoDerecho)
            {
                // Si encontramos al hijo, entonces cambiaremos los enlaces entre sus hermanos adyacentes
                if (it == nodoHoja.nodoConcreto)
                {
                    NodoConcreto* hermanoIzquierdo = it->hermanoIzquierdo;
                    NodoConcreto* hermanoDerecho = it->hermanoDerecho;

                    if (hermanoIzquierdo != nullptr)
                        it->hermanoIzquierdo->hermanoDerecho = hermanoDerecho;

                    if (hermanoDerecho != nullptr)
                        it->hermanoDerecho->hermanoIzquierdo = hermanoIzquierdo;

                    // Adicionalmente, si la hoja que estamos borrando es el hijo más izquierdo del padre, entonces
                    // el nuevo hijo más izquierdo del padre será el hermano derecho del viejo hijo más izquierdo
                    if (it == padreConcreto->hijoMasIzquierdo) // it->hermanoIzquierdo == nullptr
                        padreConcreto->hijoMasIzquierdo = hermanoDerecho;
                }

                // Tras este punto, ya se cambiaron los enlaces de los nodos, y ahora se puede borrar a este nodo
                delete it;
                hojaBorrada = true;
                break;
            }

            // Si la hoja no fue borrada tras aquel recorrido, entonces eso significa que la hoja no está correctamente
            // enlazada etre sus hermanos
            if (!hojaBorrada)
                throw NodoEsForaneo();
        }

        /// @brief Cambia la etiqueta de un nodo de un árbol por otra nueva
        /// @param nodo Nodo al cual sustituirle la etiqueta
        /// @param nuevoValor Elemento con el cual basarse para construir una copia y así reemplazar a la etiqueta
        /// @remarks Requiere que el nodo no sea nulo, y que el elemento tenga un constructor por copia válido
        inline void ModificaEtiqueta(const Nodo& nodo, const Elemento& nuevoValor) const
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
        /// @remarks Requiere que el nodo no sea nulo
        inline Nodo Padre(const Nodo& nodoHijo) const
        {
            if (nodoHijo.nodoConcreto == nullptr)
                throw NodoConcretoInvalido();

            return Nodo(nodoHijo.nodoConcreto->padre);
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
            std::queue<Nodo> colaNodos;

            // Encolemos a la raiz para iniciar el recorrido usándola como punto de partida
            colaNodos.push(this->Raiz());

            // Mientras tengamos nodos en la cola, no hemos terminado el recorrido
            while (!colaNodos.empty())
            {
                // Siempre obtendremos el nodo encolado más antigüamente (de primero)
                Nodo nodoActual = colaNodos.front();
                colaNodos.pop();

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
                    for (NodoConcreto* it = padreConcreto->hijoMasIzquierdo; it != nullptr; it = it->hermanoDerecho)
                        colaNodos.push(Nodo(it));
                }
            }

            return cantidadNodos;
        }
};

template <typename Elemento>
std::ostream& operator<<(std::ostream& salida, const Arbol<Elemento>& arbol)
{
    // Imprimamos la cantidad de nodos presentes en el árbol
    std::cout << "N = " << arbol.NumNodos() << std::endl;

    // Caso 1: El árbol tiene raíz nula (no tiene nodos)
    if (arbol.raiz == nullptr)
        return salida;

    // Caso 2: El árbol tiene nodos
    // Realizaremos un recorrido por niveles utilizando una cola de nodos
    std::queue<typename Arbol<Elemento>::Nodo> colaNodos;

    // Encolemos a la raiz para iniciar el recorrido usándola como punto de partida
    colaNodos.push(arbol.Raiz());

    // Adicionalmente, imprimiremos sus contenidos de primero
    std::cout << '[' << arbol.raiz->getElemento() << ']' << std::endl;

    // Adicionalmente, llevaremos cuenta de cuántos nodos corresponden al nivel actual y su correspondiente siguiente
    size_t nodosPendientesNivelActual = 1;
    size_t nodosPendientesNivelSiguiente = 0;

    // Mientras tengamos nodos en la cola, no hemos terminado el recorrido
    // Si resulta que encontramos al padre, escaparemos el recorrido mediante un retorno prematuro
    while (!colaNodos.empty())
    {
        // Siempre obtendremos el nodo encolado más antigüamente (de primero)
        auto nodoActual = colaNodos.front();
        colaNodos.pop();

        // Tras obtener ese nodo, la cantidad de nodos pendientes en el nivel actual disminuye en 1
        --nodosPendientesNivelActual;

        // Tras obtener un nodo, encolaremos cada hijo
        // Para distinguir a cada grupo de hijos, encerraremos la impresión de cada grupo entre llaves
        salida << "[";
        auto padreConcreto = nodoActual.nodoConcreto;

        // Únicamente citaremos a sus hijos si es que existen en el primer lugar
        if (padreConcreto->hijoMasIzquierdo != nullptr)
        {
            for (auto it = padreConcreto->hijoMasIzquierdo; it != nullptr; it = it->hermanoDerecho)
            {
                // Tras obtener un hijo, imprimiremos sus contenidos
                salida << it->getElemento();

                // Si el hijo tiene un hermano derecho, entonces los separeremos a ambos mediante un espacio
                if (it->hermanoDerecho != nullptr)
                    salida << ' ';

                // Luego, tras imprimir sus contenidos, lo encolaremos
                colaNodos.push(typename Arbol<Elemento>::Nodo(it));

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

/// @brief Mini demo, incompleta hasta terminar de implementar el árbol
int main()
{
    // Creación
    Arbol<int> a;
    std::cout << a << std::endl;
    std::cout << "^^^ Arbol tras crearlo ^^^" << std::endl;

    // Colocar Raíz
    a.PonerRaiz(1);
    Arbol<int>::Nodo raiz = a.Raiz();
    std::cout << a << std::endl;
    std::cout << "^^^ Arbol tras insertar 1 como raíz ^^^" << std::endl;

    // Agregar hijos
    Arbol<int>::Nodo nodo_2 = a.AgregarHijo(2, raiz);
    Arbol<int>::Nodo nodo_3 = a.AgregarHijoMasDerecho(3, raiz);
    a.AgregarHijoMasDerecho(4, raiz);
    std::cout << a << std::endl;
    std::cout << "^^^ Arbol tras insertar 2, 3 y 4 ^^^" << std::endl;

    Arbol<int>::Nodo nodo_5 = a.AgregarHijo(5, nodo_2);
    Arbol<int>::Nodo nodo_6 = a.AgregarHijoMasDerecho(6, nodo_2);
    a.AgregarHijoMasDerecho(7, nodo_2);
    std::cout << a << std::endl;
    std::cout << "^^^ Arbol tras insertar 5, 6 y 7 ^^^" << std::endl;

    Arbol<int>::Nodo nodo_8 = a.AgregarHijo(8, nodo_3);
    Arbol<int>::Nodo nodo_9 = a.AgregarHijoMasDerecho(9, nodo_3);
    a.AgregarHijoMasDerecho(10, nodo_3);
    std::cout << a << std::endl;
    std::cout << "^^^ Arbol tras insertar 8, 9 y 10 ^^^" << std::endl;

    // Borrar hojas
    a.BorrarHoja(nodo_8);
    a.BorrarHoja(nodo_9);
    std::cout << a << std::endl;
    std::cout << "^^^ Arbol tras borrar hojas 8 y 9 ^^^" << std::endl;

    // Recuperar etiquetas
    std::cout << "Etiqueta del nodo raiz = " << a.Etiqueta(a.Raiz()) << std::endl;
    std::cout << "Etiqueta del nodo 5 = " << a.Etiqueta(nodo_5) << std::endl;
    std::cout << "Etiqueta del nodo 6 = " << a.Etiqueta(nodo_6) << std::endl;

    // Modificar etiquetas
    a.ModificaEtiqueta(raiz, 111);
    a.ModificaEtiqueta(nodo_5, 555);
    std::cout << a << std::endl;
    std::cout << "^^^ Arbol tras modificar etiquetas 1 -> 111, 5 -> 555 ^^^" << std::endl;

    // Obtener cantidad de nodos
    std::cout << "Cantidad de nodos en el arbol = " << a.NumNodos() << std::endl;

    // Obtener el nodo padre
    std::cout << "Etiqueta del nodo padre del nodo 2 = " << a.Etiqueta(a.Padre(nodo_2)) << std::endl;
    std::cout << "Etiqueta del nodo padre del nodo 3 = " << a.Etiqueta(a.Padre(nodo_3)) << std::endl;
    std::cout << "Etiqueta del nodo padre del nodo 5 = " << a.Etiqueta(a.Padre(nodo_5)) << std::endl;

    // Obtener el nodo padre de la raiz
    Arbol<int>::Nodo padre_raiz = a.Padre(a.Raiz());
    std::cout << "¿Es el nodo padre de la raiz nulo?" << std::endl;
    try
    {
        a.Etiqueta(padre_raiz);
        std::cout << "No, es nulo." << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cout << "Sí, es nulo. La excepción es:" << std::endl;
        std::cout << "[ERROR] = " << e.what() << std::endl;
    }

    // TODO: Realizar pruebas de casos mas específicos
    // TODO: Probar el manejo de excepciones

    return 0;
}
