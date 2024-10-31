#ifndef PILA_SOLICITUDES_H
#define PILA_SOLICITUDES_H

#include <string>
#include "nodosolicitud.h"
#include <fstream>
#include <QJsonArray>

class PilaSolicitudes {
private:
    NodoSolicitud* tope;

public:
    PilaSolicitudes();
    ~PilaSolicitudes();

    void pushSolicitud(const std::string& emisor, const std::string& receptor, const std::string& estado);
    void popSolicitud();
    void imprimirPila() const;
    bool existeSolicitudPendiente(const std::string& receptor, const std::string& email) const;
    void limpiarPila();

    // Nuevas funciones para generar gráficos
    void generarDot(const std::string& nombreArchivo) const;
    void renderGraphviz(const std::string& nombreArchivoDot, const std::string& nombreImagen) const;
    void guardarSolicitudesEnJson(QJsonArray& solicitudesArray) const;
};

#endif // PILA_SOLICITUDES_H
