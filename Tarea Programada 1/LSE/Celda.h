#ifndef Celda_Multitool
#define Celda_Multitool

class Celda{
	private:
		int etiqueta;
		Celda * siguiente; 
	public:
		Celda(int); 
		~Celda();
		Celda();
		int operator ==(Celda*);
		int getEtiqueta();
		Celda * getSiguiente();
		void setSiguiente(Celda*); 
		void imprimir(); 
};
#endif
