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
    //void AgregarHijoMasDerecho(int);
    void BorrarHoja();
    int getRaiz();
    int getPadre(int);
    //int getHijoMasIzquierdo();
    //int getHermanoDerecho();
    void ModificaEtiqueta(int, int);
    int NumNodos();

/*
    class Node
    {
        int etiqueta;
        friend ArbolSenalador;
        Node(int);
        ~Node();
    };
    */

private:
    int **doubleEntryArray;
    int sizeM;
    int sizeN;
};
#endif