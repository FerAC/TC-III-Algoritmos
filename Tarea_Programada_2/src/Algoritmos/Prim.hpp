#include "Controlador.hpp"
#include <list>
#include <map> 
#include <iostream> 
#ifndef HOLA4
#define HOLA4

class Prim{
    public:
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
        Prim();
        static Grafo prim(Grafo& grafo){
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
                        Vertice z = lista[i].getVertice();
                        if(grafo.ExisteArista(pivote, z ) == 1){
                            if(lista[i].getPeso()!=0){
                                Vertice a = lista[i].getVertice();
                                if(grafo.ExisteArista(pivote, a)){
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
            return retornado;
        }

        static Vertice encontrarPivote(Tripleta * lista, std::map<char, Vertice> mapaVerticesVisitados, Grafo grafo){
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

        static int ** Floyd(Grafo grafo){
            std::cout<< "Entre floyd" << std::endl;
            const Vertice NULO;
            Vertice listaVertices [grafo.NumVertices()]; 
            size_t i =0;
            size_t iteradorPivotes =0 ;

            Vertice vertice; 
            for(vertice = grafo.PrimerVertice(); vertice!=NULO; vertice = grafo.SiguienteVertice(vertice)){
                std::cout << "i, primer paso" << i << std::endl;
                listaVertices[i] = vertice; 
                i++; 
            }
            
            //Mostrar conexiones
            /*
            std::cout<< "Termino lista" << std::endl;
            for (size_t i = 0; i < grafo.NumVertices(); i++)
            {   
                std::cout << i << endl;
                grafo.ImprimirConexiones(listaVertices[i]); 
            }
            */
            
            //Primer paso de inicializacion, ya tengo la lista de vertices
            std::cout<< "Primer paso se logro" << std::endl;
            int numVertices = grafo.NumVertices();
            std::cout<< "A" << std::endl;
            std::cout<< "NUM VERTICES " << grafo.NumVertices() << std::endl;
            int matrizCostos[numVertices][numVertices]; 
            for(int i =0; i<grafo.NumVertices(); i++){
                std::cout << "I " << i << std::endl;
                for (int j = 0; j < grafo.NumVertices(); j++)
                {
                    std::cout << "J " << j << std::endl;
                    if(i!=j){
                        if(grafo.ExisteArista(listaVertices[i], listaVertices[j])){
                            std::cout << "Voy a acceder " << std::endl;
                            std::cout<< "Vertice 1 :" << listaVertices[i].getEtiqueta()<< std::endl;
                            std::cout<< "Vertice 2 :" << listaVertices[j].getEtiqueta()<< std::endl;
                            std::cout<< "Peso  :" << grafo.Peso(listaVertices[i], listaVertices[j]) << std::endl;
                            matrizCostos[i][j] = grafo.Peso(listaVertices[i], listaVertices[j]); 
                        } else{
                            matrizCostos[i][j] = 4;
                        }
                    } else{
                        std::cout<< "SON IGUALES " << std::endl;
                    }
                }
            }
            std::cout<< "Segundo paso se logro" << std::endl;
            //Ya se inicializo la matriz costos 
            std::cout<< "Voy a imprimir costos" << std::endl; 
            for (size_t i = 0; i < grafo.NumVertices(); i++)
            {
                for (size_t j = 0; j < grafo.NumVertices(); j++)
                {
                    std::cout << matrizCostos[i][j] << " ";
                }
                std::cout<< "\n";
        
            }
            std::cout << "\n"; 
            Vertice matrizVertices[grafo.NumVertices()][grafo.NumVertices()]; 
            //Matriz de vertices con basura

            //Paso 2
            
            for(iteradorPivotes; iteradorPivotes<grafo.NumVertices(); iteradorPivotes++)
            { //Pivotea
                for(i =0; i<grafo.NumVertices(); i++)
                {
                    for (size_t j = 0; j < grafo.NumVertices(); j++)
                    {
                       if(i != iteradorPivotes)
                        {
                            if(matrizCostos[i][j]!=-1){
                                if(matrizCostos[iteradorPivotes][j] != -1){
                                    if(grafo.ExisteArista(listaVertices[iteradorPivotes], listaVertices[j])){
                                        if(matrizCostos[i][j] > matrizCostos[iteradorPivotes][j] + grafo.Peso(listaVertices[iteradorPivotes], listaVertices[j])){
                                            matrizCostos[i][j] = matrizCostos[iteradorPivotes][j] + grafo.Peso(listaVertices[iteradorPivotes], listaVertices[j]);
                                            matrizVertices[i][j] = listaVertices[iteradorPivotes];
                                        }
                                    }
                                }
                            } else{
                                if(matrizCostos[iteradorPivotes][j] != -1){
                                    if(grafo.ExisteArista(listaVertices[iteradorPivotes], listaVertices[j])){
                                        matrizCostos[i][j] = matrizCostos[iteradorPivotes][j] + grafo.Peso(listaVertices[iteradorPivotes], listaVertices[j]);
                                        matrizVertices[i][j] = listaVertices[iteradorPivotes];
                                    }
                                }
                            }
                        }
                    }
                }
            }
            std::cout<< "Voy a imprimir costos" << std::endl; 
            for (size_t i = 0; i < grafo.NumVertices(); i++)
            {
                for (size_t j = 0; j < grafo.NumVertices(); j++)
                {
                    std::cout << matrizCostos[i][j] << " ";
                }
                std::cout<< "\n";
        
            }
            int *p[numVertices];
            int **q;
            for (int i=0; i<4;i++)
		        p[i]=matrizCostos[i];
            q = p;
            return  q; 
        }

};


#endif