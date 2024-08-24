#ifndef LISTACIRCULARDOBLE_H
#define LISTACIRCULARDOBLE_H

#include <string>

class NodoCircular {
public:
    std::string correo;
    std::string contenido;
    std::string fecha;
    std::string hora;
    NodoCircular* siguiente;
    NodoCircular* anterior;

    NodoCircular(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora);
};

class ListaCircularDoble {
private:
    NodoCircular* cabeza;
    NodoCircular* cola;

public:
    ListaCircularDoble();
    ~ListaCircularDoble();

    void agregarPublicacion(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora);
    void mostrarPublicaciones() const;
    void limpiar();
    void navegarPublicaciones() const;
    void generateDot(const std::string& filename) const;
    void renderGraphviz(const std::string& dotFilename, const std::string& imageFilename) const;
};

#endif // LISTACIRCULARDOBLE_H
