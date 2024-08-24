#ifndef RED_SOCIAL_H
#define RED_SOCIAL_H

#include <string>
#include "ListaSimple.h"
// #include "PilaSolicitudes.h"
#include "UserList.h"  // Incluye UserList
#include "Matrix.h"

class RedSocial {
public:
    ListaSimple listaSolicitudesEnviadas;
    // PilaSolicitudes pilaSolicitudesRecibidas;
    Matrix matrizAmigos;
    UserList* listaUsuarios; // Agrega un puntero a UserList
    int emisorId, receptorId;

    // Constructor que recibe un puntero a UserList
    RedSocial(UserList* listaUsuarios);

    // Método para cargar solicitudes desde un archivo JSON
    void cargarSolicitudesDesdeJSON(const std::string& filePath);

    // Método para aceptar una solicitud
    // void aceptarSolicitud(const std::string& emisor, const std::string& receptor);
};

#endif // RED_SOCIAL_H
