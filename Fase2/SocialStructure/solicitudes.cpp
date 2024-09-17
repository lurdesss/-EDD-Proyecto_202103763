#include "solicitudes.h"
#include "ui_solicitudes.h"

Solicitudes::Solicitudes(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Solicitudes)
{
    ui->setupUi(this);
}

Solicitudes::~Solicitudes()
{
    delete ui;
}
