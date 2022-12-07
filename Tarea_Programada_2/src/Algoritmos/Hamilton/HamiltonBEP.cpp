#include "AuxiliaresHamiltonBEP.hpp"

static void HamiltonBEPRecursivo (size_t i, Datos& datos, const Grafo& grafo) {
    //Itero posibilidades
    Vertice va = grafo.PrimerVerticeAdyacente(datos.solActual[i-2]);
    const Vertice NULO;
    while (va!=NULO) {
        if (datos.diccionario.count(va.getEtiqueta())==0) { //Factible
            datos.solActual[i-1] = va;
            datos.costoActual+= grafo.Peso(datos.solActual[i-2], va);
            datos.diccionario.insert(std::pair<char, Vertice>(va.getEtiqueta(), va)); 
            if (i == grafo.NumVertices()) { //Veo si es solucion
                if (grafo.ExisteArista(va, datos.solActual[0])) {
                    if (datos.costoActual + grafo.Peso(va, datos.solActual[0])<datos.mejorCosto) //Comparo si es mejor solucion
                    {
                        datos.mejorCosto = datos.costoActual + grafo.Peso(va, datos.solActual[0]);
                        datos.mejorSol = datos.solActual;
                    }
                }
            } else { //Recursivo
                HamiltonBEPRecursivo(i+1, datos, grafo);
            } 
        }
        datos.diccionario.erase(va.getEtiqueta());
        datos.costoActual-= grafo.Peso(datos.solActual[i-2], va); 
        va = grafo.SiguienteVerticeAdyacente(datos.solActual[i-2], va); 
    }
}

namespace Algoritmos
{
    std::vector<Vertice> HamiltonBEP (const Grafo& grafo) {
        Datos datos(grafo);
        HamiltonBEPRecursivo(2, datos, grafo);

        return datos.mejorSol;
    }  
}
