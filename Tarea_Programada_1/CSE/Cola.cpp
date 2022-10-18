#include "Cola.hpp"

/// @brief Mini demo, incompleta hasta terminar de implementar el árbol
int main()
{
    // Creación
    Cola<int> cola;
    std::cout << cola << std::endl;
    std::cout << "^^^ Cola tras crearla ^^^" << std::endl;

    // Encoladas
    cola.Encolar(1);
    std::cout << cola << std::endl;
    std::cout << "^^^ Cola tras encolar 1 ^^^" << std::endl;

    cola.Encolar(2); cola.Encolar(3); cola.Encolar(4);
    std::cout << cola << std::endl;
    std::cout << "^^^ Cola tras insertar 2, 3 y 4 ^^^" << std::endl;

    // Desencolar
    std::cout << "Valor desencolado = " << cola.Desencolar() << std::endl;
    std::cout << cola << std::endl;
    std::cout << "^^^ Cola tras desencolar 1 ^^^" << std::endl;

    std::cout << "Valores desencolados = " 
        << cola.Desencolar() 
        << ", " << cola.Desencolar()
        << ", " << cola.Desencolar()
    << std::endl;
    std::cout << cola << std::endl;
    std::cout << "^^^ Cola tras desencolar 2, 3 y 4 ^^^" << std::endl;

    std::cout << "¿Esta la cola vacia? ";
    if (cola.Vacio()) std::cout << "Si" << std::endl;
    else std::cout << "No" << std::endl;

    // Desencolar una cola vacía
    std::cout << "¿Es posible seguir desencolando la cola?" << std::endl;
    try
    {
        int valorDesencolado = cola.Desencolar();
        std::cout << "Sí, es valor desencolado es " << valorDesencolado << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cout << "No, es imposible. La excepción es:" << std::endl;
        std::cout << "[ERROR] = " << e.what() << std::endl;
    }

    // TODO: Realizar pruebas de casos mas específicos
    // TODO: Probar el manejo de excepciones

    return 0;
}
