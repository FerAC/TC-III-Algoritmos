#ifndef COLA_ARRAYCIRCULAR
#define COLA_ARRAYCIRCULAR

// TODO: ¿EMPLANTILLAR? (REVISAR SI ES NECESARIO HACER DE TIPO AGNÓSTICO)
class Cola{
    private:
        // TODO: HACER SIZE DE TIPO SIZE_T
        int size;
        int head;   // first out
        int end;    // last in
        int *arrayCircular;

    public:
        // TODO: FALTA VACIAR Y VACIA
        Cola(int);                 // Crear
        ~Cola();                // Destruir
        void Encolar(int);      // Encolar
        int Desencolar();       // Desencolar
        int NumElem();          // Size
};
#endif
