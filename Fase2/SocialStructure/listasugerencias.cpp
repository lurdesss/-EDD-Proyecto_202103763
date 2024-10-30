#include "listasugerencias.h"
#include <iostream>

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

void ListaSugerencias::mostrarLista() {
    NodoSugerencias* actual = cabeza;
    while (actual) {
        std::cout << "Usuario: " << actual->usuario << ", Frecuencia: " << actual->frecuencia << std::endl;
        actual = actual->siguiente;
    }
}
