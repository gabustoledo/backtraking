#include <stdio.h>
#include <stdlib.h>
#include "../incl/ficheros.h"

// Funcion que lee los datos de la primera linea.
void lecturaInicial(int *centros, int *incineradores, int *subsidio, char nombre[50]){

	// Se define el archivo y es abierto para leer.
	FILE *archivo;
	archivo = fopen(nombre,"r");

	if(archivo == NULL){
		printf("El archivo con nombre %s no pudo ser abierto.\n",nombre );
	}else{
		// Los valores son leidos y almacenados de inmediato en la variables correspondientes.
		fscanf(archivo, "%d %d %d", centros, incineradores, subsidio);
	}
	// Se cierra el archivo.
	fclose(archivo);
}

// Funcino que permite la lectura de las toneladas de basura y la distancia de cada centro de acopio.
void lecturaDetallada(int *distancias, int *basura, char nombre[50]){

	// El archivo es definico y abierto para leer.
	FILE *archivo;
	archivo = fopen(nombre,"r");

	if(archivo == NULL){
		printf("El archivo con nombre %s no pudo ser abierto.\n",nombre );
	}else{
		// Se lee la primera linea.
		int centros = 0;
		int aux1 = 0;
		int aux2 = 0;
		fscanf(archivo, "%d %d %d", &centros, &aux1, &aux2);

		// Por cada linea se lee la distancia y toneladas.
		for(int i=0; i<centros ; i++){
			int dist = 0;
			int ton = 0;
			fscanf(archivo, "%d", &dist);
			fscanf(archivo, "%d",  &ton);
			// Los valores son almacenados en los arreglos correspondientes.
			distancias[i] = dist;
			basura[i] = ton;
		}

	}
	// Archivo cerrado.
	fclose(archivo);
}

// Funcion para escribir el archivo de salida con la solucion.
void escritura(float costo, int *rutaOrigen, int *rutaDestino, int *basura, int *distancias, int rutas, int centros, char nombre[50]){
	
	// El archivo es definido y abierto para escribir.
	FILE *archivo;
	archivo = fopen(nombre,"w");

	// Para cada ruta.
	for(int i=0;i<rutas;i++){
		// Se obtienen los valores de origen y destino.
		int origen = rutaOrigen[i];
		int destino = rutaDestino[i];
		// Son escritos en ese orden en el archivo.
		fprintf(archivo, "%i -> %i\n" , distancias[origen],distancias[destino]);
	}

	// Por cada centro.
	for(int i=0; i<centros ; i++){
		// Se busca los centros que tienen basura.
		if(basura[i] != 0){
			// Se escribe que centro es y cuanta basura ha quedado en el.
			fprintf(archivo, "Centro %d: %d toneladas\n" ,distancias[i],basura[i] );
		}
	}

	// Por ultimo se escribe el costo que tendra esa ruta.
	fprintf(archivo, "Costo: %f\n\n" ,costo );

	// Finalmente el archivo es cerrado.
	fclose(archivo);
}