#include "ArbolLH.h"
/// @brief Crea un nuevo Arbol e inicializa su lista principal
/// @remarks Requiere que el arbol no este inicializado 
ArbolLH::ArbolLH(){
	listaPrincipal = new Lista<Nodo>;
	
}

/// @brief Elimina al arbol y su lista principal
/// @remarks Requiere que el arbol este inicializado
ArbolLH::~ArbolLH(){
	delete listaPrincipal;									//listaPrincipal->										//listaPrincipal
} 

void ArbolLH::imprimir(){
	
	listaPrincipal->imprimir();
	
}

void ArbolLH::imprimirLP(){
	Celda<Nodo> * actual = listaPrincipal->getPrimera();
	while(actual!=nullptr){
		std::cout<< "ELEMENTO : " << actual->getEtiqueta()->getEtiqueta() << std::endl;
		
		actual = actual->getSiguiente();
		
	}
	
}

/// @brief Inserta un nodo en el arbol como raiz del mismo
/// @remarks Requiere que el arbol sea vacia  
void ArbolLH::ponerRaiz(Nodo * nuevoNodo){
	listaPrincipal->insertarAlPrincipio(*nuevoNodo);
}

/// @brief Agrega un hijo a un nodo alimentado como parametro 
/// @param  Un nodo padre y una etiqueta (entero)   
/// @remarks Requiere que el arbol este inicializado y padre no nulo 
/// @return El nodo agregado	
Nodo* ArbolLH::agregarHijo(Nodo nodoPadre, int etiqueta){
	Nodo * nodoNuevo = new Nodo(etiqueta); 
	listaPrincipal->insertar(*nodoNuevo);
	nodoPadre.insertarEnLista(nodoNuevo); 
	return nodoNuevo;
}

/// @brief Agrega un hijo a un nodo alimentado como parametro 
/// @param  Un nodo padre y una etiqueta (entero)   
/// @return El nodo agregado 
Nodo* ArbolLH::agregarHijoMasDerecho(Nodo nodoPadre, int etiqueta){
	return agregarHijo(nodoPadre, etiqueta);
}

/// @brief Borra una hoja del arbol  
/// @param  Un nodo hoja
/// @remarks Requiere que el arbol este inicializado y que el nodo alimentado como paramtero sea una hoja	
void ArbolLH::borrarHoja(Nodo* borrado){
	for(Celda<Nodo> * buffer1= listaPrincipal->getPrimera(); buffer1!=nullptr; buffer1 = buffer1->getSiguiente()){
		int validez = buffer1->getEtiqueta()->getListaHijos()->borrar(borrado); 
		if(validez!=0){
			int valorBorrado = borrado->getEtiqueta(); 
			Nodo nodoBorrado = listaPrincipal->buscar(valorBorrado)->getEtiqueta(4); 
			listaPrincipal->borrar(listaPrincipal->buscar(borrado->getEtiqueta())->getEtiqueta(4)); 
			imprimir();
			return; 
		}
	}
}

 		
Lista<Nodo>* ArbolLH::getLP(){
	return listaPrincipal;
}

/// @brief Agrega un hijo a un nodo alimentado como parametro 
/// @remarks Requiere que el arbol este inicializado y padre no nulo 	
Nodo* ArbolLH::raiz() {
	return (listaPrincipal->getPrimera()->getEtiqueta()); 
}

/// @brief Devuelve el padre de un nodo alimentado como parametro 
/// @param  un nodo que sera agregado como hijo  
/// @remarks Requiere un arbol inicializado y que el nodo alimentado como parametro pertenezca al arbol 	
Nodo* ArbolLH::padre(Nodo * hijo){
	Nodo * a;
	Celda<Nodo> * actual = listaPrincipal->getPrimera();
	
	if(actual->getEtiqueta() == hijo){ //Caso trivial, raiz
		return nullptr; 
	} else{
		while(actual!=nullptr){
			Celda<Nodo*> * celdaHijos = actual->getEtiqueta()->getListaHijos()->getPrimera();  //Apunta al primer indice de la lista de hijos si es que existe
			a = *(celdaHijos->getEtiqueta());
			while(a!=nullptr){
				if(a->getEtiqueta() == hijo->getEtiqueta()){ //Significa que encontre a mi padre
					
					return actual->getEtiqueta();
				} else{ //Sigo avanzando
					celdaHijos = celdaHijos->getSiguiente();
				}
				a = *(celdaHijos->getEtiqueta());
			}
			actual = actual->getSiguiente(); 	
		}
		return nullptr; //Si sali del while principal significa que no encontre padre
	}
	
}

/// @brief Agrega un hijo a un nodo alimentado como parametro 
/// @param  Un nodo padre y una etiqueta (entero)   
/// @remarks Requiere que el arbol este inicializado y padre no nulo 	
Nodo* hijoMasIzquierdo(Nodo* padre){
	return padre->getListaHijos()->getPrimera()->getEtiqueta(4);
}

/// @brief Devuelve la etiqueta de un nodo
/// @param  Un nodo con la etiqueta   
/// @remarks Requiere que el nodo tenga una etiqueta	
int  etiqueta(Nodo* nodo){
	return nodo->getEtiqueta();
}

/// @brief modifica el valor de la etiqueta de un nodo
/// @param  Un nodo y un entero que sera etiqueta
/// @remarks Requiere que el nodo tenga un valor y que el valor nuevo no este en el arbol  	
void modificaEtiqueta(Nodo* nodo, int valorNuevo){
	nodo->setEtiqueta(valorNuevo);
}

/// @brief Devuelve el hermano derecho del nodo alimentado como parametro
/// @param  Un nodo del cual queremos saber el hermano   
/// @remarks Requiere que el arbol este inicializado y que el nodo sea parte del arbol	
/// @return Devuelve un puntero a Nodo
Nodo* ArbolLH::hermanoDerecho(Nodo* celdaParam){
	int contador = 0;
	Celda<Nodo*> hermanoDerecho; 
	int terminado = 0;
	Nodo * nodoDer = nullptr;
	int i =0;
	for(Celda<Nodo> * buffer = listaPrincipal->getPrimera(); buffer!=nullptr; buffer = buffer->getSiguiente()){ //Busca a celdaParam en la lista de hijos
		
		int j =0;
		for(Celda<Nodo*> * buffer2 = buffer->getEtiqueta()->getListaHijos()->getPrimera(); buffer2!=nullptr; buffer2 = buffer2->getSiguiente()){
			
			Nodo* a = (buffer2->getEtiqueta(4));
			
			if( a->getEtiqueta() == celdaParam->getEtiqueta()){
				
				if(buffer2->getSiguiente() != nullptr){
					nodoDer = buffer2->getSiguiente()->getEtiqueta(4);
					
					return nodoDer;
				} else{
					return nullptr;
				}
			}
		}
	}
}

/// @brief Devuelve la cantidad de nodos del arbol
/// @remarks Requiere que el arbol este inicializado 	
int ArbolLH::numNodos(){
	//Celda<Nodo> * buffer = listaPrincipal->getPrimera();
	int contador = 0;
	for(Celda<Nodo> * buffer = listaPrincipal->getPrimera(); buffer!=nullptr; buffer = buffer->getSiguiente()){
		++contador;
	}
	return contador;	
}
	