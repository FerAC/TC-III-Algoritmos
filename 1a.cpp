bool serSubconjunto(L1, L2){
	posicion p1 = Primera(L1); 
	posicion p2 = Primera(L2);
	bool banderaProvisional = false;
	bool banderaFinal = true; 
	while(p1 && banderaFinal){ //Mientras p no apunte a null
		p2= Primera(L2)
		while(p2){
			
			if(Recuperar(p1,L1) == Recuperar(p2, L2){
				banderaProvisional = true;
			}
			p2 = Siguiente(p2,L2);
		}
		if(!banderaProvisional){
			banderaFinal = false; 
		}
		banderaProvisional = false;
		p1 = Siguiente(p1, L1);
}