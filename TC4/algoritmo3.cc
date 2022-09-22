/*
3. Averiguar cuántos nodos hay en el i-ésimo nivel. Debe hacer un recorrido en pre orden.
*/

// when we first call the function, quantityNodes must be in 0

int quantityNodesInLevel(Arbol tree, node N, int level, quantityNodes) {
	int quantityNodes = 0
	if(level == 0) {
		node child = N.HijoMásIzq()
		while(child != null) {
			++ quantityNodes
			child = child.hermanoDer()
		}
		return quantityNodes
	} else {
		
		node child = N.HijoMásIzq()
		while(child != null) {
			quantityNodes = quantityNodesInLevel(child, level-1, quantityNodes)
			child = child.hermanoDer()
		}
		return quantityNodes
	}
}