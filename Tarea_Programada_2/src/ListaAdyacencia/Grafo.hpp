#ifndef GRAFO_LISTA_ADYACENCIA
#define GRAFO_LISTA_ADYACENCIA
#include "../2/Lista.hpp"
#include <iostream>
class Vertice{
    friend class Grafo;

    private:
        class Contenedor 
        {
        friend class Grafo;

        private:
            size_t peso;
            Vertice* VAdyacente;
        public:
            Contenedor(Vertice& vertice, size_t pesoN){
                VAdyacente = &vertice;
                peso = pesoN; 
            }
            Contenedor(const Contenedor& original){
                VAdyacente = original.VAdyacente;
                peso = original.peso; 
            }
            Contenedor(){};
            ~Contenedor(){};
            int operator==(const Contenedor& otro){
                if (otro.VAdyacente == this->VAdyacente)
                {
                    return 1;
                }
                return 0;
            }
            int operator!=(const Contenedor& otro){
                if (otro.VAdyacente == this->VAdyacente)
                {
                    return 0;
                }
                return 1;
            }
        };
		
        int esNulo(){
            return 0;
        }
        
        char etiqueta;
		Lista<Contenedor> * listaAdyacencia; 
    public:	
		/// @brief Constructor por omision de la clase nodo
		/// @remarks Requiere que el nodo no este inicializado 
		Vertice(){
			listaAdyacencia = nullptr;
            etiqueta = '@'; 
		}

		/// @brief Destructor por omision de la clase nodo
		/// @remarks Requiere que el nodo este inicializada
		~Vertice(){
		}

		/// @brief constructor con parametros de clase nodo
		/// @remarks Requiere que el nodo no este inicializada
		/// @param char et  
		Vertice(char et){
			etiqueta = et;
		}
        
        Vertice(Vertice * otro){
            this->listaAdyacencia = otro->listaAdyacencia;
            this->etiqueta = otro->etiqueta; 
        }

		/// @brief inserta en la lista de hijos de un nodo
		/// @remarks Requiere que el nodo este inicializado y que tenga una lista de hijos inicializada
		/// @param Vertice*  

		/// @brief Retorna la lista de hijos de un nodo
		/// @remarks Requiere que el nodo este inicializado y tenga una lista de hijos
		/// @return Lista<Vertice*> en caso de no encontralo devuelve un nullptr 
		Lista<Contenedor>* getlistaAdyacencia(){
			return listaAdyacencia; 
		}

		/// @brief imprime la etiqueta de un nodo
		/// @remarks Requiere que el nodo este inicializado
        /*
		void imprimirValor(){
			std::cout<< etiqueta << std::endl;
		}
        */

		/// @brief operador de igualdad de la clase nodo
		/// @remarks Requiere que ambos nodos esten inicializados y que posean etiquetas comparables
		/// @param Vertice 
		/// @return 1 si son iguales, 0 si no
		int operator==(Vertice nodo2){
			if(this->etiqueta== nodo2.etiqueta){
				return 1;
			}
			return 0;
		}
       
		/// @brief operador de desigualdad de la clase nodo
		/// @remarks Requiere que ambos nodos esten inicializados y que posean etiquetas comparables
		/// @param Vertice 
		/// @return 0 si son iguales, 1 si no
		int operator!=(Vertice nodo2){
			if(this->etiqueta == nodo2.etiqueta){
				return 0;
			}
			return 1;
		}

		/// @brief Devuelve la etiqueta de un nodo
		/// @remarks Requiere que el nodo este inicializado
		/// @return char etiqueta
		char getEtiqueta(){
			return etiqueta;
		}

		/// @brief modifica la etiqueta de un nodo
		/// @remarks Requiere que el nodo este inicializado
		/// @param char  
		void setEtiqueta(char valorNuevo){
			this->etiqueta = valorNuevo;
		}
    
};
class Grafo{
    private:
		Lista<Vertice> * listaPrincipal; 
		
	public:
		
/// @brief Crea un nuevo Arbol e inicializa su lista principal
/// @remarks Requiere que el arbol no este inicializado 
Grafo(){
	listaPrincipal = new Lista<Vertice>;
	
}

/// @brief Elimina al arbol y su lista principal
/// @remarks Requiere que el arbol este inicializado
~Grafo(){
	if(listaPrincipal->getPrimera()!=nullptr){
		for (Celda<Vertice> * it = listaPrincipal->getPrimera(); it != nullptr; it = it->getSiguiente()){
			delete it->getEtiqueta().getlistaAdyacencia();
		}
	} 
	delete listaPrincipal;									//listaPrincipal->										//listaPrincipal
} 

Vertice AgregarVertice(char etiqueta){
    Vertice vertice = Vertice(etiqueta);
    Lista<Vertice::Contenedor> * lista = new Lista<Vertice::Contenedor>();
    vertice.listaAdyacencia = lista; 
    listaPrincipal->insertar(vertice);
    return listaPrincipal->getUltima()->getEtiqueta(); 
}

void EliminarVertice(Vertice& vertice){
    Celda<Vertice> * celda;
    for (celda= listaPrincipal->getPrimera();  celda->getEtiqueta() != vertice; celda = celda->getSiguiente() ) //Muevo en lista Principal
    {}  
    delete celda->getEtiqueta().getlistaAdyacencia();
    listaPrincipal->borrar(vertice); 
}

const size_t NumVertices(){
     return listaPrincipal->getContador();
}

void ModificarEtiqueta(Vertice& vertice, char nueva){
    vertice.etiqueta = nueva;
}

char Etiqueta(Vertice& vertice){
    return vertice.etiqueta; 
}

void AgregarArista(Vertice& origen, Vertice& destino, size_t peso){
    Vertice * modificado1;
    Vertice * modificado2;
    for (auto i = listaPrincipal->getPrimera(); i != nullptr; i = i->getSiguiente())
    {
        if(i->getEtiqueta().etiqueta == origen.etiqueta){
            modificado1 = & i->getEtiqueta();
        } 
        if(i->getEtiqueta().etiqueta == destino.etiqueta){
            modificado2 = & i->getEtiqueta();
        }
    }
    
    Vertice::Contenedor contenedor1= Vertice::Contenedor(*modificado1, peso);
    modificado2->listaAdyacencia->insertar(contenedor1);
    Vertice::Contenedor contenedor2= Vertice::Contenedor(*modificado2, peso);
    modificado1->listaAdyacencia->insertar(contenedor2);
}

void EliminarArista(Vertice& origen, Vertice& destino){
    int borrados = 0;
    for (Celda<Vertice> * celda= listaPrincipal->getPrimera();  celda != nullptr; celda = celda->getSiguiente() ) //Muevo en lista Principal
    {
       if(celda->getEtiqueta() == origen){
            std::cout<< "Voy a borrar a "<< celda->getEtiqueta().etiqueta << std::endl;
            Vertice::Contenedor copia = Vertice::Contenedor(destino, this->Peso(origen, destino));
            celda->getEtiqueta().getlistaAdyacencia()->borrar(copia); 
            borrados++;
        } 
        if(celda->getEtiqueta() == destino){
            Vertice::Contenedor copia = Vertice::Contenedor(origen, this->Peso(origen, destino));
            celda->getEtiqueta().getlistaAdyacencia()->borrar(copia); 
            borrados++;
       }
       if (borrados == 2)
       {
        return;
       }
       
    }
    
}

void ModificarPeso(Vertice& origen, Vertice& destino, size_t nuevoPeso){
    int cantidadCambiados = 0;
    for (Celda<Vertice> * celda= listaPrincipal->getPrimera();  celda != nullptr; celda = celda->getSiguiente() ) //Muevo en lista Principal
    {
       if(celda->getEtiqueta() == origen || celda->getEtiqueta() == destino){
            for(Celda<Vertice::Contenedor> * iterador = celda->getEtiqueta().getlistaAdyacencia()->getPrimera(); iterador != nullptr; iterador = iterador->getSiguiente() ){
                if (iterador->getEtiqueta().VAdyacente == &origen || iterador->getEtiqueta().VAdyacente == &destino)
                {
                   iterador->getEtiqueta().peso = nuevoPeso; 
                }
                if (cantidadCambiados == 2)
                {
                    return; 
                }
                
            }
       }
    }  
}
size_t Peso(const Vertice& origen, const Vertice& destino){
    for (Celda<Vertice> * celda= listaPrincipal->getPrimera();  celda != nullptr; celda = celda->getSiguiente() ) //Muevo en lista Principal
    {
       if(celda->getEtiqueta().etiqueta == origen.etiqueta || celda->getEtiqueta().etiqueta == destino.etiqueta){
            for(Celda<Vertice::Contenedor> * iterador = celda->getEtiqueta().getlistaAdyacencia()->getPrimera(); iterador != nullptr; iterador = iterador->getSiguiente() ){
                if (iterador->getEtiqueta().VAdyacente->etiqueta == origen.etiqueta || iterador->getEtiqueta().VAdyacente->etiqueta == destino.etiqueta)
                {
                    return iterador->getEtiqueta().peso; 
                }
                
            }
       }
    }  
    return 0;
}
Vertice PrimerVertice(){
    if(listaPrincipal->getPrimera())
        return listaPrincipal->getPrimera()->getEtiqueta();
    Vertice nulo;
    return nulo; 
}
Vertice SiguienteVertice(Vertice& original){
    Celda<Vertice> * celda;
    for (celda= listaPrincipal->getPrimera();  celda->getEtiqueta() != original && celda!=nullptr; celda = celda->getSiguiente() ) //Muevo en lista Principal
    {}  
    if (celda->getSiguiente()!=nullptr)
        return celda->getSiguiente()->getEtiqueta(); 
    Vertice nulo;
    return nulo; 
}
Vertice PrimerVerticeAdyacente(Vertice& original){
    Celda<Vertice> * celda;
    for (celda= listaPrincipal->getPrimera();  celda->getEtiqueta() != original && celda->getSiguiente()!=nullptr; celda = celda->getSiguiente() ) //Muevo en lista Principal
    {} 
    if(celda->getEtiqueta() == original)
        return * celda->getEtiqueta().getlistaAdyacencia()->getPrimera()->getEtiqueta().VAdyacente; 
    Vertice nulo;
    return nulo;
}
int ExisteArista(Vertice& inicio, Vertice& fin){
    auto a = listaPrincipal->buscar(inicio); 
    int i = 0; 
    for (auto b  =a->getEtiqueta().getlistaAdyacencia()->getPrimera() ; i < a->getEtiqueta().getlistaAdyacencia()->getContador(); i++)
    {
       if (b->getEtiqueta().VAdyacente->etiqueta == fin.etiqueta )
       {
        return 1;
       }
       
       b = b->getSiguiente(); 
    }
    return 0;
}
Vertice SiguienteVerticeAdyacente(Vertice& original, Vertice& adyAnterior){
    Celda<Vertice> * celda;
    for (celda= listaPrincipal->getPrimera();  celda->getEtiqueta() != original; celda = celda->getSiguiente() ) //Muevo en lista Principal
    {} //Esto me el vertice inicial
    Celda<Vertice::Contenedor> * iterador;
    for( iterador= celda->getEtiqueta().getlistaAdyacencia()->getPrimera(); iterador->getEtiqueta().VAdyacente != &adyAnterior && iterador->getSiguiente()!=nullptr; iterador = iterador->getSiguiente() ){
    }
    if(iterador->getEtiqueta().VAdyacente == &adyAnterior)
        return * iterador->getSiguiente()->getEtiqueta().VAdyacente; 
    Vertice nulo;
    return nulo; 
}

void ImprimirConexiones(Vertice& vertice){
    auto a = listaPrincipal->buscar(vertice); 
    std::cout<< "Soy Arista " << a->getEtiqueta().etiqueta << "\nMis adyacentes son : " << std::endl; 
    int i =0;
    for (auto b  =a->getEtiqueta().getlistaAdyacencia()->getPrimera() ; i < a->getEtiqueta().getlistaAdyacencia()->getContador(); i++)
    {
       std::cout<< b->getEtiqueta().VAdyacente->etiqueta << std::endl;
       b = b->getSiguiente(); 
    }
    
}


void ImprimirVertices(){
	Celda<Vertice> * actual = listaPrincipal->getPrimera();
	while(actual!=nullptr){
		std::cout<< "ELEMENTO : " << actual->getEtiqueta().getEtiqueta() << std::endl;
		actual = actual->getSiguiente();
	}
}




};
#endif