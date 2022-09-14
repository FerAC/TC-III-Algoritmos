/* Ejercio #4A - Lista Posicionada
 * 
 * Ordenar una lista usando el algoritmo Burbuja
 */

void 3a_Intersection(L)
{
	
	for (position element1 = Primera(L); element1 != NULL; element1 = Siguiente(element1, L) ) 
	{
		for ( position element2 = Primera(L); element2 != NULL; element2 = Siguiente(element2, L) ) 
		{
			if ( Recuperar(element2, L) > Recuperar(Siguiente(element2, L)) 
			{
				element temporal = Recuperar(element2, L)
				Modificar( element2, Recuperar(element2+1, L), L)
				Modificar( element2+1, temporal, L)				
			}		
		}
	}
	
	return L
}