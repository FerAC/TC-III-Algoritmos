/*
ColorearVértice(V)
{
    Para color C = 1 hasta N haga {
        Si el conjunto de vértices adyacentes a V y el conjunto de vértices coloreados de
        color C son disjuntos entonces {
            Pinte a V de color C (agrega al conjunto correspondiente)
            Si el color C se usa por primera vez entonces {
                Agréguelo al conjunto correspondiente
            }
            Si V = N (acaba de pintar el último vértice) entonces {
                Si la cardinalidad del conjunto de colores usados es menor que el menor
                número de colores usado en la mejor solución hasta ese momento encontrada
                entonces {
                    Actualice la mejor solución encontrada
                }
            }
            Sino {
                ColorearVértice(V+1)
            }
            Quítele a V el color C (sáquelo del conjunto correspondiente) y si el color C se
            estaba usando por primera vez entonces sáquelo del conjunto de colores usados
        }
    }
}
*/