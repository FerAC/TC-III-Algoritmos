/*
2. Averiguar cuántas hojas tiene un árbol. Debe hacer un recorrido en pre orden. 
Se sugiere que el contador de hojas sea una variable global.
*/

int cantityLeaves = 0	// will be used as a counter to keep track of the cantity of leaves in the tree

void cantityLeavesInTree(Node N) {
	if(N.HijoMásIzq() == null) {
		++cantityLeaves
		return
	} else {
		Node child = N.HijoMásIzq()
		while(child != null) {
			cantityLeavesInTree(child)
			child = child.hermanoDer()
		}
		return
	}
}





// recursive
//go down to the left until finding leaves, if right brother is no leaves, then go down, else increment counter and go up and down
// if leaves icnrement, else 