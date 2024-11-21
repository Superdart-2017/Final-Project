#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "grafos.h"
#include "Serializacion.h"
#include "cJSON.h"

/**
 * @brief Escribe el grafo en el archivo
 * 
 * @param g El grafo
 * @param archivo El archivo
 */
void Grafo_Serializar(Grafo* grafo, FILE* archivo) {
    assert(grafo);
    assert(archivo);

    fprintf( archivo, "{\n" );
    fprintf( archivo, "   \"nombre_ruta\": \"%s\",\n", grafo->nombre_ruta );
    fprintf( archivo, "   \"num_estaciones\": \"%d\",\n", grafo->num_estaciones );
    fprintf( archivo, "   \"estaciones\": [\n" );
    for (int i = 0; i < grafo->num_estaciones; i++) {
        if(i > 0) fprintf(archivo, ",\n" );
        fprintf(archivo, "\n");
        Estacion* estacion = grafo->estaciones[i];
        fprintf( archivo, "      {\n" );
        fprintf( archivo, "      \"id\": \"%d\",\n", estacion->id );
        fprintf( archivo, "      \"nombre\": \"%s\",\n", estacion->nombre);
        fprintf( archivo, "      \"num_conexiones\": \"%d\",\n", estacion->num_conexiones );
        fprintf( archivo, "      \"conexiones\": [\n" );
        for(int j = 0; j < estacion->num_conexiones; j++){
            if(j > 0) fprintf(archivo, ",\n" );
            
            // Buscar la estación de conexión por ID
            int id_conexion = estacion->conexiones[j];
            Estacion* conexion = NULL;
            for(int k = 0; k < grafo->num_estaciones; k++){
                if(grafo->estaciones[k]->id == id_conexion){
                    conexion = grafo->estaciones[k];
                    break;
                }
            }

            if(conexion != NULL){
                fprintf( archivo, "         { \"id\": \"%d\", \"nombre\": \"%s\" }", conexion->id, conexion->nombre);
            } else {
                fprintf( archivo, "         { \"id\": \"%d\", \"nombre\": \"Desconocido\" }", id_conexion);
            }
        }
        fprintf( archivo, "\n" );
        fprintf( archivo, "         ]\n" );
        fprintf( archivo, "      }" );
    }
    fprintf( archivo, "   \n   ]" );
    fprintf( archivo, "   \n}" );
}

/**
 * @brief Lee el grafo del archivo
 * 
 * @param archivo El archivo
 */

void Grafo_Deserializar(const char *filename) {
    // Leer el archivo JSON
    FILE *archivo = fopen(filename, "r");
    if (!archivo) {
        printf("Error al abrir el archivo\n");
        return;
    }

    fseek(archivo, 0, SEEK_END);
    long length = ftell(archivo);
    fseek(archivo, 0, SEEK_SET);

    char *data = (char *)malloc(length + 1);
    fread(data, 1, length, archivo);
    data[length] = '\0';
    fclose(archivo);

    // Parsear el JSON
    cJSON *json = cJSON_Parse(data);
    if (!json) {
        printf("Error al parsear JSON: %s\n", cJSON_GetErrorPtr());
        free(data);
        return;
    }

    // Leer datos principales del JSON
    const char *nombre_ruta = cJSON_GetObjectItem(json, "nombre_ruta")->valuestring;
    const char *num_estaciones = cJSON_GetObjectItem(json, "num_estaciones")->valuestring;

    printf("Ruta: %s\n", nombre_ruta);
    printf("Número de estaciones: %s\n", num_estaciones);

    // Procesar estaciones
    cJSON *estaciones = cJSON_GetObjectItem(json, "estaciones");
    cJSON *estacion;

    cJSON_ArrayForEach(estacion, estaciones) {
        const char *id = cJSON_GetObjectItem(estacion, "id")->valuestring;
        const char *nombre = cJSON_GetObjectItem(estacion, "nombre")->valuestring;
        const char *num_conexiones = cJSON_GetObjectItem(estacion, "num_conexiones")->valuestring;

        printf("Estación ID: %s, Nombre: %s, Número de conexiones: %s\n", id, nombre, num_conexiones);

        // Procesar conexiones
        cJSON *conexiones = cJSON_GetObjectItem(estacion, "conexiones");
        cJSON *conexion;

        printf("Conexiones:\n");
        cJSON_ArrayForEach(conexion, conexiones) {
            const char *conexion_id = cJSON_GetObjectItem(conexion, "id")->valuestring;
            const char *conexion_nombre = cJSON_GetObjectItem(conexion, "nombre")->valuestring;

            printf("   -> ID: %s, Nombre: %s\n", conexion_id, conexion_nombre);
        }
    }

    // Liberar memoria
    cJSON_Delete(json);
    free(data);
}
