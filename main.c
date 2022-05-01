#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "Map.h"
#include "list.h"
#include "funciones.h"

int main()
{   
    /*char *NombreArchivo;
    printf("Ingrese el nombre del archivo: ");
    scanf("%s", NombreArchivo);*/
    //FILE *archivo = fopen(NombreArchivo,"r");

    FILE *archivo = fopen("Archivo_100productos.csv","r");

    if(archivo == NULL)
    {
        printf("No se pudo abrir el archivo");
        return(EXIT_FAILURE);
    }
    Almacen *inventario = crearInventario();
    ImprimirMenu(inventario, archivo);
    return 0;
}