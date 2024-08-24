#ifndef NODOCORREO_H
#define NODOCORREO_H

#include <string>

class NodoCorreo {
public:
    std::string correo;
    int conteo;
    NodoCorreo* siguiente;
    NodoCorreo* anterior;

    NodoCorreo(const std::string& correo, int conteo)
        : correo(correo), conteo(conteo), siguiente(nullptr), anterior(nullptr) {}
};

#endif // NODOCORREO_H
