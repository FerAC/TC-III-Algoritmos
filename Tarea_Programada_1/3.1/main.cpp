#include "Tree_senaladorPadre.h"
#include <iostream>

int main(){

    ArbolSenalador tree(10);
    tree.PonerRaiz(5);
    tree.printTree();
    tree.AgregarHijo(0,2);
    tree.printTree();
    
    tree.AgregarHijo(0,10);
    tree.printTree();
    
    return 0;
}