#define FORMATO_PRUEBAS "[NOMBRE PRUEBA]\n[APODO PRUEBA]\n[NUM REPETICIONES PRUEBA]\n[PARAMETROS...]"

#ifdef CONTROLADOR

  #include "Controlador.hpp"

  int main() {

    Controlador::iniciar();
    return 0;
  }

#else

  #ifdef CONCURRENTE
    #include <thread>
  #endif

  #include <iostream>

  #include "Ensayos.hpp"
  #include "Pruebas.hpp"

  int main()
  {
    // INFO DE EJECUTABLE
    std::cout << "VERSION: " << VERSION_ENSAYOS << std::endl;

    // SETUP PRUEBAS
  
    std::map<std::string, FuncionPrueba<std::string, std::string, size_t>>
    funcionesDePrueba;

    funcionesDePrueba["Coloreo"] = Pruebas::coloreo;
    funcionesDePrueba["Arbol Minimal"] = Pruebas::arbolMinimal;
    funcionesDePrueba["Circuito Hamilton"] = Pruebas::circuitoHamiltoniano;
    funcionesDePrueba["Distancia de un vertice"] = Pruebas::distanciaCortaUno;
    funcionesDePrueba["Distancia entre todo vertice"] = Pruebas::distanciaCortaTodos;

    // INFO DE PRUEBAS

    std::cout << std::endl << "PRUEBAS DISPONIBLES:" << std::endl;
    for (auto it = funcionesDePrueba.cbegin(); it != funcionesDePrueba.cend(); ++it) {
      std::cout << it->first << std::endl;
    }
    std::cout << std::endl;

    // INFO DE PARÁMETROS
    std::cout << FORMATO_PRUEBAS << std::endl;

    // LEER PARAMETROS

    Ensayos<std::string, std::string, size_t> ensayos(funcionesDePrueba, std::cin
      , Pruebas::leerParametros, Pruebas::imprimirParametros);

    // EJECUTAR PRUEBAS

    #ifdef CONCURRENTE
      ensayos.ejecutarPruebasConcurrente(std::thread::hardware_concurrency(), std::cout)
    #else
      ensayos.ejecutarPruebasSerial(std::cout);
    #endif


    // IMPRIMIR RESULTADOS
    ensayos.imprimirPruebas(std::cout);

    return 0;
  }

#endif
