#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../incl/listaEstado.h"
#include "../incl/backtraking.h"
#include "../incl/ficheros.h"

int main(){

	printf("\n\n############  COMENZANDO EJECUCION DEL PROGRAMA  ############\n\n\n");

//		  INGRESO DE LOS NOMBRES DEL ARCHIVO DE ENTRADA Y DE SALIDA.
//	#######################################################################
	char entrada[50];
	printf ("Introduzca nombre del archivo de entrada (sin txt): ");
   	scanf("%s", &entrada);
   	strcat(entrada,".txt");

   	char salida[50];
	printf ("Introduzca nombre del archivo de salida (sin txt): ");
   	scanf("%s", &salida);
   	strcat(salida,".txt");
//	########################################################################


//			INICIALIZACION DE VARIABLES Y ARREGLOS A UTILIZAR. 
   	int centros = 0;
   	int incineradores = 0;
   	int subsidio = 0;
   	int *basura;
   	int *distancias;
   	float costo = (float)0;


//		LECTURA DE LA CANTIDAD DE CENTROS, INCINERADORES Y EL SUBSIDIO.
   	lecturaInicial(&centros, &incineradores, &subsidio, entrada);

//		MEMORIA RESERVADA PARA LA BASURA Y LAS DISTANCIAS.
   	distancias = (int*)malloc(sizeof(int)* centros);
	basura = (int*)malloc(sizeof(int)* centros);

//		SON LEIDAS LAS DISTANCIAS Y CANTIDAD DE BASURA.
   	lecturaDetallada(distancias, basura, entrada);

//		ES RESERVADA LA MEMORIA PARA LA CANTIDAD MAXIMA DE MOVIMIENTOS.
   	// La cantidad de rutas debe ser asi ya que o se dejan centros con basura o se mueve mas basura de la necesaria.
   	int rutas = centros - incineradores;

   	int *rutaOrigen = (int*)malloc(sizeof(int)*rutas);
	for(int i=0; i<rutas ; i++){
		rutaOrigen[i] = -1;
	}

	int *rutaDestino = (int*)malloc(sizeof(int)*rutas);
	for(int i=0; i<rutas ; i++){
		rutaDestino[i] = -1;
	}

//		SE REALIZA EL BACKTRAKING PARA ENCONTRAR MEJOR RUTA A SEGUIR.
	backtraking(basura, distancias, subsidio, centros, incineradores, rutaOrigen, rutaDestino, &costo);

//		EL ARCHIVO ES ESCRITO CON LA RUTA Y COSTO MEJORES. 
	escritura(costo, rutaOrigen, rutaDestino, basura, distancias, rutas, centros, salida);

	printf("\n\n\n############  EJECUCION DEL PROGRAMA FINALIZADA  ############\n\n\n");

	return 0;
}