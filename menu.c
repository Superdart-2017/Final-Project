
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>

#include "grafos.h"
#include "QuickSort.h"
#include "Busqueda_Binaria.h"
#include "Serializacion.h"

#define NUM_ESTACIONES 11

/**
 * @brief Funcion que desplega un menú con opciones
 * 
 * @param texto Es el mensaje que se desplegará al usuario
 * @param n Es el número de opciones que se pueden elegir
 * @return El número de la opción elegida
 */
int desplegarMenu (char texto[], int n){
    int opcion;
    do{
        printf("%s", texto);
        scanf("%d", &opcion);
        if(opcion < 1 || opcion > n){
            printf("Opcion invalida\n");
        }
    } while (opcion < 1 || opcion > n);
    return opcion;
}

//----------------------------------------------------------------------
//                     funcion Main
//----------------------------------------------------------------------


int main(){

    int opcion;
    Grafo* grafo = Crear_Grafo(NUM_ESTACIONES, "Ruta Pumabus");
    
    Estacion* estacion1 = Crear_Estacion(24, "Filosia y Letras");
    Estacion* estacion2 = Crear_Estacion(411, "Derecho");
    Estacion* estacion3 = Crear_Estacion(66, "Economia");
    Estacion* estacion4 = Crear_Estacion(350, "Medicina");
    Estacion* estacion5 = Crear_Estacion(410, "Odontologia");
    Estacion* estacion6 = Crear_Estacion(775, "Ingenieria");
    Estacion* estacion7 = Crear_Estacion(67, "Ciencias");
    Estacion* estacion8 = Crear_Estacion(27, "Psicología");
    Estacion* estacion9 = Crear_Estacion(777, "Arquitectura");
    Estacion* estacion10 = Crear_Estacion(77, "Contaduria y Administración");
    Estacion* estacion11 = Crear_Estacion(518, "Veterinaria y Zootecnia");

    Agregar_Estacion_Grafo(grafo, estacion1);
    Agregar_Estacion_Grafo(grafo, estacion2);
    Agregar_Estacion_Grafo(grafo, estacion3);
    Agregar_Estacion_Grafo(grafo, estacion4);
    Agregar_Estacion_Grafo(grafo, estacion5);
    Agregar_Estacion_Grafo(grafo, estacion6);
    Agregar_Estacion_Grafo(grafo, estacion7);
    Agregar_Estacion_Grafo(grafo, estacion8);
    Agregar_Estacion_Grafo(grafo, estacion9);
    Agregar_Estacion_Grafo(grafo, estacion10);
    Agregar_Estacion_Grafo(grafo, estacion11);

    Agregar_Conexion(estacion1, 27, 1);
    Agregar_Conexion(estacion1, 350, 1);
    Agregar_Conexion(estacion5, 775, 1);
    Agregar_Conexion(estacion8, 67, 1);
    Agregar_Conexion(estacion3, 67, 1);
    Agregar_Conexion(estacion6, 27, 1);
    Agregar_Conexion(estacion2, 410, 1);
    Agregar_Conexion(estacion3, 411, 1);
    Agregar_Conexion(estacion4, 66, 1);
    Agregar_Conexion(estacion5, 24, 1);
    Agregar_Conexion(estacion7, 350, 1);
    Agregar_Conexion(estacion9, 77, 1);
    Agregar_Conexion(estacion10, 518, 1);
    Agregar_Conexion(estacion1, 777, 1);
    Agregar_Conexion(estacion5, 77, 1);
    Agregar_Conexion(estacion6, 410, 1);
    Agregar_Conexion(estacion3, 518, 1);
    Agregar_Conexion(estacion11, 350, 1);
    Agregar_Conexion(estacion11, 24, 1);
    Agregar_Conexion(estacion11, 777, 1);

    int lista[NUM_ESTACIONES];

    for(int i = 0; i < NUM_ESTACIONES; i++){
        Estacion* Estacion = grafo->estaciones[i];

        lista[i] = Estacion->id;
    }

    quick_sort(lista, 0, NUM_ESTACIONES - 1);

    do{
        printf("\nProyecto Rutas Pumabus");
        printf("\n-------------------------------\n");
        opcion = desplegarMenu("\n1)Imprimir Grafo \n2)Buscar Estación\n3)Buscar Ruta\n4)Serializar Grafo\n5)Deserializar Grafo\n6)Salir\nOpcion: ",6);
        switch (opcion){
        case 1:
            printf("Imprimiendo el grafo\n");
            Grafo_Imprimir(grafo, 0);
            break;
        case 2:
            int num;
            printf("id de la estacion a buscar: ");
            scanf("%d", &num);
            printf("Buscando estación %d\n", num);
            binary_search_it(lista, NUM_ESTACIONES, num);
            if(binary_search_it(lista, NUM_ESTACIONES, num)){
                printf("Encontrado\n");
            }else {printf("No encontrado\n");}
            break;
        case 3:
            int id_origen, id_destino;
            printf("Ingrese el ID de la estación origen: ");
            scanf("%d", &id_origen);
            printf("Ingrese el ID de la estación destino: ");
            scanf("%d", &id_destino);
            Buscar_Ruta(grafo, id_origen, id_destino);
            break;
        case 4:
            FILE* archivo = fopen("Rutas_Pumabus.json", "w");
            if(!archivo){
                printf("Error al abrir el archivo");
                return 1;
            }
            printf("Serializando grafo\n");
            Grafo_Serializar(grafo, archivo);
            fclose(archivo);
            printf("Grafo serializado\n");
            break;
        case 5:
            printf("Ingrese el nombre del archivo a deserializar con el .json: ");
            char nombre[50];
            scanf("%s", nombre);
            printf("\nDeserializando grafo\n");
            Grafo_Deserializar(nombre);
            break;
        case 6:
            printf("Liberando memoria\n");
            Liberar_Grafo(grafo);
            printf("Grafo liberado\n");
            break;
        }
    } while (opcion != 6);
    return 0;
}
