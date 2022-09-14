/* Ejercio #4B - Lista Posicionada
 * 
 * Averiguar si la lista es simétrica
 */

bool serSimetrica(L1){
	int tamano = numElem(L1)
	posicion p1 = Primera(L1)
	posicion p2 = Primera(L1)
	bool bandera = true
	while(tamano>1 && bandera ) {
		for(int contador2 = 0; contador2< tamano ; contador++){
			p2 = Siguiente(ultima , L1)
		}
		if(Recuperar(p1, L1) == Recuperar(p2, L1){
			p1 = Siguiente(p1 , L1) 
			p2 = Primera(L1)
			-- tamano
		} else{
			bandera = false 
		}
	}
	
	
}
	
}