#include "ListaSolicitudes.h"
#include <iostream>
#include <cstdlib> 

using namespace std;

// Constructor
ListaSolicitudes::ListaSolicitudes() : primero(nullptr) {}

// Agregar una solicitud al final de la lista
void ListaSolicitudes::agregarSolicitud(const std::string& emisor, const std::string& receptor, const std::string& estado) {
    SolicitudAmistad* nuevaSolicitud = new SolicitudAmistad(emisor, receptor, estado);
    if (!primero) {
        primero = nuevaSolicitud;
    } else {
        SolicitudAmistad* actual = primero;
        while (actual->siguiente) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevaSolicitud;
        nuevaSolicitud->anterior = actual;
    }
}

// Eliminar una solicitud específica de la lista
void ListaSolicitudes::eliminarSolicitud(const std::string& emisor, const std::string& receptor, const std::string& estado) {
    SolicitudAmistad* actual = primero;
    SolicitudAmistad* anterior = nullptr;

    while (actual) {
        if (actual->emisor == emisor && actual->receptor == receptor && actual->estado == estado) {
            if (anterior) {
                anterior->siguiente = actual->siguiente;
            } else {
                primero = actual->siguiente;
            }
            if (actual->siguiente) {
                actual->siguiente->anterior = anterior;
            }
            delete actual;
            cout << "Solicitud de " << emisor << " a " << receptor << " eliminada." << endl;
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }

    cout << "No se encontró la solicitud en la lista." << endl;
}

// Imprimir el contenido de la lista de solicitudes
void ListaSolicitudes::imprimirSolicitudes() const {
    SolicitudAmistad* actual = primero;
    while (actual) {
        cout << "Emisor: " << actual->emisor << ", Receptor: " << actual->receptor << ", Estado: " << actual->estado << endl;
        actual = actual->siguiente;
    }
}

void ListaSolicitudes::generateDotPorEmisor(const std::string& emisorFiltro, const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "digraph G {" << std::endl;
        file << "node [shape=box, style=filled, fillcolor=yellow, fontcolor=black, color=none];" << std::endl;
        file << "rankdir=RL;" << std::endl;  // RL para el orden de derecha a izquierda

        SolicitudAmistad* actual = primero;
        int id = 0;
        while (actual != nullptr) {
            if (actual->emisor == emisorFiltro) {
                file << "node" << id << " [label=\"" 
                    << "[Solicitud] " << "\\nEmisor: " << actual->emisor 
                    << "\\nReceptor: " << actual->receptor 
                    << "\\nEstado: " << actual->estado 
                    << "\"];" << std::endl;

                // Verifica si el siguiente nodo tiene el mismo emisor para dibujar la flecha
                if (actual->siguiente != nullptr && actual->siguiente->emisor == emisorFiltro) {
                    file << "node" << id << " -> node" << (id + 1) << ";" << std::endl;
                }
                id++;
            }
            actual = actual->siguiente;
        }

        file << "}" << std::endl;  // Se cierra la definición del gráfico
        file.close();
    } else {
        std::cout << "No se pudo abrir el archivo" << std::endl;
    }
}

void ListaSolicitudes::renderGraphviz(const std::string& dotFilename, const std::string& imageFilename) const {
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
