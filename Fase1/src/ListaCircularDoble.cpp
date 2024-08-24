#include "listaCircularDoble.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

NodoCircular::NodoCircular(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora)
    : correo(correo), contenido(contenido), fecha(fecha), hora(hora), siguiente(nullptr), anterior(nullptr) {}

ListaCircularDoble::ListaCircularDoble() : cabeza(nullptr), cola(nullptr) {}

ListaCircularDoble::~ListaCircularDoble() {
    if (cabeza != nullptr) {
        NodoCircular* actual = cabeza;
        NodoCircular* siguiente;
        do {
            siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        } while (actual != cabeza);
    }
}

void ListaCircularDoble::agregarPublicacion(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora) {
    NodoCircular* nuevoNodo = new NodoCircular(correo, contenido, fecha, hora);
    if (cabeza == nullptr) {
        cabeza = cola = nuevoNodo;
        cabeza->siguiente = cabeza;
        cabeza->anterior = cabeza;
    } else {
        nuevoNodo->siguiente = cabeza;
        nuevoNodo->anterior = cola;
        cola->siguiente = nuevoNodo;
        cabeza->anterior = nuevoNodo;
        cola = nuevoNodo;
    }
}

void ListaCircularDoble::mostrarPublicaciones() const {
    if (cabeza != nullptr) {
        NodoCircular* actual = cabeza;
        do {
            std::cout << "[Autor] " << actual->correo << "\n";
            std::cout << "[Contenido] " << actual->contenido << "\n";
            std::cout << "[Fecha] " << actual->fecha << "\n";
            std::cout << "[Hora] " << actual->hora << "\n";
            std::cout << "-----------------------------------------------------\n";
            actual = actual->siguiente;
        } while (actual != cabeza);
    }
}

void ListaCircularDoble::limpiar() {
    if (cabeza != nullptr) {
        NodoCircular* actual = cabeza;
        NodoCircular* siguiente;

        // Iterar a través de la lista y eliminar nodos
        do {
            siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        } while (actual != cabeza);

        // Restablecer los punteros de cabeza y cola
        cabeza = nullptr;
        cola = nullptr;
    }
}

void ListaCircularDoble::navegarPublicaciones() const {
    if (cabeza == nullptr) {
        std::cout << "No hay publicaciones para mostrar." << std::endl;
        return;
    }

    NodoCircular* actual = cabeza;
    char opcion;

    do {
        std::cout << "\n[Autor] " << actual->correo << "\n";
        std::cout << "[Contenido] " << actual->contenido << "\n";
        std::cout << "[Fecha] " << actual->fecha << "\n";
        std::cout << "[Hora] " << actual->hora << "\n";
        std::cout << "-----------------------------------------------------\n";

        std::cout << "Opciones: (A)nterior | (S)iguiente | (Q)uitar: ";
        std::cin >> opcion;

        if (opcion == 'A' || opcion == 'a') {
            actual = actual->anterior;
        } else if (opcion == 'S' || opcion == 's') {
            actual = actual->siguiente;
        } else if (opcion != 'Q' && opcion != 'q') {
            std::cout << "Opción no válida, por favor intente nuevamente." << std::endl;
        }

    } while (opcion != 'Q' && opcion != 'q');
}

void ListaCircularDoble::generateDot(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "digraph G {" << std::endl;
        file << "node [shape=box, style=filled, fillcolor=lightblue, fontcolor=black, color=none];" << std::endl;
        file << "rankdir=LR;" << std::endl;

        if (cabeza != nullptr) {
            NodoCircular* actual = cabeza;
            int id = 0;

            do {
                file << "node" << id << " [label=\"" 
                     << actual->correo << "\\n"
                     << actual->contenido << "\\n"
                     << "Fecha: " << actual->fecha << "\\n"
                     << "Hora: " << actual->hora << "\"];" << std::endl;

                int nextId = id + 1;
                if (actual->siguiente != cabeza) {
                    file << "node" << id << " -> node" << nextId << ";" << std::endl;
                    file << "node" << nextId << " -> node" << id << ";" << std::endl;
                } else {
                    file << "node" << id << " -> node0;" << std::endl;
                    file << "node0 -> node" << id << ";" << std::endl;
                }

                actual = actual->siguiente;
                id++;
            } while (actual != cabeza);
        }

        file << "}" << std::endl;  
        file.close();
    } else {
        std::cout << "No se pudo abrir el archivo" << std::endl;
    }
}

void ListaCircularDoble::renderGraphviz(const std::string& dotFilename, const std::string& imageFilename) const {
    generateDot(dotFilename);
    std::string command = "dot -Tpng " + dotFilename + " -o " + imageFilename;
    system(command.c_str());

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
