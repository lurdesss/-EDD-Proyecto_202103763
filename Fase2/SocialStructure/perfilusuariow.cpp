#include "perfilusuariow.h"
#include "ui_perfilusuariow.h"
#include "globals.h"


PerfilUsuarioW::PerfilUsuarioW(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PerfilUsuarioW)
{
    ui->setupUi(this);
}

PerfilUsuarioW::~PerfilUsuarioW()
{
    delete ui;
}


void PerfilUsuarioW::on_pushButton_edit_clicked()
{
    // habilitar lineEdit
    ui->lineEdit_nameuser_2->setEnabled(true);
    ui->lineEdit_passworduser_2->setEnabled(true);
    ui->lineEdit_emailuser_2->setEnabled(true);
    ui->lineEdit_dateuser_2->setEnabled(true);
    ui->lineEdit_lastnameuser_2->setEnabled(true);
}


void PerfilUsuarioW::on_pushButton_save_clicked()
{
    // deshabilitar lineEdit
    ui->lineEdit_nameuser_2->setEnabled(false);
    ui->lineEdit_passworduser_2->setEnabled(false);
    ui->lineEdit_emailuser_2->setEnabled(false);
    ui->lineEdit_dateuser_2->setEnabled(false);
    ui->lineEdit_lastnameuser_2->setEnabled(false);
}


void PerfilUsuarioW::on_pushButton_delete_clicked()
{
    // Guardar los valores de los QLineEdit en las variables globales
    globalName = ui->lineEdit_nameuser_2->text();
    globalLastname = ui->lineEdit_lastnameuser_2->text();
    globalDate = ui->lineEdit_dateuser_2->text();
    globalPassword = ui->lineEdit_passworduser_2->text();
    globalEmail = ui->lineEdit_emailuser_2->text();

    // Opcional: Mostrar un mensaje de confirmación o realizar otras acciones
    qDebug() << "Datos guardados:";
    qDebug() << "Nombre:" << globalName;
    qDebug() << "Apellido:" << globalLastname;
    qDebug() << "Fecha:" << globalDate;
    qDebug() << "Contraseña:" << globalPassword;
    qDebug() << "Correo electrónico:" << globalEmail;
}

