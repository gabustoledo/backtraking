#include <stdbool.h>
#include "estructuraEstado.h"

#ifndef LISTAEST_H
#define LISTAEST_H

void insertar(listaEstado *lista, nodoEstado *nuevo);
void insertarInicial(listaEstado *lista, int *basura, int centros, int rutas);
void liberar(listaEstado *lista);
void remover(listaEstado *lista);
void obtener(listaEstado *lista, nodoEstado *nuevo);
bool esta(listaEstado *lista, nodoEstado *actual, int origen, int destino);
bool iguales(nodoEstado *primero, nodoEstado *segundo);

#endif