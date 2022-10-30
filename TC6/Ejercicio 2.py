/* Aislar un vértice de un grafo dirigido.
-> Sin aristas paralelas y sin lazos. 
-> No puede usar el operador ExisteArista
*/

void AislarVertice(Grafo grafo, Vertice verticeVictima)
{
    // Realizaremos un recorrido por anchura
    // Para ello necesitaremos una cola de recorridos...
	Cola colaPorRecorrer
    Iniciar(colaPorRecorrer)

	// ...y un Diccionario de visitados
	Diccionario yaRecorridos
	Iniciar(yaRecorridos)

	// Comenzaremos recorridos en cada vértice del grafo sin visitar todavía
	// Esto nos permite cubrir islas de vértices aislados, en caso de que el grafo no sea totalmente conexo
	For (Vertice verticeIsla = PrimerVertice(grafo)
		, verticeIsla != NULL
		, verticeIsla = SiguienteVertice(verticeIsla, grafo))
	{
		// Si ya hemos recorrido antes este vertice de partida, entonces ya recorrimos a todos sus adyacentes
		// En ese caso, no lo consideramos
		If (Pertence(verticeIsla, yaRecorridos))
			Saltar Iteracion
		
		// Si no lo hemos recorrido antes, nos encargaremos de recorrer todos sus adyacentes
		// Esto contempla a los adyacentes de sus adyacentes, y así (recorreremos toda la isla)
		Encolar(verticeIsla, colaPorRecorrer)
		While (!Vacio(colaPorRecorrer))
		{
			// Para cada iteracion del recorrido por anchura, consideraremos un vertice de partida
			Vertice verticePartida = Desencolar(colaPorRecorrer)

			// Si este vertice de la isla ya fue recorrido antes, entonces no es necesario recorrerlo de nuevo
			// En ese caso, no lo consideramos
			If (Pertence(verticePartida, yaRecorridos))
				Saltar Iteracion

			// Sino, podemos marcarlo como recorrido y continuar
			Agregar(verticePartida, yaRecorridos)

			// Encolaremos a cada uno de los vertices adyacentes al vertice de partida...
			For (Vertice verticeAdyacente = PrimerVerticeAdyacente(verticePartida, grafo)
				, verticeAdyacente != NULL
				, verticeAdyacente = SiguienteVerticeAdyacente(verticePartida, verticePartida, grafo))
			{
				// Si este vértice adyacente es el que queremos aislar, borraremos la arista entre
				// el vertice de partida del y este vértice adyacente
				// Esto se hace inclusive si ya recorrimos el vértice víctima, porque podemos 
				// visitarle varias veces.
				If (verticeAdyacente == verticeVictima || verticePartida == verticeVictima)
				{
					// No importa si el vértice víctima termina siendo isla, pues visitaremos a todas las
					// islas
					BorrarArista(verticePartida, verticeAdyacente, grafo)
				
                }

				// Si este vértice adyacente ya ha sido visitado, no es necesario encolarlo
				If (Pertence(yaRecorridos, verticeAdyacente))
					Saltar Iteracion

				Encolar(verticeIsla, colaPorRecorrer)
			}
		}
	}
}
