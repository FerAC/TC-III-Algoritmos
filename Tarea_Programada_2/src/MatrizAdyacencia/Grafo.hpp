#ifndef Grafo_Matriz_Adyacencia
#define Grafo_Matriz_Adyacencia

#include <iostream>

class Vertice
{
    friend class Grafo;

    private:
        size_t indice; //Posicion en el arreglo
        char etiqueta;
        int nulo = 0; 

        int esNulo(){
            if (nulo == 1 && etiqueta == '0')
            {
                return 1;
            }
            return 0;            
        }

        void setPosicion(int indice){
            this->indice = indice;
        }

        size_t getindice(){
            return indice; 
        }

        void setEtiqueta(char valor){
            this->etiqueta = valor;
        }

        char getEtiqueta(){
            return this->etiqueta;
        }

    public:
        Vertice(){
            indice = 0;
            etiqueta = '0';
            nulo = 1;
        }
        Vertice(size_t indice, char etiqueta){
            this->indice = indice;
            this->etiqueta = etiqueta;
        }
        ~Vertice(){}
        bool operator ==(const Vertice& otro){
            if(otro.etiqueta == this->etiqueta && otro.indice == this->indice)
                return 1;
            return 0;
        }
        bool operator!=(const Vertice&otro){
            return !(*this==otro); 
        }
};

class Grafo{
    private:
        size_t vertices = 0; 
        int matriz[100][100]; 
        char vector[100]; 
    public:
    Grafo(){}
    ~Grafo(){}
    Vertice AgregarVertice(char elemento){
        vector[vertices] = elemento;
        Vertice vertice(vertices++, elemento); 
       // matriz[vertices][vertices] = 1; 
       return vertice; 
    }
    void EliminarVertice(Vertice &borrado){
        int encontrado = 0; 
        size_t indiceBorrado; 
        //Vertices es uno mayor al ultimo
        for (size_t i = 0; i < vertices; i++)
        {
            if(encontrado == 0){
                if(vector[i] == borrado.etiqueta){
                    encontrado = 1;
                    indiceBorrado = i;
                    vector[i] = vector[i+1];
                }
            } else{
                if(i< vertices -1){
                    vector[i] = vector[i+1];
                } else if(i == vertices -1 ){
                    vector[i] = '0'; //Borrado logico 
                }
            }
        } //Ya lo borre del array
        for (size_t i = indiceBorrado; i < vertices; i++)
        { //Corrimiento de filas
            if(i<vertices-1){
                for (size_t j = 0; j < vertices; j++)
                {
                    matriz[i][j] =matriz[i+1][j]; 
                }
            } else{
                //No se si hacer borrado logico
            }   
        }
        for (size_t i = indiceBorrado; i < vertices; i++)
        { //Corrimiento de filas
            if(i<vertices-1){
                for (size_t j = 0; j < vertices; j++)
                {
                    matriz[j][i] =matriz[j][i+1]; 
                }
            } else{
                //No se si hacer borrado logico
            }
        }
        vertices--;
    }
    const size_t NumVertices(){
        return vertices; 
    }
    void ModificarEtiqueta(Vertice& vertice, char etiqueta){
        vertice.etiqueta = etiqueta;
        vector[vertice.indice] = etiqueta; 
    }
    char Etiqueta(Vertice& vertice){
        return vertice.etiqueta; 
    }
    void AgregarArista(Vertice& origen, Vertice& destino, size_t peso){
        matriz[origen.indice][destino.indice] = peso;
        matriz[destino.indice][origen.indice] = peso;
    }
    void EliminarArista(Vertice& origen, Vertice& destino){
        matriz[origen.indice][destino.indice] = -1;
        matriz[destino.indice][origen.indice] = -1;
    }
    void ModificarArista(Vertice& origen, Vertice& destino, size_t peso){
        AgregarArista(origen, destino, peso);
    }
    size_t Peso(Vertice& origen, Vertice& destino){
        return matriz[origen.indice][destino.indice]; 
    }
    Vertice PrimerVertice(){
        Vertice vertice(0, vector[0]); 
        return vertice; 
    }
    Vertice SiguienteVertice(Vertice& anterior){
        Vertice vertice(anterior.indice+1, vector[anterior.indice+1]);
        return vertice; 
    }
    Vertice PrimerVerticeAdyacente(Vertice& original){
        for(size_t i = 0; i<vertices; i++){
            if(matriz[original.indice][i]>0){
                Vertice  vertice (i, vector[i]);
                return vertice;
            }
        }
        Vertice vertice;
        return vertice; 
    }
int ExisteArista(Vertice& inicio, Vertice& fin){
    const Vertice NULO;
    for(Vertice iterador = PrimerVerticeAdyacente(inicio); iterador != NULO; iterador = SiguienteVerticeAdyacente(inicio, iterador)){
        if(iterador == fin){
            return 1;
        }
    }
    return 0; 
}
    Vertice SiguienteVerticeAdyacente(Vertice& original, Vertice& adyacente){
        if(adyacente.indice+1<=vertices){
            for (size_t i = adyacente.indice+1; i < vertices; i++)
            {
                if(matriz[original.indice][i]> 0){
                    Vertice  vertice (i, vector[i]);
                    return vertice; 
                }
            }
        }
        Vertice vertice;
        return vertice; 
    }
    void ImprimirGrafo(){
        for (size_t i = 0; i < vertices; i++)
        {
           for (size_t j = 0; j < vertices; j++)
           {
                std::cout<< matriz[i][j]<< " "; 
           }
           std::cout<< std::endl;
        }
        
    }
    void ImprimirVertices(){
        for (size_t i = 0; i < vertices; i++)
        {
            std::cout << vector[i] << " ";
        }
        
    }
};
#endif