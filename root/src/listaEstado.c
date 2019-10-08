#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../incl/listaEstado.h"

// Funcion que inserta el nodo ingresado al final de la lista.
void insertar(listaEstado *lista, nodoEstado *nuevo){
	if(lista->tamano == 0){
		// Al solo tener un elemento, inicio y fin apuntan al nuevo nodo.
		lista->inicio = nuevo;
		lista->fin = nuevo;
		lista->tamano++;
	}else{
		// Solo se modifica el ultimo elemento de la lista con el puntero al final.
		nodoEstado *ultimo;
		ultimo = lista->fin;
		ultimo->sgte = nuevo;
		lista->fin = nuevo;
		lista->tamano++;
	}
}

// Funcion que inserta un nodo con valor ingresados y con valores negativos.
void insertarInicial(listaEstado *lista, int *basura, int centros, int rutas){

	// La memoria es reservda para el nodo a ingresar.
	nodoEstado *nuevo;
	nuevo = (nodoEstado *) malloc (sizeof (nodoEstado));

	// Todos los atributos son inicializados.
	if(nuevo != NULL){
		// Costo negativo para indicar que aun no es calculado.
		nuevo->costo = (float)-1;

		// El arreglo de la basura es inicializado con lo que se ha ingresado.
		nuevo->basura = (int*)malloc(sizeof(int)*centros);
		for(int i=0; i<centros ; i++){
			nuevo->basura[i] = basura[i];
		}

		// Los valores de las rutas son -1 ya que aun no se ha hecho ninguna ruta.
		nuevo->rutaOrigen = (int*)malloc(sizeof(int)*rutas);
		nuevo->rutaDestino = (int*)malloc(sizeof(int)*rutas);
		for(int i=0; i<rutas ; i++){
			nuevo->rutaOrigen[i] = -1;
			nuevo->rutaDestino[i] = -1;
		}

		// Son definidos los valores ingresados.
		nuevo->centros = centros;
		nuevo->rutas = rutas;
		nuevo->sgte = NULL;

		// El nodo recien creado es insertado al final de la lista.
		if(lista->tamano == 0){     // Si no hay mas elementos.
			lista->inicio = nuevo;
			lista->fin = nuevo;
			lista->tamano++;
		}else{                      // Por si hay elementos, solo se modifica el final de la lista.
			nodoEstado *ultimo;
			ultimo = lista->fin;
			ultimo->sgte = nuevo;
			lista->fin = nuevo;
			lista->tamano++;
		}
	}
}

// Funcion para liberar el contenido de una lista.
void liberar(listaEstado *lista){
	// Mientras hayan elementos en la lista, se removeran cada uno.
	while(lista->tamano > 0){
		remover(lista);
	}
}

// Remueve el ultimo elemento de la lista
void remover(listaEstado *lista){
	// En el caso de solo tener un elemento, todo queda en NULL.
	if(lista->tamano == 1){
		// Se obtiene el elemento
		nodoEstado *ultimo;
		ultimo = lista->fin;

		// Los valores de la lista son redefinidos.
		lista->inicio = NULL;
		lista->fin = NULL;
		lista->tamano--;

		// El contenido del nodo el liberado.
		free(ultimo->basura);
		free(ultimo->rutaOrigen);
		free(ultimo->rutaDestino);
		free(ultimo);
	}else if(lista->tamano != 0){
		// Nodo para recorrer la lista hasta llegar al penultimo.
		nodoEstado *ultimo;
		nodoEstado *penultimo;

		// Se define de donde partiran.
		penultimo = lista->inicio;
		ultimo = lista->fin;

		// La lista es recorrida hasta llegar al penultimo.
		while(penultimo->sgte->sgte != NULL){
			penultimo = penultimo->sgte;
		}

		// Los valores de la lista son redefinidos.
		lista->fin = penultimo;
		lista->tamano--;

		// La memoria del ultimo elemento son liberados.
		free(ultimo->basura);
		free(ultimo->rutaOrigen);
		free(ultimo->rutaDestino);
		free(ultimo);
	}
}

// Funcion para obtener el ultimo elemento de la lista.
void obtener(listaEstado *lista, nodoEstado *nuevo){
	if(lista->tamano != 0){

		// Se crea un nodo auxiliar para obtener el ultimo elemento y copiarlo.
		nodoEstado *aux;
		aux = lista->fin;

		// El contenido de basura es copiado al nuevo elemento.
		nuevo->basura = (int*)malloc(sizeof(int)* aux->centros);
		for(int i=0; i<aux->centros ; i++){
			nuevo->basura[i] = aux->basura[i];
		}

		// Las rutas son copiadas.
		nuevo->rutaOrigen = (int*)malloc(sizeof(int)* aux->rutas);
		nuevo->rutaDestino = (int*)malloc(sizeof(int)* aux->rutas);
		for(int i=0; i<aux->rutas ; i++){
			nuevo->rutaOrigen[i] = aux->rutaOrigen[i];
			nuevo->rutaDestino[i] = aux->rutaDestino[i];
		}

		// Los valores son copiados.
		nuevo->centros = aux->centros;
		nuevo->costo = aux->costo;
		nuevo->rutas = aux->rutas;
		nuevo->sgte = NULL;
	}
}

// Funcion que nos indica si existe un nodo con la misma distribucion de basura.
bool esta(listaEstado *lista, nodoEstado *actual, int origen, int destino){
	// Arreglo que tendra la basura modificada, para ser buscada en la lista.
	int *basura;
	basura = (int*)malloc(sizeof(int)* actual->centros);

	// Los valores son pasados.
	for(int k=0 ; k<actual->centros ; k++){
		basura[k] = actual->basura[k];
	}

	// Se realiza el movimiento de basura indicado.
	basura[destino] += basura[origen];
	basura[origen] = 0;

	// El arreglo es buscado en la lista.
	if(lista->tamano != 0){
		// La lista se recorre.
		nodoEstado *aux = lista->inicio;
		while(aux != NULL){
			int flag = 0;

			for(int i=0; (i<aux->centros) && flag == 0; i++){
				if(aux->basura[i] != basura[i])// En caso de que sean distintas.
					flag = 1;
			}
			if(flag == 0){// Si permanece en 0 es debido a que existe un arreglo igual al buscado.
				return true;
			}
			aux = aux->sgte;
		}
	}
	return false;
}

// Funcion que comprueba si dos nodos tienen la misma distribucion de basura.
bool iguales(nodoEstado *primero, nodoEstado *segundo){
	// Se recorre el arreglo de la basura.
	for(int i=0;i<primero->centros;i++){
		if(primero->basura[i] != segundo->basura[i]) // En caso de que sean distintos de retorna false.
			return false;
	}
	return true;// Si se llega hasta aca es debido a que son iguales.
}