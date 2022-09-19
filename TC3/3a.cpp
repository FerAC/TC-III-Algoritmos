/* Ejercio #3A - Lista Posicionada
 * 
 * Crear una lista L3, no ordenada, que contenga los elementos que pertenecen a C1 ∪ C2
 */

// function return a list
List 3A_Merge_Union(L1, L2) 
{
	// Initialize union list (to be filled later)
	Iniciar(L3)
	
	// Copy L1's elements into L3
	Position element = Primera(L1)
	while (element != nullPos)
	{
		AgregarAlFinal(Recuperar(element, L1), L3)
		element = Siguiente(element, L1)
	}
	
	// Find non-duplicates of L3's elements on L2
	bool exist = true
	element = Primera(L2)
	while (element != nullPos) 
	{
		Position elementL3 = Primera(L3)
		// loop to verify if the element already exist in the L3 list
		while (elementL3 != nullPos && exist==true) 
		{
			if (Recuperar(element, L2) != Recuperar(elementL3, L3))
				exist = false
			else
				elementL3 = Siguiente(elementL3, L3)
		}
		
		if (exist == false)
			AgregarAlFinal(Recuperar(element, L2), L3)	
		
		element = Siguiente(element, L2)
		exist = true
	}
	
	return L3
}