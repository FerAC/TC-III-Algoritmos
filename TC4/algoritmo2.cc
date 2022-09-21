/*
2. Averiguar cuántas hojas tiene un árbol. Debe hacer un recorrido en pre orden. Se
sugiere que el contador de hojas sea una variable global.
*/

global int cantityLeaves = 0;	// will be used 
global Node recursiv

void cantityLeaves(node N) {
	if(N.HijoMásIzq() == null) {
		++cantityLeaves
		return
	} else {
		node child = N.HijoMásIzq()
		while(child != null) {
			cantityLeaves(child)
			child = child.hermanoDer()
		}
	}
}





// recursive
//go down to the left until finding leaves, if right brother is no leaves, then go down, else increment counter and go up and down
// if leaves icnrement, else 