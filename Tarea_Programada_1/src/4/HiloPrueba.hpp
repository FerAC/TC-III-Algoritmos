#ifndef HILO_PRUEBA_HPP
#define HILO_PRUEBA_HPP

#include "Ensayos.hpp"
#include <thread>

// Declaración adelantada de estado para resolver dependnecias circulares
class Ensayos;

class HiloPrueba
{
    private:
        /// @brief Hilo de ejecución interno asociado a alguna unidad de prueba
        std::thread* hiloInterior = nullptr;

    public:
        HiloPrueba();
        ~HiloPrueba();

        /// @brief Envoltorio de método invocado por el hilo de ejecución interno para su unidad de prueba
        static void wrapperPrueba(Ensayos& ensayo);

        /// @brief Espera a que termine el hilo de ejecución interno asociado a su unidad de prueba
        void esperarHilo();

        /// @brief Corre el hilo de ejecución interno asociado a una unidad de prueba
        void correrHilo(Ensayos& ensayo);
};

#endif
