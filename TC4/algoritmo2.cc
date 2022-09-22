/*
2. Averiguar cuántas hojas tiene un árbol. Debe hacer un recorrido en pre orden. 
Se sugiere que el contador de hojas sea una variable global.
*/

int quantityLeaves = 0	// will be used as a counter to keep track of the cantity of leaves in the tree

void quantityLeavesInTree(Node N) {
	if(N.HijoMásIzq() == null) {
		++quantityLeaves
		return
	} else {
		Node child = N.HijoMásIzq()
		while(child != null) {
			quantityLeavesInTree(child)
			child = child.hermanoDer()
		}
		return
	}
}





// recursive
//go down to the left until finding leaves, if right brother is no leaves, then go down, else increment counter and go up and down
// if leaves icnrement, else 