#include <exception> // Para las excepciones
#include <cstddef> // Para poder usar size_t

#include <iostream> // Para impresiones en la salida estándar

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

/// @brief Árbol N-Ario implementado con Hijo-Más-Izquierdo, Hermano Derecho y contador
template <typename Elemento>
class Arbol 
{
    protected: 
        /// @brief Nodo concreto, poseedor de elementos y poseído por el árbol
        class NodoConcreto
        {
            friend class Nodo;
            friend class Arbol;

            private:
                /// @brief Elemento en la memoria dinámica apuntado (y poseído) por este nodo concreto
                Elemento* elemento = nullptr;
                /// @brief Apuntador al nodo concreto correspondiente al hermano derecho de este nodo concreto
                NodoConcreto* hermanoDerecho = nullptr;
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
            friend class Arbol;

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
        /// @brief Cantidad de elementos existentes en total en todo el árbol (a partir de la raíz, incluyéndola)
        size_t cantidadNodos = 0;

    public:

        /// @brief Inicializa a un árbol en un estado por defecto
        Arbol() {}

        /// @brief Elimina los nodos de un árbol
        ~Arbol()
        {
            // TODO: Usar cola para recorrido por niveles
        }

        /// @brief Coloca un elemento en la raíz del arbol como un nodo
        /// @param valorRaiz Elemento a colocar en la raiz del arbol
        /// @remarks Requiere que no exita raiz previamente
        inline void PonerRaiz(const Elemento& valorRaiz)
        {
            if (this->raiz != nullptr) 
                throw RaizPreexistente();

            this->raiz = new NodoConcreto(valorRaiz);
            this->cantidadNodos = 1;
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
            
            NodoConcreto* viejoPrimerHijo = nodoPadre.nodoConcreto->hijoMasIzquierdo;
            NodoConcreto* nuevoPrimerHijo = new NodoConcreto(valorHijo);

            nodoPadre.nodoConcreto->hijoMasIzquierdo = nuevoPrimerHijo;
            nuevoPrimerHijo->hermanoDerecho = viejoPrimerHijo;

            ++this->cantidadNodos;
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
                nodoPadre.nodoConcreto->hijoMasIzquierdo = nuevoUltimoHijo;
            // Caso 2: Si hay hijos
            else
            {
                while(it->hermanoDerecho != nullptr)
                    it = it->hermanoDerecho;

                it->hermanoDerecho = nuevoUltimoHijo;
            }

            ++this->cantidadNodos;
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

            // TODO: Usar cola para recorrido por niveles
            --this->cantidadNodos;
        }

        /// @brief Cambia la etiqueta de un nodo de un árbol por otra nueva
        /// @param nodo Nodo al cual sustituirle la etiqueta
        /// @remarks Requiere que el nodo no sea nulo
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
        /// @param nodo Nodo del cual recuperar el nodo padre
        /// @return Presunto padre del nodo. Nodo nulo si resulta no tener padre (caso de la raiz)
        /// @remarks Requiere que el nodo no sea nulo, y que exista una raiz previamente en el arbol
        inline Nodo Padre(const Nodo& nodo) const
        {
            if (nodo.nodoConcreto == nullptr)
                throw NodoConcretoInvalido();

            if (this->raiz == nullptr)
                throw RaizNula();

            NodoConcreto* it = nodo.nodoConcreto;

            // Caso 1: El nodo es la raiz
            if (it == this->raiz)
                return Nodo();

            // TODO: Usar cola para recorrido por niveles
            return Nodo();
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

        /// @brief Recupera la cantidad de nodos existentes en este arbol, a partir de cierto nodo
        /// @param nodoInicial Nodo del cual partir para contar los nodos existentes en el árbol
        /// @return Cantidad de nodos existentes en todo el sub-árbol (incluyendo al nodo inicial)
        /// @remarks Requiere que el nodo inicial no sea nulo
        inline const size_t NumNodos(const Nodo& nodoInicial) const
        {
            if (nodoInicial.nodoConcreto == nullptr)
                throw NodoConcretoInvalido();
            
            if (this->raiz == nullptr)
                throw RaizNula();
            
            NodoConcreto* it = nodoInicial.nodoConcreto;

            if (this->raiz == it)
                return this->cantidadNodos;

            // TODO: Usar cola para recorrido por niveles
            return 0;
        }
};

/// @brief Mini demo, incompleta hasta terminar de implementar el árbol
int main()
{
    Arbol<int> a;
    a.PonerRaiz(100);
    std::cout << a.Etiqueta(a.Raiz()) << std::endl;

    a.ModificaEtiqueta(a.Raiz(), 999);
    std::cout << a.Etiqueta(a.Raiz()) << std::endl;

    a.Padre(a.Raiz());

    return 0;
}