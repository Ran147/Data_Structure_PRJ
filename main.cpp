#include <iostream>
using namespace std;

//Estructura de clientes: Lista doble
struct Cliente{
    string  nombre;
    string apellido;
    int cedula;
    int edad;
    string direccion;

    //Enlace a la sublista simple de Negocio
    struct Negocio* listaSimpleNegocios;

    //Punteros
    Cliente * siguiente;
    Cliente * anterior;

    //Constructor
    Cliente(string nombre_, string apellido_, int cedula_, int edad_, string direccion_) {
        nombre = nombre_;
        apellido = apellido_;
        cedula = cedula_;
        edad = edad_;
        direccion = direccion_;

        siguiente = NULL;
        anterior = NULL;
        listaSimpleNegocios = NULL;
    }
}*listaClientes;


//Estructura de negocios: Lista simple
struct Negocio{
    int id;
    string nombre;
    string horario;
    string ubicacion;

    //Puntero de la sublista simple
    Negocio * sig;

    //Constructor
    Negocio(int id_, string nombre_, string horario_, string ubicacion_){
        id = id_;
        nombre = nombre_;
        horario = horario_;
        ubicacion = ubicacion_;

        sig = NULL;
    }
};

//Estructura Producto: Lista circular
struct Producto{
    string nombre;
    int precio;
    Producto* siguiente;
    Producto* anterior;

    struct Ingredientes* listaIngredientes; //sublista simple

    //Constructor
    Producto(string nombre_, int precio_){
        nombre = nombre_;
        precio = precio_;
        siguiente = NULL;
        anterior = NULL;
        listaIngredientes = NULL;
    }
};

//Estructura de ingregredientes: Lista simple
struct Ingredientes{
    string nombre;
    int cantidad;
    string unidad;

    Ingredientes * next;

    //Constructor
    Ingredientes(string nombrecito, int cantidad_, string unidad_){
        nombre = nombrecito;
        cantidad = cantidad_;
        unidad = unidad_;
        next = NULL;
    }

}*listaIngredientes;

//Estructura Inventario: lista simple
struct Inventario{
    int cantidad;

    //agregar enlace a ingfrediente y fecha de vencimiento
    Inventario(){

    }
};

//Estructura de ventas:
struct Venta {
    string fecha;
    int cantidadProducto;
    Producto* producto;
    Venta* next;

    Venta(string fechaVenta, int cantidad, Producto* prod) {
        fecha = fechaVenta;
        cantidadProducto = cantidad;
        producto = prod;
        next = NULL;
    }

}*listaVentas;

//MÉTODOS
//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
/*
 * insertarClienteOrdenado: Inserta un nuevo cliente en la lista ordenada por apellido y verifica si la cédula ya existe.
 * Parámetros:
 * - nombre: Nombre del cliente a insertar.
 * - apellido: Apellido del cliente a insertar.
 * - cedula: Cédula del cliente a insertar.
 * - edad: Edad del cliente a insertar.
 * - direccion: Dirección del cliente a insertar.
 * Si la cédula ya existe en la lista, imprime un mensaje de error y no inserta el cliente.
 */

void insertarClienteOrdenado(string nombre, string apellido, int cedula, int edad, string direccion) {
    // Verificar si la cédula ya existe en la lista
    for (Cliente* cliente = listaClientes; cliente != NULL; cliente = cliente->siguiente) {
        if (cliente->cedula == cedula) {
            cout << "Error: La cédula ya existe, no se puede insertar el cliente." << endl;
            return;
        }
    }

    // Crear el nuevo cliente
    Cliente* nuevoCliente = new Cliente(nombre, apellido, cedula, edad, direccion);

    // Caso base: si la lista de clientes está vacía o el nuevo cliente debe ir al principio
    if (listaClientes == NULL || apellido < listaClientes->apellido) {
        nuevoCliente->siguiente = listaClientes;
        if (listaClientes != NULL)
            listaClientes->anterior = nuevoCliente;
        listaClientes = nuevoCliente;
        return;
    }

    // Recorrer la lista para encontrar la posición de inserción
    Cliente* actual = listaClientes;
    while (actual->siguiente != NULL && actual->siguiente->apellido <= apellido) {
        if (actual->siguiente->apellido == apellido) {
            actual = actual->siguiente; // Moverse al siguiente cliente con el mismo apellido
        } else {
            break; // No hay más clientes con el mismo apellido
        }
    }

    // Insertar el nuevo cliente después del actual
    nuevoCliente->siguiente = actual->siguiente;
    if (actual->siguiente != NULL)
        actual->siguiente->anterior = nuevoCliente;
    actual->siguiente = nuevoCliente;
    nuevoCliente->anterior = actual;
}

/*
 * ordenarClientesPorApellido: Ordena la lista de clientes por apellido utilizando el método de ordenamiento burbuja.
 * Este método se encarga de intercambiar los clientes según su apellido hasta que la lista esté ordenada de forma ascendente.
 */

void ordenarClientesPorApellido() {
    // Método de ordenamiento burbuja para ordenar los clientes por apellido
    bool intercambio;
    do {
        intercambio = false;
        for (Cliente* cliente = listaClientes; cliente != NULL && cliente->siguiente != NULL; cliente = cliente->siguiente) {
            if (cliente->apellido > cliente->siguiente->apellido) {
                // Intercambiar los clientes
                Cliente* temp = cliente->siguiente;
                cliente->siguiente = temp->siguiente;
                if (temp->siguiente != NULL)
                    temp->siguiente->anterior = cliente;
                temp->anterior = cliente->anterior;
                temp->siguiente = cliente;
                if (cliente->anterior != NULL)
                    cliente->anterior->siguiente = temp;
                cliente->anterior = temp;
                if (cliente == listaClientes)
                    listaClientes = temp;
                intercambio = true;
            }
        }
    } while (intercambio);
}

/*
 * imprimirClientesOrdenadosPorApellido: Imprime la lista de clientes ordenada por apellido en la consola.
 * Este método recorre la lista de clientes y muestra el nombre, apellido, cédula, edad y dirección de cada cliente.
 */

void imprimirClientesOrdenadosPorApellido() {
    cout << "Lista de clientes ordenada por apellido:" << endl;
    for (Cliente* cliente = listaClientes; cliente != NULL; cliente = cliente->siguiente) {
        cout << "Nombre: " << cliente->nombre << " " << cliente->apellido << endl;
        cout << "Cedula: " << cliente->cedula << endl;
        cout << "Edad: " << cliente->edad << endl;
        cout << "Direccion: " << cliente->direccion << endl << endl;
    }
}

/*
Método: insertarIngrediente
Descripción: Este método permite agregar un nuevo ingrediente a la lista de ingredientes.
Parámetros:
    - nombre: Nombre del ingrediente a agregar.
    - cantidad: Cantidad del ingrediente a agregar.
    - unidad: Unidad de medida del ingrediente a agregar.
Retorno:
    - Ingredientes*: Puntero al inicio de la lista de ingredientes actualizada después de la inserción.
*/
Ingredientes* insertarIngrediente(string nombre, int cantidad, string unidad){
    // Crear un nuevo ingrediente
    Ingredientes* nuevo = new Ingredientes(nombre, cantidad, unidad);

    if(listaIngredientes == NULL){
        listaIngredientes = nuevo;
    }
    else{
        // Agregar el nuevo ingrediente al inicio de la lista
        nuevo->next = listaIngredientes;
        listaIngredientes = nuevo;
    }
    // Retornar el puntero al inicio de la lista actualizada
    return listaIngredientes;
}

int main() {

    return 0;
}
int main() {

    return 0;
}
