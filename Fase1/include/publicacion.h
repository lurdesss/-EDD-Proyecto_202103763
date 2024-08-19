#ifndef PUBLICACION_H
#define PUBLICACION_H

#include <string>
#include <ctime>

class Publicacion {
public:
    std::string correo;
    std::string contenido;
    std::string fecha;  // En formato "YYYY-MM-DD"
    std::string hora;   // En formato "HH:MM:SS"
    
    Publicacion* siguiente;
    Publicacion* anterior;
    
    Publicacion(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora);
    void mostrar() const;
};

#endif // PUBLICACION_H
