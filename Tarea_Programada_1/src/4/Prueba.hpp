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

using PuntoTiempo = std::chrono::_V2::system_clock::time_point;

/**
 * @brief Función que agún objeto prueba invocará para luego informar acerca de resultados. Modifica el tiempo de inicio y final alimentados
 * @param n Tamaño de la prueba
 * @param puntoInicio Punto de inicio (en el tiempo) que será modificado por la función, para indicar el principio del experimento
 * @param puntoFinal Punto de finalización (en el tiempo) que será modificado por la función, para indicar el final del experimento
 * @remark El tamaño n debe estar inicializado. Los puntos de inicio y de final serán modificados
 */
typedef void (*FuncionPrueba)(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);

/// @brief Clase encapsuladora de pruebas para casos particulares del árbol
class Prueba
{
    /// @brief Los ensayos pueden acceder a las entrañas de las pruebas, para efectos de ID y tiempos
    friend class Ensayos;

    private:
        /// @brief Identificación de este experimento
        size_t id = 0;
        /// @brief Tamaño del experimento
        size_t n = 0;
        /// @brief Nombre de este experimento
        std::string nombre = std::string("");
        /// @brief Tiempo de inicio del experimento
        PuntoTiempo principioPrueba;
        /// @brief Tiempo de finalización del experimento
        PuntoTiempo finalPrueba;
        /// @brief Función que esta prueba invocará para medir el tiempo
        FuncionPrueba funcionPrueba;

    public:
        /**
         * @brief Crea una unidad de prueba asociada a un tamaño de entrada n, una función (prueba) para ejecutar, y un apodo
         * @param n Tamaño de la prueba
         * @param funcionPrueba Prueba (función estática) a ser invocada con el tamaño asociado a esta unidad (n), y cronometrada
         * @param nombre Apodo asociado a esta prueba (meramente para la impresión)
         * @remark Tanto el tamaño como el nombre deben estar inicializados. La función de prueba debe coincidir en firma con una FuncionPrueba
         */
        Prueba(size_t n, FuncionPrueba funcionPrueba, std::string nombre = std::string("Default"));
        ~Prueba();

        /// @brief Ejecuta la función de prueba asignada, con su tamaño asignado
        void correrPrueba();

        /// @brief Devuelve el tamaño de esta prueba. No modifica nada
        size_t getN() const;

        /// @brief Devuelve el ID de esta prueba. No modifica nada.
        size_t getId() const;

        /// @brief Retorna el nombre de esta prueba. No modifica nada.
        std::string getNombre() const;

        /// @brief Retorna la duración de esta prueba. No modifica nada.
        template <typename TipoDuracion>
        double getDuracion() const;
};

/**
 * @brief Imprime los contenidos de esta prueba. No modifica a la prueba
 * @param salida Flujo de salida estándar donde imprimir la prueba
 * @param prueba Prueba a ser impresa
 * @return Una referencia al flujo de salida estándar, para concatenar el método
 * @remark La prueba debe estar inicializada
 */
std::ostream &operator<<(std::ostream &salida, const Prueba &prueba);

#endif
