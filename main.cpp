#include <iostream>
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

int main() {

    return 0;
}
