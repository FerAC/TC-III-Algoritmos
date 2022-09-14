/* ENUNCIADO
 * Insertar en una lista ordenada un nuevo elemento de tal manera que la lista resultado
 * quede ordenada.
 * 
 * Lista Indexada
 * Ejemplo: Si L = 1, 7, 8, 9, 9, 10, 11 y E = 6
 * Entonces L deberá ser igual a 1, 6, 7, 8, 9, 9, 10, 11
 */

void Sorted_Insertion(Lista i, Element e)
{
    // Get the list size for edge partitioning
    int size = NumElem(i)

    // Base case of no elements
    if(size == 0)
    {
        Insertar(0, e, i)
        return
    } // Base case of 1 element
    else if(tamano == 1)
    {
        if(e < Recuperar(1, i)) // Goes before existing element
            Insertar(0, e, i)
        else 
            Insertar(1, e, i) // Goes after existing element
        return
    }

    // Set-up edges for binary search
    int index_start = 0
    int index_end = size - 1

    // Set up search index (middle) and comparison element
    int index_mid = (index_end + index_start) / 2
    Element f = Recuperar(index_mid, i)

    // Iterative binary search
    // Space complexity of O(1) yet time complexity of O(log(n))
    while(index_mid != index_start)
    {
        // Update edges
        if(e < f) // Go backwards
            index_end = index_mid
        else // Go forward
            index_start = index_mid

        // Update middle
        index_mid = (index_end + index_start) / 2}

        // Update comparison element
        f = Recuperar(index_mid, i)
    }

    // Get upper-edge element
    Element g = Recuperar(index_end, i)

    // Problem has been reduced to a comparison of two elements
    if (e < g) // Goes behind last element
    {
        if (e < f) // Goes behind the previous-to-last element
            Insertar(index_start, e, i)
        else // Goes directly behind the last element
            Insertar(index_end, e, i)
    }
    else // Goes after last element
        Insertar(index_end + 1, e, i)

    // We're done :)
    return
}
