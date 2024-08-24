#ifndef LISTAPUBLICACIONES_H
#define LISTAPUBLICACIONES_H

#include "publicacion.h"
#include "UserList.h"
#include <unordered_map>
#include <vector>
#include <utility> // Para std::pair
#include <string>
#include <fstream>

class ListaDePublicaciones {
private:
    Publicacion* cabeza;
    Publicacion* cola;
    UserList* listaUsuarios;

public:
    ListaDePublicaciones(UserList* listaUsuarios);
    ~ListaDePublicaciones();

    void agregarPublicacion(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora);
    void eliminarPublicacion(const std::string& correo, const std::string& fecha, const std::string& hora);
    void mostrarPublicaciones() const;
    void mostrarTopPublicaciones() const; // Declaración del nuevo método
    void generateDot(const std::string& filename) const;
    void renderGraphviz(const std::string& dotFilename, const std::string& imageFilename) const;
};

#endif // LISTAPUBLICACIONES_H
