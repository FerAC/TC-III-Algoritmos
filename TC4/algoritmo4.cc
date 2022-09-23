/* EJERCICIO 4
 * Construir un árbol completo de i niveles y k hijos por nodo a partir de la información que
   contiene una Lista Indexada L, tal que L contiene las (k^i – 1) / (k-1) etiquetas del árbol. 
 * Las etiquetas están acomodadas en L de acuerdo al orden de un recorrido por niveles de A.
 */
Tree createTree(int i, int k , ListaIndexada L) {

	// The tree is assumed to be empty until noted otherwise
	Arbol myTree
	Iniciar(myTree)

	// First condition: At least one level and one child per level
	if (i > 0 && k > 0) {
		// Since the tree has at least one level, and at least one child per level, there must be a root
		PonerRaiz(Recuperar(0, L))

		// Second condition: At least two levels
		if (i > 1) {
			// On top of the first condition, since the tree has at least two levels, we must consider if it's children are parents as well
			Cola parentNodesQueue
			Iniciar(parentNodesQueue)
			Encolar(Raiz(myTree), parentNodesQueue)

			int numNodesTotal =  (k^i – 1) / (k-1) // The total amount of nodes to add into the tree after it's fully constructed
			int numNodesLastLevel = k^(i - 1) // The amount of nodes to be expected on the last level of the tree
			int numNodesAdded = 1 // The current amount of nodes added so far. The root has been added, therefore it's 1

			// We'll add children nodes until before the last level. There's no use in adding children on the last level
			while (numNodesTotal - numNodesAdded > numNodesLastLevel) {
				Node currentParent = Desencolar(travelQueue) // The current parent to add children to

				// The amount of children per parent is already known. We can produce as many.
				for (int numChildAdded = 0, numChildAdded < k, ++numChildAdded) {
					// It is a precondition of this function that we're guaranteed a child on the list for every possible node on the tree
					Nodo newChild = AgregarHijo(currentParent, Recuperar(numNodesAdded, L), myTree)
					++numNodesAdded

					// Whenever we produce a new child, it can be considered to be a new parent worth visiting to later on.
					// However, this consideration may only be made if we haven't reached the last level of the tree
					if (numNodesTotal - numNodesAdded > numNodesLastLevel)
						Encolar(newChild, parentNodesQueue)
				}
			}
			
			// We're done visting parents. We can free the memory allocated by the travel queue
			Destruir(travelQueue)
		}
	}
	
	// Our tree is done! We can return it safely by this point
	return myTree 
}
