#include <list>
#include <map>
#include <stack>
#include <iostream>
#include <limits>

#include "Algoritmos.hpp"
#include "Tripleta.hpp"

static Vertice encontrarPivote(Tripleta *lista, std::map<char, Vertice> &mapaVerticesVisitados, const Grafo &grafo)
{   
   

       
   
    
    Vertice pivote;
    size_t menorPeso = 0;
    size_t indiceMenor = std::numeric_limits<size_t>::max();
    for (size_t i = 0; i < grafo.NumVertices() - 1; i++)
    {
       
        // Verifico que no haya sido pivoteado antes
        if (mapaVerticesVisitados.empty())
        { // Caso trivial, esta vacio
         
            if (menorPeso != 0)
            {
                if (lista[i].getPeso() != 0 && lista[i].getPeso() <= menorPeso)
                {
                    indiceMenor = i;
                    menorPeso = lista[indiceMenor].getPeso();
                }
            }
            else
            {
                if (lista[i].getPeso() != 0)
                {
                    indiceMenor = i;
                    menorPeso = lista[indiceMenor].getPeso();
                }
            }
        }
        else
        {
           
            if (mapaVerticesVisitados.count(lista[i].getVertice().getEtiqueta()) > 0)
            {
              
            }
            else
            {
                
                if (menorPeso != 0)
                {
                    if (lista[i].getPeso() != 0 && lista[i].getPeso() <= menorPeso)
                    {
                        indiceMenor = i;
                        menorPeso = lista[i].getPeso();
                    }
                }
                else
                {
                    if (lista[i].getPeso() != 0)
                    {
                        indiceMenor = i;
                        menorPeso = lista[i].getPeso();
                    }
                }
            }
        }
    }
   
  
    char a = lista[indiceMenor].getVertice().getEtiqueta();
   
    Vertice b = lista[indiceMenor].getVertice();
    mapaVerticesVisitados.insert(std::pair<char, Vertice>(a, b));
    return b;
}

namespace Algoritmos {

    void Prim(const Grafo &grafo, Grafo& grafoRecipiente) {
        // int a = grafo.NumVertices();
        Tripleta lista[grafo.NumVertices() - 1];
        // Inicializacion
        Vertice vInicial = grafo.PrimerVertice();
        const Vertice NULO;
        size_t i = 0;
       
        for (Vertice iterador = grafo.PrimerVertice(); iterador != NULO; iterador = grafo.SiguienteVertice(iterador))
        {
            int peso = 0;
            if (vInicial != iterador)
            {
                
                if (grafo.ExisteArista(vInicial, iterador))
                {
                    peso = grafo.Peso(vInicial, iterador);
                }
                Tripleta tripleta(iterador, peso, vInicial);
                lista[i] = tripleta;
               // lista[i].imprimir();
                i++;
            }
        }
       
        // Primer pivote
        std::map<char, Vertice> mapaVerticesPivoteados;
        for (size_t j = 0; j < grafo.NumVertices() - 1; j++)
        {
            Vertice pivote = encontrarPivote(lista, mapaVerticesPivoteados, grafo);
            for (size_t i = 0; i < grafo.NumVertices() - 1; i++)
            {
                if (lista[i].getVertice() != pivote && mapaVerticesPivoteados.count(lista[i].getVertice().getEtiqueta()) <= 0)
                {
                    if(grafo.ExisteArista(pivote, lista[i].getVertice())){
                         
                            if(lista[i].getPeso() == 0){
                                lista[i].setPeso(grafo.Peso(pivote, lista[i].getVertice()));
                                lista[i].setVerticeAnterior(pivote);
                            } else
                            if (lista[i].getPeso() > grafo.Peso(pivote, lista[i].getVertice()))
                            {
                                lista[i].setPeso(grafo.Peso(pivote, lista[i].getVertice()));
                                lista[i].setVerticeAnterior(pivote);
                            }
                        
                    }
                }
            }
        }

        for (size_t i = 0; i < grafo.NumVertices() - 1; i++)
        {
            Vertice llegada;
            Vertice salida;

            // Verifico no haber anadido el vertice anteriormente
            Vertice buscado = BuscarVertice(grafoRecipiente, lista[i].getVertice().getEtiqueta());
            if (buscado == NULO) {
                salida = grafoRecipiente.AgregarVertice(lista[i].getVertice().getEtiqueta());
            } else {
                salida = buscado;
            }
            buscado = BuscarVertice(grafoRecipiente, lista[i].getVerticeAnterior().getEtiqueta());

            if (buscado == NULO) {
                llegada = grafoRecipiente.AgregarVertice(lista[i].getVerticeAnterior().getEtiqueta());
            } else {
                llegada = buscado;
            }
            
            grafoRecipiente.AgregarArista(llegada, salida, lista[i].getPeso());
        }

        Vertice vertice;
        for (size_t i = 0; i < grafoRecipiente.NumVertices(); i++)
        {
            if (i == 0) {
                vertice = grafoRecipiente.PrimerVertice();
            }
            else {
                vertice = grafoRecipiente.SiguienteVertice(vertice);
            }
            // retornado.ImprimirConexiones(vertice);
        }

        for (size_t i = 0; i < grafoRecipiente.NumVertices(); i++)
        {
            if (i == 0) {
                vertice = grafo.PrimerVertice();
            }
            else {
                vertice = grafo.SiguienteVertice(vertice);
            }
            //  grafo.ImprimirConexiones(vertice);
        }

        // Ya terminamos el algoritmo
        return;
    }

    Grafo primMetodo(Grafo& grafo) {
        //int a = grafo.NumVertices(); 
        Tripleta lista[grafo.NumVertices()-1];
        //Inicializacion
        Vertice vInicial = grafo.PrimerVertice();
        const Vertice NULO;
        size_t i =0;
        
        for(Vertice iterador = grafo.PrimerVertice(); iterador != NULO; iterador = grafo.SiguienteVertice(iterador)){
            int peso = 0; 
            if(vInicial!=iterador){
               
                if(grafo.ExisteArista(vInicial, iterador)){
                    peso = grafo.Peso(vInicial, iterador);
                }
                Tripleta tripleta(iterador, peso,  vInicial);
                lista[i] = tripleta; 
               
                    i++;
            } 
        }
        
       
        
        
       
        //Primer pivote
        std::map<char, Vertice> mapaVerticesPivoteados; 
        for(size_t j = 0; j<grafo.NumVertices()-1; j++){
          
            Vertice pivote = encontrarPivote(lista, mapaVerticesPivoteados, grafo);
           
            for (size_t i = 0; i < grafo.NumVertices()-1; i++)
            {
                if(lista[i].getVertice()!=pivote && mapaVerticesPivoteados.count(lista[i].getVertice().getEtiqueta())<=0){
                    if(grafo.Peso(pivote, lista[i].getVertice())>0){
                        if (lista[i].getPeso()> grafo.Peso(pivote, lista[i].getVertice()))
                        {
                            lista[i].setPeso(grafo.Peso(pivote, lista[i].getVertice()));
                            lista[i].setVerticeAnterior(pivote);
                        }
                    }
                }
            }
           
        }
        
        Grafo retornado;
        /*
        for (Vertice vertice = grafo.PrimerVertice(); vertice != NULO; vertice = grafo.SiguienteVertice(vertice))
        {
            retornado.AgregarVertice(grafo.Etiqueta(vertice));
        }
            for (Vertice vertice = retornado.PrimerVertice(); vertice != NULO; vertice = retornado.SiguienteVertice(vertice))
        {
            std::cout<< grafo.Etiqueta(vertice) << std::endl;
        }
        */
        
        
        
        for(size_t i =0 ; i< grafo.NumVertices()-1; i++){
            Vertice llegada;
            Vertice salida; 
            /*
            llegada = retornado.PrimerVertice();
            salida = retornado.PrimerVertice();
            int bandera = 0;
            while (!bandera)
            {
                if (salida.getEtiqueta() == lista[i].getVerticeAnterior().getEtiqueta())
                {
                    bandera = 1; 
                } else{
                    salida = retornado.SiguienteVertice(salida); 
                }
            }
            bandera = 0;
                while (!bandera)
            {
                if (llegada.getEtiqueta() == lista[i].getVertice().getEtiqueta())
                {
                    bandera = 1; 
                } else{
                    llegada = retornado.SiguienteVertice(llegada); 
                }
            }
            */
            //Verifico no haber anadido el vertice anteriormente
            Vertice buscado = BuscarVertice(retornado, lista[i].getVertice().getEtiqueta());
            if(buscado==NULO){
              
                salida = retornado.AgregarVertice(lista[i].getVertice().getEtiqueta());
            } else{
               
                salida = buscado;
            }
            buscado = BuscarVertice(retornado, lista[i].getVerticeAnterior().getEtiqueta());
            if(buscado==NULO){
               
                llegada = retornado.AgregarVertice(lista[i].getVerticeAnterior().getEtiqueta());
            } else{
                 llegada = buscado;
            }
            /*
            llegada = buscarVertice(retornado, lista[i].getVertice().getEtiqueta());
            salida = buscarVertice(retornado, lista[i].getVerticeAnterior().getEtiqueta()); 
            */
          
            retornado.AgregarArista(llegada, salida, lista[i].getPeso());
        }
        Vertice vertice;
            for (size_t i = 0; i < retornado.NumVertices(); i++)
        {
            if(i == 0){
                vertice = retornado.PrimerVertice();
            } else{
                vertice = retornado.SiguienteVertice(vertice); 
            }
            // retornado.ImprimirConexiones(vertice);  
        }
            for (size_t i = 0; i < retornado.NumVertices(); i++)
        {
            if(i == 0){
                vertice = grafo.PrimerVertice();
            } else{
                vertice = grafo.SiguienteVertice(vertice); 
            }
            //  grafo.ImprimirConexiones(vertice);  
        }
        return retornado;
    }

}
