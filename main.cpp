#include <iostream>
#include <string>
using namespace std;

struct Ingredientes{
    string nombre;
    int cantidad;
    string unidad;
    Ingredientes * next;
    Ingredientes(string nombrecito, int cantida, string unida){
        nombre = nombrecito;
        cantidad = cantidad;
        unidad = unidad;
        next = NULL;
    }
}* first_ingridient;
Ingredientes * insertarIngrediente(string nombre, int cantidad, string unidad){
    Ingredientes * nuevo = new Ingredientes(nombre, cantidad, unidad);
    if(first_ingridient == NULL){
        first_ingridient= nuevo;
    }
    else{
        nuevo->next = first_ingridient;
        first_ingridient= nuevo;
    }
    return first_ingridient;
}

struct Producto {
    string nombre;
    float precio;
    Ingredientes *ingredientes;
    Producto *next;

    Producto(string nombreProd, float precioProd) {
        nombre = nombreProd;
        precio = precioProd;
        ingredientes = NULL;
        next = NULL;
    }

    void agregarIngrediente(string nombre, int cantidad, string unidad) {
        Ingredientes *nuevoIngrediente = new Ingredientes(nombre, cantidad, unidad);
        if (ingredientes == NULL) {
            ingredientes = nuevoIngrediente;
        } else {
            Ingredientes *temp = ingredientes;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = nuevoIngrediente;
        }
    }
};


struct Cliente {
    string name;
    string lastname;
    int id;
    string address;


    string* restaurantes;
    int numRestaurantes;


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
    };

    Venta* ventas;


    struct Inventario {
        Producto* producto;
        int cantidad;
        string fechaVencimiento;
        Inventario* next;

        Inventario(Producto* prod, int cant, string fecha) {
            producto = prod;
            cantidad = cant;
            fechaVencimiento = fecha;
            next = NULL;
        }
    };

    Inventario* inventario;

    // Puntero al siguiente cliente de la lista
    Cliente* next;

    // Constructor de cliente
    Cliente(string nom, string apellido, int cedula, string direccion) {
        name = nom;
        lastname = apellido;
        id = cedula;
        address = direccion;
        restaurantes = NULL;
        numRestaurantes = 0;
        ventas = NULL;
        inventario = NULL;
        next = NULL;
    }

    // Función para agregar un producto al inventario del cliente
    void agregarProductoInventario(Producto* producto, int cantidad, string fechaVencimiento) {
        Inventario* nuevoProducto = new Inventario(producto, cantidad, fechaVencimiento);
        if (inventario == NULL) {
            inventario = nuevoProducto;
        } else {
            nuevoProducto->next = inventario;
            inventario = nuevoProducto;
        }
    }
}*listaClientes;


// Función para insertar una venta en la lista circular de ventas
void insertarVenta(Cliente* cliente, string fechaVenta, int cantidad, Producto* producto) {
    Cliente::Venta* nuevaVenta = new Cliente::Venta(fechaVenta, cantidad, producto);

    // Si la lista de ventas del cliente está vacía, se asigna la nueva venta
    if (cliente->ventas == NULL) {
        cliente->ventas = nuevaVenta;
        nuevaVenta->next = nuevaVenta;
    } else {
        nuevaVenta->next = cliente->ventas->next;
        cliente->ventas->next = nuevaVenta;
        cliente->ventas = nuevaVenta;
    }
}

// Función para insertar un restaurante en la lista de restaurantes de un cliente.
void insertarRestaurante(Cliente* cliente, string nombreRestaurante, string identificacion, string horario, string ubicacion) {
    string restaurante = identificacion + ";" + nombreRestaurante + ";" + horario + ";" + ubicacion;

    // Si la lista de restaurantes del cliente está vacía, se asigna el nuevo restaurante.
    if (cliente->restaurantes == NULL) {
        cliente->restaurantes = new string(restaurante);
        cliente->numRestaurantes++;
    } else {
        // Busca si el restaurante ya está en la lista del cliente.
        bool encontrado = false;
        for (int i = 0; i < cliente->numRestaurantes; ++i) {
            if (*(cliente->restaurantes + i) == restaurante) {
                encontrado = true;
                break;
            }
        }
        // Si no esta se agrega.
        if (!encontrado) {
            string* nuevoRestaurante = new string[cliente->numRestaurantes + 1];
            for (int i = 0; i < cliente->numRestaurantes; ++i) {
                nuevoRestaurante[i] = cliente->restaurantes[i];
            }
            nuevoRestaurante[cliente->numRestaurantes] = restaurante;
            delete[] cliente->restaurantes;
            cliente->restaurantes = nuevoRestaurante;
            cliente->numRestaurantes++;
        }
    }
}

//Inserta el cliente en la lista por orden de alfabeto.
Cliente* insertarClienteOrdenado(string nom, string apellido, int cedula, string direccion) {
    Cliente* nuevoCliente = new Cliente(nom, apellido, cedula, direccion);

    // si la lista esta vacía o el nuevo cliente va antes del primero en la lista.
    if (listaClientes == NULL || apellido < listaClientes->lastname) {
        nuevoCliente->next = listaClientes;
        listaClientes = nuevoCliente;
    } else {
        Cliente* actual = listaClientes;
        while (actual->next != NULL && apellido > actual->lastname) {
            actual = actual->next;
        }
        // Inserta el nuevo cliente en la posición correcta según el alfabeto.
        nuevoCliente->next = actual->next;
        actual->next = nuevoCliente;
    }

    return listaClientes;
}

int main() {

    return 0;
}
