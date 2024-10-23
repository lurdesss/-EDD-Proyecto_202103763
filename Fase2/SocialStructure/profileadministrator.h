#ifndef PROFILEADMINISTRATOR_H
#define PROFILEADMINISTRATOR_H

#include "avltree.h"
#include "listapublicaciones.h"
#include "abb.h"
#include "btree.h"

// include RedSocial .h
#include "listasimple.h"
#include "pilasolicitudes.h"
#include "listasimplesolicitudes.h"
#include "relationlist.h"

#include <QMainWindow>

namespace Ui {
class ProfileAdministrator;
}

class ProfileAdministrator : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProfileAdministrator(QWidget *parent = nullptr);
    ~ProfileAdministrator();
    void cargaArchivo(AVLTree* arbol, ListaDePublicaciones* lista, ABB* abbsi, BTree* btreesi, PilaSolicitudes* pilasol, ListaSimpleSolicitudes* listasol, ListOfList* listooflst, FrequencyList* frequencylst);
    void addButtonsToTable();

    ListaSimple listaSolicitudesEnviadas;

private slots:
    void on_actionclosesesionadmin_triggered();

    void on_actionbuscar_triggered();

    void on_actioncargamasiva_triggered();

    void on_actionreportes_triggered();

    void on_pushButton_cargausuarios_clicked();

    void on_pushButton_cargasolicitudes_clicked();

    void on_pushButton_cargapublicaciones_clicked();

    void on_pushButton_reportesfromadminsi_clicked();

    void on_pushButton_searchemail_admin_clicked();

    void on_pushButton_ordercaseaplicar_clicked();

    void on_pushButton_reportesfromadminsi_2_clicked();

private:
    Ui::ProfileAdministrator *ui;
    AVLTree* arbolUsuariosGeneral;
    ListaDePublicaciones* listaDoblePublicaciones;
    ABB* abbPublicaciones;
    BTree* btreeComentarios;
    PilaSolicitudes* pilaSolicitudes;
    ListaSimpleSolicitudes* listaSolicitudes;
    ListOfList* listOfList;
    FrequencyList* frequencyList;
};

#endif // PROFILEADMINISTRATOR_H
