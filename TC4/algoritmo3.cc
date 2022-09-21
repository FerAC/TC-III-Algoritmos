/*
3. Averiguar cuántos nodos hay en el i-ésimo nivel. Debe hacer un recorrido en pre orden.
*/

int cantityNodes = 0

void cantityNodesInLevel(node N, int level) {
	if(level == 0) {
		node child = N.HijoMásIzq()
		while(child != null) {
			++ cantityNodes
			child = child.hermanoDer()
		}
		return
	} else {
		node child = N.HijoMásIzq()
		while(child != null) {
			cantityNodesInLevel(child, level-1)
			child = child.hermanoDer()
		}
	}
}