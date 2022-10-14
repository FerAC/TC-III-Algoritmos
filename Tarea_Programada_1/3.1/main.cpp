#include "Tree_senaladorPadre.h"
#include <iostream>

int main()
{

    ArbolSenalador tree(10);
    tree.PonerRaiz(5);
    tree.AgregarHijo(0, 2);
    tree.AgregarHijo(1, 3);
    tree.AgregarHijo(1, 125);
    // tree.PonerRaiz(1000);

    tree.AgregarHijo(0, 25);
    tree.AgregarHijo(4, 12);
    tree.AgregarHijo(3, 7);
    tree.AgregarHijo(1, 76);
    tree.AgregarHijo(2, 0);
    tree.AgregarHijo(3, 65);
    tree.BorrarHoja(9);
    tree.AgregarHijo(0, 12343); // extra element
    tree.printTree();
    /*
    tree.printTree();

    tree.printTree();

    tree.AgregarHijo(0, 10);
    tree.printTree();

    tree.BorrarHoja(1);
    tree.printTree();


    tree.AgregarHijo(0, 1);
    tree.printTree();
    // tree.BorrarHoja(2);
    tree.printTree();
    */

    std::cout << "_______________________\n"
              << std::endl;

    return 0;
}