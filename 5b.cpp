/* ENUNCIADO
 * Insertar en una lista ordenada un nuevo elemento de tal manera que la lista resultado
 * quede ordenada.
 * 
 * Lista Indexada
 * Ejemplo: Si L = 7, 1, 7, 9, 1, 7, 3
 * Entonces L deberá ser igual a 7, 1, 9, 3
*/

void Insercion_Ordenada(Lista i, Elemento e)
{
    int tamano = NumElem(i);

    if (tamano == 0)
    {
        Insertar(0, e, i)
        return;
    }
    else if (tamano == 1)
    {
        Insertar(1, e, i)
        return;
    }

    // Set-up edges for binary search
    int index_start = 0;
    int index_end = tamano - 1;

    // Set up search index (middle) and comparison element
    int index_mid = (index_end + index_start) / 2;
    Elemento f = Recuperar(index_mid, i);

    // Iterative binary search
    // Space complexity of O(1) yet time complexity of O(log(n))
    while(index_mid != index_start)
    {
        // Update edges
        if(e < f) // Go backwards
            index_end = index_mid;
        else // Go forward
            index_start = index_mid;

        // Update middle
        index_mid = (index_end + index_start) / 2;

        // Update lower-edge element
        f = Recuperar(index_mid, i);
    }

    // Get upper-edge element
    Elemento g = Recuperar(index_end, i);

    // Problem has been reduced to a comparison of two elements
    if (e < g) // Goes behind last element
    {
        if (e < f) // Goes behind the previous-to-last element
            Insertar(index_start, e, i);    
        else // Goes directly behind the last element
            Insertar(index_end, e, i);    
    }
    else // Goes after last element
        Insertar(index_end + 1, e, i);

    return;
}