#if defined(CONCURRENTE)

#include "HiloPrueba.hpp"

HiloPrueba::HiloPrueba()
{}

void HiloPrueba::wrapperPrueba(Ensayos& ensayo)
{
    size_t marcadorPrueba = 0;

    while (ensayo.avanzarMarcadorPruebas(marcadorPrueba))
    {
        ensayo.getPrueba(marcadorPrueba).correrPrueba();
        ensayo.avanzarBarraProgresoTSafe();
    }

    return;
}

void HiloPrueba::esperarHilo()
{
    if (this->hiloInterior != nullptr && this->hiloInterior->joinable())
        this->hiloInterior->join();
}

void HiloPrueba::correrHilo(Ensayos& ensayo)
{
    if (this->hiloInterior != nullptr)
    {
        this->esperarHilo();
        delete this->hiloInterior;
    }

    this->hiloInterior = new std::thread(wrapperPrueba, std::ref(ensayo));
}

HiloPrueba::~HiloPrueba()
{
    if (this->hiloInterior != nullptr)
    {
        this->esperarHilo();
        delete this->hiloInterior;
    }
}

#endif
