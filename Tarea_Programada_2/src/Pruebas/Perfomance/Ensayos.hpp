#ifndef ENSAYOS_HPP
#define ENSAYOS_HPP

// Unidades de prueba
#include "UnidadPrueba.hpp"

// Pruebas multihilo
#if defined(CONCURRENTE)
    #include <omp.h>
#endif

// LLevar cuenta de las pruebas
#include <vector>

// Para hileras en nombres de pruebas
#include <string>

// Llevar cuenta de los métodos de pruebas
#include <map>

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

        Ensayos(std::map<std::string, FuncionPrueba<ArgumentosEnsayos...>>& funciones
            , std::istream& entrada) {
            // Llevaremos cuenta de la función actual
            FuncionPrueba funcionActual = funciones.begin()->second;

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
                        break;
                    }
                    case 2: // Nombre
                    {
                        std::string bufferLinea;
                        std::getline(entrada, bufferLinea);

                        nombreActual = bufferLinea;
                        break;
                    }
                    case 3: // Repeticiones
                    {
                        std::string bufferLinea;
                        std::getline(entrada, bufferLinea);

                        kActual = std::atoll(bufferLinea.c_str());
                        break;
                    }
                    case std::tuple_size_v<ArgumentosEnsayos...> + 1: // Ignorar línea
                    {
                        // Tras recolectar los parámetros, se crea la prueba
                        // Se realizará k veces
                        for (size_t i = 0; i < kActual; ++i)
                        {
                            UnidadPrueba pruebaInsertada(nombreActual, funcionActual, parametros);
                            pruebaInsertada.id = idActual++;

                            pruebas.push_back(pruebaInsertada);
                        }
                    
                        // Listo! Tras la inserción, debemos devolver nuestro marcador
                        // de índice de parámetro al principio
                        paramActual = 0;

                        // De manera defensiva, reiniciaremos el k para evitar realizar
                        // muchas pruebas de manera accidental
                        kActual = 0;
                        break;
                    }
                    default: // Recolectar un parámetro
                    {
                        try 
                        {std::cin >> std::get<paramActual-4>(argumentos);}
                        catch(const std::exception& e)
                        {
                            std::cerr << "No se puedo leer el parametro " 
                            << paramActual-3 << "de la unidad de prueba" << std::endl;
                            std::cerr << e.what() << '\n';
                        }
                    }
                }
            }
        }

        ~Ensayos() {
        }

        void ejecutarPruebasSerial() {
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
                double progresoActual = 100.0 * ((double)pruebasHechas / (double)pruebasTotales);
                if (progresoActual != progreso)
                {
                    progreso = progresoActual;

                    size_t bloques = size_t(progreso);
                    std::cout << "\r[";
                    for (size_t i = 0; i < progreso; ++i)
                    {
                        std::cout << "=";
                    }
                    std::cout << "] %" << progreso;
                    std::cout.flush();
                }
            }
        }

        void imprimirPruebas() {
            // Dejar una línea de separación
            std::cout << std::endl;

            // Si no estamos imprimiendo datos bonitos imprimiremos un encabezado
            #if not defined(DATOS_BONITOS)
                std::cout << "ID\tNombre" << std::endl 
                << "[Parametros...] (" std::tuple_size_v<ArgumentosEnsayos...> << ')' << std::endl
                << "Nano\tMicro\tMili\tSeg\tMin" << std::endl;
            #endif
            // En caso contrario, cada prueba tendría su propio encabezado bonito ~~

            // Imprime todas las pruebas que se encuentran en el vector de pruebas
            for (auto it = pruebas.begin(); it != pruebas.end(); ++it)
                std::cout << *it << std::endl;
        }

        UnidadPrueba<ArgumentosEnsayos...>& getPrueba(size_t indice)
        {return this->pruebas[indice];}

        // Adiciones de ejecución concurrente
        #if defined(CONCURRENTE)
            void Ensayos::ejecutarPruebasConcurrente(size_t cantidadHilos)
            {
                // Hay que llevar cuenta de las pruebas totales
                const size_t pruebasTotales = pruebas.size();

                // Y de las pruebas realizadas al momento
                size_t pruebasHechas = 0;
                
                // Comenzaremos a ejecutar los hilos
                #pragma omp parallel for \
                num_threads(cantidadHilos) \
                default(none) shared(this->pruebas, this->progreso, pruebasHechas, pruebasTotales)
                for (size_t i = 0; i < cantidadHilos; ++i) {
                    this->pruebas[i].correrPrueba();

                    #pragma omp critical
                    {
                        // Actualizar la cuenta de pruebas hechas hasta ahora
                        ++pruebasHechas;

                        // Actualizar la barra de progreso de pruebas hechas hasta ahora
                        double progresoActual = 100.0 * ((double)pruebasHechas / (double)pruebasTotales);
                        if (progresoActual != progreso)
                        {
                            progreso = progresoActual;

                            size_t bloques = size_t(progreso);
                            std::cout << "\r[";
                            for (size_t i = 0; i < progreso; ++i)
                            {
                                std::cout << "=";
                            }
                            std::cout << "] %" << progreso;
                            std::cout.flush();
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
