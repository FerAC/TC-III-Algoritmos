// function return a list
list 3a_mergeLists(L1, L2) {
	Iniciar(L3)
	position element = Primera(L1)
	bool exist = true
	
	while ( element != NULL ) {
		AgregarAlFinal(Recuperar(element, L1), L3)
		element = Siguiente(element, L1)
		// elementL3 = Siguiente(elementL3, L3)
	}
	
	element = Primera(L2)
	
	while ( element != NULL ) {
		position elementL3 = Primera(L3) 
		// loop to verify if the element already exist in the L3 list
		while ( elementL3 != NULL && existe==true) {
			if ( Recuperar(element, L2) != Recuperar(elementL3, L3) ) {
				exist = false
			}
			elementL3 = Siguiente(elementL3, L3)
		}
		
		if (exist == false) {
			AgregarAlFinal(Recuperar(element, L2), L3)	
		}
		element = Siguiente(element, L2)
		exist = true
	}
	
	return L3
}