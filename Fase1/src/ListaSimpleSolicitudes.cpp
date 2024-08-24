#include "ListaSimpleSolicitudes.h"
#include <iostream>
#include <fstream>

ListaSimpleSolicitudes::ListaSimpleSolicitudes() : cabeza(nullptr) {}

ListaSimpleSolicitudes::~ListaSimpleSolicitudes() {
    while (cabeza != nullptr) {
        NodoSolicitud* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

void ListaSimpleSolicitudes::agregarSolicitud(const std::string& emisor, const std::string& receptor, const std::string& estado) {
    // Verifica si ya existe una solicitud pendiente entre emisor y receptor
    if (!existeSolicitudPendiente(emisor, receptor) && !existeSolicitudPendiente(receptor, emisor)) {
        // Si no existe, agrega la nueva solicitud
        NodoSolicitud* nuevaSolicitud = new NodoSolicitud(emisor, receptor, estado);
        nuevaSolicitud->siguiente = cabeza;
        cabeza = nuevaSolicitud;
    } else {
        std::cout << "Ya existe una solicitud pendiente entre " << emisor << " y " << receptor << "." << std::endl;
    }
}


void ListaSimpleSolicitudes::imprimirLista() const {
    cout << "Lista de solicitudes enviadas:" << endl;
    NodoSolicitud* actual = cabeza;
    while (actual != nullptr) {
        std::cout << "    " << actual->receptor << endl;
        actual = actual->siguiente;
    }
}

// Implementación de eliminarSolicitud
void ListaSimpleSolicitudes::eliminarSolicitud(const std::string& receptor, const std::string& email, const std::string& estado) {
    NodoSolicitud* actual = cabeza;
    NodoSolicitud* previo = nullptr;

    while (actual != nullptr) {
        if (((actual->emisor == receptor && actual->receptor == email) ||
             (actual->emisor == email && actual->receptor == receptor)) &&
            actual->estado == estado) {
            if (previo == nullptr) {
                cabeza = actual->siguiente;
            } else {
                previo->siguiente = actual->siguiente;
            }
            delete actual;
            return; // Salir después de eliminar
        }
        previo = actual;
        actual = actual->siguiente;
    }
}

// Implementación de existeSolicitudPendiente
bool ListaSimpleSolicitudes::existeSolicitudPendiente(const std::string& receptor, const std::string& email) const {
    NodoSolicitud* actual = cabeza;
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

void ListaSimpleSolicitudes::limpiarLista() {
    while (cabeza != nullptr) {
        NodoSolicitud* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}


void ListaSimpleSolicitudes::generateDot(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "digraph G {" << std::endl;
        file << "node [shape=box, style=filled, fillcolor=yellow, fontcolor=black, color=none];" << std::endl;
        file << "rankdir=RL;" << std::endl;

        NodoSolicitud* actual = cabeza;
        int id = 0;
        while (actual != nullptr) {
            file << "node" << id << " [label=\"" 
                << "[Solicitud] " << "\\n"
                << "Emisor: " << actual->emisor << "\\n"
                << "Receptor: " << actual->receptor << "\\n"
                << "Estado: " << actual->estado 
                << "\"];" << std::endl;
                
            if (actual->siguiente != nullptr) {
                file << "node" << id << " -> node" << (id + 1) << ";" << std::endl;
            }
            actual = actual->siguiente;
            id++;
        }

        file << "}" << std::endl;  // Se cierra la definición del gráfico
        file.close();
    } else {
        std::cout << "No se pudo abrir el archivo" << std::endl;
    }
}



void ListaSimpleSolicitudes::renderGraphviz(const std::string& dotFilename, const std::string& imageFilename) const {
    std::string command = "dot -Tpng " + dotFilename + " -o " + imageFilename;
    system(command.c_str());

    // Abrir el archivo de imagen después de generarlo
    #ifdef _WIN32
        std::string openCommand = "start " + imageFilename;
    #elif __APPLE__
        std::string openCommand = "open " + imageFilename;
    #elif __linux__
        std::string openCommand = "xdg-open " + imageFilename;
    #else
    #error "Sistema operativo no soportado"
    #endif
    
    system(openCommand.c_str());
}