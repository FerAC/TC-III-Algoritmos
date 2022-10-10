#ifndef NODOLH
#define NODOLH
#include "Celda.h"

class Nodo{
	private:
		Celda<int,int> * hijo;
		
	public: 
		Nodo();
		~Nodo();
};
#endif 