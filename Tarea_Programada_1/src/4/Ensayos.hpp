#ifndef ENSAYOS_HPP
#define ENSAYOS_HPP

// Algoritmos y árbol particular
#include "Controlador.hpp"

// I/O estandar
#include <iostream>

// I/O con precisión científica y dígitos acotados
#include <iomanip>

// Para hileras en nombres de pruebas
#include <string>

// LLevar cuenta de las pruebas
#include <vector>

// Llevar cuenta de los métodos de pruebas
#include <map>

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
    /// @brief Nombre de este experimento
    std::string nombre;
    /// @brief Tamaño del experimento
    size_t n;
    /// @brief Tiempo de inicio del experimento
    PuntoTiempo principioPrueba;
    /// @brief Tiempo de finalización del experimento
    PuntoTiempo finalPrueba;
    /// @brief Función que esta prueba invocará para medir el tiempo
    FuncionPrueba funcionPrueba;

public:
    Prueba(size_t n, FuncionPrueba funcionPrueba, std::string nombre = std::string("Default"))
        : n(n), funcionPrueba(funcionPrueba), nombre(nombre)
    {}

    ~Prueba()
    {};

    /**
     * @brief Corre la prueba mediante la función especificada para esta prueba en su construcción. Modifica los marcadores de tiempo de principio y final
     * @param n Tamaño de la prueba
     * @remark El tamaño debe estar inicializado
     */
    void correrPrueba()
    {funcionPrueba(n, this->principioPrueba, this->finalPrueba);}

    /// @brief Devuelve el tamaño de esta prueba. No modifica nada
    size_t getN() const
    {return n;}

    /// @brief Devuelve el ID de esta prueba. No modifica nada.
    size_t getId() const
    {return id;}

    /// @brief Retorna el nombre de esta prueba. No modifica nada.
    std::string getNombre() const
    {return nombre;}

    /// @brief Retorna la duración de esta prueba. No modifica nada.
    template <typename TipoDuracion>
    double getDuracion() const
    {return std::chrono::duration_cast<TipoDuracion>(this->finalPrueba - this->principioPrueba).count();}
};

std::ostream &operator<<(std::ostream &salida, const Prueba &prueba)
{
    std::cout << "~~~~~~~~~~~~~~PARAMETROS~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "N: " << prueba.getN() << std::endl;
    std::cout << "ID: " << prueba.getId() << std::endl;
    std::cout << "Nombre: " << prueba.getNombre() << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

    double duracionNano = prueba.getDuracion<std::chrono::nanoseconds>();
    double duracionMicro = prueba.getDuracion<std::chrono::microseconds>();
    double duracionMili = prueba.getDuracion<std::chrono::milliseconds>();
    double duracionSeg = prueba.getDuracion<std::chrono::seconds>();
    double duracionMin = prueba.getDuracion<std::chrono::minutes>();

    std::cout << "~~~~~~~~~~~~~~~~DURACION~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "Nanosegundos\t" << std::setprecision(5) << std::scientific << duracionNano << std::endl;
    std::cout << "Microsegundos\t" << std::setprecision(5) << std::scientific << duracionMicro << std::endl;
    std::cout << "Milisegundos\t" << std::setprecision(5) << std::scientific << duracionMili << std::endl;
    std::cout << "Segundos\t" << std::setprecision(5) << std::scientific << duracionSeg << std::endl;
    std::cout << "Minutos \t" << std::setprecision(5) << std::scientific << duracionMin << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

    return salida;
}

class Ensayos
{
private:
    std::vector<Prueba> pruebas;
    size_t pruebasHechas = 0;
    double progreso = 0;

public:
    /**
    *     
    */
    Ensayos(std::map<std::string, FuncionPrueba>& funciones, std::istream& entrada)
    {
        // LLevaremos cuenta de los parámetros que hemos leídos al momento
        FuncionPrueba funcionActual = funciones.begin()->second;
        std::string nombreActual = std::string("Default");
        size_t nActual = 0;

        // Y cuenta del id de la prueba
        size_t idActual = 0;

        // Tenemos que llevar cuenta de la línea actual
        std::string bufferLinea;

        // Leeremos líneas hasta que se nos acabe
        for (size_t paramActual = 1; !entrada.eof(); ++paramActual)
        {
            // Leer la línea actual
            std::getline(entrada, bufferLinea);

            // Parsear selectivamente esa línea de acuerdo al parámetro siendo leído
            switch (paramActual)
            {
                case 1: // Función
                {
                    auto cualFunc = funciones.find(bufferLinea);
                    if (cualFunc != funciones.end())
                        funcionActual = cualFunc->second;
                    else
                        std::cerr << "FUNC " << bufferLinea <<  " NO ENCONTRADA" << std::endl;
                    break;
                }
                case 2: // Nombre
                {
                    nombreActual = bufferLinea;
                    break;
                }              
                case 3: // Tamaño
                {
                    nActual = std::atoll(bufferLinea.c_str());
                    break;
                }
                default: // Ignorar línea. 
                {
                    // Tras recolectar los parámetros tres, se crea la prueba
                    Prueba pruebaInsertada(nActual, funcionActual, nombreActual);
                    pruebaInsertada.id = idActual++;

                    pruebas.push_back(pruebaInsertada);
                    paramActual = 0;
                    break;
                }
            }
        }
    }

    ~Ensayos(){}

    void ejecutarPruebas()
    {
        // Hay que llevar cuenta de las pruebas totales
        size_t pruebasTotales = pruebas.size();

        // Ejecuta todas las pruebas que se encuentran en el vector de pruebas
        for(auto it = pruebas.begin(); it != pruebas.end(); ++it)
        {
            it->correrPrueba();

            // Actualizar la cuenta de pruebas hechas hasta ahora
            ++pruebasHechas;

            // Actualizar la barra de progreso de pruebas hechas hasta ahora
            double progresoActual = 100.0 * ((double) pruebasHechas / (double) pruebasTotales);
            if (progresoActual != progreso) 
            {
                progreso = progresoActual;

                size_t bloques = size_t(progreso);
                std::cout << "[";
                for (size_t i = 0; i < progreso; ++i)
                {
                    std::cout << "=";
                }
                std::cout << "] %" << progreso << std::endl;
                std::cout.flush();
            }
        }
            
    }

    void imprimirPruebas()
    {
        // Imprime todas las pruebas que se encuentran en el vector de pruebas
        for(auto it = pruebas.begin(); it != pruebas.end(); ++it)
            std::cout << *it << std::endl;
    }

    static void etiquetasRepetidas(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal)
    {
        Arbol arbol = Arbol();
        size_t cantidadNiveles = 4;
        size_t anchoPorNivel = 2;
        ListaIndexada lista;
        for (size_t j = 0; j < n; j++)
            lista.insertar(j, j);

        Controlador::crearArbol(cantidadNiveles, anchoPorNivel, lista, arbol);
        
        std::chrono::high_resolution_clock clock;
        puntoInicio = clock.now();
        Controlador::averiguarEtiquetasRepetidas(arbol);
        puntoFinal = clock.now();
    }

    static void borrarSubarbol(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal)
    {
        Arbol arbol = Arbol();
        size_t cantidadNiveles = 4;
        size_t anchoPorNivel = 2;
        ListaIndexada lista;
        for (size_t j = 0; j < n; j++)
            lista.insertar(j, j);

        Controlador::crearArbol(cantidadNiveles, anchoPorNivel, lista, arbol);

        Nodo subraiz = arbol.Raiz();    // hay que cambiar
        
        std::chrono::high_resolution_clock clock;
        puntoInicio = clock.now();
        Controlador::borrarSubArbol(arbol, subraiz);
        puntoFinal = clock.now();
    }

    static void crearArbol(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal)
    {
        Arbol arbol = Arbol();
        std::chrono::high_resolution_clock clock;

        size_t cantidadNiveles = n;
        size_t hijosPorNodo = 2;
        size_t cantidadNodos = (pow(hijosPorNodo, cantidadNiveles) - 1) / (hijosPorNodo - 1);

        ListaIndexada lista;
        for (size_t j = 0; j < cantidadNodos; ++j)
            lista.insertar(j, j);

        puntoInicio = clock.now();
        Controlador::crearArbol(cantidadNiveles, hijosPorNodo, lista, arbol);
        puntoFinal = clock.now();
    }
    
    static void crearArbolAlturaExtrema(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal)
    {
        Arbol arbol = Arbol();
        std::chrono::high_resolution_clock clock;
        //int cantidadNodos = 100;
        
        puntoInicio = clock.now();
        Controlador::crearArbolAlturaExtrema(n, arbol);
        puntoFinal = clock.now();
    }
 
    static void crearArbolAnchuraExtrema(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal)
    {
        Arbol arbol = Arbol();
        std::chrono::high_resolution_clock clock;
        //int cantidadNodos = 100;
        
        puntoInicio = clock.now();
        Controlador::crearArbolAnchuraExtrema(n, arbol);
        puntoFinal = clock.now();
    }

    static void crearArbolHijoCortoHijoLargo(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal)
    {
        Arbol arbol = Arbol();
        std::chrono::high_resolution_clock clock;
       // int cantidadNodos = 100;
        //size_t cantidadHijosRaiz = 5;                   // para crearArbolHijoCortoHijoLargo
        size_t cantidadHijosRaiz = 100;   // para crearArbolHijoCortoHijoLargo
        
        puntoInicio = clock.now();
        Controlador::crearArbolHijoCortoHijoLargo(n, cantidadHijosRaiz, arbol);
        puntoFinal = clock.now();
    }
    
};

#endif
