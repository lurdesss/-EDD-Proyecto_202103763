#include "listapublicaciones.h"
#include <iostream>
#include <fstream>

// Constructor y Destructor
ListaDePublicaciones::ListaDePublicaciones() : cabeza(nullptr), cola(nullptr) {}

ListaDePublicaciones::~ListaDePublicaciones() {
    while (cabeza != nullptr) {
        eliminarPublicacion(cabeza->correo, cabeza->fecha, cabeza->hora);
    }
}

// Métodos de agregar y eliminar publicaciones
void ListaDePublicaciones::agregarPublicacion(const QString& correo, const QString& contenido, const QString& fecha, const QString& hora) {
    // Validaciones
    if (contenido.isEmpty() || fecha.isEmpty() || hora.isEmpty()) {
        std::cout << "Todos los campos deben estar completos." << std::endl;
        return;
    }

    // Crear nueva publicación
    Publicacion* nuevaPublicacion = new Publicacion(correo, contenido, fecha, hora);
    if (cola == nullptr) {
        cabeza = cola = nuevaPublicacion;
    } else {
        cola->siguiente = nuevaPublicacion;
        nuevaPublicacion->anterior = cola;
        cola = nuevaPublicacion;
    }
}

void ListaDePublicaciones::eliminarPublicacion(const QString& correo, const QString& fecha, const QString& hora) {
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
        std::cout << "Correo: " << actual->correo.toStdString()
                  << ", Contenido: " << actual->contenido.toStdString()
                  << ", Fecha: " << actual->fecha.toStdString()
                  << ", Hora: " << actual->hora.toStdString() << std::endl;
        actual = actual->siguiente;
    }
}

// Métodos para generar y renderizar el gráfico DOT
void ListaDePublicaciones::generateDot(const QString& filename) const {
    // Cambiar la ruta para guardar en ../../salida
    QString outputPath = "../../salida/" + filename;
    std::ofstream file(outputPath.toStdString());

    if (file.is_open()) {
        file << "digraph G {" << std::endl;
        file << "node [shape=box, style=filled, fillcolor=lightblue, fontcolor=black, color=none];" << std::endl;
        file << "rankdir=LR;" << std::endl;

        Publicacion* actual = cabeza;
        int id = 0;
        while (actual != nullptr) {
            file << "node" << id << " [label=\""
                 << actual->correo.toStdString()
                 << "\\n" << actual->contenido.toStdString()
                 << "\\nFecha: " << actual->fecha.toStdString()
                 << "\\nHora: " << actual->hora.toStdString()
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


void ListaDePublicaciones::renderGraphviz(const QString& dotFilename, const QString& imageFilename) const {
    // Ruta para guardar el archivo .dot en ../../salida
    QString dotFilePath = "../../salida/" + dotFilename;
    QString imageFilePath = "../../salida/" + imageFilename;

    // Generar el archivo .dot en la ruta especificada
    generateDot(dotFilePath);

    // Crear el comando para generar el .png desde el .dot
    std::string command = "dot -Tpng " + dotFilePath.toStdString() + " -o " + imageFilePath.toStdString();
    system(command.c_str());

    // No abrir el archivo de imagen, solo guardarlo en la carpeta ../../salida
}
