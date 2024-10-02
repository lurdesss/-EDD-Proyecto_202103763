#include "registrarusuario.h"
#include "ui_registrarusuario.h"
#include "login.h" // para salir
#include <QCoreApplication> // cerrar app
#include <QMessageBox>
#include "globals.h"
#include <QDir>  // Para manejar rutas


RegistrarUsuario::RegistrarUsuario(AVLTree* arbolUsuarios, QWidget *parent)
    : QMainWindow(parent), arbolUsuariosGeneral(arbolUsuarios)
    , ui(new Ui::RegistrarUsuario)
{
    ui->setupUi(this);
}

RegistrarUsuario::~RegistrarUsuario()
{
    delete ui;
}

// void RegistrarUsuario::cargaData(AVLTree* arbol)
// {
//     this->arbolUsuariosGeneral = arbol;  // Asignar el árbol recibido
// }

void RegistrarUsuario::on_pushButton_savenewuser_clicked()
{   
    qDebug() << "Recorrido en orden:";
    arbolUsuariosGeneral->enorden(arbolUsuariosGeneral->raiz);
    // if (!arbolUsuariosGeneral) {
    //     QMessageBox::warning(this, "Error", "El árbol de usuarios no está inicializado.");
    //     return;
    // }
    try {
        // Your code that might throw an exception
        // Verificar que los campos no estén vacíos
        if (ui->lineEdit_nameuser_new->text().isEmpty() ||
            ui->lineEdit_lastnameuser_new->text().isEmpty() ||
            ui->lineEdit_dateuser_new->text().isEmpty() ||
            ui->lineEdit_passworduser_new->text().isEmpty() ||
            ui->lineEdit_emailuser_new->text().isEmpty())
        {
            // Crear el QMessageBox y aplicar el estilo
            QMessageBox msgBox;
            msgBox.setWindowTitle("Campos vacíos");
            msgBox.setText("Por favor, complete todos los campos antes de guardar.");
            msgBox.setIcon(QMessageBox::Warning);

            // Aplicar el estilo al QMessageBox
            QString messageBoxStyle = "QMessageBox { background-color: #f0f0f0; color: #333333; }"
                                    "QPushButton { background-color: rgb(16, 16, 16); color: white; padding: 5px 7px 5px 7px; }"
                                    "QPushButton:hover { background-color: rgb(0, 0, 0); }";
            msgBox.setStyleSheet(messageBoxStyle);

            msgBox.exec();
            return; // Terminar la función si hay campos vacíos
        }

        // Guardar los valores de los QLineEdit en las variables globales
        globalName = ui->lineEdit_nameuser_new->text();
        globalLastname = ui->lineEdit_lastnameuser_new->text();
        globalDate = ui->lineEdit_dateuser_new->text();
        globalPassword = ui->lineEdit_passworduser_new->text();
        globalEmail = ui->lineEdit_emailuser_new->text();


        qDebug() << "DATOS DE USUARIO NUEVO:";
        qDebug() << "Nombre:" << globalName;
        qDebug() << "Apellido:" << globalLastname;
        qDebug() << "Fecha:" << globalDate;
        qDebug() << "Contraseña:" << globalPassword;
        qDebug() << "Correo electrónico:" << globalEmail;
        
        Usuario* user = arbolUsuariosGeneral->buscarPorCorreo(globalEmail);
        if (user == nullptr) {
            // caso de registro
            Usuario* nuevoUsuario = new Usuario(globalName, globalLastname, globalDate, globalEmail, globalPassword);
            arbolUsuariosGeneral->add(nuevoUsuario);
            // Opcional: Mostrar un mensaje de confirmación o realizar otras acciones
            qDebug() << "DATOS DE USUARIO NUEVO:";
            qDebug() << "Nombre:" << globalName;
            qDebug() << "Apellido:" << globalLastname;
            qDebug() << "Fecha:" << globalDate;
            qDebug() << "Contraseña:" << globalPassword;
            qDebug() << "Correo electrónico:" << globalEmail;

            // actualizando avl
            arbolUsuariosGeneral->generateDot("arbol_avl.dot");

            // Generar la ruta completa para el archivo .dot y la imagen .png
            QString rutaSalida = QDir::currentPath() + "../../../salida/";
            QString rutaDot = rutaSalida + "arbol_avl.dot";
            QString rutaPng = rutaSalida + "arbol_avl.png";

            // Ejecutar el comando para generar la imagen y capturar la salida
            QString comando = "dot -Tpng " + rutaDot + " -o " + rutaPng + " 2>&1";
            FILE* pipe = popen(comando.toUtf8().constData(), "r");

            if (!pipe) {
                qDebug() << "Error al ejecutar el comando dot.";
                return;
            }

            // Leer la salida del comando
            char buffer[128];
            QString result;
            while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
                result += QString::fromUtf8(buffer);
            }
            pclose(pipe);

            // Imprimir el resultado del comando
            if (!result.isEmpty()) {
                qDebug() << "Salida de dot:" << result;
            } else {
                qDebug() << "Archivo PNG generado exitosamente.";
            }

        } else {
            // caso denegado
            std::cout << "Usuario encontrado: " << user->nombres.toStdString() << " " << user->apellidos.toStdString() << std::endl;
        }

    } catch (const std::exception& e) {
        QString errorMsg = QString("Error al generar el archivo DOT: %1").arg(e.what());
        QMessageBox::warning(this, "Error", errorMsg);
        return;
    }
}


void RegistrarUsuario::on_pushButton_backtologin_clicked()
{
    // Ocultar o cerrar la ventana actual
    close();  // Esto cerrará completamente la ventana

    // Crear una nueva instancia de Login
    Login* login = new Login();

    // Mostrar la ventana de Login
    login->show();
}


void RegistrarUsuario::on_pushButton_closeapp_clicked()
{
    QCoreApplication::quit();
}