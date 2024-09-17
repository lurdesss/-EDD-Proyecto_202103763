#ifndef PUBLICACIONES_H
#define PUBLICACIONES_H

#include <QWidget>

namespace Ui {
class Publicaciones;
}

class Publicaciones : public QWidget
{
    Q_OBJECT

public:
    explicit Publicaciones(QWidget *parent = nullptr);
    ~Publicaciones();

private:
    Ui::Publicaciones *ui;
};

#endif // PUBLICACIONES_H
