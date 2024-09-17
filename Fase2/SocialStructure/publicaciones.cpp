#include "publicaciones.h"
#include "ui_publicaciones.h"

Publicaciones::Publicaciones(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Publicaciones)
{
    ui->setupUi(this);
}

Publicaciones::~Publicaciones()
{
    delete ui;
}
