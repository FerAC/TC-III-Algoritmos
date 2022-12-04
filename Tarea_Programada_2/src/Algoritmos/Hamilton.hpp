#ifndef HAMILTON
#define HAMILTON
#include "Prim.hpp"

class Hamilton{
    private :
        std::map<char, Vertice> diccionario;  
        size_t mejorCosto = 999999999; //TODO: cambiar a infinito o algo asi xd 
        size_t costoActual = 0; 
        Vertice* solActual;
        Vertice* mejorSol;
        Grafo grafo; 

    public:
        Hamilton(Grafo& grafo) {
            solActual = new Vertice[grafo.NumVertices()]; 
            mejorSol= new Vertice[grafo.NumVertices()];
            solActual[0] = grafo.PrimerVertice();
            diccionario.insert(std::pair<char, Vertice>(grafo.PrimerVertice().getEtiqueta(), grafo.PrimerVertice()));
            this->grafo = grafo; 
        }

        void hamiltonBEP(size_t i) {
            //Itero posibilidades
            Vertice va = grafo.PrimerVerticeAdyacente(solActual[i]);
            const Vertice NULO;
            while (va!=NULO) {
                if (diccionario.count(va.getEtiqueta())==0) { //Factible
                    solActual[i+1] = va;
                    costoActual+= grafo.Peso(solActual[i], va);
                    diccionario.insert(std::pair<char, Vertice>(va.getEtiqueta(), va)); 
                    if (i = grafo.NumVertices()) { //Veo si es solucion
                        if (grafo.ExisteArista(va, solActual[0])) {
                            if (costoActual + grafo.Peso(va, solActual[0])<mejorCosto) //Comparo si es mejor solucion
                            {
                                mejorCosto = costoActual + grafo.Peso(va, solActual[0]);
                                mejorSol = solActual;
                            }
                        }
                    }  else{ //Recursivo
                        hamiltonBEP(i+1);
                    } 
                } 
                diccionario.erase(va.getEtiqueta());
                costoActual-= grafo.Peso(solActual[i], va); 
                va = grafo.SiguienteVerticeAdyacente(solActual[i], va); 
            }
        }

        Vertice* getSolucion() {
            return this->mejorSol; 
        }





};
#endif