#include "listasugerencias.h"
#include <iostream>
#include <unordered_set>

ListaSugerencias::ListaSugerencias() : cabeza(nullptr) {}

ListaSugerencias::~ListaSugerencias() {
    NodoSugerencias* actual = cabeza;
    while (actual) {
        NodoSugerencias* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void ListaSugerencias::agregarSugerencia(int frecuencia, const std::string& usuario) {
    NodoSugerencias* nuevoNodo = new NodoSugerencias(frecuencia, usuario);
    nuevoNodo->siguiente = cabeza;
    cabeza = nuevoNodo;
}

void ListaSugerencias::ordenarPorFrecuencia() {
    if (!cabeza || !cabeza->siguiente) return;

    NodoSugerencias* actual = cabeza;
    bool cambio;

    do {
        cambio = false;
        actual = cabeza;
        while (actual->siguiente) {
            if (actual->frecuencia < actual->siguiente->frecuencia) {
                std::swap(actual->frecuencia, actual->siguiente->frecuencia);
                std::swap(actual->usuario, actual->siguiente->usuario);
                cambio = true;
            }
            actual = actual->siguiente;
        }
    } while (cambio);
}

void ListaSugerencias::filtrarUsuariosDuplicados() {
    if (!cabeza) return;

    std::unordered_set<std::string> usuariosEncontrados;
    NodoSugerencias* actual = cabeza;
    NodoSugerencias* previo = nullptr;

    while (actual) {
        if (usuariosEncontrados.find(actual->usuario) != usuariosEncontrados.end()) {
            // Si el usuario ya fue agregado, eliminamos el nodo actual
            NodoSugerencias* nodoAEliminar = actual;
            actual = actual->siguiente;
            if (previo) {
                previo->siguiente = actual;
            } else {
                cabeza = actual;
            }
            delete nodoAEliminar;
        } else {
            // Agregamos el usuario al conjunto y avanzamos en la lista
            usuariosEncontrados.insert(actual->usuario);
            previo = actual;
            actual = actual->siguiente;
        }
    }
}

void ListaSugerencias::mostrarLista() {
    NodoSugerencias* actual = cabeza;
    while (actual) {
        std::cout << "Usuario: " << actual->usuario << ", Frecuencia: " << actual->frecuencia << std::endl;
        actual = actual->siguiente;
    }
}


NodoSugerencias* ListaSugerencias::obtenerCabeza() const {
    return cabeza;
}