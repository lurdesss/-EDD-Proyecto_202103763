#include "publicacion.h"
#include <iostream>

Publicacion::Publicacion(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora)
    : correo(correo), contenido(contenido), fecha(fecha), hora(hora), siguiente(nullptr), anterior(nullptr) {}

void Publicacion::mostrar() const {
    std::cout << "Correo: " << correo << "\nContenido: " << contenido
              << "\nFecha: " << fecha << "\nHora: " << hora << "\n\n";
}
