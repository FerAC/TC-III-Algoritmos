#include "Arbol.hpp"

/// @brief Mini demo, incompleta hasta terminar de implementar el árbol
int main()
{
    // Creación
    Arbol<int> a;
    std::cout << a << std::endl;
    std::cout << "^^^ Arbol tras crearlo ^^^" << std::endl;

    // Colocar Raíz
    a.PonerRaiz(1);
    Arbol<int>::Nodo raiz = a.Raiz();
    std::cout << a << std::endl;
    std::cout << "^^^ Arbol tras insertar 1 como raíz ^^^" << std::endl;

    // Agregar hijos
    Arbol<int>::Nodo nodo_2 = a.AgregarHijo(2, raiz);
    Arbol<int>::Nodo nodo_3 = a.AgregarHijoMasDerecho(3, raiz);
    a.AgregarHijoMasDerecho(4, raiz);
    std::cout << a << std::endl;
    std::cout << "^^^ Arbol tras insertar 2, 3 y 4 ^^^" << std::endl;

    Arbol<int>::Nodo nodo_5 = a.AgregarHijo(5, nodo_2);
    Arbol<int>::Nodo nodo_6 = a.AgregarHijoMasDerecho(6, nodo_2);
    a.AgregarHijoMasDerecho(7, nodo_2);
    std::cout << a << std::endl;
    std::cout << "^^^ Arbol tras insertar 5, 6 y 7 ^^^" << std::endl;

    Arbol<int>::Nodo nodo_8 = a.AgregarHijo(8, nodo_3);
    Arbol<int>::Nodo nodo_9 = a.AgregarHijoMasDerecho(9, nodo_3);
    a.AgregarHijoMasDerecho(10, nodo_3);
    std::cout << a << std::endl;
    std::cout << "^^^ Arbol tras insertar 8, 9 y 10 ^^^" << std::endl;

    // Borrar hojas
    a.BorrarHoja(nodo_8);
    a.BorrarHoja(nodo_9);
    std::cout << a << std::endl;
    std::cout << "^^^ Arbol tras borrar hojas 8 y 9 ^^^" << std::endl;

    // Recuperar etiquetas
    std::cout << "Etiqueta del nodo raiz = " << a.Etiqueta(a.Raiz()) << std::endl;
    std::cout << "Etiqueta del nodo 5 = " << a.Etiqueta(nodo_5) << std::endl;
    std::cout << "Etiqueta del nodo 6 = " << a.Etiqueta(nodo_6) << std::endl;

    // Modificar etiquetas
    a.ModificaEtiqueta(raiz, 111);
    a.ModificaEtiqueta(nodo_5, 555);
    std::cout << a << std::endl;
    std::cout << "^^^ Arbol tras modificar etiquetas 1 -> 111, 5 -> 555 ^^^" << std::endl;

    // Obtener cantidad de nodos
    std::cout << "Cantidad de nodos en el arbol = " << a.NumNodos() << std::endl;

    // TODO: Realizar pruebas de casos mas específicos
    // TODO: Probar el manejo de excepciones

    return 0;
}
