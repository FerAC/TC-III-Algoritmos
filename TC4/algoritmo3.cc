/* EJERCICIO 3
 * Averiguar cuántos nodos hay en el i-ésimo nivel. 
 * Debe hacer un recorrido en pre orden.
 */

int quantityNodesInLevel(Arbol tree, Node subroot, int level) {
	
	// Base case: Level 0. The subroot. Its the only node with its own level
	if (level == 0) {
		return 1
	}
	// Base case: Level 1. The subroot's children. They're the only one on this level (no cousins)
	else if(level == 1) {

		int childrenNodes = 0

		Node child = HijoMásIzq(subroot, tree)
		while(child != null) { // The sum of all ocurrences of children
			++ childrenNodes
			child = hermanoDer(child, tree)
		}

		return childrenNodes
	}  // Recursive case: Level > 2. The subroot's descendants. We need to consider the children' subtrees quantiies of nodes
	else {
		
		int quantityNodes = 0

		Node child = HijoMásIzq(subroot, tree)
		while(child != null) { // The sum of all children's subtrees quantities of nodes, with adjusted level (-1)
			quantityNodes += quantityNodesInLevel(child, level-1)
			child = hermanoDer(child, tree)
		}

		return quantityNodes
	}
}