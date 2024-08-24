#include "listapublicaciones.h"
#include "ListaCircularDoble.h"
#include "ListaSimpleAmigos.h"
#include "nodocorreo.h"
#include <iostream>

// Constructor y Destructor
ListaDePublicaciones::ListaDePublicaciones(UserList* listaUsuarios) : cabeza(nullptr), cola(nullptr), listaUsuarios(listaUsuarios) {}

ListaDePublicaciones::~ListaDePublicaciones() {
    while (cabeza != nullptr) {
        eliminarPublicacion(cabeza->correo, cabeza->fecha, cabeza->hora);
    }
}

// Métodos de agregar y eliminar publicaciones
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

// Método para mostrar publicaciones
void ListaDePublicaciones::mostrarPublicaciones() const {
    Publicacion* actual = cabeza;
    while (actual != nullptr) {
        actual->mostrar();
        actual = actual->siguiente;
    }
}

// Método para mostrar el top de publicaciones
void ListaDePublicaciones::mostrarTopPublicaciones() const {
    // Paso 1: Contar publicaciones y crear nodos
    NodoCorreo* cabezaLista = nullptr;
    NodoCorreo* colaLista = nullptr;

    // Contar publicaciones por correo
    Publicacion* actual = cabeza;
    while (actual != nullptr) {
        // Buscar si el nodo con el correo ya existe
        NodoCorreo* nodoActual = cabezaLista;
        NodoCorreo* nodoAnterior = nullptr;
        bool encontrado = false;
        while (nodoActual != nullptr) {
            if (nodoActual->correo == actual->correo) {
                nodoActual->conteo++;
                encontrado = true;
                break;
            }
            nodoAnterior = nodoActual;
            nodoActual = nodoActual->siguiente;
        }

        // Si no se encontró el nodo, agregar uno nuevo
        if (!encontrado) {
            NodoCorreo* nuevoNodo = new NodoCorreo(actual->correo, 1);
            if (colaLista == nullptr) {
                cabezaLista = colaLista = nuevoNodo;
            } else {
                colaLista->siguiente = nuevoNodo;
                nuevoNodo->anterior = colaLista;
                colaLista = nuevoNodo;
            }
        }

        actual = actual->siguiente;
    }

    // Paso 2: Ordenar la lista usando el algoritmo de burbuja
    bool intercambiado;
    do {
        intercambiado = false;
        NodoCorreo* nodoActual = cabezaLista;
        while (nodoActual != nullptr && nodoActual->siguiente != nullptr) {
            if (nodoActual->conteo < nodoActual->siguiente->conteo) {
                // Intercambiar los nodos
                std::swap(nodoActual->correo, nodoActual->siguiente->correo);
                std::swap(nodoActual->conteo, nodoActual->siguiente->conteo);
                intercambiado = true;
            }
            nodoActual = nodoActual->siguiente;
        }
    } while (intercambiado);

    // Paso 3: Mostrar los 5 primeros correos con más publicaciones
    std::cout << "Top 5 correos con más publicaciones:\n";
    NodoCorreo* nodoActual = cabezaLista;
    int count = 0;
    while (nodoActual != nullptr && count < 5) {
        std::cout << count + 1 << ". " << nodoActual->correo << " - " << nodoActual->conteo << " publicaciones\n";
        nodoActual = nodoActual->siguiente;
        count++;
    }

    // Liberar la memoria
    while (cabezaLista != nullptr) {
        NodoCorreo* temp = cabezaLista;
        cabezaLista = cabezaLista->siguiente;
        delete temp;
    }
}

// Método para buscar publicaciones por correo electrónico y agregarlas a la lista circular doble
void ListaDePublicaciones::buscarPublicacionesPorEmail(const std::string& correo, ListaCircularDoble& listaCircular) const {
    Publicacion* actual = cabeza;
    while (actual != nullptr) {
        if (actual->correo == correo) {
            listaCircular.agregarPublicacion(actual->correo, actual->contenido, actual->fecha, actual->hora);
        }
        actual = actual->siguiente;
    }
}

// Métodos para generar y renderizar el gráfico DOT
void ListaDePublicaciones::generateDot(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "digraph G {" << std::endl;
        file << "node [shape=box, style=filled, fillcolor=lightblue, fontcolor=black, color=none];" << std::endl;
        file << "rankdir=LR;" << std::endl;

        Publicacion* actual = cabeza;
        int id = 0;
        while (actual != nullptr) {
            file << "node" << id << " [label=\""
                 << actual->correo 
                 << "\\n" << actual->contenido 
                 << "\\nFecha: " << actual->fecha 
                 << "\\nHora: " << actual->hora 
                 << "\"];" << std::endl;

            if (actual->siguiente != nullptr) {
                file << "node" << id << " -> node" << (id + 1) << " [label=\"siguiente\"];" << std::endl;
                file << "node" << (id + 1) << " -> node" << id << " [label=\"anterior\"];" << std::endl;
            }

            actual = actual->siguiente;
            id++;
        }

        file << "}" << std::endl;  // Cerrar la definición del gráfico
        file.close();
    } else {
        std::cout << "No se pudo abrir el archivo" << std::endl;
    }
}

void ListaDePublicaciones::renderGraphviz(const std::string& dotFilename, const std::string& imageFilename) const {
    generateDot(dotFilename);  // Generar el archivo .dot
    std::string command = "dot -Tpng " + dotFilename + " -o " + imageFilename;
    system(command.c_str());

    // Abrir el archivo de imagen después de generarlo
    #ifdef _WIN32
        std::string openCommand = "start " + imageFilename;
    #else
        std::string openCommand = "xdg-open " + imageFilename;
    #endif
    system(openCommand.c_str());
}


void ListaDePublicaciones::buscarPublicacionesPorListaEmails(const ListaSimpleAmigos& listaEmails, ListaCircularDoble& listaCircular) const {
    NodoAmigos* nodoEmail = listaEmails.obtenerCabeza();
    
    // Recorrer cada correo en la lista simple
    while (nodoEmail != nullptr) {
        Publicacion* actual = cabeza;

        // Buscar y agregar publicaciones correspondientes al correo actual
        while (actual != nullptr) {
            if (actual->correo == nodoEmail->correo) {
                listaCircular.agregarPublicacion(actual->correo, actual->contenido, actual->fecha, actual->hora);
            }
            actual = actual->siguiente;
        }
        
        nodoEmail = nodoEmail->siguiente;  // Ir al siguiente correo en la lista simple
    }
}
