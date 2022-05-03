#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include "Map.h"
#include "funciones.h"

const char *get_csv_field (char * tmp, int k)
{
    int open_mark = 0;
    char *ret = (char *) malloc (150 * sizeof(char));
    int ini_i = 0, i = 0, j = 0;
    while(tmp[i+1] != '\0')
    {
        if(tmp[i] == '\"')
        {
            open_mark = 1 - open_mark;
            if(open_mark) ini_i = i + 1;
            i++;
            continue;
        }
        if(open_mark || tmp[i] != ',')
        {
            if(k == j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }
        if(tmp[i] == ',')
        {
            if(k == j) 
            {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i + 1;
        }
        i++;
    }
    if(k == j)
    {
        i = i - 1;
        for (i; tmp[i] != '\0'; i++)
        {
            ret[i - ini_i] =  tmp[i];
        }
       ret[i - ini_i] = 0;
       return ret;
    }
    return NULL;
}

int is_equal_string(void * key1, void * key2) 
{
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

// int is_equal_int(void * key1, void * key2) 
// {
//     if(*(int*)key1 == *(int*)key2) return 1;
//     return 0;
// }

void ImprimirMenu(Almacen *inventario, FILE *archivo)
{
    int op, op2;

    do{
        printf("\nopcion 1. Importar\n");
        printf("opcion 2. Exportar\n");
        printf("opcion 3. Buscar productos\n");
        printf("opcion 4. Agregar producto\n");
        printf("opcion 5. Mostrar todos los productos\n");
        printf("opcion 6. Agregar al carrito\n");
        printf("opcion 7. Eliminar del carrito\n");
        printf("opcion 8. Concretar compra\n");
        printf("opcion 9. Mostrar carritos de compra\n");
        printf("opcion 10. Salir\n");
        scanf("%d", &op);

        while(op < 1 || op > 10)
        {
            printf("ingrese una opcion valida\n");
            scanf("%d", &op);
        }

        switch(op)
        {
            case 1:
                importar(archivo, inventario);
                break;
            case 2:
                exportar(inventario->Nombre);    // esto hay que arreglar
                break; 
            case 3:
                printf("\n\n\n\n\n-> opcion 1. Tipo\n");
                printf("-> opcion 2. Marca\n");
                printf("-> opcion 3. Nombre\n");
                scanf("%d", &op2);
                switch(op2)
                {
                    case 1:
                        BuscarPorTipo(inventario->Tipo);
                        break;
                    case 2:
                        BuscarPorMarca(inventario->Marca);
                        break;
                    case 3:
                        BuscarPorNombre(inventario->Nombre);
                        break;
                }
                break;
            case 4:
                agregarProducto(inventario);
                break;
            case 5:
                ImprimirProductos(inventario->Nombre);
                break;
            case 6:
                agregarAlCarrito(inventario->Nombre, inventario->Carritos);
                break;
            case 7:
                EliminarDelCarrito(inventario->Carritos);   // esto hay que arreglar
                break;
            case 8:
                ConcretarCompra(inventario->Nombre, inventario->Carritos);   // hay que revisar
                break;
            case 9:
                mostrarCarritos(inventario->Carritos);
                break;
            case 10:
                break;
        }
        printf("\n\n\n");
    } while(op > 0 && op < 10);
}

Almacen* crearInventario()
{
    Almacen* inventario = (Almacen*) malloc(sizeof(Almacen));
    inventario->Nombre = createMap(is_equal_string);
    inventario->Tipo = createMap(is_equal_string);
    inventario->Marca  = createMap(is_equal_string);
    inventario->Carritos = createList();
    
    return inventario;
}

Producto* crearProducto()
{
    Producto* productoUnitario = (Producto*) malloc(sizeof(Producto));
    productoUnitario->Nombre = (char*) malloc(sizeof(char)*50);
    productoUnitario->Tipo = (char*) malloc(sizeof(char)*50);
    productoUnitario->Marca = (char*) malloc(sizeof(char)*50);
    productoUnitario->precio = 0;
    productoUnitario->stock = 0;
    productoUnitario->cantCompra = 0;
    
    return productoUnitario;
}

void mostrarProducto(Producto *prod)
{
    printf("------------------------------------------------------\n");
    printf("   Nombre           ------>   %s\n", prod->Nombre);
    printf("   Marca            ------>   %s\n", prod->Marca);
    printf("   Tipo             ------>   %s\n", prod->Tipo);
    printf("   Stock disponible ------>   %zd\n", prod->stock);
    printf("   Precio           ------>   %zd\n", prod->precio);
    printf("------------------------------------------------------\n");
}

size_t numero(const char *num)
{
    char *digitos = (char *) malloc(sizeof(char *) * 10);
    strcpy(digitos, "0123456789");
    int i, k;
    size_t nuevo = 0;

    i = 0;
    while (num[i] != '\0')
    {
        k = 0;
        while (k != 10)
        {
            if (digitos[k] == num[i])
            {
                if (nuevo == 0)
                    nuevo = k;
                else
                {
                    if (k == 0)
                        nuevo *= 10;
                    else
                        nuevo = nuevo * 10 + k;
                }
                break;
            }
            k++;
        }
        i++;
    }
    return nuevo;
}

void importar(FILE *archivo, Almacen* inventario)
{
    int i;
    char linea[1024];

    while (fgets(linea, 1024, archivo) != NULL)
    {
        linea[strcspn(linea, "\n")] = 0;

        Producto* AuxProd = crearProducto();
        
        for (int i = 0; i < 5; i++)
        {
            const char* aux = get_csv_field(linea, i);

            switch (i)
            {
                case 0:
                    strcpy(AuxProd->Nombre, aux);
                    break;
                case 1:
                    strcpy(AuxProd->Marca, aux); 
                    break;
                case 2:
                    strcpy(AuxProd->Tipo, aux);
                    break;
                case 3:
                    AuxProd->stock = numero(aux);
                    break;
                case 4:
                    AuxProd->precio = numero(aux);
                    break;    
            }
        }
        agregarProductoImportar(inventario, AuxProd);
    }
    fclose(archivo);
    printf("Archivo importado!\n\n");
}

void agregarProductoImportar(Almacen *inventario, Producto *AuxProd){
    Producto* prod = searchMap(inventario->Nombre, AuxProd);

    if (prod != NULL)
        prod->stock++;
    else
        insertMap(inventario->Nombre, AuxProd->Nombre, AuxProd);

    List* ListaMarca = searchMap(inventario->Marca, AuxProd->Marca);

    if (ListaMarca != NULL)
        pushBack(ListaMarca, AuxProd);
    else
    {
        ListaMarca = createList();
        pushBack(ListaMarca, AuxProd);
        insertMap(inventario->Marca, AuxProd->Marca, ListaMarca);
    }
        
    List* ListaTipo = searchMap(inventario->Tipo, AuxProd->Tipo);

    if (ListaTipo != NULL)
        pushBack(ListaTipo, AuxProd);
    else
    {
        ListaTipo = createList();
        pushBack(ListaTipo, AuxProd);
        insertMap(inventario->Tipo, AuxProd->Tipo, ListaTipo);
    }
}

void agregarProducto(Almacen *inventario){

    Producto *AuxProd = crearProducto();
    char aux_nom[50], aux_marca[50], aux_tipo[50];

    printf("Ingrese el nombre del producto:\n");
    getchar();
    scanf("%[^\n]s", aux_nom);
    strcpy(AuxProd->Nombre, aux_nom);

    printf("Ingrese la marca del producto:\n");
    getchar();
    scanf("%[^\n]s", aux_marca);
    strcpy(AuxProd->Marca, aux_marca);

    printf("Ingrese el tipo de producto:\n");
    getchar();
    scanf("%[^\n]s", aux_tipo);
    strcpy(AuxProd->Tipo, aux_tipo);

    printf("Ingrese la cantidad de producto:\n");
    getchar();
    scanf("%zd", &(AuxProd->stock));
    
    printf("Ingrese el precio del producto:\n");
    getchar();
    scanf("%zd", &(AuxProd->precio));

    Producto* prod = searchMap(inventario->Nombre, AuxProd->Nombre);

    if (prod != NULL){
        prod->stock += AuxProd->stock;
    }   
    else
        insertMap(inventario->Nombre, AuxProd->Nombre, AuxProd);

    List* ListaMarca = searchMap(inventario->Marca, AuxProd->Marca);

    if (ListaMarca != NULL)
        pushBack(ListaMarca, AuxProd);
    else
    {
        ListaMarca = createList();
        pushBack(ListaMarca, AuxProd);
        insertMap(inventario->Marca, AuxProd->Marca, ListaMarca);
    }
        
    List* ListaTipo = searchMap(inventario->Tipo, AuxProd->Tipo);

    if (ListaTipo != NULL)
        pushBack(ListaTipo, AuxProd);
    else
    {
        ListaTipo = createList();
        pushBack(ListaTipo, AuxProd);
        insertMap(inventario->Tipo, AuxProd->Tipo, ListaTipo);
    }
}

void BuscarPorMarca(Map *mapMarca){
    printf("\nIngrese la marca del producto que desea buscar: ");
    char *marca = (char *) malloc(sizeof(char) * 35);
    getchar();
    scanf("%[^\n]s", marca);

    List *aux = searchMap(mapMarca, marca);
    if(aux == NULL){
        printf("No existen productos de esta marca");
        return;
    }

    Producto *aux2 = firstList(aux);

    if(aux2 == NULL){
        printf("No quedan productos de esta marca");
        return;
    }
    printf("Productos de la marca %s:\n------------------------------\n", marca);
    while(aux2 != NULL){
        mostrarProducto(aux2);
        aux2 = nextList(aux);
    }
}

void BuscarPorTipo(Map *mapTipo)
{
    printf("\nIngrese el Tipo de producto que desea buscar: ");
    char *tipo = (char *) malloc(sizeof(char) * 35);
    getchar();
    scanf("%[^\n]s", tipo);

    List *aux = searchMap(mapTipo, tipo);
    if(aux == NULL){
        printf("No existen productos de este tipo");
        return;
    }

    Producto *aux2 = firstList(aux);

    if(aux2 == NULL){
        printf("No quedan productos de este tipo");
        return;
    }
    printf("Productos del tipo %s:\n------------------------------\n", tipo);
    while(aux2 != NULL){
        mostrarProducto(aux2);
        aux2 = nextList(aux);
    }
}

void BuscarPorNombre(Map *mapNom)
{
    printf("\nIngrese el Nombre del producto que desea buscar: ");
    char *nombre = (char *)malloc(sizeof(char) * 35);
    getchar();
    scanf("%[^\n]s", nombre);

    Producto *aux = searchMap(mapNom, nombre);
    if (aux != NULL)
    {
        mostrarProducto(aux);
    }
    else
        printf("El producto ''%s'' no existe");
}

void ImprimirProductos(Map* MapNom){
    Producto* prod = firstMap(MapNom);
    while (prod != NULL)
    {
        mostrarProducto(prod);
        prod = nextMap(MapNom);
    }
}

void EliminarDelCarrito(List *carritos)
{
    printf("Se eliminara el ultimo elemento del siguiente carrito\n");
    printf("Ingrese nombre del carrito : ");

    char *nomCarrito = (char *)malloc(sizeof(char) * 50);
    getchar();
    scanf("%[^/n]s", nomCarrito);

    Carrito *auxCarrito = firstList(carritos);
    if (auxCarrito != NULL)
    {
        while (auxCarrito != NULL)
        {
            if (strcmp(auxCarrito->nombre, nomCarrito) == 0)
            {
                Producto *last = lastList(auxCarrito->compras);
                auxCarrito->cantidad -= last->cantCompra;
                auxCarrito->total -= last->precio * last->stock;
                popBack(auxCarrito->compras);
                // printf("Se eliminaron %d unidad/de de '%s' del carrito '%s'", last->stock, last->nombre, auxCarrito->nombre);
                return;
            }
            auxCarrito = nextList(carritos);
        }
        printf("No se encontro ningun carrito de nombre '%s'\n", nomCarrito);
    }
    else
    {
        printf("Aun no se ha creado ningun carrito\n");
    }
}

void mostrarCarritos(List *carritos)
{
    Carrito *carrito = firstList(carritos);
    if (carrito != NULL)
    {
        while (carrito != NULL)
        {
            printf("\n----------------------------------");
            printf("\nNombre : %s", carrito->nombre);
            printf("\nCantidad de productos : %d", carrito->cantidad);
            carrito = nextList(carritos);
        }
        printf("\n----------------------------------");
    }
    else
    {
        printf("\nAun no se a creado ningun carrito");
    }
}

Carrito *crearCarrito()
{
    Carrito *aux = (Carrito *)malloc(sizeof(Carrito));
    aux->compras = createList();
    aux->nombre = (char *)malloc(sizeof(char) * 50);
    aux->total = 0;
    aux->cantidad = 0;
}

void agregarAlCarrito(Map *nombre, List *carritos)
{
    printf("\nIngrese nombre del producto que desea agregar : ");
    char *prod = (char *)malloc(sizeof(char) * 50);
    getchar();
    scanf("%[^\n]s", prod);

    Producto *auxProd = searchMap(nombre, prod);
    if (auxProd == NULL)
    {
        printf("\nNo se encontro el producto ''%s''\n", prod);
        return;
    }

    printf("\nIngrese la cantidad productos que desea agregar : ");
    char *cant = (char *)malloc(sizeof(char) * 10);
    getchar();
    scanf("%[^\n]s", cant);
    if (numero(cant) > auxProd->stock)
    {
        printf("No hay stock suficiente");
        return;
    }

    printf("\nIngrese el nombre del carrito al que desea agregar los productos : ");
    char *carrito = (char *)malloc(sizeof(char) * 35);
    getchar();
    scanf("%[^\n]s", carrito);

    Carrito *auxCarrito = firstList(carritos);
    if (auxCarrito != NULL)
    {
        while (auxCarrito != NULL)
        {
            if (strcmp(auxCarrito->nombre, carrito) == 0)
            {
                Producto *cpyProd = crearProducto();
                strcpy(cpyProd->Nombre, auxProd->Nombre);
                strcpy(cpyProd->Marca, auxProd->Marca);
                strcpy(cpyProd->Tipo, auxProd->Tipo);
                cpyProd->stock = auxProd->stock;
                cpyProd->precio = auxProd->precio;
                cpyProd->cantCompra = numero(cant);

                auxCarrito->cantidad += numero(cant);
                auxCarrito->total += auxProd->precio * numero(cant);
                pushBack(auxCarrito->compras, cpyProd);
                // pushFront(carritos, auxCarrito);
                printf("Se agregaron %s unidad/es de '%s' al carrito '%s'\n", cant, cpyProd->Nombre, auxCarrito->nombre);
                return;
            }
            auxCarrito = nextList(carritos);
        }
    }
    else
    {
        auxCarrito = crearCarrito();
        strcpy(auxCarrito->nombre, carrito);

        Producto *cpyProd = crearProducto();
        strcpy(cpyProd->Nombre, auxProd->Nombre);
        strcpy(cpyProd->Marca, auxProd->Marca);
        strcpy(cpyProd->Tipo, auxProd->Tipo);
        cpyProd->stock = auxProd->stock;
        cpyProd->precio = auxProd->precio;
        cpyProd->cantCompra = numero(cant);

        auxCarrito->cantidad += numero(cant);
        auxCarrito->total += auxProd->precio * numero(cant);

        pushBack(auxCarrito->compras, cpyProd);
        pushBack(carritos, auxCarrito);
        printf("Se agregaron %s unidad/es de '%s' al carrito '%s'\n", cant, cpyProd->Nombre, auxCarrito->nombre);
        return;
    }

    auxCarrito = crearCarrito();
    strcpy(auxCarrito->nombre, carrito);

    Producto *cpyProd = crearProducto();
    strcpy(cpyProd->Nombre, auxProd->Nombre);
    strcpy(cpyProd->Marca, auxProd->Marca);
    strcpy(cpyProd->Tipo, auxProd->Tipo);
    cpyProd->stock = auxProd->stock;
    cpyProd->precio = auxProd->precio;
    cpyProd->cantCompra = numero(cant);

    auxCarrito->cantidad += numero(cant);
    auxCarrito->total += auxProd->precio * numero(cant);

    pushBack(auxCarrito->compras, cpyProd);
    pushBack(carritos, auxCarrito);
    printf("Se agregaron %s unidad/es de '%s' al carrito '%s'\n", cant, cpyProd->Nombre, auxCarrito->nombre);
}

void mostrarProdCarrito(Carrito *carrito, Map *nombre){
    Producto *aux = firstList(carrito->compras);
    Producto *buscado = searchMap(nombre, aux->Nombre);
    while(aux != NULL){
        printf("nombre producto: %s\n", aux->Nombre);
        printf("Cantidad a comprar: %zd\n\n", aux->cantCompra);
        if(buscado->stock < buscado->cantCompra){
            printf("No se pudo concretar la compra, ya que no hay la cantidad de producto que desea.\n");
            return;
        }
        aux = nextList(carrito->compras);
    }

    buscado->stock = (buscado->stock) - (aux->cantCompra);
    printf("\nCantidad de productos : %d", carrito->cantidad);
    printf("\n----------------------------------\n");
}


void ConcretarCompra(Map* nombre, List* carritos){
    char* nomCarrito = (char *)malloc(sizeof(char) * 50);
    getchar();
    printf("Ingrese el nombre del carrito: ");
    scanf("%[^\n]s", nomCarrito);
    //char producto;
    Carrito* auxCarrito = firstList(carritos);
    if (auxCarrito != NULL){
        while (auxCarrito != NULL)
        {
            if (strcmp(auxCarrito->nombre, nomCarrito) == 0){
                printf("Debe pagar el total de $ %d", auxCarrito->total);
                printf("\n----------------------------------\n");
                mostrarProdCarrito(auxCarrito, nombre);
                printf("\n----------------------------------\n");
                popCurrent(carritos);
                return;
            }
            auxCarrito = nextList(carritos);
        }

    }
    if (auxCarrito == NULL){
        printf("El carrito que desea pagar no existe");
        return;
    }
}

void exportar(Map *nombre){
    //FILE *exportFile = fopen("final.csv","w+");

    //if(exportFile == NULL){
    //    printf("No se pudo abrir el archivo\n");
    //    return(EXIT_FAILURE);
    //}

    //Producto *aux = firstList();
    //while(aux != NULL){

    //}
}

/*void exportar(Map *mapNom)
{
    char *linea;
    linea = (char *) malloc(sizeof(char) * 100000);
    strcpy(linea,"");
    FILE* exportFile = fopen("InventarioFinal.csv", "w+");
    Producto* prod = firstMap(mapNom);
    while (prod != NULL)
    {
        for (int i = 0; i < 5; i++)
        {
            switch (i)
            {
                case 0:
                    strcat(linea,prod->Nombre);
                    break;
                case 1:
                    strcat(linea,prod->Marca);
                    break;

                case 2: 
                    strcat(linea,prod ->Tipo);
                    break;

                case 3:
                    (char *) prod->stock;
                    //prod->stock = numero(linea);
                    strcat(linea, prod->stock);
                    printf("linea = %s\n", prod->stock);
                    break;
                case 4:
                    prod->precio = numero(linea);
                    break;
            }
            strcat(linea,",");
        }
        strcat(linea,"\n");
        prod = nextMap(mapNom);
    }
    fprintf(exportFile, "%s\n", linea);
    fclose(exportFile);
}*/