#include "nodosolicitud.h"

NodoSolicitud::NodoSolicitud(string emisor, string receptor, string estado)
    : emisor(emisor), receptor(receptor), estado(estado),
    siguiente(nullptr) {}
