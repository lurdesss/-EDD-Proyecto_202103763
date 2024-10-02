#ifndef NODOAMIGOS_H
#define NODOAMIGOS_H

#include <string>

class NodoAmigos {
public:
    std::string correo;
    NodoAmigos* siguiente;

    NodoAmigos(const std::string& correo);
};

#endif // NODOAMIGOS_H
