bool serSubconjunto(L1, L2){
	position p2 = Primera(L2)
	position p1 = Primera(L1)
	position preP1 = p1 
	bool condition = true
	while( p2 != posnull && condition) {
		if( Recuperar(p1, L1) > Recuperar(p2, L2) ) {
			p2 = Siguiente(p2, L2)
		
		} else if( Recuperar(p1, L1) < Recuperar(p2, L2){
			if( Recuperar(preP1, L1) == Recuperar(p2 , L2){
				p1 = Siguiente(p1, L1) 
			} else{
				condition = false
			}
		} else{
			p2 = Siguiente(p2, L2)
			p1= Siguiente(p1, L1)
		}
	}
}