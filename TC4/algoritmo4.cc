/*
4. Construir un árbol completo de i niveles y k hijos por nodo a partir de la información que
contiene una Lista Indexada L, tal que L contiene las (k^i – 1) / (k-1) etiquetas del árbol. Las
etiquetas están acomodadas en L de acuerdo al orden de un recorrido por niveles de A.
*/

Tree createTree(i, k, L)
{
	int counter = 0 int numChilds = 0

		Tree myTree
		Iniciar(myTree)
			PonerRaiz(Recuperar(counter++, L))
				node nodeTemp = Raiz(myTree)

					while (numChilds < k)
	{
		AgregarHijo(nodeTemp, Recuperar(counter++, L), myTree)
			numChilds++
	}
	while (HermanoDer(nodeTemp, A))
	{
		while (numChilds < k)
		{
			AgregarHijo(nodeTemp, Recuperar(counter++, L), myTree)
				numChilds++
		}
	}
}