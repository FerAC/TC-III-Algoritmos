// #include "3.1/3.1.hpp"
// #include "3.2/3.2.hpp"
// #include "3.3/3.3.hpp"
// #include "3.4/3.4.hpp"
#include "3.5/3.5.hpp"

/// @brief Mini demo, incompleta hasta terminar de implementar el árbol
int main()
{
    // Creación
    Arbol arbol;
    std::cout << arbol << std::endl;
    std::cout << "^^^ Arbol tras crearlo ^^^" << std::endl;

    // Colocar Raíz
    arbol.PonerRaiz(1);
    Nodo raiz = arbol.Raiz();
    std::cout << arbol << std::endl;
    std::cout << "^^^ Arbol tras insertar 1 como raíz ^^^" << std::endl;

    // Agregar hijos
    Nodo nodo_2 = arbol.AgregarHijo(2, raiz);
    Nodo nodo_3 = arbol.AgregarHijoMasDerecho(3, raiz);
    arbol.AgregarHijoMasDerecho(4, raiz);
    std::cout << arbol << std::endl;
    std::cout << "^^^ Arbol tras insertar 2, 3 y 4 ^^^" << std::endl;

    Nodo nodo_5 = arbol.AgregarHijo(5, nodo_2);
    Nodo nodo_6 = arbol.AgregarHijoMasDerecho(6, nodo_2);
    arbol.AgregarHijoMasDerecho(7, nodo_2);
    std::cout << arbol << std::endl;
    std::cout << "^^^ Arbol tras insertar 5, 6 y 7 ^^^" << std::endl;

    Nodo nodo_8 = arbol.AgregarHijo(8, nodo_3);
    Nodo nodo_9 = arbol.AgregarHijoMasDerecho(9, nodo_3);
    arbol.AgregarHijoMasDerecho(10, nodo_3);
    std::cout << arbol << std::endl;
    std::cout << "^^^ Arbol tras insertar 8, 9 y 10 ^^^" << std::endl;

    // Borrar hojas
    arbol.BorrarHoja(nodo_8);
    arbol.BorrarHoja(nodo_9);
    std::cout << arbol << std::endl;
    std::cout << "^^^ Arbol tras borrar hojas 8 y 9 ^^^" << std::endl;

    // Recuperar etiquetas
    std::cout << "Etiqueta del nodo raiz = " << arbol.Etiqueta(arbol.Raiz()) << std::endl;
    std::cout << "Etiqueta del nodo 5 = " << arbol.Etiqueta(nodo_5) << std::endl;
    std::cout << "Etiqueta del nodo 6 = " << arbol.Etiqueta(nodo_6) << std::endl;

    // Modificar etiquetas
    arbol.ModificaEtiqueta(raiz, 111);
    arbol.ModificaEtiqueta(nodo_5, 555);
    std::cout << arbol << std::endl;
    std::cout << "^^^ Arbol tras modificar etiquetas 1 -> 111, 5 -> 555 ^^^" << std::endl;

    // Obtener cantidad de nodos
    std::cout << "Cantidad de nodos en el arbol = " << arbol.NumNodos() << std::endl;

    // TODO: Realizar pruebas de casos mas específicos
    // TODO: Probar el manejo de excepciones

    return 0;
}
