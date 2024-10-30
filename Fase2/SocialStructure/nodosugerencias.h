#ifndef NODOSUGERENCIAS_H
#define NODOSUGERENCIAS_H

#include <string>

class NodoSugerencias {
public:
    int frecuencia;
    std::string usuario;
    NodoSugerencias* siguiente;

    NodoSugerencias(int freq, const std::string& user) : frecuencia(freq), usuario(user), siguiente(nullptr) {}
};

#endif
