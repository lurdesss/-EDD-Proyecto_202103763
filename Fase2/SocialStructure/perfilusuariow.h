#ifndef PERFILUSUARIOW_H
#define PERFILUSUARIOW_H

#include <QWidget>

namespace Ui {
class PerfilUsuarioW;
}

class PerfilUsuarioW : public QWidget
{
    Q_OBJECT

public:
    explicit PerfilUsuarioW(QWidget *parent = nullptr);
    ~PerfilUsuarioW();

private slots:

    void on_pushButton_edit_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_delete_clicked();

private:
    Ui::PerfilUsuarioW *ui;
};

#endif // PERFILUSUARIOW_H
