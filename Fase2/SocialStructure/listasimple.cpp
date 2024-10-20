#include "listasimple.h"
#include <iostream>

ListaSimple::ListaSimple() : cabeza(nullptr) {}

ListaSimple::~ListaSimple() {
    while (cabeza != nullptr) {
        SolicitudAmistad* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

void ListaSimple::carga(PilaSolicitudes* pilasolsi, ListaSimpleSolicitudes* listasolsi){
    this->pilaSolicitudes = pilasolsi;
    this->listaSolicitudes = listasolsi;
}

void ListaSimple::agregarSolicitud(const std::string& emisor, const std::string& receptor, const std::string& estado) {
    SolicitudAmistad* nuevaSolicitud = new SolicitudAmistad(emisor, receptor, estado);
    nuevaSolicitud->siguiente = cabeza;
    cabeza = nuevaSolicitud;
}

void ListaSimple::eliminarSolicitud(const std::string& emisor, const std::string& receptor, const std::string& estado) {
    SolicitudAmistad* actual = cabeza;
    SolicitudAmistad* previo = nullptr;

    while (actual != nullptr) {
        if (((actual->emisor == emisor && actual->receptor == receptor) ||
             (actual->emisor == receptor && actual->receptor == emisor)) &&
            actual->estado == estado) {
            if (previo == nullptr) {
                cabeza = actual->siguiente;
            } else {
                previo->siguiente = actual->siguiente;
            }
            delete actual;
            actual = (previo != nullptr) ? previo->siguiente : cabeza;
        } else {
            previo = actual;
            actual = actual->siguiente;
        }
    }
}

bool ListaSimple::existeSolicitudPendiente(const std::string& emisor, const std::string& receptor) const {
    SolicitudAmistad* actual = cabeza;
    while (actual != nullptr) {
        if (((actual->emisor == emisor && actual->receptor == receptor) ||
             (actual->emisor == receptor && actual->receptor == emisor)) &&
            actual->estado == "PENDIENTE") {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

bool ListaSimple::existeSolicitudAceptada(const std::string& emisor, const std::string& receptor) const {
    SolicitudAmistad* actual = cabeza;
    while (actual != nullptr) {
        if (((actual->emisor == emisor && actual->receptor == receptor) ||
             (actual->emisor == receptor && actual->receptor == emisor)) &&
            actual->estado == "ACEPTADA") {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

void ListaSimple::imprimirLista() const {
    SolicitudAmistad* actual = cabeza;
    while (actual != nullptr) {
        std::cout << "Solicitud de " << actual->emisor
                  << " a " << actual->receptor
                  << " con estado " << actual->estado << std::endl;
        actual = actual->siguiente;
    }
}

void ListaSimple::buscarPorReceptor(const std::string& receptor) {
    SolicitudAmistad* actual = cabeza;
    while (actual != nullptr) {
        if (actual->receptor == receptor) {
            pilaSolicitudes->pushSolicitud(actual->emisor, actual->receptor, actual->estado);
        }
        actual = actual->siguiente;
    }
}

void ListaSimple::buscarPorEmisor(const std::string& emisor) {
    SolicitudAmistad* actual = cabeza;
    while (actual != nullptr) {
        if (actual->emisor == emisor) {
            listaSolicitudes->agregarSolicitud(actual->emisor, actual->receptor, actual->estado);
        }
        actual = actual->siguiente;
    }
}
