/* Ejercio #5A - Lista Indexada
 * 
 * Eliminar los elementos repetidos de una lista. 
 * Ejemplo: si L = 7, 1, 7, 9, 1, 7, 3 entonces L deberá ser igual a 7, 1, 9, 3
 */

void 5A_Remove_Duplicates(Lista i, Elemento e)
{
    // Get the list size for list end
    int size = NumElem(i);

    // Iterative linear, nested search
    // Space complexity of O(1) yet time complexity of O(n^2)
    for(Index iter_a = 0, iter_a < size, iter_a = iter_a + 1)
    {
        // Element to find matches for
        Elemento a = Recuperar(iter_a, i)

        // Linear search to find duplicates
        // Problem has been reduced to a compariso of n-k elements
        for(Index iter_b = a + 1, iter_b < size, iter_b = iter_a + 1)
        {
            Elemento b = Recuperar(iter_b, i)

            if(a == b)
            {
                Borrar(iter_b, i)
                iter_b = iter_b - 1
            }
        }
    }

    // We're done :)
    return
}
