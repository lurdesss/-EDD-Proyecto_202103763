#include "PilaSolicitudes.h"
#include <iostream>
#include <cstdlib>

PilaSolicitudes::PilaSolicitudes() : tope(nullptr) {}

PilaSolicitudes::~PilaSolicitudes() {
    limpiarPila();
}

void PilaSolicitudes::pushSolicitud(const std::string& emisor, const std::string& receptor, const std::string& estado) {
    if (!existeSolicitudPendiente(emisor, receptor) && !existeSolicitudPendiente(receptor, emisor)) {
        NodoSolicitud* nuevaSolicitud = new NodoSolicitud(emisor, receptor, estado);
        nuevaSolicitud->siguiente = tope;
        tope = nuevaSolicitud;
    } else {
        std::cout << "Ya existe una solicitud pendiente entre " << emisor << " y " << receptor << "." << std::endl;
    }
}

void PilaSolicitudes::popSolicitud() {
    if (tope != nullptr) {
        NodoSolicitud* temp = tope;
        tope = tope->siguiente;
        delete temp;
    } else {
        std::cout << "La pila está vacía." << std::endl;
    }
}

void PilaSolicitudes::imprimirPila() const {
    NodoSolicitud* actual = tope;
    while (actual != nullptr) {
        std::cout << actual->emisor << endl;
        actual = actual->siguiente;
    }
}

bool PilaSolicitudes::existeSolicitudPendiente(const std::string& receptor, const std::string& email) const {
    NodoSolicitud* actual = tope;
    while (actual != nullptr) {
        if (((actual->emisor == receptor && actual->receptor == email) ||
             (actual->emisor == email && actual->receptor == receptor)) &&
            actual->estado == "PENDIENTE") {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

void PilaSolicitudes::limpiarPila() {
    while (tope != nullptr) {
        NodoSolicitud* temp = tope;
        tope = tope->siguiente;
        delete temp;
    }
}

void PilaSolicitudes::generarDot(const std::string& nombreArchivo) const {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo para escribir el gráfico DOT." << std::endl;
        return;
    }

    archivo << "digraph G {" << std::endl;
    archivo << "node [shape=box, style=filled, fillcolor=lightgray, fontcolor=black, color=none];" << std::endl;
    archivo << "rankdir=BT;" << std::endl;  // Orientación de abajo hacia arriba, típico en una pila

    NodoSolicitud* actual = tope;
    int nodoId = 0;

    while (actual != nullptr) {
        archivo << "  nodo" << nodoId << " [label=\"" 
                << "[Solicitud] " << "\\n"
                << "Emisor: " << actual->emisor << "\\n"
                << "Receptor: " << actual->receptor << "\\n"
                << "Estado: " << actual->estado 
                << "\"];" << std::endl;

        if (actual->siguiente != nullptr) {
            archivo << "  nodo" << nodoId << " -> nodo" << (nodoId + 1) << ";" << std::endl;
        }

        actual = actual->siguiente;
        nodoId++;
    }

    archivo << "}" << std::endl;
    archivo.close();
}


void PilaSolicitudes::renderGraphviz(const std::string& nombreArchivoDot, const std::string& nombreImagen) const {
    std::string command = "dot -Tpng " + nombreArchivoDot + " -o " + nombreImagen;
    system(command.c_str());
    // Abrir el archivo de imagen después de generarlo
    #ifdef _WIN32
        std::string openCommand = "start " + nombreImagen;
    #elif __APPLE__
        std::string openCommand = "open " + nombreImagen;
    #elif __linux__
        std::string openCommand = "xdg-open " + nombreImagen;
    #else
    #error "Sistema operativo no soportado"
    #endif
}

