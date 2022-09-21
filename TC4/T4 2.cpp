Tree createTree(i , k , L){
	int counter =0
	int numChilds = 0
	
	Tree myTree
	Iniciar(myTree)
	PonerRaiz(Recuperar(counter++, L))
	node nodeTemp = Raiz(myTree)
	
	while(numChilds < k){
		AgregarHijo(nodeTemp, Recuperar(counter++, L), myTree )
		numChilds++
	}
	while(HermanoDer(nodeTemp,A)){
		while(numChilds < k){
		AgregarHijo(nodeTemp, Recuperar(counter++, L), myTree )
		numChilds++
	}
	
	






}