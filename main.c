#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "Map.h"
#include "list.h"
#include "funciones.h"

int main()
{   
    /*char *NomArchivo;
    printf("Ingrese el nombre del archivo: ");
    scanf("%s", NomArchivo);
    printf("nombre archivo = %s\n", NomArchivo);
    FILE *archivo = fopen(NomArchivo, "r");*/

    FILE *archivo = fopen("Archivoproductos.csv","r");

    if(archivo == NULL)
    {
        printf("No se pudo abrir el archivo");
        return(EXIT_FAILURE);
    }
    Almacen *inventario = crearInventario();
    ImprimirMenu(inventario, archivo);
    return 0;
}