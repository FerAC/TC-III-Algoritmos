/*
2. Averiguar cuántas hojas tiene un árbol. Debe hacer un recorrido en pre orden. 
Se sugiere que el contador de hojas sea una variable global.
*/

int quantityLeaves = 0	// Will be used as a global counter to keep track of the cantity of leaves in the tree

void quantityLeavesInTree(Arbol tree, Nodo subroot) {
	// Base case: The subroot IS the leaf. Add 1 to the leaf counter
	if(HijoMásIzq(subroot, tree) == null) {
		++quantityLeaves

		return
	}
	// Recursive case: The subroot is NOT a leaf. We must consider the sum of the children's leafs.
	else {
		Nodo child = HijoMásIzq(subroot, tree)
		while(child != null) {
			quantityLeavesInTree(child)
			child = hermanoDer(child, tree)
		}

		return
	}
}
