#ifndef LISTASIMPLE_H
#define LISTASIMPLE_H

#include <string>
#include "SolicitudAmistad.h"
#include "PilaSolicitudes.h"
#include "ListaSimpleSolicitudes.h"

class ListaSimple {
private:
    SolicitudAmistad* cabeza;
    

public:
    PilaSolicitudes pilaSolicitudes;
    ListaSimpleSolicitudes listaSolicitudes;
    ListaSimple();
    ~ListaSimple();

    void agregarSolicitud(const std::string& emisor, const std::string& receptor, const std::string& estado);
    void eliminarSolicitud(const std::string& emisor, const std::string& receptor, const std::string& estado);
    bool existeSolicitudPendiente(const std::string& emisor, const std::string& receptor) const;
    bool existeSolicitudAceptada(const std::string& emisor, const std::string& receptor) const;
    void imprimirLista() const;
    void buscarPorReceptor(const std::string& receptor);
    void buscarPorEmisor(const std::string& emisor);
};

#endif // LISTASIMPLE_H
