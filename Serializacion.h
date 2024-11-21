#ifndef SERIALIZACION_H
#define SERIALIZACION_H

#include "grafos.h"

void Grafo_Serializar(Grafo* grafo, FILE* archivo);

void Grafo_Deserializar(const char *filename);

#endif // SERIALIZACION_H