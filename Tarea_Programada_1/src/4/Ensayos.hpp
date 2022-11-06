#ifndef ENSAYOS_HPP
#define ENSAYOS_HPP

// Algoritmos y árbol particular
#include "Controlador.hpp"

// Unidades de prueba
#include "Prueba.hpp"

// Pruebas multihilo
#if defined(CONCURRENTE)
    #include "HiloPrueba.hpp"
    #include <mutex>
    #include <thread>
#endif

// LLevar cuenta de las pruebas
#include <vector>

// Para hileras en nombres de pruebas
#include <string>

// Llevar cuenta de los métodos de pruebas
#include <map>

using PuntoTiempo = std::chrono::_V2::system_clock::time_point;

/**
 * @brief Función que agún objeto prueba invocará para luego informar acerca de resultados. Modifica el tiempo de inicio y final alimentados
 * @param n Tamaño de la prueba
 * @param puntoInicio Punto de inicio (en el tiempo) que será modificado por la función, para indicar el principio del experimento
 * @param puntoFinal Punto de finalización (en el tiempo) que será modificado por la función, para indicar el final del experimento
 * @remark El tamaño n debe estar inicializado. Los puntos de inicio y de final serán modificados
 */
typedef void (*FuncionPrueba)(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);

class Ensayos
{
    private:
        /// @brief Pruebas a realizar en conjunto tras un llamado a ejecutar pruebas (serial o concurrente)
        std::vector<Prueba> pruebas;
        /// @brief Cantidad de pruebas realizadas al momento
        size_t pruebasHechas = 0;
        /// @brief Porcentaje de progreso realizado hasta el momento
        double progreso = 0;

        // Adiciones de ejecución concurrente
        #if defined(CONCURRENTE)
            /// @brief Marcador de cuál prueba es accesible al siguiente hilo solicitante
            size_t marcadorPrueba = 0;
            /// @brief Mutex para evitar condiciones de carrera al acceder al marcador de prueba accesible
            std::mutex mutexMarcadorPrueba;
            /// @brief Mutex para evitar condiciones de carrera al acceder la cantidad de pruebas hechas
            std::mutex mutexPruebasHechas;
        #endif

    public:

        Ensayos(std::map<std::string, FuncionPrueba>& funciones, std::istream& entrada);

        ~Ensayos();

        void ejecutarPruebasSerial();

        void imprimirPruebas();

        Prueba& getPrueba(size_t indice);

        // Adiciones de ejecución concurrente
        #if defined(CONCURRENTE)
            void ejecutarPruebasConcurrente(size_t cantidadHilos);

            bool avanzarMarcadorPruebas(size_t& variableDeposito);

            void avanzarBarraProgresoTSafe();
        #endif

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~ METODOS DE PRUEBA ~~~~~~~~~~~~~~~~~~~~~~~~~~

        static void etiquetasRepetidas(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);

        static void borrarSubarbol(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);

        static void crearArbol(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);
        
        static void crearArbolAlturaExtrema(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);
    
        static void crearArbolAnchuraExtrema(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);

        static void crearArbolHijoCortoHijoLargo(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);
        
        static void poblarNormalSegunPrueba(Arbol& arbol, int n, int caso);
        
        static void etiquetasRepetidasNormal1(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);
        
        static void etiquetasRepetidasAlto1(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);
        
        static void etiquetasRepetidasAlto2(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);
        
        static void etiquetasRepetidasAlto3(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);
        
        static void etiquetasRepetidasNormal2(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);
        
        static void etiquetasRepetidasNormal3(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);
        
        static void poblarArbolAlturaExtremaSegunPrueba(Arbol& arbol, int caso, int n);

        static void PoblarArbolAnchuraExtremaSegunPrueba(Arbol& arbol, int caso, int n);

        static void PoblarArbolHijoCortoHijoLargoSegunPrueba(Arbol& arbol, int caso, int n);

        void etiquetasRepetidasAncho1(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);

        void etiquetasRepetidasAncho2(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);

        void etiquetasRepetidasAncho3(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);

        void etiquetasRepetidasHijoCortoHijoLargo1(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);
        void etiquetasRepetidasHijoCortoHijoLargo2(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);
        void etiquetasRepetidasHijoCortoHijoLargo3(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);
};

#endif
