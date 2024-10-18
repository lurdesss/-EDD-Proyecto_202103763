#ifndef SOLICITUD_AMISTAD_H
#define SOLICITUD_AMISTAD_H

#include <string>
using namespace std;

class SolicitudAmistad {
public:
    string emisor;
    string receptor;
    string estado;

    SolicitudAmistad* siguiente; // Para la lista simple
    SolicitudAmistad* anterior;  // Para la pila y la lista
    SolicitudAmistad* up;        // Para la matriz dispersa
    SolicitudAmistad* down;
    SolicitudAmistad* left;
    SolicitudAmistad* right;

    SolicitudAmistad(string emisor, string receptor, string estado);
};

#endif // SOLICITUD_AMISTAD_H
