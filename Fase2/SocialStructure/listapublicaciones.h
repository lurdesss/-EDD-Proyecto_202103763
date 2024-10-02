#ifndef LISTAPUBLICACIONES_H
#define LISTAPUBLICACIONES_H
#include <QString>

class Publicacion {
public:
    QString correo;
    QString contenido;
    QString fecha;
    QString hora;

    Publicacion* siguiente;
    Publicacion* anterior;

    Publicacion(QString correo_, QString contenido_, QString fecha_, QString hora_)
        : correo(correo_), contenido(contenido_), fecha(fecha_), hora(hora_), siguiente(nullptr), anterior(nullptr) {}
};

class ListaDePublicaciones {
private:
    Publicacion* cabeza;
    Publicacion* cola;

public:
    ListaDePublicaciones();
    ~ListaDePublicaciones();

    void agregarPublicacion(const QString& correo, const QString& contenido, const QString& fecha, const QString& hora);
    void eliminarPublicacion(const QString& correo, const QString& fecha, const QString& hora);
    void mostrarPublicaciones() const;
    void generateDot(const QString& filename) const;
    void renderGraphviz(const QString& dotFilename, const QString& imageFilename) const;
};

#endif // LISTAPUBLICACIONES_H
