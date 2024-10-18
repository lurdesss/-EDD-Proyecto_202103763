#include "listasimpleamigos.h"
#include <iostream>

ListaSimpleAmigos::ListaSimpleAmigos() : cabeza(nullptr) {}

ListaSimpleAmigos::~ListaSimpleAmigos() {
    NodoAmigos* actual = cabeza;
    while (actual != nullptr) {
        NodoAmigos* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void ListaSimpleAmigos::agregarAmigo(const std::string& correo) {
    NodoAmigos* nuevoNodo = new NodoAmigos(correo);
    if (cabeza == nullptr) {
        cabeza = nuevoNodo;
    } else {
        NodoAmigos* actual = cabeza;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
    }
}

void ListaSimpleAmigos::mostrarAmigos() const {
    NodoAmigos* actual = cabeza;
    while (actual != nullptr) {
        std::cout << actual->correo << std::endl;
        actual = actual->siguiente;
    }
}

void ListaSimpleAmigos::limpiarLista() {
    NodoAmigos* actual = cabeza;
    while (actual != nullptr) {
        NodoAmigos* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    cabeza = nullptr;  // Asegúrate de que la cabeza apunte a nullptr después de limpiar
}
