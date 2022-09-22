/*
4. Construir un árbol completo de i niveles y k hijos por nodo a partir de la información que
contiene una Lista Indexada L, tal que L contiene las (k^i – 1) / (k-1) etiquetas del árbol. Las
etiquetas están acomodadas en L de acuerdo al orden de un recorrido por niveles de A.
*/

Tree createTree(int i, int  k, ListaIndexada L){
	int counter = 0
	int numChilds = 0
	int numElements =  (k^i – 1) / (k-1) 
	
	Tree myTree
	Iniciar(myTree)
	PonerRaiz(Recuperar(counter++, L))
	node nodeTemp = Raiz(myTree)
	node nodeLeft = Raiz(myTree) 
	
	while(counter< numElements){
		while(numChilds < k){
			AgregarHijo(nodeTemp, Recuperar(counter++, L), myTree )
			numChilds++
		}
		numChilds = 0
		if(HermanoDer(nodeTemp,myTree) != null){
			nodeTemp = HermanoDer(nodeTemp, myTree)
		} else{ //Bajo un nivel
			nodeLeft = HijoMásIzq(nodeLeft, myTree)
			nodeTemp = nodeLeft
		}
	}
	return myTree
}