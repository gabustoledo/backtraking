#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../incl/listaEstado.h"
#include "../incl/backtraking.h"

void backtraking(int *basuraInicial, int *distancias, int subsidio, int centros, int incineradores, int *rutaOrigenOptima, int *rutaDestinoOptima, float *costoOptimo){
	
	// Lista de estados por revisar.
	listaEstado *abiertos;
	abiertos = (listaEstado *)malloc(sizeof(listaEstado));
	abiertos->inicio = NULL;
	abiertos->fin = NULL;
	abiertos->tamano = 0;

	// Lista de estados cerrados sin mas posibilidades.
	listaEstado *cerrados;
	cerrados = (listaEstado *)malloc(sizeof(listaEstado));
	cerrados->inicio = NULL;
	cerrados->fin = NULL;
	cerrados->tamano = 0;

	// Hay una cantidad de rutas maximas para que tenga sentido.
	int rutas = centros - incineradores;

	// Primer elemento de abiertos.
	insertarInicial(abiertos,basuraInicial,centros,rutas);

	// Datos optimos.
	float mejorCosto = (float)-1;
	int *mejorOrigen = (int*)malloc(sizeof(int)*rutas);
	int *mejorDestino = (int*)malloc(sizeof(int)*rutas);

	// Mientras hayan elementos por revisar.
	while(abiertos->tamano != 0){

		// Nodo que indica cual es el ultimo elemento de abiertos.
		nodoEstado *actual;
		actual = (nodoEstado *)malloc(sizeof(nodoEstado));
		obtener(abiertos,actual);

		// Nodo al cual se le haran modificaciones.
		nodoEstado *nuevo;
		nuevo = (nodoEstado *)malloc(sizeof(nodoEstado));
		obtener(abiertos,nuevo);

		// En el caso en que se tome el primer elemento de abiertos.
		if(nuevo->costo == (float)-1)
			nuevo->costo = (float)0;

		// Bucles anidados para hacer el movimiento de la basura entre dos centros de acopio.
		int salir = 0;
		for(int i=0 ; i<centros && salir==0 ; i++){
			// Si hay basura en aquel centro.
			if(nuevo->basura[i] != 0){
				for(int j=0 ; j<centros && salir==0 ; j++){
					// Si hay basura en aquel centro y es distinto del que ya se ha seleccionado.
					if((nuevo->basura[j] != 0) && i!=j){
						// Si el movimiento que se hara no esta en cerrados.
						if(!esta(cerrados,nuevo,i,j)){

							// Se realiza el calculo del costo.
							nuevo->costo += fabs(distancias[i] - distancias[j]) * nuevo->basura[i] * (1 - 1.0/subsidio);

							// La basura es movida.
							nuevo->basura[j] += nuevo->basura[i];
							nuevo->basura[i] = 0;

							// La nueva ruta es ingresada.
							for(int k=0 ; k<rutas ; k++){
								if(nuevo->rutaOrigen[k] == -1){
									nuevo->rutaOrigen[k] = i;
									nuevo->rutaDestino[k] = j;
									break;
								}
							}
							// Se indica que ya se debe salir de los bucles.
							salir = 1;
						}	
					}
				}
			}
		}

		// Se cuenta cuantos centros aun tienen basura.
		int contador = 0;
		for(int i=0 ; i<centros ; i++){
			if(nuevo->basura[i] != 0){
				contador++;
			}
		}


		if(iguales(actual,nuevo)){  // Si son iguales es debido a que no se le pudieron hacer mas cambios.
			// Es insertado en cerrados.
			insertar(cerrados,actual);
			// Se remueve de abiertos.
			remover(abiertos);
		}else if(contador > incineradores){ // En el caso en que aun no se llegue al valor esperado.
			// El nuevo es insertado en abiertos.
			insertar(abiertos,nuevo);
		}else if(((mejorCosto == (float)-1) || (nuevo->costo < mejorCosto)) && contador == incineradores){// En el caso de llegar a la cantidad esperada y ser un costo mejor que el anterior.
			// Los valor de los mejores son actualizados.
			mejorCosto = nuevo->costo;

			for(int i=0;i<rutas;i++){
				mejorOrigen[i] = nuevo->rutaOrigen[i];
				mejorDestino[i] = nuevo->rutaDestino[i];
			}
			// El nuevo es insertado en cerrados.
			insertar(cerrados,nuevo);
			for(int i=0;i<centros;i++)
				basuraInicial[i] = nuevo->basura[i];
		}else{
			// En el caso de no entrar en ninguna, es debido a que se llego al final, pero con un costo superior al mejor.
			// Por lo tanto se inserta en cerrados.
			insertar(cerrados,nuevo);
		}
	}

	// Son ingresados los valores en las variables de salida.
	*costoOptimo = mejorCosto;

	for(int i=0;i<rutas;i++){
		rutaOrigenOptima[i] = mejorOrigen[i];
		rutaDestinoOptima[i] = mejorDestino[i];
	}

	// Se libera toda la memoria de las dos listas.
	liberar(abiertos);
	liberar(cerrados);
}