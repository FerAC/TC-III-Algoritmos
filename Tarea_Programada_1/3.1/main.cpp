#include "Tree_senaladorPadre.h"
#include <iostream>

int main(){

    ArbolSenalador tree(10);
    tree.PonerRaiz(5);
    tree.printTree();
    //std::cout<<"_______________________\n" <<std::endl;
    tree.AgregarHijo(5,2);
    tree.printTree();
    //std::cout<<"_______________________\n" << std::endl;
    
    return 0;
}