#include "listapublicaciones.h"
#include <iostream>

ListaDePublicaciones::ListaDePublicaciones(UserList* listaUsuarios) : cabeza(nullptr), cola(nullptr), listaUsuarios(listaUsuarios) {}

ListaDePublicaciones::~ListaDePublicaciones() {
    while (cabeza != nullptr) {
        eliminarPublicacion(cabeza->correo, cabeza->fecha, cabeza->hora);
    }
}

void ListaDePublicaciones::agregarPublicacion(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora) {
    if (!listaUsuarios->emailExists(correo)) {
        std::cout << "El correo electrónico del usuario no está registrado." << std::endl;
        return;
    }

    if (contenido.empty() || fecha.empty() || hora.empty()) {
        std::cout << "Todos los campos deben estar completos." << std::endl;
        return;
    }

    Publicacion* nuevaPublicacion = new Publicacion(correo, contenido, fecha, hora);
    if (cola == nullptr) {
        cabeza = cola = nuevaPublicacion;
    } else {
        cola->siguiente = nuevaPublicacion;
        nuevaPublicacion->anterior = cola;
        cola = nuevaPublicacion;
    }
}

void ListaDePublicaciones::eliminarPublicacion(const std::string& correo, const std::string& fecha, const std::string& hora) {
    Publicacion* actual = cabeza;

    while (actual != nullptr) {
        if (actual->correo == correo && actual->fecha == fecha && actual->hora == hora) {
            // Encontrar la publicación que coincide con el correo, fecha y hora
            if (actual->anterior) {
                actual->anterior->siguiente = actual->siguiente;
            } else {
                cabeza = actual->siguiente;
            }
            if (actual->siguiente) {
                actual->siguiente->anterior = actual->anterior;
            } else {
                cola = actual->anterior;
            }

            delete actual;
            return;
        }
        actual = actual->siguiente;
    }

    std::cout << "No se encontró una publicación con la fecha y hora especificados." << std::endl;
}

void ListaDePublicaciones::mostrarPublicaciones() const {
    Publicacion* actual = cabeza;
    while (actual != nullptr) {
        actual->mostrar();
        actual = actual->siguiente;
    }
}
