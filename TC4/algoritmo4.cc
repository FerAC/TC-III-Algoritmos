/*
4. Construir un árbol completo de i niveles y k hijos por nodo a partir de la información que
contiene una Lista Indexada L, tal que L contiene las (k^i – 1) / (k-1) etiquetas del árbol. Las
etiquetas están acomodadas en L de acuerdo al orden de un recorrido por niveles de A.
*/

Tree createTree(i , k , L){
	int counter = 0
	int numChilds = 0
	int numElements =  (k^i – 1) / (k-1) 
	
	Cola queue
	Iniciar(queue)
	Tree myTree
	Iniciar(myTree)
	PonerRaiz(Recuperar(counter, L))
	counter++
	node nodeTemp = Raiz(myTree)
	
	while(counter< numElements){
		while(numChilds < k){
			AgregarHijo(nodeTemp, Recuperar(counter, L), myTree )
			counter++
			numChilds++
			Encolar(nodeTemp, queue)
		}
		numChilds = 0
		nodeTemp = Desencolar(queue) 
	}
	
	Destruir(queue)
	
	return myTree 
}