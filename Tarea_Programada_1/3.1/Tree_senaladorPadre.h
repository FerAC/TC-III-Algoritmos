#ifndef ARBOL_SENALADORPADRE
#define ARBOL_SENALADORPADRE

class ArbolSenalador
{

public:
    ArbolSenalador(int);
    ~ArbolSenalador();
    void PonerRaiz(int);
    void AgregarHijo(int, int);
    void BorrarHoja(int);
    int getRaiz();
    int getPadre(int);
    void ModificaEtiqueta(int, int);
    int NumNodos();
    //int buscar(int);
    void printTree();

private:
    int **doubleEntryArray;
    int sizeM;
    int sizeN;
    int isEmpty;
};
#endif