// pseudolenguaje
// Invertir la dirección de todas las aristas de un grafo dirigido, con pesos, 
// sin aristas paralelas y sin lazo

void invertirAristas(Grafo grafo){

	Pila pila = Pila.Iniciar()
	Vertice verticePartida = PrimerVertice(grafo)
	// pasamos por cada vertice del grafo n cantidad de veces, n siendo la cantidad de aristas que sale del vertice
	mientras(verticePartida != verticeNulo){
		Vertice verticeLLegada = primerVerticeAdyacente(verticePartida, grafo)
		// pasamos por cada vertice connectado a verticeLlegada
		mientras(verticeLlegada != verticeNulo){
			pila.agregar((verticeLlegada, verticePartida, peso(verticePartida, verticeLlegada, grafo)))
			borrarArista(verticePartida, verticeLlegada, grafo)
			verticeLlegada = siguienteVerticeAdyacente(verticePartida, verticeLlegada, grafo)
		}
		verticePartida = siguienteVertice(verticePartida, grafo)
	}
	
	// a ese punto el grafo yo no tiene aristas, entonces podemos sacar los elementos y volver a poner las aristas en el otro sentido
	mientras (!vacia(pila)) {
		(verticePartida, verticeLlegada, pesoArista) = sacar(pila)
		agregarArista((verticePartida, verticeLlegada, pesoArista))
	}

	destruir(pila)
}
