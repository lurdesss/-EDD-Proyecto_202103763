#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "profileuser.h"
#include "registrarusuario.h"
#include "profileadministrator.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Login;
}
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_createacc_clicked();

private:
    Ui::Login *ui;
    ProfileUser *profileUser;
    RegistrarUsuario *registrarUsuario;
    ProfileAdministrator *profileAdministrator;
};
#endif // LOGIN_H
