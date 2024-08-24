#ifndef LISTA_SOLICITUDES_H
#define LISTA_SOLICITUDES_H

#include "SolicitudAmistad.h"
#include <string>
#include <fstream>

class ListaSolicitudes {
public:
    SolicitudAmistad* primero;

    ListaSolicitudes();
    void agregarSolicitud(const std::string& emisor, const std::string& receptor, const std::string& estado);
    void eliminarSolicitud(const std::string& emisor, const std::string& receptor, const std::string& estado);
    void imprimirSolicitudes() const;

    void generateDotPorEmisor(const std::string& emisorFiltro, const std::string& filename) const;
    void renderGraphviz(const std::string& dotFilename, const std::string& imageFilename) const;
};

#endif // LISTA_SOLICITUDES_H
