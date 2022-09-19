/* Ejercio #4B - Lista Posicionada
 * 
 * Averiguar si la lista es simétrica
 */

bool 4B_Is_Symmetric(L1)
{
	int size = NumElem(L1)

	posicion p1 = Primera(L1)
	posicion p2 = Primera(L1)
	bool flag = true

	while(size>1 && flag )
	{
		for(int counter = 0, counter < size, counter++)
			p2 = Siguiente(p2 , L1)

		if(Recuperar(p1, L1) == Recuperar(p2, L1)
		{
			p1 = Siguiente(p1, L1) 
			p2 = Primera(L1)
			--size
		} 
		else
			flag = false 
	}
	
	return flag
}