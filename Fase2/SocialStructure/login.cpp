#include "login.h"
#include "ui_login.h"
#include "QMessageBox"
#include "avltree.h"
#include "listapublicaciones.h"
#include "abb.h"
#include "btree.h"

AVLTree* arbolUsuariosGeneral = new AVLTree();
ListaDePublicaciones* listaDoblePublicaciones = new ListaDePublicaciones();
ABB* abbPublicaciones = new ABB();
BTree* btreeComentarios = new BTree();

Usuario* usuarioensesion;

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    // profileAdministrator = new ProfileAdministrator(); /*teamo moshi*/
}

Login::~Login()
{
    delete ui;
}

// try to login
void Login::on_pushButton_login_clicked()
{
    QString adminEmail = "3312"; //"admin@gmail.com"
    QString adminPassword = "3312"; //"EDD2S2024"

    QString username = ui->lineEdit_email->text();  // Obtener el email ingresado
    QString password = ui->lineEdit_password->text();  // Obtener la contraseña ingresada

    // Llama a la función preordenLogin para verificar las credenciales
    Usuario* usuarioEncontrado = arbolUsuariosGeneral->preordenLogin(arbolUsuariosGeneral->raiz, username, password);

    // Definición del estilo para el QMessageBox
    QString messageBoxStyle = "QMessageBox { background-color: #f0f0f0; color: #333333; }"
                              "QPushButton { background-color: rgb(16, 16, 16); color: white; padding: 5px 7px 5px 7px; }"
                              "QPushButton:hover { background-color: rgb(0, 0, 0); }";

    // Verifica si las credenciales del administrador son correctas
    if (username == adminEmail && password == adminPassword) {
        QMessageBox msgBox;
        msgBox.setText("Login successful as administrator");
        msgBox.setWindowTitle("Login");
        msgBox.setStyleSheet(messageBoxStyle);
        msgBox.exec();

        hide();  // Oculta la ventana de login
        profileAdministrator = new ProfileAdministrator();  // Crea la ventana de perfil del administrador
        profileAdministrator->show();
        profileAdministrator->cargaArchivo(arbolUsuariosGeneral, listaDoblePublicaciones, abbPublicaciones, btreeComentarios);  // Carga datos del árbol
    }
    // Verifica si se encontró un usuario
    else if (usuarioEncontrado != nullptr) {
        usuarioensesion = usuarioEncontrado; // usuario en sesion actual
        QString emailsi = usuarioEncontrado->correo;
        QString passwordsi = usuarioEncontrado->contrasena;
        QString nombresi = usuarioEncontrado->nombres;
        QString apellidosi = usuarioEncontrado->apellidos;
        QString cum = usuarioEncontrado->fechaNacimiento;
        
        QMessageBox msgBox;
        msgBox.setText("Login successful as user");
        msgBox.setWindowTitle("Login");
        msgBox.setStyleSheet(messageBoxStyle);
        msgBox.exec();

        hide();  // Oculta la ventana de login
        // profileUser = new ProfileUser();  // Crea la ventana de perfil del usuario
        ProfileUser *profileUser = new ProfileUser(nullptr, nombresi, apellidosi, emailsi, passwordsi, cum);
        profileUser->show();
        profileUser->cargaData(arbolUsuariosGeneral, listaDoblePublicaciones, abbPublicaciones, btreeComentarios);
    }
    // Si no se encuentra el usuario o las credenciales son incorrectas
    else {
        QMessageBox msgBox;
        msgBox.setText("Incorrect email or password");
        msgBox.setWindowTitle("Login");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStyleSheet(messageBoxStyle);
        msgBox.exec();

        // No ocultar ni cerrar la ventana de Login, el usuario debe poder intentarlo de nuevo
    }
}

// registrarse
void Login::on_pushButton_createacc_clicked()
{
    qDebug() << "Recorrido en orden:";
    arbolUsuariosGeneral->enorden(arbolUsuariosGeneral->raiz);  // Imprime el recorrido en orden
    hide();
    registrarUsuario = new RegistrarUsuario(arbolUsuariosGeneral);
    registrarUsuario->show();
}

