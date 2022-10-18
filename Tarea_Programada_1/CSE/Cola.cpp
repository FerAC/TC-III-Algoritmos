#include <exception> // Para las excepciones
#include <iostream> // Para impresiones en la salida estándar

/// @brief Excepción para cuando se intenta desreferenciar un puntero a elemento nulo (a nivel de bloque)
class ElementoInvalido : public std::exception 
{
    public:
        ElementoInvalido() {}
        ~ElementoInvalido() {}

        virtual const char* what() const noexcept
        {return "Imposible acceder a elemento. Es nulo";}
};

/// @brief Excepción para cuando se intenta desreferenciar un puntero a nodo bloque nulo
class BloqueInvalido : public std::exception 
{
    public:
        BloqueInvalido() {}
        ~BloqueInvalido() {}

        virtual const char* what() const noexcept
        {return "Imposible acceder a bloque en cola. Es nulo";}
};

/// @brief Excepción para cuando se intenta desencolar a una cola no vacía
class DesencoladoEnVacio : public std::exception 
{
    public:
        DesencoladoEnVacio() {}
        ~DesencoladoEnVacio() {}

        virtual const char* what() const noexcept
        {return "Imposible desencolar cola. Esta vacia";}
};

// Declaraciones adelantadas para resolver dependencias circulares en impresión

/// @brief Cola dinámica implementada mediante una lista doblemente enlazada
template <typename Elemento>
class Cola;

/// @brief Imprime los contenidos de una Cola de forma horizontal a un flujo de salida
/// @param salida Flujo de salida para imprimir los contenidos del árbol
/// @param Cola Cola dináminca de la cual imprimir los contenidos
/// @return Referencia al flujo de salida utilizado (para encadenar impresiones)
template <typename Elemento>
std::ostream& operator<<(std::ostream& salida, const Cola<Elemento>& cola);

/// @brief Cola dinámica implementada mediante una lista doblemente enlazada
template <typename Elemento>
class Cola
{
    // La función de impresión puede ver las entrañas de una Cola
    template <typename T>
    friend std::ostream& operator<<(std::ostream&, const Cola<T>&);

    protected:
        /// @brief Bloque (contenedor) poseedor de elemento y poseído por la Cola
        class Bloque
        {
            // Una Cola pueden manipular y ver las entrañas de un Bloque
            friend class Cola;

            // La función de impresión puede ver las entrañas de un Bloque
            template <typename T>
            friend std::ostream& operator<<(std::ostream&, const Cola<T>&);

            Bloque* siguiente = nullptr;
            Bloque* previo = nullptr;
            Elemento* elemento = nullptr;

            /// @brief Inicializa a un bloque apuntando a un nuevo elemento creado por copia
            /// @param valorElemento Elemento el cual será usado como base para construir una copia
            /// @remark Requiere que el elemento tenga un constructor por copia válido
            Bloque(const Elemento& valorElemento)
            {this->elemento = new Elemento(valorElemento);}

            /// @brief Libera la memoria del elemento apuntado, si resultase no ser nulo
            /// @remark Requiere que el elemento tenga un destructor por defecto válido
            ~Bloque()
            {
                if (this->elemento != nullptr)
                    delete this->elemento;
            }
    
            /// @brief Obtiene el elemento apuntado por este bloque
            /// @return Elemento obtenido al desreferenciar el apuntador de elemento
            /// @remarks Requiere que el apuntador de elemento nulo no apunte a un elemento nulo
            const Elemento& getElemento() const
            {
                if (this->elemento == nullptr)
                    throw ElementoInvalido();
                
                return *(this->elemento);
            }
    
            /// @brief Destruye el elemento apuntado por este bloque para apuntar a otro nuevo
            /// @param nuevoValor Elemento el cual será usado como base para construir una copia
            /// @remark Requiere que el elemento tenga un constructor por copia y destructor por defecto válidos
            void cambiarElemento(const Elemento& nuevoValor)
            {
                delete this->elemento;
                this->elemento = new Elemento(nuevoValor);
            }
        };

        /// @brief Primer bloque apuntado (y poseído) por esta Cola
        Bloque* primero = nullptr;
        /// @brief Último bloque apuntado (y poseído) por esta Cola
        Bloque* ultimo = nullptr;

    public:
        /// @brief Inicializa a una cola en un estado por defecto
        Cola () {}

        /// @brief Elimina los bloques de una cola
        ~Cola ()
        {
            for (Bloque* it = this->primero; it != nullptr; it = it = it->siguiente)
                delete it;
        }

        /// @brief Indica si la cola está vacía o no
        /// @return Verdadero si esta vacía, Falso en caso contrario
        inline bool Vacio()
        {return (this->primero == nullptr);}

        /// @brief Agrega una copia de un elemento al principio de la Cola
        /// @param valorEntrante Elemento del cual obtener un clon que será insertado al final de la Cola
        /// @remark Requiere que el elemento tenga un constructor por copia válido
        inline void Encolar(const Elemento& valorEntrante)
        {
            // Obtengamos al nuevo bloque y al previo primer bloque en la Cola
            Bloque* nuevoBloque = new Bloque(valorEntrante);
            Bloque* previoPrimerBloque = this->primero;

            // Conectemos ambos bloques
            nuevoBloque->siguiente = previoPrimerBloque;
            if (previoPrimerBloque != nullptr) previoPrimerBloque->previo = nuevoBloque;

            // Conectemos al comienzo de la Cola y al nuevo bloque
            this->primero = nuevoBloque;

            // Si antes no habían elementos, entonces el último bloque corresponde a este nuevo
            if (this->ultimo == nullptr)
                this->ultimo = nuevoBloque;
        }

         /// @brief Retorna una copia del último elemento en la Cola, y luego elimina al original
        /// @remark Requiere que el elemento tenga un constructor por copia válido, y que la Cola no esté vacía
        inline Elemento Desencolar()
        {
            if (this->ultimo == nullptr)
                throw DesencoladoEnVacio();

            // Obtengamos al ultimo bloque
            Bloque* ultimo = this->ultimo;

            // Descomuniquemoslo con la Cola
            this->ultimo = ultimo->previo;
            if (this->ultimo == nullptr) this->primero = nullptr;

            // Descominiquemoslo con su bloque previo
            if (ultimo->previo != nullptr)
                ultimo->previo->siguiente = nullptr;

            // Capturemos una copia del elemento en el bloque para retornala tras destruir el original
            Elemento copiaRetornada = ultimo->getElemento();
            delete ultimo;

            return copiaRetornada;
        }
};

template <typename Elemento>
std::ostream& operator<<(std::ostream& salida, const Cola<Elemento>& cola)
{
    // Acotaremos los contenidos de la Cola entre llaves
    salida << "[";

    // Imprimiremos a la Cola en el orden que mantiene al momento (FIFO)
    for (auto* it = cola.primero; it != nullptr; it = it->siguiente)
    {
        // Para evitar copiados y borrados, imprimiremos por referencia a puntero cada elemento
        Elemento* et = it->elemento;

        if (et == nullptr)
            throw ElementoInvalido();

        salida << (*et);

        // Luego, si hay otro bloque tras el actual, dejeremos un espacio de separación entre ambos
        if (it->siguiente != nullptr)
            salida << ' ';
    }

    salida << "]";

    // Ya terminamos la impresión, Retornemos una referencia al flujo de salida para encadenar impresiones
    return salida;
}

/// @brief Mini demo, incompleta hasta terminar de implementar el árbol
int main()
{
    // Creación
    Cola<int> cola;
    std::cout << cola << std::endl;
    std::cout << "^^^ Cola tras crearla ^^^" << std::endl;

    // Encoladas
    cola.Encolar(1);
    std::cout << cola << std::endl;
    std::cout << "^^^ Cola tras encolar 1 ^^^" << std::endl;

    cola.Encolar(2); cola.Encolar(3); cola.Encolar(4);
    std::cout << cola << std::endl;
    std::cout << "^^^ Cola tras insertar 2, 3 y 4 ^^^" << std::endl;

    // Desencolar
    std::cout << "Valor desencolado = " << cola.Desencolar() << std::endl;
    std::cout << cola << std::endl;
    std::cout << "^^^ Cola tras desencolar 1 ^^^" << std::endl;

    std::cout << "Valores desencolados = " 
        << cola.Desencolar() 
        << ", " << cola.Desencolar()
        << ", " << cola.Desencolar()
    << std::endl;
    std::cout << cola << std::endl;
    std::cout << "^^^ Cola tras desencolar 2, 3 y 4 ^^^" << std::endl;

    std::cout << "¿Esta la cola vacia? ";
    if (cola.Vacio()) std::cout << "Si" << std::endl;
    else std::cout << "No" << std::endl;

    // Desencolar una cola vacía
    std::cout << "¿Es posible seguir desencolando la cola?" << std::endl;
    try
    {
        int valorDesencolado = cola.Desencolar();
        std::cout << "Sí, es valor desencolado es " << valorDesencolado << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cout << "No, es imposible. La excepción es:" << std::endl;
        std::cout << "[ERROR] = " << e.what() << std::endl;
    }

    // TODO: Realizar pruebas de casos mas específicos
    // TODO: Probar el manejo de excepciones

    return 0;
}
