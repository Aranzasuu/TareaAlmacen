#ifndef funciones_h
#define funciones_h

typedef struct Almacen
{
    Map *Nombre;
    Map *Marca;
    Map *Tipo;
    List *Carritos;  // lista de todos los carritos
}Almacen;

typedef struct Producto
{
    char *Nombre;
    char *Marca;
    char *Tipo;
    size_t stock, precio;
    size_t cantCompra;
}Producto;

typedef struct Carrito
{
    char *nombre;
    List *compras;
    int total;    // monto total de la compra
    int cantidad; // cantidad de productos en le carrito

} Carrito;

int is_equal_string(void * key1, void * key2);

Almacen *crearInventario();

void ImprimirMenu(Almacen *inventario, FILE *archivo);

const char *get_csv_field (char * tmp, int k);

void importar(FILE *archivo, Almacen* inventario);

Producto* crearProducto();

size_t numero(const char *num);

void agregarProductoImportar(Almacen *inventario, Producto *AuxProd);

void agregarProducto(Almacen *inventario);

void mostrarProducto(Producto *prod);

void BuscarPorMarca(Map *mapMarca);

void BuscarPorTipo(Map *mapTipo);

void BuscarPorNombre(Map *mapNom);

void ImprimirProductos(Map *Nombres);

void agregarAlCarrito(Map *MapNom, List *Carritos);

void mostrarCarritos(List *carritos);

void EliminarDelCarrito(List* carritos);

void ConcretarCompra(Map* nombre, List* carritos);

void mostrarProdCarrito(List *auxCarrito, Map *nombre);

void exportar(Map *mapNom);

#endif