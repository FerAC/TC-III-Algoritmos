// function return a list
list simetricDifference(L1, L2) {
	index elementL1 = 0	 // index is an unsigned int
	index elementL2 = 0
	index elementL3 = 0
	bool condition = true
	Iniciar(L3)
	
	while ( elementL1 <= NumElemt(L1) ) {
		while ( (condition == true) and ( elementL2 <= NumElemt(L2) ) ) {
			if ( Recuperar(elementL1, L1) !=  Recuperar(elementL2++, L2) ) {
				condition = false
			}
		}
		if (condition == false) {
			Insertar(elementL3, Recuperar(elementL1, L1), L3)
			++elementL3
			condition = true
		}
		++elementL1
		elementL2 = 0
	}
	
	while ( elementL2 <= NumElemt(L2) ) {
		elementL1 = 0
		while ( (condition == true) and ( elementL1 <= NumElemt(L1) ) ) {
			if ( Recuperar(elementL2, L2) !=  Recuperar(elementL1++, L1) ) {
				condition = false
			}
		}
		if (condition == false) {
			Insertar(elementL3, Recuperar(elementL2, L2), L3)
			++elementL3
			condition = true
		}
		++elementL2
	}
	
	// bubble sort L3 list
	for ( index index1 = 0; index1 <= NumElemt(L3); ++index1) {
		for ( index index2 = 0; index2 <= NumElemt(L3); ++index2) {
			if ( Recuperar(index2, L3) > Recuperar(Siguiente(index2, L3)) {
				element temporal = Recuperar(index2, L3)
				Modificar( index2, Recuperar(index2+1, L3), L3)
				Modificar( index2+1, temporal, L3)				
			}		
		}
	}
	
	
	
	return L3
}