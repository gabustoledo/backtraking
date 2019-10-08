#ifndef FICHEROS_H
#define FICHEROS_H

void lecturaInicial(int *centros, int *incineradores, int *subsidio, char nombre[50]);
void lecturaDetallada(int *distancias, int *basura, char nombre[50]);
void escritura(float costo, int *rutaOrigen, int *rutaDestino, int *basura, int *distancias, int rutas, int centros, char nombre[50]);

#endif