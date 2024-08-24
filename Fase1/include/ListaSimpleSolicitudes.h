#ifndef LISTASIMPLESOLICITUDES_H
#define LISTASIMPLESOLICITUDES_H

#include <string>
#include "NodoSolicitud.h"

class ListaSimpleSolicitudes {
private:
    NodoSolicitud* cabeza;

public:
    ListaSimpleSolicitudes();
    ~ListaSimpleSolicitudes();

    void agregarSolicitud(const std::string& emisor, const std::string& receptor, const std::string& estado);
    void imprimirLista() const;
    void eliminarSolicitud(const std::string& receptor, const std::string& email, const std::string& estado);
    bool existeSolicitudPendiente(const std::string& receptor, const std::string& email) const;
    void limpiarLista();
    void generateDot(const std::string& filename) const;
    void renderGraphviz(const std::string& dotFilename, const std::string& imageFilename) const;

};

#endif // LISTASIMPLESOLICITUDES_H
