#ifndef ARBOL_SENALADORPADRE
#define ARBOL_SENALADORPADRE

class ArbolSenalador
{

public:

    class Etiqueta
    {
        friend ArbolSenalador;
        Etiqueta();
        ~Etiqueta();
    };

    ArbolSenalador();
    ~ArbolSenalador();
    void PonerRaiz(Etiqueta);
    void AgregarHijo(Etiqueta);
    void AgregarHijoMasDerecho(Etiqueta);
    void BorrarHoja();
    Etiqueta getRaiz();
    Etiqueta getPadre();
    Etiqueta getHijoMasIzquierdo();
    Etiqueta getHermanoDerecho();
    void ModificaEtiqueta();
    int NumNodos();

private:
    class Node
    {
        friend ArbolSenalador;
        Node(Etiqueta);
        ~Node();
    };
};
#endif