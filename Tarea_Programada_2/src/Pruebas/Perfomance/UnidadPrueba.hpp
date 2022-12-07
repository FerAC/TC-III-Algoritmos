#ifndef PRUEBA_HPP
#define PRUEBA_HPP

// I/O estandar
#include <iostream>

// I/O con precisión científica y dígitos acotados
#include <iomanip>

// Para hileras en nombres de pruebas
#include <string>

// Llevar cuenta de la duracion
#include <chrono>

// Para múltiples parámetros de plantilla
#include <tuple>

using PuntoTiempo = std::chrono::_V2::system_clock::time_point;

/**
 * @brief Función que agún objeto prueba invocará para luego informar acerca de resultados. Modifica el tiempo de inicio y final alimentados
 * @param parametros Parametros de la prueba
 * @param puntoInicio Punto de inicio (en el tiempo) que será modificado por la función, para indicar el principio del experimento
 * @param puntoFinal Punto de finalización (en el tiempo) que será modificado por la función, para indicar el final del experimento
 * @remark El tamaño n debe estar inicializado. Los puntos de inicio y de final serán modificados
 */
template <typename ...Parametros>
using FuncionPrueba = void (*)(PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal, std::tuple<Parametros...> parametros);

/// @brief Clase encapsuladora de pruebas para casos particulares del árbol
template <class ...Argumentos>
class UnidadPrueba
{
    /// @brief Los ensayos pueden acceder a las entrañas de las pruebas, para efectos de ID y tiempos
    friend class Ensayos;

    /// @brief Las impresiones también pueden acceder a la entrañas
    template <typename ...ArgumentosImprimibles>
    friend std::ostream &operator<<(std::ostream &salida, const UnidadPrueba<Argumentos...>& prueba);

    private:
        /// @brief Identificación de este experimento
        size_t id = 0;
        /// @brief Nombre de este experimento
        std::string nombre;
        /// @brief Tiempo de inicio del experimento
        PuntoTiempo principioPrueba;
        /// @brief Tiempo de finalización del experimento
        PuntoTiempo finalPrueba;
        /// @brief Parámetros del experimento
        std::tuple<Argumentos...> parametros;
        /// @brief Función que esta prueba invocará para medir el tiempo
        FuncionPrueba<Argumentos...> funcionPrueba;

    public:
        /**
         * @brief Crea una unidad de prueba asociada a un tamaño de entrada n, una función (prueba) para ejecutar, y un apodo
         * @param nombre Apodo asociado a esta prueba (meramente para la impresión)
         * @param funcionPrueba UnidadPrueba (función estática) a ser invocada con el tamaño asociado a esta unidad (n), y cronometrada
         * @param parametros Parámetros de la prueba
         * @remark Tanto el tamaño como el nombre deben estar inicializados. La función de prueba debe coincidir en firma con una FuncionPrueba
         */
        UnidadPrueba(std::string nombre, FuncionPrueba<Argumentos...> funcionPrueba, const Argumentos& ... parametros)
        : nombre(nombre)
        , funcionPrueba(funcionPrueba)
        , parametros(parametros) {
        }

        /**
         * @brief Crea una unidad de prueba asociada a un tamaño de entrada n, una función (prueba) para ejecutar, y un apodo
         * @param nombre Apodo asociado a esta prueba (meramente para la impresión)
         * @param funcionPrueba UnidadPrueba (función estática) a ser invocada con el tamaño asociado a esta unidad (n), y cronometrada
         * @param parametros Parámetros de la prueba
         * @remark Tanto el tamaño como el nombre deben estar inicializados. La función de prueba debe coincidir en firma con una FuncionPrueba
         */
        UnidadPrueba(std::string nombre, FuncionPrueba<Argumentos...> funcionPrueba, const std::tuple<Argumentos...>& ... parametros)
        : nombre(nombre)
        , funcionPrueba(funcionPrueba)
        , parametros(parametros) {
        }

        ~UnidadPrueba() {
        }

        /// @brief Ejecuta la función de prueba asignada, con su tamaño asignado
        void correrPrueba() 
        {funcionPrueba(this->principioPrueba, this->finalPrueba, this->parametros);}

        /// @brief Devuelve el ID de esta prueba. No modifica nada.
        size_t getId() const
        {return this->id;}

        /// @brief Retorna el nombre de esta prueba. No modifica nada.
        std::string getNombre() const
        {return this->nombre}

        /// @brief Devuelve una copia de los parámetros de esta prueba. No modifica nada
        std::tuple<Argumentos...> getParametros() const 
        {return this->parametros}

        /// @brief Retorna la duración de esta prueba. No modifica nada.
        template <typename TipoDuracion>
        double getDuracion() const {
            return std::chrono::duration_cast<TipoDuracion>
                (this->finalPrueba - this->principioPrueba).count();
        }
};

/**
 * @brief Imprime los contenidos de esta prueba. No modifica a la prueba
 * @param salida Flujo de salida estándar donde imprimir la prueba
 * @param prueba UnidadPrueba a ser impresa
 * @return Una referencia al flujo de salida estándar, para concatenar el método
 * @remark La prueba debe estar inicializada
 */
template <typename ...ArgumentosImprimibles>
std::ostream &operator<<(std::ostream &salida, const UnidadPrueba<ArgumentosImprimibles...>& prueba) {
    #if defined(DATOS_BONITOS)
        std::cout << "~~~~~~~~~~~~~~PARAMETROS~~~~~~~~~~~~~~~~" << std::endl;
        std::cout << "ID: " << prueba.getId() << std::endl;
        std::cout << "Nombre: " << prueba.getNombre() << std::endl;
        for (size_t paramI = 0; paramI < std::tuple_size_v<ArgumentosImprimibles...>; ++paramI)
            std::cout << '[' << paramI << ']' << std::endl
            <<  std::get<paramI>(prueba.parametros) << std::endl;
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    #endif

    double duracionNano = prueba.getDuracion<std::chrono::nanoseconds>();
    double duracionMicro = prueba.getDuracion<std::chrono::microseconds>();
    double duracionMili = prueba.getDuracion<std::chrono::milliseconds>();
    double duracionSeg = prueba.getDuracion<std::chrono::seconds>();
    double duracionMin = prueba.getDuracion<std::chrono::minutes>();

    #if defined(DATOS_BONITOS)
        std::cout << "~~~~~~~~~~~~~~~~DURACION~~~~~~~~~~~~~~~~" << std::endl;
        std::cout << "Nanosegundos\t" << std::setprecision(5) << std::scientific << duracionNano << std::endl;
        std::cout << "Microsegundos\t" << std::setprecision(5) << std::scientific << duracionMicro << std::endl;
        std::cout << "Milisegundos\t" << std::setprecision(5) << std::scientific << duracionMili << std::endl;
        std::cout << "Segundos\t" << std::setprecision(5) << std::scientific << duracionSeg << std::endl;
        std::cout << "Minutos \t" << std::setprecision(5) << std::scientific << duracionMin << std::endl;
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    #else
        std::cout << prueba.getId() << ":\t" << prueba.getNombre() << std::endl
        << duracionNano << '\t' << duracionMicro << '\t' << duracionMili << '\t' << duracionSeg << '\t' << duracionMin << std::endl;
    #endif

    return salida;
}

#endif
