#ifndef ARBOL_SENALADORPADRE
#define ARBOL_SENALADORPADRE

class ArbolSenalador
{
private:
    class Node
    {
        friend ArbolSenalador;
    };

public:
    class Etiqueta
    {
        friend ArbolSenalador;
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
};
#endif