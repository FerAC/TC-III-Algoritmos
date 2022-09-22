/*
3. Averiguar cuántos nodos hay en el i-ésimo nivel. Debe hacer un recorrido en pre orden.
*/

// when we first call the function, cantityNodes must be in 0

int cantityNodesInLevel(node N, int level, cantityNodes) {
	int cantityNodes = 0
	if(level == 0) {
		node child = N.HijoMásIzq()
		while(child != null) {
			++ cantityNodes
			child = child.hermanoDer()
		}
		return cantityNodes
	} else {
		
		node child = N.HijoMásIzq()
		while(child != null) {
			cantityNodes = cantityNodesInLevel(child, level-1, cantityNodes)
			child = child.hermanoDer()
		}
		return cantityNodes
	}
}