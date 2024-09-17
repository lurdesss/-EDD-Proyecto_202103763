#include "profileuser.h"
#include "ui_profileuser.h"
#include "login.h"  // Asegúrate de incluir el encabezado de Login
#include "QMessageBox"

ProfileUser::ProfileUser(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ProfileUser)
{
    ui->setupUi(this);
    ui->w_buscar->hide();
    ui->w_publicaciones->hide();
    ui->w_reportes->hide();
    ui->w_solicitudes->hide();
    ui->w_perfilusuario->show();
}

ProfileUser::~ProfileUser()
{
    delete ui;
}

void ProfileUser::on_actionLog_out_triggered()
{
    // Ocultar o cerrar la ventana actual (ProfileUser)
    close();  // Esto cerrará completamente la ventana de ProfileUser

    // Crear una nueva instancia de Login
    Login* login = new Login();  // No le pases 'this' como padre

    // Mostrar la ventana de Login
    login->show();
}


void ProfileUser::on_actionSearch_triggered()
{
    ui->w_perfilusuario->hide();
    ui->w_publicaciones->hide();
    ui->w_reportes->hide();
    ui->w_solicitudes->hide();
    ui->w_buscar->show();
}


void ProfileUser::on_actionPosts_triggered()
{
    ui->w_buscar->hide();
    ui->w_perfilusuario->hide();
    ui->w_reportes->hide();
    ui->w_solicitudes->hide();
    ui->w_publicaciones->show();
}


void ProfileUser::on_actionFriend_Requests_triggered()
{
    ui->w_buscar->hide();
    ui->w_perfilusuario->hide();
    ui->w_publicaciones->hide();
    ui->w_reportes->hide();
    ui->w_solicitudes->show();
}


void ProfileUser::on_actionReports_triggered()
{
    ui->w_buscar->hide();
    ui->w_perfilusuario->hide();
    ui->w_publicaciones->hide();
    ui->w_solicitudes->hide();
    ui->w_reportes->show();
}


void ProfileUser::on_actionProfile_triggered()
{
    ui->w_buscar->hide();
    ui->w_publicaciones->hide();
    ui->w_reportes->hide();
    ui->w_solicitudes->hide();
    ui->w_perfilusuario->show();
}


void ProfileUser::on_actionInformation_triggered()
{
    QMessageBox msgBox;
    QString message = 
        "<b>PROYECTO FASE 2</b><br>"
        "<br><b>Nombre:</b> Jennifer Yulissa Lourdes Taperio Manuel<br>"
        "<b>Carnet:</b> 202103763<br>"
        "<b>Curso:</b> Estructura de Datos<br>"
        "<b>Sección:</b> C";

    msgBox.setText(message);
    msgBox.setWindowTitle("About");
    msgBox.setIcon(QMessageBox::Information);

    // Estilo para el QMessageBox
    QString messageBoxStyle =
        "QMessageBox { background-color: #f0f0f0; color: #333333; font-size: 16px; }"
        "QLabel { font-size: 16px; }"
        "QPushButton { background-color: rgb(16, 16, 16); color: white; padding: 5px 7px; }"
        "QPushButton:hover { background-color: rgb(0, 0, 0); }";

    msgBox.setStyleSheet(messageBoxStyle);

    msgBox.exec();

}

