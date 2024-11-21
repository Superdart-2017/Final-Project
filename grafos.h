#ifndef GRAFOS_H
#define GRAFOS_H

/**
 * @brief Estructura para los vertices
 */

typedef struct{
    int id;
    char nombre[50];
    int* conexiones;
    int num_conexiones;
}Estacion;

/**
 * @brief Estructura para el grafo
 */

typedef struct{
    Estacion** estaciones;
    int num_estaciones;
    char nombre_ruta[50];
}Grafo;

//parte Estaciones
Estacion* Crear_Estacion(int id, const char* nombre);
void Agregar_Conexion(Estacion* estacion, int id_destino, int peso);
int Buscar_Indice_Por_ID(Grafo* grafo, int id);
void Liberar_Estacion(Estacion* estacion);

//parte Grafos
Grafo* Crear_Grafo(int num_estaciones, const char* nombre_ruta);
void Agregar_Estacion_Grafo(Grafo *grafo, Estacion* estacion);
void Grafo_Imprimir(Grafo* grafo,  int depth);
void Conectar_Estaciones(Grafo *grafo, int origen, int destino, int peso);
void Buscar_Ruta(Grafo *grafo, int id_origen, int id_destino);
void Liberar_Grafo(Grafo *grafo);

#endif // GRAFOS_H