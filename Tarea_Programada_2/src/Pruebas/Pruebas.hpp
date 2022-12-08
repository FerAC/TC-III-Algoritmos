#ifndef PRUEBAS
#define PRUEBAS

#include "GrafoImplementado.hpp"
#include "Pruebas/Perfomance/UnidadPrueba.hpp"

// TODO(us): Cambiar invocaciones para que compile
namespace Pruebas {

    // // ARBOLES MINIMALES

    // void arbolMinimal(PuntoTiempo& inicio, PuntoTiempo& fin, std::tuple<std::string, std::string, size_t>);

    // // CAMINOS DE MENOR COSTO

    // void distanciaCortaUno(PuntoTiempo& inicio, PuntoTiempo& fin, std::tuple<std::string, std::string, size_t>);

    // void distanciaCortaTodos(PuntoTiempo& inicio, PuntoTiempo& fin, std::tuple<std::string, std::string, size_t>);

    // // CIRCUITO HAMILTONIANO

    // void circuitoHamiltoniano(PuntoTiempo& inicio, PuntoTiempo& fin, std::tuple<std::string, std::string, size_t>);

    // // COLOREO

    // void coloreo(PuntoTiempo& inicio, PuntoTiempo& fin, std::tuple<std::string, std::string, size_t>);

    void crearGrafoArana(size_t limite, Grafo& grafo);

    void crearGrafoCircular(size_t limite, Grafo& grafo);

    void crearGrafoMalla(size_t limite, Grafo& grafo);
};

#endif
