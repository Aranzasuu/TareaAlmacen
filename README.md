# TareaAlmacen

Estructuras:

1. Almacen:
    Map *Nombre = corresponde a un mapa que guarda la información según el nombre del producto, además de su respectiva información (nombre, marca, tipo, stock y precio).
    Map *Marca = corresponde a un mapa que guarda la información según la marca, donde cada key guarda los productos de esa respectiva marca.
    Map *Tipo = corresponde a un mapa que guarda la información según el tipo, donde cada key guarda los productos de ese respectivo tipo.
    List *Carritos = corresponde a una lista que guarda los carritos que cree el usuario.

2. Producto:
    char *Nombre = almacena el nombre del producto.
    char *Marca = almacena la marca del producto.
    char *Tipo = almacena el tipo de producto.
    size_t stock = almacena la cantidad de producto que existe.
    size_t precio = almacena el precio unitario del producto.
    size_t cantCompra = almacena la cantidad de producto que quiere comprar el usuario.

3. Carrito:
    char *nombre = almacena el nombre del carrito.
    List *compras = almacena la lista de productos que el usuario desea comprar.
    int total = almacena el total a pagar.
    int cantidad = almacena la cantidad total de productos en el carrito.

Instrucciones para correr el programa:

-> Primero abrimos el terminal, donde debemos escribir gcc main.c list.c funciones.c Map.c -o TareaAlmacen y luego escribir .\TareaAlmacen.exe para poder ejecutar el programa. Aquí viene el primer problema, se tuvo que poner directamente el nombre del archivo con los productos, ya que si leemos el nombre del archivo a leer, el programa no se ejecuta.

-> Luego de abrir el archivo y corroborar que se haya abierto exitosamente, nos aparecerá un menú con opciones, para poder trabajar con los productos debemos escribir "1" para poder importar el archivo y guardar la información en las respectivas variables descritas anteriormente.
    
    - Funcion importar: esta función recibe dos parámetros (el archivo FILE y el inventario de tipo almacén definidas en el main), a través de un ciclo while vamos leyendo línea por línea con la función fgets() hasta el EOF (NULL), creamos nuestra variable de tipo producto, donde guarda la información del producto leído, y a traves de la función agregarProductoImportar() guardamos cada producto en el almacen.

        - Función agregarProductoImportar: primero recorremos el mapa de nombre, donde si el producto ya existe, aumenta el stock, en caso contrario, se inserta al mapa. Luego recorremos el mapa de marca, nos aseguramos si existe el producto, en caso de que eso suceda insertamos el producto al final de la lista, en caso contrario se crea la lista (ListaMarca) y la insertamos al mapa. Finalmente recorremos el mapa de tipo, nos aseguramos que exista, en caso de que eso suceda, insertamos el producto al final de la lista, en caso contario creamos la lista (ListaTipo) y la insertamos en el mapa.

        - crearInventario(): dimensiona cada variable de la struct Almacen.

-> Ahora podemos realizar las demás operaciones descritas en el menú.

    - opción 2. Exportar: nos crea el archivo con el nombre de "InventarioFinal.csv" vacio, luego se va rellenando con la información guardada y cambiada en el proceso, el único detalle es que el stock y el precio al ser de tipo entero, no se guarda en el archivo, por lo que quedan comas pegadas sin información.

    - opción 3. Buscar productos: en esta opción podemos buscar un producto a través del nombre, marca y tipo.

        - opción 1. BuscarPorTipo: se le pedirá al usuario que ingrese el tipo de producto que está buscando, se asegura que exista, en caso que no, se imprimirá un mensaje correspondiente ("No existen productos de este tipo") y se terminará la búsqueda, en caso contrario, se seguirá en la función, si no hay elementos de ese tipo, se imprimirá un mensaje ("No quedan productos de este tipo") y se terminará la búsqueda, finalmente si existe el tipo y existen productos, se utilizará el mapa de tipo para recorrer la lista e imprimir los productos y su respectiva información.

        - opción 2. BuscarPorMarca: se le pedirá al usuario que ingrese la marca de producto que está buscando, se asegura que exista, en caso que no, se imprimirá un mensaje correspondiente ("No existen productos de esta marca") y se terminará la búsqueda, en caso contrario, se seguirá en la función, si no hay elementos con esta marca, se imprimirá un mensaje ("No quedan productos de esta marca") y se terminará la búsqueda, finalmente si existe la marca y existen productos, se utilizará el mapa de marca para recorrer la lista e imprimir los productos y su respectiva información.

        - opción 3. BuscarPorNombre: se le pedirá al usuario que ingrese el nombre de producto que está buscando, se asegura que exista, en caso que no, se imprimirá un mensaje correspondiente ("El producto ____ no existe") y se terminará la búsqueda, en caso contrario, se seguirá en la función, y se imprimirá la información respectiva de ese producto.
    
    - opción 4. Agregar Producto: se le pedirá al usuario que ingrese toda la información correspondiente a ingresar, en caso que este exista, sólo se aumenta el stock con la cantidad ingresada, en caso contrario se ingresara la nueva información en los mapas de nombre, tipo y marca.

    - opción 5. Mostrar todos los productos: a través del mapa nombre, se va recorriendo la lista y se va imprimiendo la información de cada producto en un ciclo while hasta llegar al final.

    - opción 6. Agregar al carrito: se le pide al usuario que ingrese el nombre del producto que desea agregar, se asegura que este produtco exista, en caso que si, se pide que ingrese la cantidad comprar, se asegura que haya stock suficiente para poder realizar la compra, si es que hay suficiente stock, se pide que ingrese el nombre del carrito al cual agregar el producto. 

    - opción 7. Eliminar del carrito: intentamos dos funciones, en una el programa se cae, y la otra no elimina. La idea es eliminar el último producto ingresado al carrito, por lo que se pide el nombre del carrito, luego se recorre la lista de carritos buscando el carrito, si existe, con la función popBack() se elimina el último. Si probamos el mismo código en otro computador si funciona.

    - opción 8. Concretar compra: hay algunos detalles que el porgrama no funciona, como por ejemplo, no asegura que si se completa la compra de un carrito y el producto se agregó a otro carrito, exista stock para vender. Se imprime el monto a pagar y los productos (nombre y cantidad) y finalmente se elimina el carrito.

    - opción 9. Mostrar carritos de compra: recorre la lista de carritos y va imprimiendo el nombre del carrito y la cantidad de productos guardados.

    - opción 10. termina la ejecución del programa.

Puntos por cada integrante:

-> Catalina Araya: +0  puntual y realiza su parte.
    
-> Luis Castro: +0  puntual, buen ambiente.

-> Rocío Arriagada: +0  puntual, buen desempeño.

-> Nicolás Mery: +0 puntual, realiza sus tareas.

-> Aranzasu Larraín: +0  puntual, da ideas.