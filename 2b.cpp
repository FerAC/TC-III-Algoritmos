// function return a list
list simetricDifference(L1, L2) {
	bool condition = true
	Iniciar(L3)
	
	int sizeL1 = numElem(L1)
	int sizeL2 = numElem(L2)
	
	index elementL1 = 0		// index is an unsigned int
	index elementL2 = 0
	index elementL3 = 0
	//elementL1 -> 4
	//L1 -> 
	//L2 -> 10, 11, 12, 13, 14, 15
	while ( elementL1<sizeL1 and elementL2<sizeL2) {
		if(Recuperar(elementL1, L1) < Recuperar(elementL2, L2) ){
			Insertar(elementL3, Recuperar(elementL1, L1), L3)
			++elementL1
			++elementL3
		}
		elif (Recuperar(elementL2, L2) < Recuperar(elementL1, L1) ) {
			Insertar(elementL3, Recuperar(elementL2, L2), L3)
			++elementL2
			++elementL3
		}
		else {
			++elementL1
			++elementL2
		}
	}
	
	while (elementL1<sizeL1) {
		Insertar(elementL3, Recuperar(elementL1, L1), L3)
		++elementL1
		++elementL3
    }
	
    while (elementL2<sizeL2) {
        Insertar(elementL3, Recuperar(elementL2, L2), L3)
		++elementL2
		++elementL3
    }	
	
	return L3
}