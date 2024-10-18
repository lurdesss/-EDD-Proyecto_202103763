#include "solicitudamistad.h"

SolicitudAmistad::SolicitudAmistad(string emisor, string receptor, string estado)
    : emisor(emisor), receptor(receptor), estado(estado),
    siguiente(nullptr), anterior(nullptr),
    up(nullptr), down(nullptr), left(nullptr), right(nullptr) {}
