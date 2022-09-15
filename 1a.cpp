/* Ejercio #1B - Lista Posicionada
 * 
 * Averiguar si C1 es subconjunto de C2, es decir si todos los elementos de C1 están en C2
 */

bool 1A_Be_Subset(L1, L2)
{
	// Base case: The subset can't be greater than the set
	if (NumElem(L1) > NumElem(L2))
		return false

	// If the presumed subset is equal or smaller in size than the set, we can check for elements
	Position p2 = Primera(L2) // We'll try to match the first element on the greater set
	Position p1 = Primera(L1) // And the first element on the presumed subset
	bool condition = true // If at any point we find there's no possible match, we will abort the search

	// If we haven't found any strong indication the presumed subset isn't a subset, we will continue to test until exhaustion
	while(p1 != posnull && condition) 
	{
		// Any quick comparison assumes the sets are ordered

		// If the current element on the subset is smaller than the set's, we can still check for other elements on the set
		if(Recuperar(p1, L1) > Recuperar(p2, L2)) 
			p2 = Siguiente(p2, L2)
		
		// If the current element on the set is greater than the subset's, all following elements in the set are greater
		// Since all following elements in the set are greater, there is no match for this subset elmement
		// SInce there's no match for this given "subset" element, it cant' really be a subset
		else if( Recuperar(p1, L1) < Recuperar(p2, L2)
			condition = false 
		
		// Otherwise, both elements are equal, and we can still check for other elements matches on both sets
		else
		{
			p2 = Siguiente(p2, L2)
			p1 = Siguiente(p1, L1)
		}
	}

	// After the search, the condition holds true only if all of the presumed subset's elements had a match on the set
	return condition;
}