#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "grafos.h"

#define NUM_ESTACIONES 11

//----------------------------------------------------------------------
//                           Parte Vertices: 
//----------------------------------------------------------------------

/**
 * @brief crea una nueva estacion
 * 
 * @param id el id de la estacion
 * @param nombre el nombre de la estacion
 */
Estacion* Crear_Estacion(int id, const char* nombre){
    Estacion* estacion = (Estacion*)malloc(sizeof(Estacion));
    if(estacion != NULL){
        estacion->id = id;
        strcpy(estacion->nombre, nombre);
        estacion->conexiones =  NULL;
        estacion->num_conexiones = 0;
    }
    return estacion;
}

/**
 * @brief agrega una conexion a la estacion
 * 
 * @param estacion la estacion a la que se agrega la conexion
 * @param destino el id de la conexion
 * @param peso el peso de la conexion
 * 
 */
void Agregar_Conexion(Estacion *estacion, int id_destino, int peso) {
    int* nueva_conexion = realloc(estacion->conexiones, (estacion->num_conexiones + 1) * sizeof(int));
    if (nueva_conexion == NULL) {
        printf("Error: No se pudo asignar memoria para conexiones.\n");
        return;
    }
    estacion->conexiones = nueva_conexion;
    estacion->conexiones[estacion->num_conexiones] = id_destino;
    estacion->num_conexiones++;
}

/**
 * @brief Encuentra el índice de una estación en el grafo por su ID.
 * 
 * @param grafo El grafo donde buscar.
 * @param id El ID de la estación.
 * 
 * @return El índice de la estación si se encuentra, -1 si no se encuentra.
 */
int Buscar_Indice_Por_ID(Grafo* grafo, int id) {
    for (int i = 0; i < grafo->num_estaciones; i++) {
        if (grafo->estaciones[i] != NULL && grafo->estaciones[i]->id == id) {
            return i;
        }
    }
    return -1; 
}

/**
 * @brief Libera la memoria de la estacion
 * 
 * @param estacion la estacion a liberar
 */
void Liberar_Estacion(Estacion* estacion){
    assert(estacion);
    free(estacion->conexiones);
    free(estacion);
    estacion = NULL;
}

//----------------------------------------------------------------------
//                           Parte Grafos: 
//----------------------------------------------------------------------

/**
 * @brief Crea un grafo nuevo
 * 
 * @param num_estaciones El numero de vertices que tendra el grafo
 * 
 * @return El grafo creado
 * 
 * @pre El numero de vertices debe ser mayor que cero
 */
Grafo* Crear_Grafo(int num_estaciones, const char* nombre_ruta){
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    if (grafo != NULL){
        grafo->num_estaciones = num_estaciones;
        strcpy(grafo->nombre_ruta, nombre_ruta);
        grafo->estaciones = (Estacion**)malloc(num_estaciones * sizeof(Estacion*));
        for (int i = 0; i < num_estaciones; i++) {
            grafo->estaciones[i] = NULL;
        }
        return grafo;
    }
    
}

/**
 * @brief Agrega una estacion al grafo
 * 
 * @param grafo el grafo al que se agrega la estacion
 * @param estacion la estacion a agregar
 */
void Agregar_Estacion_Grafo(Grafo* grafo, Estacion* estacion) {
    for (int i = 0; i < grafo->num_estaciones; i++) {
        if (grafo->estaciones[i] == NULL) {
            grafo->estaciones[i] = estacion;
            return;
        }
    }
    printf("Error: No se pudo agregar la estacion, el grafo está lleno.\n");
}

/**
 * @brief imprime el grafo
 * 
 * @param g El grafo
 * @param depth La profundidad del grafo
 */
void Grafo_Imprimir(Grafo* grafo, int depth){
    if (grafo == NULL || grafo->estaciones == NULL) {
        printf("Error: Grafo o estaciones no inicializados\n");
        return;
    }

    for( int i = 0; i < grafo->num_estaciones; i++){
        Estacion* estacion = grafo->estaciones[i];
        if (estacion == NULL) {
            printf("Error: Estacion %d no inicializada\n", i);
            continue;
        }

        printf("[%d]%d (%s)=> ", i, estacion->id, estacion->nombre);
    
        if(estacion->conexiones > 0 && estacion->conexiones != NULL){
            for(int j = 0; j < estacion->num_conexiones; j++){
                int id_conexion = estacion->conexiones[j];
                Estacion* conexion = NULL;

                //Buscar la estación de conexión por ID
                for(int k = 0; k < grafo-> num_estaciones; k++){
                    if(grafo->estaciones[k]->id == id_conexion){
                        conexion = grafo->estaciones[k];
                        break;
                    }
                }

                if(conexion != NULL){
                    printf("%d (%s)", conexion->id, conexion->nombre);
                } else {
                printf("%d (Desconocido)", id_conexion);
                }

                if(j != estacion->num_conexiones - 1){
                    printf(",");
                }
            }
        } else {
            printf(" Nil");
        }
        printf("\n");
    }
}

/**
 * @brief conecta dos estaciones
 * 
 * @param grafo El grafo
 * @param origen el id de la estacion origen
 * @param destino el id de la estacion destino
 * @param peso el peso de la conexion
 */
void Conectar_Estaciones(Grafo *grafo, int origen, int destino, int peso){
    assert(grafo);
    Agregar_Conexion(grafo->estaciones[origen], destino, peso);
    Agregar_Conexion(grafo->estaciones[destino], origen, peso);
}

/**
 * @brief Busca una ruta entre dos estaciones en el grafo utilizando BFS
 * 
 * @param grafo El grafo
 * @param id_origen El id de la estación origen
 * @param id_destino El id de la estación destino
 */
void Buscar_Ruta(Grafo *grafo, int id_origen, int id_destino) {
    assert(grafo);

    // Encuentra los índices de las estaciones por sus IDs
    int indice_origen = Buscar_Indice_Por_ID(grafo, id_origen);
    int indice_destino = Buscar_Indice_Por_ID(grafo, id_destino);

    if (indice_origen == -1 || indice_destino == -1) {
        printf("Estacion no valida\n");
        return;
    }

    Estacion *origen = grafo->estaciones[indice_origen];
    Estacion *destino = grafo->estaciones[indice_destino];

    // Algoritmo BFS (igual que antes)
    bool* visitado = (bool*)calloc(grafo->num_estaciones, sizeof(bool));
    int* cola = (int*)malloc(grafo->num_estaciones * sizeof(int));
    int* predecesor = (int*)malloc(grafo->num_estaciones * sizeof(int));
    
    int front = 0, rear = 0;
    cola[rear++] = indice_origen;
    visitado[indice_origen] = true;
    predecesor[indice_origen] = -1;

    while (front < rear) {
        int actual = cola[front++];
        Estacion *est_actual = grafo->estaciones[actual];

        if (actual == indice_destino) {
            printf("Ruta encontrada: ");
            int recorrido[NUM_ESTACIONES];
            int contador = 0;
            for (int v = indice_destino; v != -1; v = predecesor[v]) {
                recorrido[contador++] = v;
            }
            for (int i = contador - 1; i >= 0; i--) {
                printf("%d ", grafo->estaciones[recorrido[i]]->id);
            }
            printf("\n");
            free(visitado);
            free(cola);
            free(predecesor);
            return;
        }

        for (int i = 0; i < est_actual->num_conexiones; i++) {
            int vecino = Buscar_Indice_Por_ID(grafo, est_actual->conexiones[i]);
            if (!visitado[vecino]) {
                cola[rear++] = vecino;
                visitado[vecino] = true;
                predecesor[vecino] = actual;
            }
        }
    }

    printf("No hay ruta entre %d y %d\n", id_origen, id_destino);
    free(visitado);
    free(cola);
    free(predecesor);
}

/**
 * @brief Libera la memoria del grafo
 * 
 * @param grafo el grafo
 */
void Liberar_Grafo(Grafo *grafo){
    assert(grafo);
    for(int i = 0; i < grafo->num_estaciones; i++){
        Liberar_Estacion(grafo->estaciones[i]);
    }
    free(grafo->estaciones);
    free(grafo);
    grafo = NULL;
}