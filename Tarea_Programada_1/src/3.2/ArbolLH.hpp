#ifndef ARBOLLH
#define ARBOLLH
#include "../2/Lista.h"
#include "Celda.h"
#include "NodoConcreto.hpp"

class ArbolLH{
	private:
		Lista<NodoConcreto> * listaPrincipal; 
		
	public:
		
/// @brief Crea un nuevo Arbol e inicializa su lista principal
/// @remarks Requiere que el arbol no este inicializado 
ArbolLH(){
	listaPrincipal = new Lista<NodoConcreto>;
	
}

/// @brief Elimina al arbol y su lista principal
/// @remarks Requiere que el arbol este inicializado
~ArbolLH(){
	for (Celda<NodoConcreto> * it = listaPrincipal->getPrimera(); it != nullptr; it = it->getSiguiente()){
		 delete it->getEtiqueta().getListaHijos();
	}

	delete listaPrincipal;									//listaPrincipal->										//listaPrincipal
} 

void Imprimir(){
	listaPrincipal->imprimir();
	
}

void ImprimirLP(){
	Celda<NodoConcreto> * actual = listaPrincipal->getPrimera();
	while(actual!=nullptr){
		std::cout<< "ELEMENTO : " << actual->getEtiqueta().getEtiqueta() << std::endl;
		actual = actual->getSiguiente();
	}
	
}

/// @brief Inserta un NodoConcreto en el arbol como raiz del mismo
/// @remarks Requiere que el arbol sea vacia  
void PonerRaiz(int etiqueta){
	NodoConcreto nuevoNodoConcreto = NodoConcreto(etiqueta); 
	Lista<NodoConcreto*> * lista = new Lista<NodoConcreto*>();

	nuevoNodoConcreto.listaHijos = lista; 
	listaPrincipal->insertarAlPrincipio(nuevoNodoConcreto);
}

/// @brief Agrega un hijo a un NodoConcreto alimentado como parametro 
/// @param  Un NodoConcreto padre y una etiqueta (entero)   
/// @remarks Requiere que el arbol este inicializado y padre no nulo 
/// @return El NodoConcreto agregado	
NodoConcreto* AgregarHijo(int etiqueta, NodoConcreto * NodoConcretoPadre) {
	
	NodoConcreto NodoConcretoNuevo(etiqueta); 
	NodoConcretoNuevo.listaHijos = new Lista<NodoConcreto*>();
	
	listaPrincipal->insertar(NodoConcretoNuevo);
	
	NodoConcreto* direccionInsertado =  listaPrincipal->getUltima()->getEtiqueta(4);
	
	NodoConcretoPadre->insertarEnLista(direccionInsertado);
	return direccionInsertado;
}

/// @brief Agrega un hijo a un NodoConcreto alimentado como parametro 
/// @param  Un NodoConcreto padre y una etiqueta (entero)   
/// @return El NodoConcreto agregado 
NodoConcreto* AgregarHijoMasDerecho(int etiqueta, NodoConcreto * NodoConcretoPadre){
	return AgregarHijo(etiqueta, NodoConcretoPadre);
}

/// @brief Borra una hoja del arbol  
/// @param  Un NodoConcreto hoja
/// @remarks Requiere que el arbol este inicializado y que el NodoConcreto alimentado como paramtero sea una hoja	
void BorrarHoja(NodoConcreto* borrado){
	//Lista<NodoConcreto*> *punteroALista = borrado->listaHijos; 
	for(Celda<NodoConcreto> * buffer1 = listaPrincipal->getPrimera(); buffer1!=nullptr; buffer1 = buffer1->getSiguiente()){
		
		int validez = buffer1->getEtiqueta().getListaHijos()->borrar(borrado); 
		
		if(validez==1){		//Si lo borre de secundarias voy a borrarlo a principal
			delete borrado->listaHijos;  
			listaPrincipal->borrar(*borrado); 
			return; 
		}
	}
}

 		
Lista<NodoConcreto>* GetLP(){
	return listaPrincipal;
}

/// @brief Agrega un hijo a un NodoConcreto alimentado como parametro 
/// @remarks Requiere que el arbol este inicializado y padre no nulo 	
NodoConcreto* Raiz()
 {
	
	return & listaPrincipal->getPrimera()->getEtiqueta(); 

}

/// @brief Devuelve el padre de un NodoConcreto alimentado como parametro 
/// @param  un NodoConcreto que sera agregado como hijo  
/// @remarks Requiere un arbol inicializado y que el NodoConcreto alimentado como parametro pertenezca al arbol 	
NodoConcreto* Padre(NodoConcreto * hijo){
	NodoConcreto * a;
	Celda<NodoConcreto> * actual = listaPrincipal->getPrimera();
	
	if(actual->getEtiqueta() == *hijo){ //Caso trivial, raiz
		return nullptr; 
	} else{
		while(actual!=nullptr){
			Celda<NodoConcreto*> * celdaHijos = actual->getEtiqueta().getListaHijos()->getPrimera();  //Apunta al primer indice de la lista de hijos si es que existe
			a = (celdaHijos->getEtiqueta());
			while(a!=nullptr){
				if(a->getEtiqueta() == hijo->getEtiqueta()){ //Significa que encontre a mi padre
					
					return & actual->getEtiqueta();
				} else{ //Sigo avanzando
					celdaHijos = celdaHijos->getSiguiente();
				}
				a = celdaHijos->getEtiqueta();
			}
			actual = actual->getSiguiente(); 	
		}
		return nullptr; //Si sali del while principal significa que no encontre padre
	}
	
}

/// @brief Agrega un hijo a un NodoConcreto alimentado como parametro 
/// @param  Un NodoConcreto padre y una etiqueta (entero)   
/// @remarks Requiere que el arbol este inicializado y padre no nulo 	
NodoConcreto* HijoMasIzquierdo(NodoConcreto* padre) {
	auto listaHijos = padre->getListaHijos();
	if (listaHijos != nullptr)
	{
		auto primerHijo = listaHijos->getPrimera();

		if (primerHijo != nullptr)
			return primerHijo->getEtiqueta();
	}
	
	return nullptr;
}

/// @brief Devuelve la etiqueta de un NodoConcreto
/// @param  Un NodoConcreto con la etiqueta   
/// @remarks Requiere que el NodoConcreto tenga una etiqueta	
int  Etiqueta(NodoConcreto* NodoConcreto){
	return NodoConcreto->getEtiqueta();
}

/// @brief modifica el valor de la etiqueta de un NodoConcreto
/// @param  Un NodoConcreto y un entero que sera etiqueta
/// @remarks Requiere que el NodoConcreto tenga un valor y que el valor nuevo no este en el arbol  	
void ModificaEtiqueta(int valorNuevo, NodoConcreto* NodoConcretoPadre){
	NodoConcretoPadre->setEtiqueta(valorNuevo);
}

/// @brief Devuelve el hermano derecho del NodoConcreto alimentado como parametro
/// @param  Un NodoConcreto del cual queremos saber el hermano   
/// @remarks Requiere que el arbol este inicializado y que el NodoConcreto sea parte del arbol	
/// @return Devuelve un puntero a NodoConcreto
NodoConcreto* HermanoDerecho(NodoConcreto* celdaParam){
	int contador = 0;
	Celda<NodoConcreto*> hermanoDerecho; 
	int terminado = 0;
	NodoConcreto * NodoConcretoDer = nullptr;
	int i =0;
	for(Celda<NodoConcreto> * buffer = listaPrincipal->getPrimera(); buffer!=nullptr; buffer = buffer->getSiguiente()){ //Busca a celdaParam en la lista de hijos
		
		int j =0;
		for(Celda<NodoConcreto*> * buffer2 = buffer->getEtiqueta().getListaHijos()->getPrimera(); buffer2!=nullptr; buffer2 = buffer2->getSiguiente()){
			
			NodoConcreto* a = (buffer2->getEtiqueta());
			
			if( a->getEtiqueta() == celdaParam->getEtiqueta()){
				
				if(buffer2->getSiguiente() != nullptr){
					NodoConcretoDer = buffer2->getSiguiente()->getEtiqueta();
					
					return NodoConcretoDer;
				} else{
					return nullptr;
				}
			}
		}
	}

	return nullptr;
}

/// @brief Devuelve la cantidad de NodoConcretos del arbol
/// @remarks Requiere que el arbol este inicializado 	
int NumNodoConcretos(){
	//Celda<NodoConcreto> * buffer = listaPrincipal->getPrimera();
	int contador = 0;
	for(Celda<NodoConcreto> * buffer = listaPrincipal->getPrimera(); buffer!=nullptr; buffer = buffer->getSiguiente()){
		++contador;
	}
	return contador;	
}

/// @brief metood retorna cuantos elementos hay en arbol
/// @return return cantidad de elementos en arbol
int NumNodos(){
	return listaPrincipal->getContador(); 
}
	
};
#endif
