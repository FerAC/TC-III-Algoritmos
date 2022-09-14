Lista union(L1, L2){
	position p1 = Primera(L1)
	position p2 = Primera(L2)
	List L3
	Iniciar(L3)
	int sizeL3 = numElem(L1) + numElem(L2)
	int sizeL1 = numElem(L1)
	int sizeL2 = numElem(L2)
	int cntr = 0
	
	while( cntr < sizeL3) {
		if(sizeL1==0){
			AgregarAlFinal(Recuperar( p2, L1) , L3)
		} else if( sizeL2== 0){
			AgregarAlFinal(Recuperar( p1, L1) , L3)
		} 
		if( sizeL1!=0 && sizeL2!=0){
			if( Recuperar( p1, L1)  <= Recuperar( p2, L2)  ){
				AgregarAlFinal(Recuperar( p1, L1) , L3)
				--sizeL1;
				p1 = Siguiente(p1, L1)
				
			} else{
				AgregarAlFinal(Recuperar( p2, L1) , L3)
				p2 = Siguiente(p2, L2)
				--sizeL2 
			}
			++cntr
		}
		
}