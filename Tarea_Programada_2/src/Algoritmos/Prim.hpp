#include "Controlador.hpp"
#include <list>
#include <map> 
#include <iostream> 
#ifndef HOLA4
#define HOLA4

class Prim{
    public:
        Prim();
        Grafo prim(Grafo grafo){
            //int a = grafo.NumVertices(); 
            Tripleta * lista; 
            lista[grafo.NumVertices()]; 
            //Inicializacion
            Vertice vInicial;
            vInicial = grafo.PrimerVertice();
            const Vertice NULO;
            Vertice iterador;
            size_t i =0;
            for(iterador = grafo.PrimerVertice(); iterador != NULO; iterador = grafo.SiguienteVertice(iterador)){
                int peso = 0; 
                if(grafo.ExisteArista(vInicial, iterador)){
                    peso = grafo.Peso(vInicial, iterador);
                }
                Tripleta tripleta(iterador, peso,  vInicial);
                lista[i] = tripleta; 
            }

            //Primer pivote
            std::map<char, Vertice> mapaVerticesPivoteados; 
            for(size_t j = 0; j<grafo.NumVertices()-1; j++){
                Vertice pivote = encontrarPivote(lista, mapaVerticesPivoteados, grafo);
                for (size_t i = 0; i < grafo.NumVertices()-1; i++)
                {
                    if (mapaVerticesPivoteados.count(lista[i].getVertice().getEtiqueta())<=0)
                    {
                        //Posicion de lista no pivoteada
                        
                        if(grafo.ExisteArista(pivote, lista[i].getVertice()) == 1){
                            if(lista[i].getPeso()!=0){
                                if(grafo.ExisteArista(pivote, lista[i].getVertice())){
                                    if(grafo.Peso(lista[i].getVertice(), lista[i].getVerticeAnterior()) < grafo.Peso(lista[i].getVertice(), pivote)){
                                    lista[i].setVerticeAnterior(pivote); 
                                    }
                                }
                            } else{   
                                lista[i].setVerticeAnterior(pivote); 
                            }
                        }
                    }
                }
            }
            Grafo retornado;
            for(size_t i =0 ; i< grafo.NumVertices()-1; i++){
                Vertice a = lista[i].getVertice();
                Vertice b = lista[i].getVerticeAnterior();
                grafo.AgregarArista(a, b, lista[i].getPeso());
            }
        }

        Vertice encontrarPivote(Tripleta * lista, std::map<char, Vertice> mapaVerticesVisitados, Grafo grafo){
            Vertice pivote; 
            int menorPeso = 0; 
            size_t indiceMenor; 
            for (size_t i = 0; i < grafo.NumVertices()-1  ; i++)
            {
                //Verifico que no haya sido pivoteado antes
                if(mapaVerticesVisitados.empty()){ //Caso trivial, esta vacio
                    if(lista[i].getPeso() != 0 && lista[i].getPeso()<menorPeso){
                        indiceMenor = i; 
                    }
                } else{
                    if (mapaVerticesVisitados.count(lista[i].getVertice().getEtiqueta())>0)
                    {
                        //Si lo encontro, sigo adelante

                    } else{
                        if(lista[i].getPeso() != 0 && lista[i].getPeso()<menorPeso){
                        indiceMenor = i; 
                        }
                    }    
                }
            }
            char a = lista[indiceMenor].getVertice().getEtiqueta(); 
            Vertice b = lista[indiceMenor].getVertice();
            mapaVerticesVisitados.insert(std::pair<char, Vertice>(a,b));
            return b;
        }

};
class Tripleta
{
private:
    Vertice verticeAnterior;
    int peso;
    Vertice vertice; 
public:
    Tripleta(Vertice& vertice, int peso, Vertice& verticeAnterior){
        this->vertice = vertice;
        this->peso = peso;
        this->verticeAnterior = verticeAnterior; 
    }
    ~Tripleta(){}
    Vertice getVertice(){
        return vertice;
    }
    Vertice getVerticeAnterior(){
        return verticeAnterior;
    }
    int getPeso(){
        return peso;
    }
    void setVertice(Vertice& vertice){
        this->vertice = vertice;
    }
    void setVerticeAnterior(Vertice& vertice){
        this->verticeAnterior = vertice;
    }
    void setPeso(int nuevo){
        this->peso = nuevo; 
    }
};

#endif