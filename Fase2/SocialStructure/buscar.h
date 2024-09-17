#ifndef BUSCAR_H
#define BUSCAR_H

#include <QWidget>

namespace Ui {
class Buscar;
}

class Buscar : public QWidget
{
    Q_OBJECT

public:
    explicit Buscar(QWidget *parent = nullptr);
    ~Buscar();

private:
    Ui::Buscar *ui;
};

#endif // BUSCAR_H
