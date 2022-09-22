/* EJERCICIO 1
 * Eliminar todo el subárbol que se genera a partir de un nodo n. Debe hacer un recorrido
   por niveles. 

 * Se sugiere que en lugar de usar un modelo Cola, use un modelo Lista Indexada. 
    
 * Recuerde que el operador básico de borrado requiere que el nodo sea una hoja.
*/

void deleteSubTree(Arbol tree, Nodo subroot) {	// using binary tree level order traversal 

    // We'll traverse the nodes each level using a queue
    // Each time we visit a node, we'll add its' children to the queue
    // The queue is filled with a node's children after we visited it
    // Then, after all of a node's children have been added, we take it out the queue
    Cola travelQueue
    Iniciar(travelQueue)

    // We'll delete the nodes using a stack
    // Each time we visit a node, we'll add it onto the stack
    // The stack is filled on the inverse order we added the nodes
    // Then, after all nodes were added, we delete them in the inverse order we visited them
    Lista deletionStack
    Iniciar(deletionStack)

    // The tree traversion begins on the first node of the subtree: its' root
    Encolar(subroot, travelQueue)

    // We can now begin traversion
    while(NumElem(travelQueue) > 0) {

        // Let's extract the last node on the travel queue
        Nodo visitedNode = Desencolar(travelQueue)

        // The element has been visited, let's add it to the top of the stack
        // We'll always take 0 as the top of the stack
        Insertar(0 , visitedNode, deletionStack)

        // Let's consider it's children for future travel
        for(Nodo visitedChildren = HijoMasIzq(visitedNode, tree), visitedChildren != NULL, visitedChildren = HermanoDer(visitedChildren)) {
            Encolar(visitedChildren, travelQueue)
        }

        // All is done for this iteration:
        // a) The children will always be visited after their parent => parent -> children
        // b) The siblings will always be visited after the first child => first child -> sibling
        // c) The cousins will also always be visited after the children => children -> cousins
        // d) Due to a, b, and c, the order is as follows: parent -> first child -> siblings -> cousins
    }

    // We no longer need the travel queue. Let's free its memory
    Destruir(travelQueue)

    // The whole subtree has been visited, and its' nodes placed on the stack in the inverse order they have been visited
    // We can now delete the visited nodes on the order they've been placed on within the stack
    while(NumElemn(deletionStack) > 0) {
        
        // It is guaranteed that the top element of the stack is a leaf
        Nodo currentLeaf = Recuperar(0, deletionStack)

        // It is guaranteed that we'll first delete the last child, and then its siblings
        // After deleting all siblings, it is guaranteed that its corresponding parent becomes a leaf
        // Therefore, deletion is in this reverse order is always face
        EliminarHoja(currentLeaf, tree)

        // The last leaf of the tree on the stack has been dealt (deleted off of the tree)
        // Let's take it out of the stack and carry on with the next leaf on the following iteration
        Borrar(0, deletionStack)
    }

    // We no longer need the deletion stack. Let's free its memory
    Destruir(deletionStack)

    // All is done:
    // a) The whole tree has been visited
    // b) Each node was visited only once
    // c) Each visited node was deleted in inverse order of visit
    // d) The auxiliary data structures were freed after use
}

