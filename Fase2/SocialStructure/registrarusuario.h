#ifndef REGISTRARUSUARIO_H
#define REGISTRARUSUARIO_H

#include "avltree.h"
#include <QMainWindow>

namespace Ui {
class RegistrarUsuario;
}

class RegistrarUsuario : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegistrarUsuario(AVLTree* arbolUsuarios, QWidget *parent = nullptr);
    ~RegistrarUsuario();

private slots:
    void on_pushButton_backtologin_clicked();

    void on_pushButton_closeapp_clicked();

    void on_pushButton_savenewuser_clicked();

private:
    Ui::RegistrarUsuario *ui;
    AVLTree* arbolUsuariosGeneral;
};

#endif // REGISTRARUSUARIO_H
