#ifndef SOLICITUDES_H
#define SOLICITUDES_H

#include <QWidget>

namespace Ui {
class Solicitudes;
}

class Solicitudes : public QWidget
{
    Q_OBJECT

public:
    explicit Solicitudes(QWidget *parent = nullptr);
    ~Solicitudes();

private:
    Ui::Solicitudes *ui;
};

#endif // SOLICITUDES_H
