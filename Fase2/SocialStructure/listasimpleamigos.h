#ifndef LISTASIMPLEAMIGOS_H
#define LISTASIMPLEAMIGOS_H

#include "nodoamigos.h"

class ListaSimpleAmigos {
private:
    NodoAmigos* cabeza;

public:
    ListaSimpleAmigos();
    ~ListaSimpleAmigos();

    void agregarAmigo(const std::string& correo);
    void mostrarAmigos() const;
    void limpiarLista();
    NodoAmigos* obtenerCabeza() const {
        return cabeza;
    }
};

#endif // LISTASIMPLEAMIGOS_H
