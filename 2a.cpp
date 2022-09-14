/* Ejercio #2A - Lista Indexada
 * 
 * Crear una lista L3, ordenada, que contenga los elementos que pertenecen a C1 – C2
 */

// Function return a list
List 2A_C1_Minus_C2(L1, L2) 
{
	bool condition = true
	Iniciar(L3)
	
	int sizeL1 = numElem(L1)
	int sizeL2 = numElem(L2)
	
	Index elementL1 = 0		// Index is an unsigned int
	Index elementL2 = 0
	Index elementL3 = 0

	// first while to compare each element and store in L3 each element that is a in a list and not in the other
	while (elementL1 < sizeL1 and elementL2 < sizeL2) 
	{
		if(Recuperar(elementL1, L1) < Recuperar(elementL2, L2) )
		{
			Insertar(elementL3, Recuperar(elementL1, L1), L3)
			++elementL1
			++elementL3
		}
		else if (Recuperar(elementL2, L2) < Recuperar(elementL1, L1) ) 
		{
			++elementL2
			++elementL3
		}
		else 
		{
			++elementL1
			++elementL2
		}
	}
	
	// Second while is used to store in L3 every remaining element that wasn't used in the first loop
	// This loop is used when the L2 list end before L1
	while (elementL1<sizeL1) 
	{
		Insertar(elementL3, Recuperar(elementL1, L1), L3)
		++elementL1
		++elementL3
    }

	return L3
}