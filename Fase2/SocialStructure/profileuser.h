#ifndef PROFILEUSER_H
#define PROFILEUSER_H

#include "avltree.h"
#include "listapublicaciones.h"
#include "abb.h"
#include "btree.h"

#include <QMainWindow>

namespace Ui {
class ProfileUser;
}

class ProfileUser : public QMainWindow
{
    Q_OBJECT

public:
    // explicit ProfileUser(QWidget *parent = nullptr);
    explicit ProfileUser(QWidget *parent = nullptr, const QString &name = "", const QString &lastname = "", const QString &email = "", const QString &password = "", const QString &date = "");
    ~ProfileUser();
    void cargaData(AVLTree* arbol, ListaDePublicaciones* lista, ABB* abbsi, BTree* btreesi);

private slots:

    void on_actionLog_out_triggered();

    void on_actionSearch_triggered();

    void on_actionPosts_triggered();

    void on_actionFriend_Requests_triggered();

    void on_actionReports_triggered();

    void on_actionProfile_triggered();

    void on_actionInformation_triggered();

    void on_pushButton_edit_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_search_fromuser_clicked();

    void on_pushButton_generareporte_clicked();

    void on_pushButton_hidebtn_clicked();

    void on_pushButton_aplicarorden_clicked();

private:
    Ui::ProfileUser *ui;
    bool editPerformed;
    AVLTree* arbolUsuariosGeneral;
    ListaDePublicaciones* listaDoblePublicaciones;
    ABB* abbPublicaciones;
    BTree* btreeComentarios;
};

#endif // PROFILEUSER_H
