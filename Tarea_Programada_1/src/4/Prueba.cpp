#include "Prueba.hpp"

Prueba::Prueba(size_t n, FuncionPrueba funcionPrueba, std::string nombre)
    : n(n), funcionPrueba(funcionPrueba), nombre(nombre)
{}

Prueba::~Prueba()
{};

void Prueba::correrPrueba()
{funcionPrueba(n, this->principioPrueba, this->finalPrueba);}

size_t Prueba::getN() const
{return n;}

size_t Prueba::getId() const
{return id;}

std::string Prueba::getNombre() const
{return nombre;}

template <typename TipoDuracion>
double Prueba::getDuracion() const
{return std::chrono::duration_cast<TipoDuracion>(this->finalPrueba - this->principioPrueba).count();}

std::ostream &operator<<(std::ostream &salida, const Prueba &prueba)
{
    #if defined(DATOS_BONITOS)
        std::cout << "~~~~~~~~~~~~~~PARAMETROS~~~~~~~~~~~~~~~~" << std::endl;
        std::cout << "N: " << prueba.getN() << std::endl;
        std::cout << "ID: " << prueba.getId() << std::endl;
        std::cout << "Nombre: " << prueba.getNombre() << std::endl;
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    #endif

    double duracionNano = prueba.getDuracion<std::chrono::nanoseconds>();
    double duracionMicro = prueba.getDuracion<std::chrono::microseconds>();
    double duracionMili = prueba.getDuracion<std::chrono::milliseconds>();
    double duracionSeg = prueba.getDuracion<std::chrono::seconds>();
    double duracionMin = prueba.getDuracion<std::chrono::minutes>();

    #if defined(DATOS_BONITOS)
        std::cout << "~~~~~~~~~~~~~~~~DURACION~~~~~~~~~~~~~~~~" << std::endl;
        std::cout << "Nanosegundos\t" << std::setprecision(5) << std::scientific << duracionNano << std::endl;
        std::cout << "Microsegundos\t" << std::setprecision(5) << std::scientific << duracionMicro << std::endl;
        std::cout << "Milisegundos\t" << std::setprecision(5) << std::scientific << duracionMili << std::endl;
        std::cout << "Segundos\t" << std::setprecision(5) << std::scientific << duracionSeg << std::endl;
        std::cout << "Minutos \t" << std::setprecision(5) << std::scientific << duracionMin << std::endl;
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    #else
        std::cout<< prueba.getN() << '\t' << prueba.getId() << '\t' << prueba.getNombre() << '\t'
        <<  duracionNano << '\t' << duracionMicro << '\t' << duracionMili << '\t' << duracionSeg << '\t' << duracionMin << std::endl;
    #endif

    return salida;
}
