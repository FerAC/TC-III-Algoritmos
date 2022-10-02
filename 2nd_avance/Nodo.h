#ifndef NODO_MULTITOOL
#define NODO_MULTITOOL

class Nodo {

    private:
        int etiqueta;
       // Nodo *siguiente;
        // hermanoDerecho
        // arrayHijos
         

    public:
        Nodo(int value);
        void setSiguiente(Nodo*);
        void setEtiqueta(int value);

};
#endif