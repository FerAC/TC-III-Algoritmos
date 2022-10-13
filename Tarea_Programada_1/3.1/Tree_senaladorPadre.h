#ifndef ARBOL_SENALADORPADRE
#define ARBOL_SENALADORPADRE

class ArbolSenalador
{

public:

    /*
    class Etiqueta
    {
        friend ArbolSenalador;
        Etiqueta(int);
        ~Etiqueta();
    };
    */

    ArbolSenalador(int);
    ~ArbolSenalador();
    void PonerRaiz(int);
    void AgregarHijo(int);
    void AgregarHijoMasDerecho(int);
    void BorrarHoja();
    int getRaiz();
    int getPadre();
    int getHijoMasIzquierdo();
    int getHermanoDerecho();
    void ModificaEtiqueta();
    int NumNodos();

private:
    int **doubleEntryArray;
    class Node
    {
        friend ArbolSenalador;
        Node(int);
        ~Node();
    };
};
#endif