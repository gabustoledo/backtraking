#ifndef ESTRUCTURAESTADO_H
#define ESTRUCTURAESTADO_H

typedef struct ElementoEstado {
	float costo;
	int *basura;       
	int centros;      // centros para saber el tamaño de "basuras".
	int *rutaOrigen;
	int *rutaDestino;
	int rutas;        // Rutas para saber cuantas rutas son las maximas.
	struct ElementoEstado *sgte;
}nodoEstado;

typedef struct ListaEstado {
	nodoEstado *inicio;
	nodoEstado *fin;
	int tamano;
}listaEstado;

#endif