#ifndef COLA_ARRAYCIRCULAR
#define COLA_ARRAYCIRCULAR

class Cola{
    private:
        int size;
        int start;
        int end;
        int *arrayCircular;


    public:
        Cola(int);                 // Crear
        ~Cola();                // Destruir
        void Encolar(int);      // Encolar
        int Desencolar();       // Desencolar
        int NumElem();          // Size
};
#endif