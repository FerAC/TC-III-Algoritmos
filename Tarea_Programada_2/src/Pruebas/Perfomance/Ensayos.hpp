#ifndef ENSAYOS_HPP
#define ENSAYOS_HPP

// Unidades de prueba
#include "UnidadPrueba.hpp"

// Pruebas multihilo
#if defined(CONCURRENTE)
    #include <omp.h>
    #define VERSION_ENSAYOS "CONCURRENTE"
#else
    #define VERSION_ENSAYOS "SERIAL"
#endif

// LLevar cuenta de las pruebas
#include <vector>

// Para hileras en nombres de pruebas
#include <string>

// Llevar cuenta de los métodos de pruebas
#include <map>

/**
 * @brief Función que rellena la tupla de datos de las unidades de prueba en la construcción de un ensayo
 * @param tuple Parametros de la prueba
 * @param entrada Flujo de entrada de datos del cual agarrar información
 */
template <typename ...Parametros>
using FuncionLectura = void (*)(std::tuple<Parametros...>& tuple, std::istream& entrada);

template <class ...ArgumentosEnsayos>
class Ensayos
{
    private:
        /// @brief Pruebas a realizar en conjunto tras un llamado a ejecutar pruebas (serial o concurrente)
        std::vector<UnidadPrueba<ArgumentosEnsayos...>> pruebas;
        /// @brief Cantidad de pruebas realizadas al momento
        size_t pruebasHechas = 0;
        /// @brief Porcentaje de progreso realizado hasta el momento
        double progreso = 0;

    public:

        Ensayos(const std::map<std::string, FuncionPrueba<ArgumentosEnsayos...>>& funciones
            , std::istream& entrada
            , FuncionLectura<ArgumentosEnsayos...> leerDatos
            , FuncionEscritura<ArgumentosEnsayos...> escribirParametros) {
            // Llevaremos cuenta de la función de prueba actual
            FuncionPrueba<ArgumentosEnsayos...> funcionActual = funciones.begin()->second;

            // El nombre de la prueba...
            std::string nombreActual = std::string("Default");

            // La cantidad de repeticiones para la prueba...
            size_t kActual = 0;

            // El id de la prueba...
            size_t idActual = 0;

            // Y los parámetros a alimentarle
            std::tuple<ArgumentosEnsayos...> argumentos;

            // Tenemos que llevar cuenta de la línea actual
            std::string bufferLinea;

            // Leeremos líneas hasta que se nos acabe
            for (size_t paramActual = 1; !entrada.eof(); ++paramActual)
            {
                // Parsear selectivamente esa línea de acuerdo al parámetro siendo leído
                switch (paramActual)
                {
                    case 1: // Función
                    {
                        std::string bufferLinea;
                        std::getline(entrada, bufferLinea);

                        auto cualFunc = funciones.find(bufferLinea);
                        if (cualFunc != funciones.end())
                            funcionActual = cualFunc->second;
                        else
                            std::cerr << "Funcion de prueba " << bufferLinea << " desconocida" << std::endl;
                    }
                    break;
                    case 2: // Nombre
                    {
                        std::string bufferLinea;
                        std::getline(entrada, bufferLinea);

                        nombreActual = bufferLinea;
                    }
                    break;
                    case 3: // Repeticiones
                    {
                        std::string bufferLinea;
                        std::getline(entrada, bufferLinea);

                        kActual = std::atoll(bufferLinea.c_str());
                    }
                    break;
                    case 4: // Recolectar un parámetro
                    {
                        try 
                        {leerDatos(argumentos, entrada);}
                        catch(const std::exception& e)
                        {
                            std::cerr << "No se pudieron leer los parametros de la unidad de prueba #" 
                            << idActual << std::endl;
                            std::cerr << e.what() << '\n';
                        }
                    }
                    break;
                    default: // Ignorar línea
                    {
                        // Tras recolectar los parámetros, se crea la prueba
                        // Se realizará k veces
                        for (size_t i = 0; i < kActual; ++i)
                        {
                            UnidadPrueba<ArgumentosEnsayos...> 
                            pruebaInsertada(nombreActual, funcionActual, argumentos, escribirParametros);
                            
                            pruebaInsertada.id = idActual++;
                            pruebas.push_back(pruebaInsertada);
                        }
                    
                        // Listo! Tras la inserción, debemos devolver nuestro marcador
                        // de índice de parámetro al principio
                        paramActual = 0;

                        // De manera defensiva, reiniciaremos el k para evitar realizar
                        // muchas pruebas de manera accidental
                        kActual = 0;

                        // Y nos comeremos la siguiente línea
                        std::string buffer = "";
                        std::getline(entrada, buffer);
                        std::getline(entrada, buffer);
                    }
                    break;
                }
            }
        }

        ~Ensayos() {
        }

        void ejecutarPruebasSerial(std::ostream& salida) {
            // Hay que llevar cuenta de las pruebas totales
            size_t pruebasTotales = pruebas.size();

            // Y de las pruebas realizadas al momento
            size_t pruebasHechas = 0;

            // Ejecuta todas las pruebas que se encuentran en el vector de pruebas
            for (auto it = pruebas.begin(); it != pruebas.end(); ++it)
            {
                it->correrPrueba();

                // Actualizar la cuenta de pruebas hechas hasta ahora
                ++pruebasHechas;

                // Actualizar la barra de progreso de pruebas hechas hasta ahora
                const double progresoActual = 100.0 * ((double)pruebasHechas / (double)pruebasTotales);
                if (progresoActual != progreso)
                {
                    progreso = progresoActual;

                    const size_t bloques = size_t(progreso);
                    salida << "\r[";
                    for (size_t i = 0; i < bloques; ++i) {
                        salida << "=";
                    }
                    salida << "] %" << progreso;
                    salida.flush();
                }
            }
        }

        void imprimirPruebas(std::ostream& salida) {
            // Dejar una línea de separación
            salida << std::endl;

            // Si no estamos imprimiendo datos bonitos imprimiremos un encabezado
            #if not defined(DATOS_BONITOS)
                salida << "[ID]\t[Nombre]" << std::endl 
                << "[Parametros...] (" 
                << std::tuple_size<std::tuple<ArgumentosEnsayos...>>::value 
                << ')' << std::endl
                << "[Nano]\t[Micro]\t[Mili]\t[Seg]\t[Min]" << std::endl
                << "~~~~ <3" << std::endl << std::endl;
            #endif
            // En caso contrario, cada prueba tendría su propio encabezado bonito ~~

            // Imprime todas las pruebas que se encuentran en el vector de pruebas
            for (auto it = pruebas.begin(); it != pruebas.end(); ++it)
                salida << *it << std::endl;
        }

        UnidadPrueba<ArgumentosEnsayos...>& getPrueba(size_t indice)
        {return this->pruebas[indice];}

        // Adiciones de ejecución concurrente
        #if defined(CONCURRENTE)
            void ejecutarPruebasConcurrente(size_t cantidadHilos, std::ostream& salida)
            {
                // Hay que llevar cuenta de las pruebas totales
                const size_t pruebasTotales = pruebas.size();

                // Y de las pruebas realizadas al momento
                size_t pruebasHechas = 0;
                
                // Comenzaremos a ejecutar los hilos
                #pragma omp parallel for \
                num_threads(cantidadHilos) \
                schedule(dynamic) \
                default(none) \
                shared(pruebas, progreso, pruebasHechas, pruebasTotales, salida)
                for (size_t i = 0; i < pruebasTotales; ++i) {
                    pruebas[i].correrPrueba();

                    #pragma omp critical
                    {
                        // Actualizar la cuenta de pruebas hechas hasta ahora
                        ++pruebasHechas;

                        // Actualizar la barra de progreso de pruebas hechas hasta ahora
                        const double progresoActual = 100.0 * ((double)pruebasHechas / (double)pruebasTotales);
                        if (progresoActual != progreso)
                        {
                            progreso = progresoActual;

                            const size_t bloques = size_t(progreso);
                            salida << "\r[";
                            for (size_t i = 0; i < bloques; ++i)
                            {
                                salida << "=";
                            }
                            salida << "] %" << progreso;
                            salida.flush();
                        }
                    }
                }

                // Ya terminamos de ejecutar las pruebas
                return;
            }
        #endif

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~ METODOS DE PRUEBA ~~~~~~~~~~~~~~~~~~~~~~~~~~
};

#endif
