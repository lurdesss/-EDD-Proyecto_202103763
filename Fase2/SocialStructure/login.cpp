#include "login.h"
#include "ui_login.h"
#include "QMessageBox"

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_login_clicked()
{
    QString adminEmail = "3312";  // admin@gmail.com
    QString adminPassword = "3312";  // EDD2S2024
    QString userEmailTemporal = "user"; // variado
    QString userPasswordTemporal = "user"; // variado

    QString username = ui->lineEdit_email->text();
    QString password = ui->lineEdit_password->text();

    QString messageBoxStyle = "QMessageBox { background-color: #f0f0f0; color: #333333; }"
                              "QPushButton { background-color: rgb(16, 16, 16); color: white; padding: 5px 7px 5px 7px; }"
                              "QPushButton:hover { background-color: rgb(0, 0, 0); }";

    if(username == adminEmail && password == adminPassword){
        QMessageBox msgBox;
        msgBox.setText("Login successful as administrator");
        msgBox.setWindowTitle("Login");
        msgBox.setStyleSheet(messageBoxStyle);
        msgBox.exec();

        hide();  // Solo ocultar la ventana de login cuando el login es exitoso
        profileUser = new ProfileUser();
        profileUser->show();
    }
    else if(username == userEmailTemporal && password == userPasswordTemporal){
        QMessageBox msgBox;
        msgBox.setText("Login successful as user");
        msgBox.setWindowTitle("Login");
        msgBox.setStyleSheet(messageBoxStyle);
        msgBox.exec();

        hide();  // Solo ocultar la ventana de login cuando el login es exitoso
        profileUser = new ProfileUser();
        profileUser->show();
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Incorrect email or password");
        msgBox.setWindowTitle("Login");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStyleSheet(messageBoxStyle);
        msgBox.exec();

        // No ocultar ni cerrar la ventana de Login, el usuario debe poder intentarlo de nuevo
    }
}




