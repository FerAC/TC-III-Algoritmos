#include "Controlador.hpp"
//#include "../MatrizAdyacencia/Grafo.hpp"
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
            Tripleta(){}
            Tripleta(Vertice& vertice, int peso, Vertice& verticeAnterior){
                this->vertice = vertice;
                this->peso = peso;
                this->verticeAnterior = verticeAnterior; 
            }
            Tripleta(Tripleta& otra){
                this->vertice = otra.vertice;
                this->peso = otra.peso;
                this->verticeAnterior = otra.verticeAnterior;
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
            void imprimir(){
                std::cout<< "Etiqueta: " << vertice.getEtiqueta() << std::endl;
                std::cout<< "Etiqueta vieja: " << this->verticeAnterior.getEtiqueta() << std::endl;
                std::cout<< "Peso: "<< this->peso << std::endl;
            }
        };
                static Grafo primMetodo(Grafo& grafo){
                    //int a = grafo.NumVertices(); 
                    Tripleta lista[grafo.NumVertices()-1];
                    //Inicializacion
                    Vertice vInicial = grafo.PrimerVertice();
                    const Vertice NULO;
                    size_t i =0;
                    std::cout<< "Voy a for " << std::endl;
                    for(Vertice iterador = grafo.PrimerVertice(); iterador != NULO; iterador = grafo.SiguienteVertice(iterador)){
                        int peso = 0; 
                        if(vInicial!=iterador){
                            std::cout<< "No son iguales" << std::endl;
                            if(grafo.ExisteArista(vInicial, iterador)){
                                peso = grafo.Peso(vInicial, iterador);
                            }
                            Tripleta tripleta(iterador, peso,  vInicial);
                            lista[i] = tripleta; 
                            lista[i].imprimir();
                             i++;
                        } 
                    }
                    std::cout<< std::endl;
                    std::cout<< "Sali de inicializacion " << std::endl;
                    for (size_t i = 0; i < grafo.NumVertices()-1; i++)
                    {
                        lista[i].imprimir();
                    }
                    
                    
                    std::cout << "VOY A PIVOT" << std::endl;
                    //Primer pivote
                    std::map<char, Vertice> mapaVerticesPivoteados; 
                    for(size_t j = 0; j<grafo.NumVertices()-1; j++){
                        std::cout<< "J " << j << std::endl;
                        Vertice pivote = encontrarPivote(lista, mapaVerticesPivoteados, grafo);
                        std::cout<< "///////////// PIVOTEO CON " << pivote.getEtiqueta() << "///////////" << std::endl;
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
                       std::cout<<"+++++++++++++++++++BUCLE EXTERNO ++++++++++++++++++++++" << std::endl;
                            for (size_t i = 0; i < grafo.NumVertices()-1; i++)
                            {
                                std::cout<< "Vertice " << lista[i].getVertice().getEtiqueta() << std::endl;
                                std::cout<< "Peso " << lista[i].getPeso() << std::endl;
                                std::cout<< "Vertice Anterior " << lista[i].getVerticeAnterior().getEtiqueta() << std::endl;
                            }
                            std::cout<<"+++++++++++++++++++BUCLE EXTERNO ++++++++++++++++++++++" << std::endl;
                    }
                    std::cout<<"****************************************** " << std::endl;
                    for (size_t i = 0; i < grafo.NumVertices()-1; i++)
                    {
                        std::cout<<"Vertice " << lista[i].getVertice().getEtiqueta() << std::endl;
                        std::cout<<"Peso " << lista[i].getPeso() << std::endl;
                        std::cout<<"Vertice Anterior " << lista[i].getVerticeAnterior().getEtiqueta() << std::endl;
                    }
                    std::cout<<"****************************************** " << std::endl;
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
                        Vertice buscado = buscarVertice(retornado, lista[i].getVertice().getEtiqueta());
                        if(buscado==NULO){
                            std::cout<< "No se ha agregado a " << lista[i].getVertice().getEtiqueta()<<std::endl; 
                            salida = retornado.AgregarVertice(lista[i].getVertice().getEtiqueta());
                        } else{
                            std::cout<< "Si se ha agregado a " << lista[i].getVertice().getEtiqueta()<<std::endl; 
                            salida = buscado;
                        }
                        buscado = buscarVertice(retornado, lista[i].getVerticeAnterior().getEtiqueta());
                        if(buscado==NULO){
                            std::cout<< "No se ha agregado a " << lista[i].getVerticeAnterior().getEtiqueta()<<std::endl; 
                            llegada = retornado.AgregarVertice(lista[i].getVerticeAnterior().getEtiqueta());
                        } else{
                            std::cout<< "Si se ha agregado a " << lista[i].getVerticeAnterior().getEtiqueta()<<std::endl; 
                            llegada = buscado;
                        }
                        /*
                        llegada = buscarVertice(retornado, lista[i].getVertice().getEtiqueta());
                        salida = buscarVertice(retornado, lista[i].getVerticeAnterior().getEtiqueta()); 
                        */
                        std::cout<< "Se va a agregar una arista de peso " << lista[i].getPeso() << ", entre " << llegada.getEtiqueta() << " y "<< salida.getEtiqueta() <<std::endl;
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

                static Vertice encontrarPivote(Tripleta * lista, std::map<char, Vertice>& mapaVerticesVisitados, Grafo& grafo){
                    std::cout<<"Estoy en metodo buscar pivote " << std::endl;
                    std::cout<<"Tamano del mapa : " << mapaVerticesVisitados.size() << std::endl;
                    Vertice pivote; 
                    size_t menorPeso = 0; 
                    size_t indiceMenor; 
                    for (size_t i = 0; i < grafo.NumVertices()-1  ; i++)
                    {
                        //Verifico que no haya sido pivoteado antes
                        if(mapaVerticesVisitados.empty()){ //Caso trivial, esta vacio
                            std::cout<<"Primer pivote " << std::endl;
                            if(menorPeso != 0){
                                if(lista[i].getPeso() != 0 && lista[i].getPeso()<menorPeso){
                                    std::cout<<"Primer pivote " << std::endl;
                                    indiceMenor = i; 
                                    menorPeso = lista[indiceMenor].getPeso();
                                }
                            } else{
                                if(lista[i].getPeso() != 0){
                                    std::cout<<"Primer pivote " << std::endl;
                                    indiceMenor = i; 
                                    menorPeso = lista[indiceMenor].getPeso();
                                }
                            }
                        } else{
                            if (mapaVerticesVisitados.count(lista[i].getVertice().getEtiqueta())>0)
                            {
                                //Si lo encontro, sigo adelante
                                std::cout<<"YA SE PIVOTEO CON " << lista[i].getVertice().getEtiqueta() << std::endl; 

                            } else{
                                std::cout<< "No se ha pivoteado con " << lista[i].getVertice().getEtiqueta() << std::endl;
                                 std::cout<< "Su peso es  " << lista[i].getPeso() << std::endl;
                                if(menorPeso!=0){
                                    if(lista[i].getPeso() != 0 && lista[i].getPeso()<menorPeso){
                                        indiceMenor = i; 
                                        menorPeso = lista[i].getPeso();
                                    }
                                } else{
                                    if(lista[i].getPeso() != 0){
                                        indiceMenor = i; 
                                        menorPeso = lista[i].getPeso();
                                    } 
                                }
                            }    
                        }
                    }
                     std::cout<<"Encontre pivote " <<indiceMenor <<  std::endl;
                     std::cout<<"Peso menor " << menorPeso << std::endl;
                    char a = lista[indiceMenor].getVertice().getEtiqueta(); 
                    std::cout<<"Encontre pivote " << a << std::endl;
                    Vertice b = lista[indiceMenor].getVertice();
                    mapaVerticesVisitados.insert(std::pair<char, Vertice>(a,b));
                    return b;
                }

                static size_t ** Floyd(Grafo &grafo){
                    int numVertices = grafo.NumVertices();
                    std::cout<< "Entre floyd" << std::endl;
                    const Vertice NULO;
                    Vertice listaVertices [numVertices]; 
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
                    std::cout<< "A" << std::endl;
                    std::cout<< "NUM VERTICES " << numVertices << std::endl;
                    size_t matrizCostos[numVertices][numVertices]; 
                    for(int i =0; i<numVertices; i++){
                        std::cout << "I " << i << std::endl;
                        for (int j = 0; j < numVertices; j++)
                        {
                            std::cout << "J " << j << std::endl;
                            if(i!=j){
                                if(grafo.ExisteArista(listaVertices[i], listaVertices[j])){
                                    std::cout << "Voy a acceder " << std::endl;
                                    std::cout<< "Vertice 1 :" << listaVertices[i].getEtiqueta()<< std::endl;
                                    std::cout<< "Vertice 2 :" << listaVertices[j].getEtiqueta()<< std::endl;

                                    // Vertice vertice1 = 
                                    // Vertice vertice2 =


                                    int miPeso = grafo.Peso(listaVertices[i], listaVertices[j]);
                                    std::cout<< "Peso  :" << miPeso << std::endl;

                                    // std::cout<< "Peso  :" << grafo.Peso(listaVertices[i], listaVertices[j]) << std::endl;
                                    matrizCostos[i][j] = grafo.Peso(listaVertices[i], listaVertices[j]); 
                                } else{
                                    matrizCostos[i][j] = 4;
                                }
                            } else{
                                std::cout<< "SON IGUALES " << std::endl;
                                matrizCostos[i][j] = 0; 
                            }
                        }
                    }
                    std::cout<< "Segundo paso se logro" << std::endl;
                    //Ya se inicializo la matriz costos 
                    std::cout<< "Voy a imprimir costos" << std::endl; 
                    for (size_t i = 0; i < numVertices; i++)
                    {
                        for (size_t j = 0; j < numVertices; j++)
                        {
                            std::cout << matrizCostos[i][j] << " ";
                        }
                        std::cout<< "\n";
                
                    }
                    std::cout << "\n"; 
                    Vertice matrizVertices[numVertices][numVertices]; 
                    //Matriz de vertices con basura

                    //Paso 2
                    
                    for(iteradorPivotes; iteradorPivotes<numVertices; iteradorPivotes++)
                    { //Pivotea
                        for(i =0; i<numVertices; i++)
                        {
                            for (size_t j = 0; j < numVertices; j++)
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
                    for (size_t i = 0; i < numVertices; i++)
                    {
                        for (size_t j = 0; j < numVertices; j++)
                        {
                            std::cout << matrizCostos[i][j] << " ";
                        }
                        std::cout<< "\n";
                    }
                    std::cout<< "\n"; 
                    size_t *p[numVertices];
                    size_t **q;
                    for (int i=0; i<4;i++)
                        p[i]= matrizCostos[i];
                    q = p;
                    return  q; 
                }

                static Vertice buscarVertice(Grafo &grafo, char etiqueta){
                    const Vertice NULO;
                    for(Vertice vertice = grafo.PrimerVertice(); vertice!=NULO; vertice=grafo.SiguienteVertice(vertice)){
                        if (grafo.Etiqueta(vertice) == etiqueta)
                        {
                            return  vertice;
                        } 
                    }
                    return NULO;
                }

                static double calculoCota(Grafo& grafo){
                    double valorActual;
                    const Vertice NULO;
                    for (Vertice * i = & grafo.PrimerVertice(); *i != NULO; i = &grafo.SiguienteVertice(*i))
                    {
                        double menor1 = 0;
                        double menor2 = 0;
                        bool asignados = false; 
                        for (Vertice * adyacentes = & grafo.PrimerVerticeAdyacente(*i); *adyacentes != NULO; adyacentes = & grafo.SiguienteVerticeAdyacente(*i, *adyacentes))
                        {
                            if(menor1 == 0){
                                menor1 = grafo.Peso(*i, *adyacentes);
                            } else
                            if (menor2 == 0)
                            {
                                menor2 = grafo.Peso(*i, *adyacentes);
                                asignados = true; 
                            }
                            if (grafo.Peso(*i, *adyacentes)< menor1 && asignados)
                            {
                                double aux = menor1;
                                menor1 = grafo.Peso(*i, *adyacentes);
                                menor2 = aux;
                            }   
                        }
                        valorActual = menor1 + menor2; 
                    }
                    valorActual = valorActual / 2; 
                    return valorActual; 
                } 

        };


        #endif