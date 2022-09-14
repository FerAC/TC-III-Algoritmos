/* Ejercio #2B - Lista Indexada
 * 
 * Crear una lista L3, ordenada, que contenga los elementos que pertenecen a C1 Δ C2
 */

// function return a list
list 2b_simetricDifference(L1, L2) {
	bool condition = true
	Iniciar(L3)
	
	int sizeL1 = numElem(L1)
	int sizeL2 = numElem(L2)
	
	index elementL1 = 0		// index is an unsigned int, therefore we can use comparation operators
	index elementL2 = 0
	index elementL3 = 0

	// first while to compare each element and store in L3 each element that is a in a list and not in the other
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
	
	// second while is used to store in L3 every remaining element that wasn't used in the first loop
	// this loop is used when the L2 list is emptied before L1
	while (elementL1<sizeL1) {
		Insertar(elementL3, Recuperar(elementL1, L1), L3)
		++elementL1
		++elementL3
    }
	
	// third while is used to store in L3 every remaining element that wasn't used in the first loop
	// this loop is used when the L1 list is emptied before L2
    while (elementL2<sizeL2) {
        Insertar(elementL3, Recuperar(elementL2, L2), L3)
		++elementL2
		++elementL3
    }	
	
	return L3
}