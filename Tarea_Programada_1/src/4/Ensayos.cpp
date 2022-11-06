
#include "Ensayos.hpp"

// I/O estandar
#include <iostream>

// Matemática
#include <cmath>

Ensayos::Ensayos(std::map<std::string, FuncionPrueba> &funciones, std::istream &entrada)
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
                std::cerr << "FUNCION DE PRUEBA " << bufferLinea << " NO ENCONTRADA" << std::endl;
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

Ensayos::~Ensayos()
{}

void Ensayos::ejecutarPruebasSerial()
{
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

void Ensayos::imprimirPruebas()
{
    // Dejar una línea de separación
    std::cout << std::endl;

    // Imprime todas las pruebas que se encuentran en el vector de pruebas
    for (auto it = pruebas.begin(); it != pruebas.end(); ++it)
        std::cout << *it << std::endl;
}

Prueba &Ensayos::getPrueba(size_t indice)
{
    return this->pruebas[indice];
}

// Adiciones de ejecución concurrente
#if defined(CONCURRENTE)

    void Ensayos::ejecutarPruebasConcurrente(size_t cantidadHilos)
    {
        // Llevaremos cuenta de los hilos que ejecutan pruebas
        std::vector<HiloPrueba> hilosPruebas;
        hilosPruebas.resize(cantidadHilos);

        // Comenzaremos a ejecutar los hilos
        for (size_t i = 0; i < cantidadHilos; ++i)
            hilosPruebas[i].correrHilo(*this);

        // Esperaremos por cada hilo
        for (size_t i = 0; i < cantidadHilos; ++i)
            hilosPruebas[i].esperarHilo();

        // Ya terminamos de ejecutar las pruebas
        return;
    }

    bool Ensayos::avanzarMarcadorPruebas(size_t &variableDeposito)
    {
        bool status = true;

        this->mutexMarcadorPrueba.lock();
        if (this->marcadorPrueba < this->pruebas.size())
        {
            variableDeposito = this->marcadorPrueba++;
            status = true;
        }
        else
            status = false;
        this->mutexMarcadorPrueba.unlock();

        return status;
    }

    void Ensayos::avanzarBarraProgresoTSafe()
    {
        this->mutexPruebasHechas.lock();
        ++this->pruebasHechas;
        double progresoActual = 100.0 * ((double) this->pruebasHechas / (double)this->pruebas.size());
        if (progresoActual != this->progreso)
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
        this->mutexPruebasHechas.unlock();
    }

#endif

// ~~~~~~~~~~~~~~~~~~~~~~~~~~ METODOS DE PRUEBA ~~~~~~~~~~~~~~~~~~~~~~~~~~

void Ensayos::etiquetasRepetidas(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal)
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

void Ensayos::borrarSubarbol(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal)
{
    Arbol arbol = Arbol();
    size_t cantidadNiveles = 4;
    size_t anchoPorNivel = 2;
    ListaIndexada lista;
    for (size_t j = 0; j < n; j++)
        lista.insertar(j, j);

    Controlador::crearArbol(cantidadNiveles, anchoPorNivel, lista, arbol);

    Nodo subraiz = arbol.Raiz(); // hay que cambiar

    std::chrono::high_resolution_clock clock;
    puntoInicio = clock.now();
    Controlador::borrarSubArbol(arbol, subraiz);
    puntoFinal = clock.now();
}

void Ensayos::crearArbol(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal)
{
    Arbol arbol = Arbol();
    std::chrono::high_resolution_clock clock;
    // N = 1 n mas pequeno, 9841
    size_t cantidadNiveles;
    size_t hijosPorNodo;
    switch (n)
    {
    case 1:
        cantidadNiveles = 9;
        hijosPorNodo = 3;
        break;
    case 2:
        cantidadNiveles = 8;
        hijosPorNodo = 5;
        break;
    case 3:
        cantidadNiveles = 8;
        hijosPorNodo = 7;
        break;
    default:
        std::cerr << "ERROR, N DISTINTO DE 1, 2, 3 ";
        break;
    }
    size_t cantidadNodos = (std::pow(hijosPorNodo, cantidadNiveles) - 1) / (hijosPorNodo - 1);

    ListaIndexada lista;
    for (size_t j = 0; j < cantidadNodos; ++j)
        lista.insertar(j, j);

    puntoInicio = clock.now();
    Controlador::crearArbol(cantidadNiveles, hijosPorNodo, lista, arbol);
    puntoFinal = clock.now();
}

void Ensayos::crearArbolAlturaExtrema(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal)
{
    Arbol arbol = Arbol();
    std::chrono::high_resolution_clock clock;
    size_t cantidadNodos;
    switch (n)
    {
    case 1:
        cantidadNodos = 9841;
        break;
    case 2:
        cantidadNodos = 9756;
        break;
    case 3:
        cantidadNodos = 960800;
        break;
    default:
        std::cerr << "ERROR, N DISTINTO DE 1, 2, 3 ";
        break;
    }
    puntoInicio = clock.now();
    Controlador::crearArbolAlturaExtrema(cantidadNodos, arbol);
    puntoFinal = clock.now();
}

void Ensayos::crearArbolAnchuraExtrema(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal)
{
    Arbol arbol = Arbol();
    std::chrono::high_resolution_clock clock;
    size_t cantidadNodos;
    switch (n)
    {
    case 1:
        cantidadNodos = 9841 - 1;
        break;
    case 2:
        cantidadNodos = 9756 - 1;
        break;
    case 3:
        cantidadNodos = 960800 - 1;
        break;
    default:
        std::cerr << "ERROR, N DISTINTO DE 1, 2, 3 ";
        break;
    }
    puntoInicio = clock.now();
    Controlador::crearArbolAnchuraExtrema(cantidadNodos, arbol);
    puntoFinal = clock.now();
}

void Ensayos::crearArbolHijoCortoHijoLargo(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal)
{
    size_t cantidadNodos;
    switch (n)
    {
    case 1:
        cantidadNodos = 9841;
        break;
    case 2:
        cantidadNodos = 9756;
        break;
    case 3:
        cantidadNodos = 960800;
        break;
    default:
        std::cerr << "ERROR, N DISTINTO DE 1, 2, 3 ";
        break;
    }
    Arbol arbol = Arbol();
    std::chrono::high_resolution_clock clock;
    // int cantidadNodos = 100;
    // size_t cantidadHijosRaiz = 5;                   // para crearArbolHijoCortoHijoLargo
    size_t cantidadHijosRaiz = 100; // para crearArbolHijoCortoHijoLargo

    puntoInicio = clock.now();
    Controlador::crearArbolHijoCortoHijoLargo(n, cantidadHijosRaiz, arbol); //caso promedio
    // Controlador::crearArbolHijoCortoHijoLargoPeorCaso(n, cantidadHijosRaiz, arbol);
    //  Controlador::crearArbolHijoCortoHijoLargoMejorCaso(n, cantidadHijosRaiz, arbol);
    puntoFinal = clock.now();
}

void Ensayos::poblarNormalSegunPrueba(Arbol &arbol, int n, int caso)
{
    // N = 1 n mas pequeno, 9841
    size_t cantidadNiveles;
    size_t hijosPorNodo;
    switch (n)
    {
    case 1:
        cantidadNiveles = 9;
        hijosPorNodo = 3;
        break;
    case 2:
        cantidadNiveles = 8;
        hijosPorNodo = 5;
        break;
    case 3:
        cantidadNiveles = 8;
        hijosPorNodo = 7;
        break;
    default:
        std::cerr << "ERROR, N DISTINTO DE 1, 2, 3 ";
        break;
    }
    size_t cantidadNodos = (std::pow(hijosPorNodo, cantidadNiveles) - 1) / (hijosPorNodo - 1);

    ListaIndexada lista;
    switch (caso)
    {
    case 1: // Mejor caso
        lista.insertar(0, 0);
        lista.insertar(0, 1);
        for (size_t j = 2; j < cantidadNodos; ++j)
            lista.insertar(j, j);
        break;

    case 2:
        if (cantidadNodos % 2)
        { // No es divisible
            for (size_t j = 0; j < cantidadNodos; ++j)
            {
                if (j = (cantidadNodos / 2) + 1)
                {
                    lista.insertar(0, j);
                }
                lista.insertar(j, j);
            }
        }
        else
        {
            for (size_t j = 0; j < cantidadNodos; ++j)
            {
                if (j = cantidadNodos / 2)
                {
                    lista.insertar(0, j);
                }
                lista.insertar(j, j);
            }
        }
        break;
    case 3: // Peor caso
        for (size_t j = 0; j < cantidadNodos - 1; ++j)
            lista.insertar(j, j);
        lista.insertar(0, cantidadNodos);
        break;
    default:
        break;
    }
    for (size_t j = 0; j < cantidadNodos; ++j)
        lista.insertar(j, j);

    Controlador::crearArbol(cantidadNiveles, hijosPorNodo, lista, arbol);
}

void Ensayos::etiquetasRepetidasNormal1(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal)
{
    std::chrono::high_resolution_clock clock;
    Arbol arbol;
    Ensayos::poblarNormalSegunPrueba(arbol, n, 1);
    puntoInicio = clock.now();
    Controlador::averiguarEtiquetasRepetidas(arbol);
    puntoFinal = clock.now();
}

void Ensayos::etiquetasRepetidasNormal2(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal)
{
    std::chrono::high_resolution_clock clock;
    Arbol arbol;
    Ensayos::poblarNormalSegunPrueba(arbol, n, 2);
    puntoInicio = clock.now();
    Controlador::averiguarEtiquetasRepetidas(arbol);
    puntoFinal = clock.now();
}

void Ensayos::etiquetasRepetidasNormal3(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal)
{
    std::chrono::high_resolution_clock clock;
    Arbol arbol;
    Ensayos::poblarNormalSegunPrueba(arbol, n, 3);
    puntoInicio = clock.now();
    Controlador::averiguarEtiquetasRepetidas(arbol);
    puntoFinal = clock.now();
}

void Ensayos::poblarArbolAlturaExtremaSegunPrueba(Arbol &arbol, int caso, int n)
{
    std::chrono::high_resolution_clock clock;
    size_t cantidadNodos;
    switch (n)
    {
    case 1:
        cantidadNodos = 9841;
        break;
    case 2:
        cantidadNodos = 9756;
        break;
    case 3:
        cantidadNodos = 960800;
        break;
    default:
        std::cerr << "ERROR, N DISTINTO DE 1, 2, 3 ";
        break;
    }

    arbol.PonerRaiz(0);
    if (caso == 1)
    { // Mejor caso
        Nodo padre = arbol.AgregarHijo(0, arbol.Raiz());
        for (size_t i = 2; i < cantidadNodos; ++i)
            padre = arbol.AgregarHijo(i, padre);
    }
    else if (caso == 2)
    { // Caso medio
        Nodo padre;
        arbol.PonerRaiz(0);
        if (cantidadNodos % 2)
        {
            for (size_t i = 1; i < cantidadNodos; ++i)
            {
                if (i == (cantidadNodos -1 ) / 2)
                {
                    padre = arbol.AgregarHijo(0, padre);
                }
                else
                {
                    padre = arbol.AgregarHijo(i, padre);
                }
            }
        }
        else
        {
            for (size_t i = 1; i < cantidadNodos; ++i)
            {
                if (i == cantidadNodos / 2)
                {
                    padre = arbol.AgregarHijo(0, padre);
                }
                else
                {
                    padre = arbol.AgregarHijo(i, padre);
                }
            }
        }
    }
    else
    { // Peor caso
        Nodo padre;
        for (size_t i = 0; i < cantidadNodos - 1; i++)
            padre = arbol.AgregarHijo(i, padre);
        arbol.AgregarHijo(0, padre);
    }
}

void Ensayos::etiquetasRepetidasAlto1(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal){
    std::chrono::high_resolution_clock clock;
    Arbol arbol; 
    Ensayos::poblarArbolAlturaExtremaSegunPrueba(arbol, 1, n); 
    puntoInicio = clock.now();
    Controlador::averiguarEtiquetasRepetidas(arbol); 
    puntoFinal = clock.now();
}

void Ensayos::etiquetasRepetidasAlto2(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal){
    std::chrono::high_resolution_clock clock;
    Arbol arbol; 
    Ensayos::poblarArbolAlturaExtremaSegunPrueba(arbol, 2, n); 
    puntoInicio = clock.now();
    Controlador::averiguarEtiquetasRepetidas(arbol); 
    puntoFinal = clock.now();
}

void Ensayos::etiquetasRepetidasAlto3(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal){
    std::chrono::high_resolution_clock clock;
    Arbol arbol; 
    Ensayos::poblarArbolAlturaExtremaSegunPrueba(arbol, 3, n); 
    puntoInicio = clock.now();
    Controlador::averiguarEtiquetasRepetidas(arbol); 
    puntoFinal = clock.now();
}

void Ensayos::PoblarArbolAnchuraExtremaSegunPrueba(Arbol& arbol, int caso, int n)
{    
    size_t cantidadNodos;
    switch (n)
    {
    case 1:
        cantidadNodos = 9841 - 1;
        break;
    case 2:
        cantidadNodos = 9756 - 1;
        break;
    case 3:
        cantidadNodos = 960800 - 1;
        break;
    default:
        std::cerr << "ERROR, N DISTINTO DE 1, 2, 3 ";
        break;
    }
    
    arbol.PonerRaiz(0);
    Nodo raiz = arbol.Raiz();
    switch (caso)
    {
    case 1: //Mejor caso
        arbol.AgregarHijo(0, raiz);
        for (size_t etiqueta = 2; etiqueta < cantidadNodos; ++etiqueta)
            arbol.AgregarHijo(etiqueta, raiz);
        break;
    case 2: //Caso promedio
        if(cantidadNodos % 2){ //No es divisible
            for (size_t etiqueta = 1; etiqueta < cantidadNodos; ++etiqueta)
                if(etiqueta = (cantidadNodos-1)/2){
                    arbol.AgregarHijo(0, raiz);
                } else{
                    arbol.AgregarHijo(etiqueta, raiz);
                } 
        } else{ // Si es divisible 
             for (size_t etiqueta = 1; etiqueta < cantidadNodos; ++etiqueta)
                if(etiqueta = cantidadNodos/2){
                    arbol.AgregarHijo(0, raiz);
                } else{
                    arbol.AgregarHijo(etiqueta, raiz);
                } 
        }
        break;
    case 3: //Peor caso
        for (size_t etiqueta = 1; etiqueta < cantidadNodos-1; ++etiqueta)
            arbol.AgregarHijo(etiqueta, raiz);
        arbol.AgregarHijo(0, raiz);
        break;
    default:
     std::cerr << ""; 
        break;
    }
    
    /*
    cantidadNodos;
    for (size_t etiqueta = 1; etiqueta < anchura; ++etiqueta)
        arbol.AgregarHijo(etiqueta, raiz);
   */
}

void Ensayos::etiquetasRepetidasAncho1(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal){
    std::chrono::high_resolution_clock clock;
    Arbol arbol; 
    Ensayos::PoblarArbolAnchuraExtremaSegunPrueba(arbol, 1, n); 
    puntoInicio = clock.now();
    Controlador::averiguarEtiquetasRepetidas(arbol); 
    puntoFinal = clock.now();
}
void Ensayos::etiquetasRepetidasAncho2(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal){
    std::chrono::high_resolution_clock clock;
    Arbol arbol; 
    Ensayos::PoblarArbolAnchuraExtremaSegunPrueba(arbol, 2, n); 
    puntoInicio = clock.now();
    Controlador::averiguarEtiquetasRepetidas(arbol); 
    puntoFinal = clock.now();
}
void Ensayos::etiquetasRepetidasAncho3(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal){
    std::chrono::high_resolution_clock clock;
    Arbol arbol; 
    Ensayos::PoblarArbolAnchuraExtremaSegunPrueba(arbol, 3, n); 
    puntoInicio = clock.now();
    Controlador::averiguarEtiquetasRepetidas(arbol); 
    puntoFinal = clock.now();
}

void Ensayos::PoblarArbolHijoCortoHijoLargoSegunPrueba(Arbol& arbol, int caso, int n)
{
    size_t cantidadNodos;
    switch (n)
    {
    case 1:
        cantidadNodos = 9841;
        break;
    case 2:
        cantidadNodos = 9756;
        break;
    case 3:
        cantidadNodos = 960800;
        break;
    default:
        std::cerr << "ERROR, N DISTINTO DE 1, 2, 3 ";
        break;
    }
    size_t cantidadHijosRaiz = 100; 
    

     switch (caso)
    {
    case 1: // Mejor caso
        Controlador::crearArbolHijoCortoHijoLargoMejorCaso(n, cantidadHijosRaiz, arbol);
        break;

    case 2:
        Controlador::crearArbolHijoCortoHijoLargo(n, cantidadHijosRaiz, arbol); //caso promedio
        break;

    case 3: // Peor caso
        Controlador::crearArbolHijoCortoHijoLargoPeorCaso(n, cantidadHijosRaiz, arbol);
        break;
    default:
        break;
    }
}


void Ensayos::etiquetasRepetidasHijoCortoHijoLargo1(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal){
    std::chrono::high_resolution_clock clock;
    Arbol arbol; 
    Ensayos::PoblarArbolHijoCortoHijoLargoSegunPrueba(arbol, 1, n); 
    puntoInicio = clock.now();
    Controlador::averiguarEtiquetasRepetidas(arbol); 
    puntoFinal = clock.now();
}
void Ensayos::etiquetasRepetidasHijoCortoHijoLargo2(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal){
    std::chrono::high_resolution_clock clock;
    Arbol arbol; 
    Ensayos::PoblarArbolHijoCortoHijoLargoSegunPrueba(arbol, 2, n); 
    puntoInicio = clock.now();
    Controlador::averiguarEtiquetasRepetidas(arbol); 
    puntoFinal = clock.now();
}
void Ensayos::etiquetasRepetidasHijoCortoHijoLargo3(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal){
    std::chrono::high_resolution_clock clock;
    Arbol arbol; 
    Ensayos::PoblarArbolHijoCortoHijoLargoSegunPrueba(arbol, 3, n); 
    puntoInicio = clock.now();
    Controlador::averiguarEtiquetasRepetidas(arbol); 
    puntoFinal = clock.now();
}

Nodo Ensayos::borrarSubArbolAlturaSegunPrueba(size_t n, Arbol& arbol){ //No vale la pena medir el mejor caso
     // Colocamos raiz
    arbol.PonerRaiz(0);
    Nodo padre = arbol.Raiz();
    Nodo retornado; 
    // Se insertan el resto de nodos de modo que el padre de la iteracion actual, es el nodo insertado en la iteracion anterior
    int parada;
     switch (n)
    {
    case 1:
        n = 9841;
        break;
    case 2:
        n = 97656; 
        break;
    case 3:
        n = 960800; 
        break; 
    default:
        break;
    }

    if (n%2)
    {
        parada = (n-1)/2;
    } else{
        parada = n/2; 
    }
    
    for (size_t contador = 1; contador < n; contador++)
    {
        if(contador==parada){
            retornado = padre; 
        }
        padre = arbol.AgregarHijo(contador, padre);
    }
    return retornado; 
}
void Ensayos::borrarSubarbolAltura2(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal){
    std::chrono::high_resolution_clock clock;
    Arbol arbol; 
    Nodo subRaiz = Ensayos::borrarSubArbolAlturaSegunPrueba(n, arbol); 
    puntoInicio = clock.now();
    Controlador::borrarSubArbol(arbol, subRaiz); 
    puntoFinal = clock.now();
}
void Ensayos::borrarSubarbolAltura3(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal){
    std::chrono::high_resolution_clock clock;
    Arbol arbol; 
    Controlador::crearArbolAlturaExtrema(n, arbol); 
    Nodo subRaiz = arbol.Raiz(); 
    puntoInicio = clock.now();
    Controlador::borrarSubArbol(arbol, subRaiz); 
    puntoFinal = clock.now();
}
Nodo Ensayos::borrarSubarbolAnchuraSegunPrueba(size_t n, Arbol& arbol){
    // Coloquemos a la raíz
    arbol.PonerRaiz(0);
    Nodo raiz = arbol.Raiz();

    // Asignemosle tantos hijos como especifique la anchura

    // Como ya consideramos a la etiqueta '0', debemos ampliar nuestro límite superior por un campo más para
    // satisfacer a toda la anchura original
    ++n;
    int parada; 
    switch (n)
    {
    case 1:
        n = 9841;
        break;
    case 2:
        n = 97656; 
        break;
    case 3:
        n = 960800; 
        break; 
    default:
        break;
    }
    Nodo retornado; 
    if(n%2){
        parada = (n-1) / 2;
    } else{
        parada = n/2;
    }
    for (size_t etiqueta = 1; etiqueta < n; ++etiqueta){
        if(etiqueta == parada){
            retornado = arbol.AgregarHijo(etiqueta, raiz);
        } else{
            arbol.AgregarHijo(etiqueta, raiz);
        }
    }
    return retornado; 
} 
void Ensayos::borrarSubarbolAnchura2(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal){
    std::chrono::high_resolution_clock clock;
    Arbol arbol; 
    Nodo subRaiz = Ensayos::borrarSubarbolAnchuraSegunPrueba(n, arbol); 
    puntoInicio = clock.now();
    Controlador::borrarSubArbol(arbol, subRaiz); 
    puntoFinal = clock.now();
}
void Ensayos::borrarSubarbolAnchura3(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal){
    std::chrono::high_resolution_clock clock;
    Arbol arbol; 
    Ensayos::borrarSubarbolAnchuraSegunPrueba(n, arbol); 
    puntoInicio = clock.now();
    Controlador::borrarSubArbol(arbol, arbol.Raiz()); 
    puntoFinal = clock.now();
}
Nodo Ensayos::borrarSubArbolNormalSegunPrueba(size_t n, Arbol& arbol, ListaIndexada lista, int i, int k){
    Nodo retornado; 
    // Primera condicion: por lo menos un nivel y un hijo por nivel
    if (i > 0 && k > 0)
    {
        // Ya que el arbol tiene por lo menos un nivel, por lo menos un hijo por nivel, entonces hay una raiz
        arbol.PonerRaiz(lista.recuperar(0));

        // Segunda condicion: por lo menos 2 niveles
        if (i > 1)
        {
            // Ademas de la primeras condicion, ya que el arbol tiene por lo menos 2 niveles, debemos considerar si sus hijos son padres tambien
            Util::Cola<Nodo> parentNodesQueue;
            parentNodesQueue.Encolar(arbol.Raiz());

            size_t numNodesTotal = (pow(k, i) - 1) / (k - 1); // La cantidad total de nodos a agregar en el arbol despues que sea completamente construido
            size_t numNodesLastLevel = pow(k, i - 1);         // la cantidad de nodos esperados en el ultimo nivel del arbol
            size_t numNodesAdded = 1;                         // La cantidad de nodos añadidos hasta ahora, la raiz es un nodo asi que llevamos uno

            // Vamos a añadir nodos hijos a todos los niveles menos el ultimo. No hay necesidad de añadirselo al ultimo
            int parada;
            if(numNodesTotal % 2){
                parada = (n-1) /2 ;
            } else{
                parada = n/2; 
            }
            while (numNodesAdded < numNodesTotal)
            {
                // El padre al que agregarle un hijo
                // La cantidad de hijos po padre ya se conoce. Podemos producirla
                Nodo padre = parentNodesQueue.Desencolar();
                if(numNodesAdded == parada)
                    retornado = padre;
                for (size_t numChildAdded = 0; numChildAdded < k; ++numChildAdded)
                {
                    // Es una precondicion de esta funcion en el que se nos garantiza un valor en la lista por cada nodo en el arbol
                    Nodo newChild = arbol.AgregarHijo(lista.recuperar(numNodesAdded), padre);
                    ++numNodesAdded;

                    // Cada vez que poduzcamos un nuevo hijo, se puede considerar como un padre que valdria la pena visitar despues
                    // Aunque, esta consideracion solo se puede hacer si no hemos alcanzado el ultimo nivel del arbol
                    if (numNodesTotal - numNodesAdded >= numNodesLastLevel)
                        parentNodesQueue.Encolar(newChild);
                }
            }
        }
    }
    return retornado; 
}
void Ensayos::borrarSubarbolNormal2(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal){
    int i, k;
    std::chrono::high_resolution_clock clock;
    switch (n)
    {
    case 1:
        k = 7;
        i = 8;
        break;
    case 2:
        k = 5;
        i = 8;
        break;
    
    case 3:
        k = 3;
        i = 9; 
        break; 

    default:
        break;
    }
    Arbol arbol;
    ListaIndexada lista;
    size_t cantidadNodos = (std::pow(k, i) - 1) / (k - 1);
    for (size_t i = 0; i < cantidadNodos; i++)
    {
        lista.insertar(i,i);
    }
    
    Nodo subRaiz = Ensayos::borrarSubArbolNormalSegunPrueba(cantidadNodos, arbol, lista, i, k ); 
    puntoInicio = clock.now();
    Controlador::borrarSubArbol(arbol, subRaiz); 
    puntoFinal = clock.now(); 

}
void Ensayos::borrarSubarbolNormal3(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal){
    int i, k;
    std::chrono::high_resolution_clock clock;
    switch (n)
    {
    case 1:
        k = 7;
        i = 8;
        break;
    case 2:
        k = 5;
        i = 8;
        break;
    
    case 3:
        k = 3;
        i = 9; 
        break; 

    default:
        break;
    }
    Arbol arbol;
    ListaIndexada lista;
    size_t cantidadNodos = (std::pow(k, i) - 1) / (k - 1);
    for (size_t i = 0; i < cantidadNodos; i++)
    {
        lista.insertar(i,i);
    }
    
    Controlador::crearArbol(i, k, lista, arbol); 
    puntoInicio = clock.now();
    Controlador::borrarSubArbol(arbol, arbol.Raiz()); 
    puntoFinal = clock.now(); 
}

Nodo Ensayos::borrarSubarbolHijoCortoHijoLargoSegunPrueba(size_t n, Arbol& arbol){
    size_t contador = 0;
    size_t cantidadHijosRaiz = 100; 

     switch (n)
    {
    case 1:
        n = 9841;
        break;
    case 2:
        n = 97656; 
        break;
    case 3:
        n = 960800; 
        break; 
    default:
        break;
    }

    for (contador = 0; contador <= cantidadHijosRaiz; contador++)
    {
        if (contador == 0)
        {
            arbol.PonerRaiz(contador);
        }
        else
        {
            arbol.AgregarHijoMasDerecho(contador, arbol.Raiz());
        }
    }

    int parada;
    if(n%2){
        parada = (n-1)/2;
    } else{
        parada = n/2; 
    }
    Nodo nodoNulo = Nodo();
    Nodo hermano = arbol.HijoMasIzquierdo(arbol.Raiz());
    bool esLargo = 1;
    auto cantidadHijosLargos = (cantidadHijosRaiz / 2 + cantidadHijosRaiz % 2);
    int largoHijos = (n - (2 * cantidadHijosRaiz) - 1) / cantidadHijosLargos;
    int largoUltimoHijo = largoHijos + (n - (2 * cantidadHijosRaiz) - 1) - (largoHijos * cantidadHijosLargos);
    Nodo retorno;
    // recoge todos los hijos de Raiz
    while (hermano != nodoNulo)
    {   
        if(contador == parada){
            retorno = arbol.AgregarHijo(contador, hermano);
        } else{
            arbol.AgregarHijo(contador, hermano);
        }
        Nodo hijo = arbol.HijoMasIzquierdo(hermano);
        ++contador;

        if (esLargo == 0)
        {
            esLargo = 1;
        }
        else if (esLargo == 1)
        {
            int contadorLocal = 0;
            if (arbol.HermanoDerecho(hermano) == nodoNulo || arbol.HermanoDerecho(arbol.HermanoDerecho(hermano)) == nodoNulo)
            {
                while (contadorLocal < largoUltimoHijo)
                {
                    arbol.AgregarHijo(contador, hijo);
                    hijo = arbol.HijoMasIzquierdo(hijo);
                    ++contador;
                    ++contadorLocal;
                }
            }
            else
            {
                while (contadorLocal < largoHijos)
                {
                    arbol.AgregarHijo(contador, hijo);
                    hijo = arbol.HijoMasIzquierdo(hijo);
                    ++contador;
                    ++contadorLocal;
                }
                arbol.AgregarHijo(0, hijo); // caso promedio, se repite varias veces en el codigo el 0
            }
            esLargo = 0;
        }

        hermano = arbol.HermanoDerecho(hermano);
    }
    return retorno; 
}
void Ensayos::borrarSubarbolHijoCortoHijoLargo2(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal){
    std::chrono::high_resolution_clock clock;
    Arbol arbol;
    Nodo subRaiz = Ensayos::borrarSubarbolHijoCortoHijoLargoSegunPrueba(n, arbol);
    puntoInicio = clock.now();
    Controlador::borrarSubArbol(arbol, subRaiz);
    puntoFinal = clock.now();
}
void Ensayos::borrarSubarbolHijoCortoHijoLargo3(size_t n, PuntoTiempo &puntoInicio, PuntoTiempo &puntoFinal){
    std::chrono::high_resolution_clock clock;
    Arbol arbol;
    Ensayos::borrarSubarbolHijoCortoHijoLargoSegunPrueba(n, arbol);
    puntoInicio = clock.now();
    Controlador::borrarSubArbol(arbol, subRaiz);
    puntoFinal = clock.now();
}
