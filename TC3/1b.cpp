/* Ejercicio #1A - Lista Posicionada
 * 
 * Crear una lista L3, ordenada, que contenga los elementos que pertenecen a C1 ∪ C2
 */

List 1B_Union(L1, L2)
{
	// We'll iterate over both sets, always adding the lowest element on a given pair
	position p1 = Primera(L1)
	position p2 = Primera(L2)

	// The result will be stored on a sets
	List L3
	Iniciar(L3)
	
	// We'll only iterate if at least only sets hasn't fully been explored yet
	while(p1 != nullpos || p2 != nullpos)
	{
		// If the first sets has been fully explored, we'll explore and add from the second sets
		if(p1 == nullpos)
		{
			AgregarAlFinal(Recuperar(p2, L2) , L3)
			p2 = Siguiente(p2, L2);
		} 

		// Otherwise, if the second sets has been fully explored, we'll explore and add from the first sets
		else if(p2 == nullpos)
		{
			AgregarAlFinal(Recuperar(p1, L1) , L3)
			p1 = Siguiente(p1, L1);
		}

		// Otherwise, both sets haven't been fully explored yet, so we'll need to explore both
		else 
		{
			// These comparisons assume the sets are ordered

			// If the first set's element is lesser than the second's, then we'll add it and explore the next element on the first set
			if (Recuperar(p1, L1)  < Recuperar(p2, L2))
			{
				AgregarAlFinal(Recuperar(p1, L1) , L3)
				p1 = Siguiente(p1, L1)
				
			}

			// Otherwise, if the second set's element is lesser than the first's, then we'll add it and explore the next element on the second set
			else if Recuperar(p1, L1)  > Recuperar(p2, L2) 
			{
				AgregarAlFinal(Recuperar(p2, L2) , L3) 
				p2 = Siguiente(p2, L2)
			} 

			// Otherwise, both element's on the explored pair are equal, and we need only add it once and explore the following elements on both sets
			else
			{
				AgregarAlFinal(Recuperar(p1, L1) , L3)
				p1 = Siguiente(p1, L1)
				p2 = Siguiente(p2, L2)
			}
		}
	}

	// By then, the union set has contains all elements of both sets, without repetitions, since we explored them all
	return L3
}