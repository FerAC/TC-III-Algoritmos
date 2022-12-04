#ifndef MATRIZ

#include <iostream>

#include "ListaAdyacencia/Grafo.hpp"

// CONSTRUCTORES Y DESTRUCTORES

Grafo::Grafo() {
    this->listaPrincipal = new Lista<Vertice>;   
}

Grafo::~Grafo() {
	if (listaPrincipal->getPrimera()!=nullptr) {
		for (Celda<Vertice>* it = listaPrincipal->getPrimera(); it != nullptr; it = it->getSiguiente()) {
			delete it->getEtiqueta().getlistaAdyacencia();
		}
	}

	delete listaPrincipal;									//listaPrincipal->										//listaPrincipal
} 

// VERTICES

Vertice Grafo::AgregarVertice(char etiqueta) {
    Vertice vertice = Vertice(etiqueta);

    Lista<Vertice::Contenedor>* lista = new Lista<Vertice::Contenedor>();
    vertice.listaAdyacencia = lista; 

    listaPrincipal->insertar(vertice);
    return listaPrincipal->getUltima()->getEtiqueta(); 
}

void Grafo::EliminarVertice(Vertice& vertice) {
    Celda<Vertice>* celda;
    for (celda = this->listaPrincipal->getPrimera();  celda->getEtiqueta() != vertice; celda = celda->getSiguiente() ) //Muevo en lista Principal
    {}

    /* TODO(us): Mejor usar un while?
    Celda<Vertice>* celda = this->listaPrincipal->getPrimera();
    while (celda->getEtiqueta() != vertice) {
        celda = celda->getSiguiente()
    }
    */

    delete celda->getEtiqueta().getlistaAdyacencia();
    listaPrincipal->borrar(vertice); 
}

size_t Grafo::NumVertices() const {
    return listaPrincipal->getContador();
}

char Grafo::Etiqueta(const Vertice& vertice) const {
    return vertice.etiqueta; 
}

void Grafo::ModificarEtiqueta(Vertice& vertice, char nueva) {
    vertice.etiqueta = nueva;
}

Vertice Grafo::PrimerVertice() {
    if (listaPrincipal->getPrimera())
        return listaPrincipal->getPrimera()->getEtiqueta();

    Vertice nulo;
    return nulo; 
}

Vertice Grafo::SiguienteVertice(Vertice& original) {
    Celda<Vertice>* celda;
    for (celda= listaPrincipal->getPrimera();  celda->getEtiqueta() != original && celda!=nullptr; celda = celda->getSiguiente() ) //Muevo en lista Principal
    {}

    /* TODO(us): Mejor usar while?
    Celda<Vertice>* celda = this->listaPrincipal->getPrimera();
    while (celda->getEtiqueta() != original && celda->getSiguiente != nullptr) {
        celda = celda->getSiguiente()
    }
    */

    if (celda->getSiguiente()!=nullptr)
        return celda->getSiguiente()->getEtiqueta();

    Vertice nulo;
    return nulo; 
}

Vertice Grafo::PrimerVerticeAdyacente(Vertice& original) {
    Celda<Vertice>* celda;
    for (celda= listaPrincipal->getPrimera();  celda->getEtiqueta() != original && celda->getSiguiente()!=nullptr; celda = celda->getSiguiente() ) //Muevo en lista Principal
    {}

    /* TODO(us): Mejor usar while?
    Celda<Vertice>* celda = this->listaPrincipal->getPrimera();
    while (celda->getEtiqueta() != original && celda->getSiguiente != nullptr) {
        celda = celda->getSiguiente()
    }
    */

    if (celda->getEtiqueta().etiqueta == original.etiqueta) {
        std::cout << "Primer adyacente de " << original.etiqueta << " es " <<  celda->getEtiqueta().getlistaAdyacencia()->getPrimera()->getEtiqueta().VAdyacente->etiqueta << std::endl;
        return* celda->getEtiqueta().getlistaAdyacencia()->getPrimera()->getEtiqueta().VAdyacente; 
    }

    Vertice nulo;
    return nulo;
}

Vertice Grafo::SiguienteVerticeAdyacente(Vertice& original, Vertice& adyAnterior) {
    std::cout << "SE ESTA BUSCANDO ADYACENTE SIGUIENTE " << std::endl;
    Celda<Vertice>* celda;
    Vertice nulo;

    for (celda= listaPrincipal->getPrimera();  celda->getEtiqueta().etiqueta != original.etiqueta; celda = celda->getSiguiente() ) //Muevo en lista Principal
    {} //Esto me el vertice inicial
    Celda<Vertice::Contenedor>* iterador;
    for (iterador= celda->getEtiqueta().getlistaAdyacencia()->getPrimera(); iterador->getEtiqueta().VAdyacente->etiqueta != adyAnterior.etiqueta && iterador->getSiguiente()!=nullptr; iterador = iterador->getSiguiente() ) {
    }

    /* TODO(us): Mejor usar whiles?
    Celda<Vertice>* celda = this->listaPrincipal->getPrimera();
    while (celda->getEtiqueta() != original.etiqueta) {
        celda = celda->getSiguiente()
    }

    Celda<Vertice::Contenedor>* iterador = iterador= celda->getEtiqueta().getlistaAdyacencia()->getPrimera();
    while (celda->getEtiqueta().etiqueta != original.etiqueta) {
        celda = celda->getSiguiente();
    }
    */

    if (iterador == nullptr) {
        std::cout << "Iterador nulo " << std::endl;
        return nulo;
    }

    if (iterador->getEtiqueta().VAdyacente->etiqueta == adyAnterior.etiqueta) {
        std::cout << "Siguiente adyacente de  " << original.etiqueta << ", anterior "<< adyAnterior.etiqueta << " es " << iterador->getSiguiente()->getEtiqueta().VAdyacente->etiqueta << std::endl;
        return* iterador->getSiguiente()->getEtiqueta().VAdyacente; 
    }
    
    return nulo; 
}

void Grafo::ImprimirVertices() {
	Celda<Vertice>* actual = listaPrincipal->getPrimera();

	while (actual!=nullptr) {
		std::cout << "ELEMENTO : " << actual->getEtiqueta().getEtiqueta() << std::endl;
		actual = actual->getSiguiente();
	}
}

// ARISTAS

int Grafo::ExisteArista(Vertice& inicio, Vertice& fin) {
    auto a = listaPrincipal->buscar(inicio); 
    int i = 0;

    for (auto b = a->getEtiqueta().getlistaAdyacencia()->getPrimera() ; i < a->getEtiqueta().getlistaAdyacencia()->getContador(); i++)
    {
        if (b->getEtiqueta().VAdyacente->etiqueta == fin.etiqueta ) {
            return 1;
        }
       
       b = b->getSiguiente(); 
    }

    return 0;
}

void Grafo::AgregarArista(Vertice& origen, Vertice& destino, size_t peso) {
    Vertice* modificado1;
    Vertice* modificado2;
    for (auto i = listaPrincipal->getPrimera(); i != nullptr; i = i->getSiguiente())
    {
        if (i->getEtiqueta().etiqueta == origen.etiqueta) {
            modificado1 = & i->getEtiqueta();
        } 
        if (i->getEtiqueta().etiqueta == destino.etiqueta) {
            modificado2 = & i->getEtiqueta();
        }
    }

    Vertice::Contenedor contenedor1= Vertice::Contenedor(*modificado1, peso);
    modificado2->listaAdyacencia->insertar(contenedor1);
    Vertice::Contenedor contenedor2= Vertice::Contenedor(*modificado2, peso);
    modificado1->listaAdyacencia->insertar(contenedor2);
}

void Grafo::EliminarArista(Vertice& origen, Vertice& destino) {
    int borrados = 0;
    for (Celda<Vertice>* celda= listaPrincipal->getPrimera();  celda != nullptr; celda = celda->getSiguiente() ) //Muevo en lista Principal
    {
        if (celda->getEtiqueta() == origen) {
            std::cout << "Voy a borrar a "<< celda->getEtiqueta().etiqueta << std::endl;
            Vertice::Contenedor copia = Vertice::Contenedor(destino, this->Peso(origen, destino));
            celda->getEtiqueta().getlistaAdyacencia()->borrar(copia); 
            borrados++;
        } 
        if (celda->getEtiqueta() == destino) {
            Vertice::Contenedor copia = Vertice::Contenedor(origen, this->Peso(origen, destino));
            celda->getEtiqueta().getlistaAdyacencia()->borrar(copia); 
            borrados++;
        }
        if (borrados == 2) {
            return;
        }
    }
}

size_t Grafo::Peso(const Vertice& origen, const Vertice& destino) {
    for (Celda<Vertice>* celda= listaPrincipal->getPrimera();  celda != nullptr; celda = celda->getSiguiente() ) //Muevo en lista Principal
    {
       if (celda->getEtiqueta().etiqueta == origen.etiqueta || celda->getEtiqueta().etiqueta == destino.etiqueta) {
            for (Celda<Vertice::Contenedor>* iterador = celda->getEtiqueta().getlistaAdyacencia()->getPrimera(); iterador != nullptr; iterador = iterador->getSiguiente() ) {
                if (iterador->getEtiqueta().VAdyacente->etiqueta == origen.etiqueta || iterador->getEtiqueta().VAdyacente->etiqueta == destino.etiqueta) {
                    return iterador->getEtiqueta().peso; 
                }
                
            }
       }
    }  
    return 0;
}

void Grafo::ModificarPeso(Vertice& origen, Vertice& destino, size_t nuevoPeso) {
    int cantidadCambiados = 0;
    for (Celda<Vertice>* celda= listaPrincipal->getPrimera();  celda != nullptr; celda = celda->getSiguiente() ) //Muevo en lista Principal
    {
       if (celda->getEtiqueta() == origen || celda->getEtiqueta() == destino) {
            for (Celda<Vertice::Contenedor>* iterador = celda->getEtiqueta().getlistaAdyacencia()->getPrimera(); iterador != nullptr; iterador = iterador->getSiguiente() ) {
                if (iterador->getEtiqueta().VAdyacente == &origen || iterador->getEtiqueta().VAdyacente == &destino) {
                   iterador->getEtiqueta().peso = nuevoPeso; 
                }
                if (cantidadCambiados == 2) {
                    return; 
                }
                
            }
       }
    }  
}

void Grafo::ImprimirConexiones(Vertice& vertice) {
    auto a = listaPrincipal->buscar(vertice); 
    std::cout << "Soy Arista " << a->getEtiqueta().etiqueta << "\nMis adyacentes son : " << std::endl; 
    
    int i =0;
    for (auto b  =a->getEtiqueta().getlistaAdyacencia()->getPrimera() ; i < a->getEtiqueta().getlistaAdyacencia()->getContador(); i++)
    {
       std::cout << b->getEtiqueta().VAdyacente->etiqueta << std::endl;
       b = b->getSiguiente(); 
    }
}

#endif
