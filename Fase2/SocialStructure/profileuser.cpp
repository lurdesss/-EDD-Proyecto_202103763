#include "profileuser.h"
#include "ui_profileuser.h"
#include "login.h"
#include "QMessageBox"
#include "globals.h"

QString valorEntradaEn;
QString correollegada;

// ProfileUser::ProfileUser(QWidget *parent)
ProfileUser::ProfileUser(QWidget *parent, const QString &name, const QString &lastname, const QString &email, const QString &password, const QString &date)
    : QMainWindow(parent)
    , ui(new Ui::ProfileUser), editPerformed(false)
{
    ui->setupUi(this);
    ui->awidget_buscar->hide();
    ui->awidget_publicaciones->hide();
    ui->awidget_reportes->hide();
    ui->awidget_solicitudes->hide();
    ui->widget->show();

    // Asignar los valores a los QLineEdit correspondientes
    ui->lineEdit_nameuser_2->setText(name);
    ui->lineEdit_lastnameuser_2->setText(lastname);
    ui->lineEdit_emailuser_2->setText(email);
    ui->lineEdit_passworduser_2->setText(password);
    ui->lineEdit_dateuser_2->setText(date);

    // line edits
    ui->lineEdit_nameuser_2->setEnabled(false);
    ui->lineEdit_passworduser_2->setEnabled(false);
    ui->lineEdit_emailuser_2->setEnabled(false);
    ui->lineEdit_dateuser_2->setEnabled(false);
    ui->lineEdit_lastnameuser_2->setEnabled(false);

    valorEntradaEn = name + " " + lastname;
    correollegada = email;
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
    ui->awidget_publicaciones->hide();
    ui->awidget_reportes->hide();
    ui->awidget_solicitudes->hide();
    ui->widget->hide();
    ui->awidget_buscar->show();
}


void ProfileUser::on_actionPosts_triggered()
{
    ui->awidget_buscar->hide();
    ui->awidget_reportes->hide();
    ui->awidget_solicitudes->hide();
    ui->widget->hide();
    ui->awidget_publicaciones->show();
    ui->label_useractual->show();
    ui->label_useractual->setText(valorEntradaEn);
}


void ProfileUser::on_actionFriend_Requests_triggered()
{
    ui->awidget_buscar->hide();
    ui->awidget_publicaciones->hide();
    ui->awidget_reportes->hide();
    ui->widget->hide();
    ui->awidget_solicitudes->show();
}


void ProfileUser::on_actionReports_triggered()
{
    ui->awidget_buscar->hide();
    ui->awidget_publicaciones->hide();
    ui->awidget_solicitudes->hide();
    ui->widget->hide();
    ui->awidget_reportes->show();
    ui->label_imagereportehere->hide();
}


void ProfileUser::on_actionProfile_triggered()
{
    ui->awidget_buscar->hide();
    ui->awidget_publicaciones->hide();
    ui->awidget_reportes->hide();
    ui->awidget_solicitudes->hide();
    ui->widget->show();
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


void ProfileUser::on_pushButton_edit_clicked()
{
    editPerformed = true;
    // habilitar lineEdit
    ui->lineEdit_nameuser_2->setEnabled(true);
    ui->lineEdit_passworduser_2->setEnabled(true);
    ui->lineEdit_emailuser_2->setEnabled(true);
    ui->lineEdit_dateuser_2->setEnabled(true);
    ui->lineEdit_lastnameuser_2->setEnabled(true);
}


void ProfileUser::on_pushButton_save_clicked()
{
    // Verificar que los campos no estén vacíos
    if (ui->lineEdit_nameuser_2->text().isEmpty() ||
        ui->lineEdit_lastnameuser_2->text().isEmpty() ||
        ui->lineEdit_dateuser_2->text().isEmpty() ||
        ui->lineEdit_passworduser_2->text().isEmpty() ||
        ui->lineEdit_emailuser_2->text().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Campos vacíos");
        msgBox.setText("Por favor, complete todos los campos antes de guardar.");
        msgBox.setIcon(QMessageBox::Warning);

        QString messageBoxStyle = "QMessageBox { background-color: #f0f0f0; color: #333333; }"
                                  "QPushButton { background-color: rgb(16, 16, 16); color: white; padding: 5px 7px 5px 7px; }"
                                  "QPushButton:hover { background-color: rgb(0, 0, 0); }";
        msgBox.setStyleSheet(messageBoxStyle);

        msgBox.exec();
        return; // Terminar la función si hay campos vacíos
    }
    // verificar si existE globalEmail EN SISTEMA, si no existe guardar -> caso contrario MOSTRAR ADVERTENCIA Y NO GUARDAR AUN
    // Guardar los valores de los QLineEdit en las variables globales
    globalName = ui->lineEdit_nameuser_2->text();
    globalLastname = ui->lineEdit_lastnameuser_2->text();
    globalDate = ui->lineEdit_dateuser_2->text();
    globalPassword = ui->lineEdit_passworduser_2->text();
    globalEmail = ui->lineEdit_emailuser_2->text();

    editPerformed = false;

    // Opcional: Mostrar un mensaje de confirmacióN
    qDebug() << "DATOS DE USUARIO (MODIFICADOS) Y GUARDADOS:";
    qDebug() << "Nombre:" << globalName;
    qDebug() << "Apellido:" << globalLastname;
    qDebug() << "Fecha:" << globalDate;
    qDebug() << "Contraseña:" << globalPassword;
    qDebug() << "Correo electrónico:" << globalEmail;

    // Deshabilitar lineEdit
    ui->lineEdit_nameuser_2->setEnabled(false);
    ui->lineEdit_passworduser_2->setEnabled(false);
    ui->lineEdit_emailuser_2->setEnabled(false);
    ui->lineEdit_dateuser_2->setEnabled(false);
    ui->lineEdit_lastnameuser_2->setEnabled(false);
}


void ProfileUser::on_pushButton_delete_clicked()
{
    // Verificar si la acción de edición se ha realizado
    if (!editPerformed)
    {
        // Aquí van las condiciones antes de realizar la eliminación
        // Guardar los valores de los QLineEdit en las variables globales
        globalName = ui->lineEdit_nameuser_2->text();
        globalLastname = ui->lineEdit_lastnameuser_2->text();
        globalDate = ui->lineEdit_dateuser_2->text();
        globalPassword = ui->lineEdit_passworduser_2->text();
        globalEmail = ui->lineEdit_emailuser_2->text();

        // Opcional: Mostrar un mensaje de confirmación o realizar otras acciones
        qDebug() << "USUARIO ELIMINADO:";
        qDebug() << "Nombre:" << globalName;
        qDebug() << "Apellido:" << globalLastname;
        qDebug() << "Fecha:" << globalDate;
        qDebug() << "Contraseña:" << globalPassword;
        qDebug() << "Correo electrónico:" << globalEmail;

        //prof->action();
        //Login* login = new Login();  // No le pases 'this' como padre

        // Mostrar la ventana de Login
        //login->show();

    }
    else
    {
        // Si no se ha realizado la edición, puedes mostrar un mensaje
        QMessageBox::warning(this, "Acción no permitida", "Debe realizar la edición antes de eliminar.");
    }
}

void ProfileUser::cargaData(AVLTree* arbol, ListaDePublicaciones* lista, ABB* abbsi, BTree* btreesi) {
    this->arbolUsuariosGeneral = arbol;  // Asignar el árbol
    this->listaDoblePublicaciones = lista;  // Asignar la lista de publicaciones
    this->abbPublicaciones = abbsi; // Asignar la lista de publicaciones
    this->btreeComentarios = btreesi; // Asignar la lista de comentarios de publicaciones
}

void ProfileUser::on_pushButton_search_fromuser_clicked()
{
    QString usrbuscado = ui->lineEdit_search_email_userbus->text();
    Usuario* usrfoundAt = arbolUsuariosGeneral->preordenBuscarCorreo(arbolUsuariosGeneral->raiz, usrbuscado);
    qDebug() << usrfoundAt;

    if(usrfoundAt != nullptr){
        qDebug() << "Usuario encontrado";
        qDebug() << "Nombre: " << usrfoundAt->nombres;
        qDebug() << "Apellido: " << usrfoundAt->apellidos;
        qDebug() << "Correo: " << usrfoundAt->correo;
        qDebug() << "Contraseña: " << usrfoundAt->contrasena;
        qDebug() << "Fecha de nacimiento: " << usrfoundAt->fechaNacimiento;
        ui->lineEdit_nameuser_3->clear();
        ui->lineEdit_lastnameuser_3->clear();
        ui->lineEdit_emailuser_3->clear();
        ui->lineEdit_dateuser_3->clear();

        ui->lineEdit_nameuser_3->insert(usrfoundAt->nombres);
        ui->lineEdit_lastnameuser_3->insert(usrfoundAt->apellidos);
        ui->lineEdit_emailuser_3->insert(usrfoundAt->correo);
        ui->lineEdit_dateuser_3->insert(usrfoundAt->fechaNacimiento);
    }else{
        QMessageBox::warning(this, "Usuario no encontrado", "El usuario buscado no existe.");
    }
}


void ProfileUser::on_pushButton_generareporte_clicked()
{   
    ui->label_imagereportehere->show();
    // Obtener el nodo del árbol del usuario actual
    Node* NodoTemp = arbolUsuariosGeneral->preordenBuscarCorreoNodo(arbolUsuariosGeneral->raiz, correollegada);
    
    // Verificar si se encontró el nodo
    if (!NodoTemp || !NodoTemp->abbcadausr) {
        QMessageBox::warning(this, "Error", "Usuario no encontrado o sin árbol.");
        return;
    }

    // Generar el archivo DOT y la imagen PNG del ABB de publicaciones del usuario
    NodoTemp->abbcadausr->exportToDotAndGenerateImage();

    // Ruta de la imagen generada
    QString rutaImagen = "../../salida/arbol.png";

    // Mostrar la imagen generada en el QLabel
    QPixmap pixmap(rutaImagen);
    if (!pixmap.isNull()) {
        ui->label_imagereportehere->setPixmap(pixmap);
        ui->label_imagereportehere->setScaledContents(true);  // Ajustar la imagen al tamaño del QLabel
        // ui->label_imagereportehere->show();
    } else {
        QMessageBox::warning(this, "Error", "No se pudo cargar la imagen generada.");
    }
}



void ProfileUser::on_pushButton_hidebtn_clicked()
{
    ui->label_imagereportehere->hide();
}

void ProfileUser::on_pushButton_aplicarorden_clicked()
{
    // Obtener el índice actual del QComboBox
    int index = ui->comboBox_ordenpost->currentIndex();
    QString resultado;

    qDebug() << correollegada + " si";
    Node* NodoTemp = arbolUsuariosGeneral->preordenBuscarCorreoNodo(arbolUsuariosGeneral->raiz, correollegada);
    
    // Verificar si se encontró el nodo
    if (!NodoTemp || !NodoTemp->abbcadausr) {
        QMessageBox::warning(this, "Error", "Usuario no encontrado o sin árbol.");
        return;
    }

    // Ejecutar el recorrido del ABB según la opción seleccionada
    switch (index) {
    case 0: // Preorden
        resultado = NodoTemp->abbcadausr->preorderAtProfile(NodoTemp->abbcadausr->raiz); // Ejecutar preorden
        break;
    case 1: // Postorden
        resultado = NodoTemp->abbcadausr->posorderAtProfile(NodoTemp->abbcadausr->raiz); // Ejecutar postorden
        break;
    case 2: // Inorden
        resultado = NodoTemp->abbcadausr->inorderAtProfile(NodoTemp->abbcadausr->raiz); // Ejecutar inorden
        break;
    default:
        resultado = "Seleccione un recorrido válido";
        break;
    }

    // Mostrar el resultado en el label
    ui->label_imagenamostrar->setText(resultado);
    qDebug() << resultado; // Esto es opcional, para verificar en la consola
}
