/*
3. Averiguar cuántos nodos hay en el i-ésimo nivel. Debe hacer un recorrido en pre orden.
*/

// when we first call the function, quantityNodes must be in 0

int quantityNodesInLevel(Arbol tree, node N, int level, quantityNodes) {
	int quantityNodes = 0
	if(level == 0) {
		node child = HijoMásIzq(N, tree)
		while(child != null) {
			++ quantityNodes
			child = hermanoDer(child, tree)
		}
		return quantityNodes
	} else {
		
		node child = HijoMásIzq(N, tree)
		while(child != null) {
			quantityNodes = quantityNodesInLevel(child, level-1, quantityNodes)
			child = hermanoDer(child, tree)
		}
		return quantityNodes
	}
}