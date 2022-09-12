Lista union(L1, L2){
	posicion p1 = Primera(L1);
	posicion p2 = Primera(L2);
	Lista L3;
	Iniciar(L3);
	int tamanoL3 = numElem(L1) + numElem(L2);
	int tamanoL1 = numElem(L1);
	int tamanoL2 = numElem(L2);
	int contador = 0;
	
	while( contador < tamanoL3) {
		if(tamanoL1==0){
			AgregarAlFinal(Recuperar( p2, L1) , L3);
		} else if( tamanoL2== 0){
			AgregarAlFinal(Recuperar( p1, L1) , L3);
		} 
		if( tamanoL1!=0 && tamanoL2!=0){
			if( Recuperar( p1, L1)  <= Recuperar( p2, L2)  ){
				AgregarAlFinal(Recuperar( p1, L1) , L3);
				--tamanoL1;
				p1 = Siguiente(p1, L1);
				
			} else{
				AgregarAlFinal(Recuperar( p2, L1) , L3);
				p2 = Siguiente(p2, L2);
				--tamanoL2; 
			}
			++contador; 
		}
		
}