// hacer unrecorrido en profundidad primero y numerar a los vertices de un grafo dirigido sin aristas paralelas y 
// sin lazos de acuerdo al orden de devolucion de la llamada recursiva.
// para realizar dicha numericacion utilice una Lsita Indexada, tal que L(i) contenga al i-esimo vertice que hace
// devolucion de llamada recursiva


// para poder saber si un vertice ya fue visitado, tenemos que usar una estructura de datos addicional, vamos a usar
// un diccionario, el diccionario es global

// el algortimo devuelve el arregloIndexado donde cada indice del arreglo representa el valor numerico dado al
// vertice de este mismo indice

Diccionario visitados
ListaIndexada numeracion

arregloIndexado recorridoProfundidadPrimero(Grafo grafo){
	visitados = diccionario.Iniciar() 
	numeracion = listaIndexada.Iniciar() 

	Vertic verticeActual = primerVertice(grafo)

	mientras(verticeActual != verticeNulo){
		if(!existe(verticeActual, visitados)){
			RPPrecursivo(grafo, primerVertice(grafo))
		}
		verticeActual = siguienteVertice(verticeActual, grafo)
	}

	destruir(visitados)
	
	return visitados
}

void RPPrecursivo(Grafo grafo, Vertice vertice){
	
	if(!existe(vertice, visitados){
		visitados.agregar(vertice) // se agrega el vertice a la lista de vertice visitados
		Vertice adyacente = primerVerticeAdyacente(vertice, grafo)
	
		// para cada vertice adyacente de vertice
		mientras ( adyacente != verticeNulo) {
			// si adyacente no existe en la lista de los vertices visitados, entonces llamar funcion
			si (!existe(adyacente, visitados)){
				RPPrecursivo(grafo, adyacente)
				numeracion.agregarAlFinal(adyacente)
			}
			adyacente = siguienteVerticeAdyacente(vertice, grafo) 	
		}
		numeracion.agregarAlFinal(vertice)
	}
}
