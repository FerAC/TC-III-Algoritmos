/* EJERCICIO 4
 * Construir un árbol completo de i niveles y k hijos por nodo a partir de la información que
   contiene una Lista Indexada L, tal que L contiene las (k^i – 1) / (k-1) etiquetas del árbol. 
 * Las etiquetas están acomodadas en L de acuerdo al orden de un recorrido por niveles de A.
 */

Tree createTree(int i, int  k, ListaIndexada L) {
	int numElements =  (k^i – 1) / (k-1) // The total amount of elements to place
	int counter = 0 // The count of elements placed so far
	int numChilds = 0 // The current amount of children placed relative the current parent
	
	Tree myTree // The tree to place the elements into
	Iniciar(myTree)

	PonerRaiz(Recuperar(counter, L), myTree) // Place the first element
	counter++ // Root has been placed, let's take that into account on the total placed count

	node nodeTemp = Raiz(myTree) // The current parent node to insert at (the subroot)
	node nodeLeft = Raiz(myTree) // The current leftmost parent (the subroot as well, at the start)
	
	// Let's insert elements while we still got elements to place
	while(counter < numElements) {
		// Let's insert the children of the current parent
		while(numChilds < k) {
			AgregarHijo(nodeTemp, Recuperar(counter, L), myTree)
			counter++
			numChilds++
		}
		numChilds = 0 // Reset the children count for the next children insertion

		// Let's set the parent as the brother of the current parent
		if(HermanoDer(nodeTemp,myTree) != null){
			nodeTemp = HermanoDer(nodeTemp, myTree)
		} 
		// If there's no brother to the current parent, we must descend to the next level and find a new parent
		else {
			// The new leftmost parent will become the leftmost child of the leftmost parent
			nodeLeft = HijoMásIzq(nodeLeft, myTree)

			// The new parent will become the current (newly determined as of now) leftmost parent
			nodeTemp = nodeLeft
		}
	}
	return myTree
}