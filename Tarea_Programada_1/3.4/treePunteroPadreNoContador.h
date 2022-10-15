// Hijo Más Izquierdo-Hermano Derecho con puntero al padre y al hermano izquierdo sin contador
#ifndef ARBOLPUNTEROPADRENOCONTADOR
#define ARBOLPUNTEROPADRENOCONTADOR

class ArbolNoContador
{

private:
    ArbolNoContador();
    ~ArbolNoContador();
    void PonerRaiz(int);
    void AgregarHijo(int, int);
    void BorrarHoja(int);
    int getRaiz();
    int getPadre(int);
    void ModificaEtiqueta(int, int);
    int NumNodos();
    void printTree();

public:
    

};
#endif