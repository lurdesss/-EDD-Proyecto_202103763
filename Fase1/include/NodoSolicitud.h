#ifndef NODO_SOLICITUD_H
#define NODO_SOLICITUD_H

#include <string>
using namespace std;

class NodoSolicitud {
public:
    string emisor;
    string receptor;
    string estado;

    NodoSolicitud* siguiente; // Para la lista simple

    NodoSolicitud(string emisor, string receptor, string estado);
};

#endif // NODO_SOLICITUD_H
