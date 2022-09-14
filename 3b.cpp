/* Ejercio #3B - Lista Posicionada
 * 
 * Crear una lista L3, no ordenada, que contenga los elementos que pertenecen a C1 ∩ C2
 */

// Function return a list
List 3B_Intersection(L1, L2) 
{
	Iniciar(L3)
	Position elementL1 = Primera(L1)
	Position elementL2 = Primera(L2)
	
	while (elementL1 != nullPos) 
	{
		while (elementL2 != nullPos) 
		{
			if (Recuperar(elementL1, L1) == Recuperar(elementL2, L2))
				AgregarAlFinal(Recuperar(element, L1), L3)
			
			elementL2 = Siguiente(elementL2, L2)
		}

		elementL1 = Siguiente(elementL1, L1)
	}
	return L3
}