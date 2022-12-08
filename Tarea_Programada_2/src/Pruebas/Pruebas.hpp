#ifndef PRUEBAS
#define PRUEBAS

#include "GrafoImplementado.hpp"
#include "UnidadPrueba.hpp"

// TODO(us): Cambiar invocaciones para que compile
namespace Pruebas {

    // ARBOLES MINIMALES

    void arbolMinimal(PuntoTiempo& inicio, PuntoTiempo& fin
        , std::tuple<std::string, std::string, size_t> parametros);

    // CAMINOS DE MENOR COSTO

    void distanciaCortaUno(PuntoTiempo& inicio, PuntoTiempo& fin
        , std::tuple<std::string, std::string, size_t> parametros);

    void distanciaCortaTodos(PuntoTiempo& inicio, PuntoTiempo& fin
        , std::tuple<std::string, std::string, size_t> parametros);

    // CIRCUITO HAMILTONIANO

    void circuitoHamiltoniano(PuntoTiempo& inicio, PuntoTiempo& fin
        , std::tuple<std::string, std::string, size_t> parametros);

    // COLOREO

    void coloreo(PuntoTiempo& inicio, PuntoTiempo& fin
        , std::tuple<std::string, std::string, size_t> parametros);

    void leerParametros(std::tuple<std::string, std::string, size_t>& parametros
        , std::istream& entrada);

    void imprimirParametros(const std::tuple<std::string, std::string, size_t>& parametros
        , std::ostream& salida);
};

#endif
