/* Ejercio #4A - Lista Posicionada
 * 
 * Ordenar una lista usando el algoritmo Burbuja
 */

void 4A_Bubble_Sort(L)
{
	bool must_continue = true

	while(must_continue == true) 
	{
		must_continue = false

		for (Position element2 = Primera(L), element2 != NULL, element2 = Siguiente(element2, L)) 
		{
			if (Recuperar(element2, L) > Recuperar(Siguiente(element2, L)) 
			{
				Element temporal = Recuperar(element2, L)
				Modificar(element2, Recuperar(Siguiente(element2, L), L)
				Modificar(Siguiente(element2, L), temporal, L)				

				must_continue = true
			}
		}
	}

	return
}