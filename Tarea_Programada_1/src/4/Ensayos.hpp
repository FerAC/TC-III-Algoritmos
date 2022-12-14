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

        static void etiquetasRepetidasAncho1(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);

        static void etiquetasRepetidasAncho2(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);

        static void etiquetasRepetidasAncho3(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);

        static void etiquetasRepetidasHijoCortoHijoLargo1(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);

        static void etiquetasRepetidasHijoCortoHijoLargo2(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);

        static void etiquetasRepetidasHijoCortoHijoLargo3(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);

        static void borrarSubarbolAltura2(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);

        static void borrarSubarbolAltura3(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);

        static void borrarSubarbolAnchura2(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);

        static void borrarSubarbolAnchura3(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);

        static void borrarSubarbolNormal2(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);
        
        static void borrarSubarbolNormal3(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);
        
        static void borrarSubarbolHijoCortoHijoLargo2(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);
        
        static void borrarSubarbolHijoCortoHijoLargo3(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);
        
        static void profundidadAltura2(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);
        
        static void profundidadAltura3(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);
        
        static void profundidadAnchura2(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);
        
        static void profundidadAnchura3(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);
        
        static void profundidadNormal2(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);
        
        static void profundidadNormal3(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);
        
        static void profundidadHijoLargoHijoCorto2(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);
        
        static void profundidadHijoLargoHijoCorto3(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal);

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~ METODOS AUXILIARES  ~~~~~~~~~~~~~~~~~~~~~~~~~~

        static Nodo borrarSubarbolAnchuraSegunPrueba(size_t n, Arbol& arbol);

        static Nodo borrarSubArbolAlturaSegunPrueba(size_t n, Arbol& arbol);

        static Nodo borrarSubArbolNormalSegunPrueba(size_t n, Arbol& arbol, ListaIndexada& lista, int i, int k);

        static Nodo borrarSubarbolHijoCortoHijoLargoSegunPrueba(size_t n, Arbol& arbol);

        static Nodo ultimoNodoHijoLargoHijoCorto(Arbol& arbol, int n);

        static Nodo ultimoNodoNormal(Arbol& arbol, int n, int i, int k, ListaIndexada& lista);

        static Nodo ultimoNodoAlto(Arbol& arbol, int n);

        static Nodo ultimoNodoAncho(Arbol& arbol, int n);
};

#endif
