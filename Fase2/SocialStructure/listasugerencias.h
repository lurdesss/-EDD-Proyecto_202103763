#ifndef LISTASUGERENCIAS_H
#define LISTASUGERENCIAS_H

#include "nodosugerencias.h"

class ListaSugerencias {
private:
    NodoSugerencias* cabeza;

public:
    ListaSugerencias();
    ~ListaSugerencias();

    void agregarSugerencia(int frecuencia, const std::string& usuario);
    void ordenarPorFrecuencia();
    void mostrarLista();
};

#endif
