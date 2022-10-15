#ifndef COLA_ARRAYCIRCULAR
#define COLA_ARRAYCIRCULAR
#include <cstddef>

// TODO: ¿EMPLANTILLAR? (REVISAR SI ES NECESARIO HACER DE TIPO AGNÓSTICO)
class Cola{
    private:
        std::size_t size;
        int head;   // first out
        int end;    // last in
        int *arrayCircular;
        bool isEmpty;

    public:
        Cola(std::size_t);                 // Crear
        ~Cola();                // Destruir
        void Encolar(int);      // Encolar
        int Desencolar();       // Desencolar
        int NumElem();          // Size
        void vaciar();          // free the memory
        int vacia();            // isEmpty
};
#endif
