#ifndef LISTAPUBLICACIONES_H
#define LISTAPUBLICACIONES_H

#include "publicacion.h"
#include "UserList.h"

class ListaDePublicaciones {
private:
    Publicacion* cabeza;
    Publicacion* cola;
    UserList* listaUsuarios; // Puntero a la lista de usuarios para verificar correos

public:
    ListaDePublicaciones(UserList* listaUsuarios);
    ~ListaDePublicaciones();
    
    void agregarPublicacion(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora);
    void eliminarPublicacion(const std::string& correo, const std::string& fecha, const std::string& hora); // Corrección aquí
    void mostrarPublicaciones() const;
};

#endif // LISTAPUBLICACIONES_H
