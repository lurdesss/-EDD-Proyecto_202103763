#ifndef LISTAPUBLICACIONES_H
#define LISTAPUBLICACIONES_H

#include "publicacion.h"
#include "UserList.h"
#include "listaCircularDoble.h"
#include "ListaSimpleAmigos.h" 
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
    void mostrarTopPublicaciones() const; // Declaración del método para mostrar el top de publicaciones
    void generateDot(const std::string& filename) const;
    void renderGraphviz(const std::string& dotFilename, const std::string& imageFilename) const;

    // Declaración de la función para buscar publicaciones por correo electrónico
    void buscarPublicacionesPorEmail(const std::string& correo, ListaCircularDoble& listaCircular) const;
    void buscarPublicacionesPorListaEmails(const ListaSimpleAmigos& listaEmails, ListaCircularDoble& listaCircular) const;
};

#endif // LISTAPUBLICACIONES_H
