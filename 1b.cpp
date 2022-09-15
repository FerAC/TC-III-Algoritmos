/* Ejercicio #1A - Lista Posicionada
 * 
 * Crear una lista L3, ordenada, que contenga los elementos que pertenecen a C1 ∪ C2
 */

List 1B_Union(L1, L2){
	position p1 = Primera(L1)
	position p2 = Primera(L2)

	List L3
	Iniciar(L3)
	
	while( p1 != nullpos || p2 != nullpos) {
		if(p1 == nullpos)
		{
			AgregarAlFinal(Recuperar( p2, L2) , L3)
			p2 = Siguiente(p2, L2);
		} 
		else if(p2 == nullpos)
		{
			AgregarAlFinal(Recuperar( p1, L1) , L3)
			p1 = Siguiente(p1, L1);
		} 
		else 
		{
			if( Recuperar( p1, L1)  < Recuperar( p2, L2)  ){
				AgregarAlFinal(Recuperar( p1, L1) , L3)
				p1 = Siguiente(p1, L1)
				
			} else if Recuperar( p1, L1)  > Recuperar( p2, L2) {
				AgregarAlFinal(Recuperar( p2, L2) , L3) 
				p2 = Siguiente(p2, L2)
			} else{
				AgregarAlFinal(Recuperar( p1, L1) , L3)
				p1 = Siguiente(p1, L1)
				p2 = Siguiente(p2, L2)
			}
		}

	return L3
}