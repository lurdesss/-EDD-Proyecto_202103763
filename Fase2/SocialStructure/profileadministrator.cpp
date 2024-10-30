#include "profileadministrator.h"
#include "ui_profileadministrator.h"
#include "login.h"
#include <QMessageBox>
#include <QDebug>
#include <fstream>
#include "nlohmann/json.hpp"
#include <QDir>  // Para manejar rutas
#include <QFile> 
#include <QImage>       // Para cargar la imagen
#include <QPixmap> 
#include <QTimer>
#include <QSignalMapper>
#include "contador.h"
#include <map>

using json = nlohmann::json;

QString rutaBase = "/home/lurdes/Escritorio/datastructures/-EDD-Proyecto_202103763/Fase2/SocialStructure/";

ProfileAdministrator::ProfileAdministrator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ProfileAdministrator)
{
    ui->setupUi(this);
    ui->widget_buscarsi->show();
    ui->widget_cargasi->hide();
    ui->widget_reportessi->hide();
    
    
}

ProfileAdministrator::~ProfileAdministrator()
{
    delete ui;
}

// pestana carga start
void ProfileAdministrator::on_actioncargamasiva_triggered()
{
    ui->widget_buscarsi->hide();
    ui->widget_cargasi->show();
    ui->widget_reportessi->hide();
    
    
}

// Nueva función para recibir el árbol desde el login
void ProfileAdministrator::cargaArchivo(AVLTree* arbol, ListaDePublicaciones* lista, ABB* abbsi, BTree* btreesi, PilaSolicitudes* pilasol, ListaSimpleSolicitudes* listasol, ListOfList* listooflst) {
    this->arbolUsuariosGeneral = arbol;  // Asignar el árbol
    this->listaDoblePublicaciones = lista;  // Asignar la lista de publicaciones
    this->abbPublicaciones = abbsi; // Asignar la lista de publicaciones
    this->btreeComentarios = btreesi; // Asignar la lista de comentarios de publicaciones
    this->pilaSolicitudes = pilasol; // Asigna a la pila de solicitudes
    this->listaSolicitudes = listasol; // Asigna a la lista de solicitudes
    this->listOfList = listooflst; // Asigna a la lista de soicitudes
    //this->frequencyList = frequencylst; //  lista de frecuencia
}

void ProfileAdministrator::on_pushButton_cargausuarios_clicked()
{
    // Verificar que el árbol no sea nulo
    if (!arbolUsuariosGeneral) {
        QMessageBox::warning(this, "Error", "El árbol de usuarios no está inicializado.");
        return;
    }

    // Obtener el nombre del archivo desde el QLineEdit
    QString nombreArchivo = ui->lineEdit_cargausuarios->text();

    // Verificar si el nombre del archivo no está vacío
    if (nombreArchivo.isEmpty()) {
        QMessageBox::warning(this, "Error", "Por favor ingrese un nombre de archivo.");
        return;
    }

    // Construir la ruta completa: carpeta 'files' dentro del proyecto
    QString relative = "/files/";
    QString rutaCompleta = rutaBase + relative + nombreArchivo;

    // Abrir el archivo JSON usando ifstream
    std::ifstream file(rutaCompleta.toStdString());
    if (!file.is_open()) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo: " + rutaCompleta);
        return;
    }

    // Leer el contenido JSON
    json jsonData;
    try {
        file >> jsonData;
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", "Error al leer el archivo JSON.");
        return;
    }

    // Cerrar el archivo después de leerlo
    file.close();

    // Procesar los datos del archivo JSON
    for (const auto& user : jsonData) {
        QString nombres = QString::fromStdString(user["nombres"].get<std::string>());
        QString apellidos = QString::fromStdString(user["apellidos"].get<std::string>());
        QString fechaNacimiento = QString::fromStdString(user["fecha_de_nacimiento"].get<std::string>());
        QString correo = QString::fromStdString(user["correo"].get<std::string>());
        QString contrasena = QString::fromStdString(user["contraseña"].get<std::string>());

        // Crear un nuevo usuario
        int nuevoId = contadorId++;
        Usuario* nuevoUsuario = new Usuario(nuevoId, nombres, apellidos, fechaNacimiento, correo, contrasena);

        // Insertar el usuario en el árbol AVL
        arbolUsuariosGeneral->add(nuevoUsuario);

        // Mostrar recorridos
        qDebug() << "Recorrido en orden:";
        arbolUsuariosGeneral->enorden(arbolUsuariosGeneral->raiz);  // Imprime el recorrido en orden
        qDebug() << "Recorrido preorden:";
        arbolUsuariosGeneral->preorden(arbolUsuariosGeneral->raiz);  // Imprime el recorrido en preorden
        qDebug() << "Recorrido postorden:";
        arbolUsuariosGeneral->postorden(arbolUsuariosGeneral->raiz);  // Imprime el recorrido en postorden
        qDebug() << "Usuario agregado:" << nuevoUsuario->correo;
        qDebug() << "Id usuario: " << nuevoUsuario->id;
    }

    // Generar el archivo dot y la imagen PNG
    arbolUsuariosGeneral->generateDot("arbol_avl.dot");

    // Generar la ruta completa para el archivo .dot y la imagen .png
    QString rutaSalida = rutaBase + "salida/";
    QString rutaDot = rutaSalida + "arbol_avl.dot";
    QString rutaPng = rutaSalida + "arbol_avl.png";

    // Ejecutar el comando para generar la imagen
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
}


void ProfileAdministrator::on_pushButton_cargasolicitudes_clicked()
{

    // Obtener el nombre del archivo desde el QLineEdit
    QString nombreArchivo = ui->lineEdit_cargasolicitudes->text();

    // Verificar si el nombre del archivo no está vacío
    if (nombreArchivo.isEmpty()) {
        QMessageBox::warning(this, "Error", "Por favor ingrese un nombre de archivo.");
        return;
    }

    // Construir la ruta completa: carpeta 'files' dentro del proyecto
    QString relative = "files/";
    QString rutaCompleta = rutaBase + relative + nombreArchivo;     // Concatenar la ruta base con el nombre del archivo

    // Abrir el archivo JSON usando ifstream
    std::ifstream file(rutaCompleta.toStdString());
    if (!file.is_open()) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo: " + rutaCompleta);
        return;
    }

    // Leer el contenido JSON
    json jsonData;
    try {
        file >> jsonData;
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", "Error al leer el archivo JSON.");
        return;
    }

    // Cerrar el archivo después de leerlo
    file.close();

    // Procesar los datos del archivo JSON y mostrarlos con qDebug
    for (const auto& solicitud : jsonData) {
        QString emisor = QString::fromStdString(solicitud["emisor"].get<std::string>());
        QString receptor = QString::fromStdString(solicitud["receptor"].get<std::string>());
        QString estado = QString::fromStdString(solicitud["estado"].get<std::string>());

        // Imprimir los datos de la solicitud con qDebug
        qDebug() << "Emisor:" << emisor;
        qDebug() << "Receptor:" << receptor;
        qDebug() << "Estado:" << estado;
        qDebug() << "-------------------------------";

        // Verificar si ya existe una solicitud aceptada entre emisor y receptor o viceversa
        bool existeAceptada = listaSolicitudesEnviadas.existeSolicitudAceptada(emisor.toStdString(), receptor.toStdString()) ||
                              listaSolicitudesEnviadas.existeSolicitudAceptada(emisor.toStdString(), receptor.toStdString());


        // Verificar si ya existe una solicitud pendiente del emisor al receptor o viceversa
        bool existePendiente = listaSolicitudesEnviadas.existeSolicitudPendiente(emisor.toStdString(), receptor.toStdString()) ||
                               listaSolicitudesEnviadas.existeSolicitudPendiente(emisor.toStdString(), receptor.toStdString());


        if (estado == "PENDIENTE") {
            if (existeAceptada) {
                // Si ya hay una solicitud aceptada, se elimina cualquier solicitud pendiente existente
                listaSolicitudesEnviadas.eliminarSolicitud(emisor.toStdString(), receptor.toStdString(), "PENDIENTE");
                listaSolicitudesEnviadas.eliminarSolicitud(receptor.toStdString(), emisor.toStdString(), "PENDIENTE");
            } else if (!existePendiente) {
                // Si no hay una solicitud pendiente, se agrega la solicitud pendiente
                listaSolicitudesEnviadas.agregarSolicitud(emisor.toStdString(), receptor.toStdString(), estado.toStdString());

                cout << "La solicitud de " << emisor.toStdString() << " a " << receptor.toStdString() << " ha sido añadida en estado: PENDIENTE" << endl;
            }
        } else if (estado == "ACEPTADA") {
            if (existePendiente) {
                // Si existe una solicitud pendiente, se elimina y se cambia el estado a "ACEPTADA"
                listaSolicitudesEnviadas.eliminarSolicitud(emisor.toStdString(), receptor.toStdString(), "PENDIENTE");
                listaSolicitudesEnviadas.eliminarSolicitud(receptor.toStdString(), emisor.toStdString(), "PENDIENTE");
                cout << "La solicitud PENDIENTE de " << emisor.toStdString() << " a " << receptor.toStdString() << " ha sido añadida A: ACEPTADA CAMBIO" << endl;
                // se debe añadir a matriz
            }
            if (!existeAceptada) { // no deberia negarse ?
                // Inserta en la matriz de amigos y agrega la solicitud aceptada
                cout << "La solicitud de " << emisor.toStdString() << " a " << receptor.toStdString() << " ha sido añadida con estado: ACEPTADA DEFECTO" << endl;
                
                Usuario* thisemisor = arbolUsuariosGeneral->preordenBuscarCorreo(arbolUsuariosGeneral->raiz, emisor);
                qDebug() << thisemisor;
                int emisorId = thisemisor->id;
                std::string emisorName = thisemisor->nombres.toStdString();
                Usuario* thisreceptor = arbolUsuariosGeneral->preordenBuscarCorreo(arbolUsuariosGeneral->raiz, receptor);
                qDebug() << thisreceptor;
                int receptorId = thisreceptor->id;
                std::string receptorName = thisreceptor->nombres.toStdString();
                listOfList->insert(emisorId, receptorId, emisorName, receptorName);
                qDebug() << "llamo a print ----------------";
                listOfList->print();
                qDebug() << "end -----------------";
                listOfList->graph();

                listOfList->graphMeFriendsAndTheirFriends("Fase2");
                //gasdgsa =new Lisat ....();
                //listOfList->funcion(usuario, lista);

                listOfList->graphOfAdyacencia();
                }
            }
        }
    }


void ProfileAdministrator::on_pushButton_cargapublicaciones_clicked()
{

    // Obtener el nombre del archivo desde el QLineEdit
    QString nombreArchivo = ui->lineEdit_cargapublicaciones->text();

    // Verificar si el nombre del archivo no está vacío
    if (nombreArchivo.isEmpty()) {
        QMessageBox::warning(this, "Error", "Por favor ingrese un nombre de archivo.");
        return;
    }

    // Construir la ruta completa: carpeta 'files' dentro del proyecto
    QString relative = "files/";
    QString rutaCompleta = rutaBase + relative + nombreArchivo;  // Concatenar la ruta base con el nombre del archivo

    // Abrir el archivo JSON usando ifstream
    std::ifstream file(rutaCompleta.toStdString());
    if (!file.is_open()) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo: " + rutaCompleta);
        return;
    }

    // Leer el contenido JSON
    json jsonData;
    try {
        file >> jsonData;
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", "Error al leer el archivo JSON.");
        return;
    }

    // Cerrar el archivo después de leerlo
    file.close();

    // Procesar los datos del archivo JSON y mostrarlos con qDebug
    for (const auto& publicacion : jsonData) {
        QString correo = QString::fromStdString(publicacion["correo"].get<std::string>());
        QString contenido = QString::fromStdString(publicacion["contenido"].get<std::string>());
        QString fecha = QString::fromStdString(publicacion["fecha"].get<std::string>());
        QString hora = QString::fromStdString(publicacion["hora"].get<std::string>());


        listaDoblePublicaciones->agregarPublicacion(correo, contenido, fecha, hora);
        listaDoblePublicaciones->mostrarPublicaciones();

        Node* NodoTmp = arbolUsuariosGeneral->preordenBuscarCorreoNodo(arbolUsuariosGeneral->raiz, correo);
        
        Publicaciones* publi = new Publicaciones(correo, contenido, fecha, hora);


        NodoTmp->abbcadausr->add(publi);



        // recorrer arbolUsuarios listaUsuariosGeneral

        // Procesar comentarios si existen
        if (publicacion.contains("comentarios")) {
            const auto& comentarios = publicacion["comentarios"];
            for (const auto& comentario : comentarios) {
                QString correoComentario = QString::fromStdString(comentario["correo"].get<std::string>());
                QString textoComentario = QString::fromStdString(comentario["comentario"].get<std::string>());
                QString fechaComentario = QString::fromStdString(comentario["fecha"].get<std::string>());
                QString horaComentario = QString::fromStdString(comentario["hora"].get<std::string>());

                // si

                Comentario* come = new Comentario(correoComentario,textoComentario,fechaComentario,horaComentario);
                NodoTmp->abbcadausr->raiz->nodoAB->insert(come);
                //qDebug() << "si ccomentarios";
                //NodoTmp->abbcadausr->raiz->nodoAB->printTree(NodoTmp->abbcadausr->raiz->nodoAB->root);
                //qDebug() << "traversal";
                //NodoTmp->abbcadausr->raiz->nodoAB->traversal(NodoTmp->abbcadausr->raiz->nodoAB->root);
                //qDebug() << NodoTmp->abbcadausr->raiz->nodoAB->root->val[1]->comentario.toStdString();
                //qDebug() << "comentarios estan arriba";
            }
        }

        qDebug() << "-------------------------------";

        
    }


    std::cerr << "ya jalo tu :D" << std::endl;
    Node* NodoTemp = arbolUsuariosGeneral->preordenBuscarCorreoNodo(arbolUsuariosGeneral->raiz, "jm@example.com");
    //0NodoTemp->abbcadausr->preorder(NodoTemp->abbcadausr->raiz);
    qDebug() << "------------------------------- aca";
    NodoTemp->abbcadausr->raiz->nodoAB->traversal(NodoTemp->abbcadausr->raiz->nodoAB->root);
    // std::cout << std::endl;


    listaDoblePublicaciones->generateDot("publicaciones.dot");
    listaDoblePublicaciones->renderGraphviz("publicaciones.dot", "publicaciones.png");

    

}


void ProfileAdministrator::on_actionbuscar_triggered()
{
    ui->widget_buscarsi->show();
    ui->widget_cargasi->hide();
    ui->widget_reportessi->hide();
    
    
}


void ProfileAdministrator::on_actionclosesesionadmin_triggered()
{
    close();  // Esto cerrará completamente la ventana de ProfileUser
    Login* login = new Login();  // No le pases 'this' como padre
    login->show();
}

// pestana reportes start
void ProfileAdministrator::on_actionreportes_triggered()
{
    ui->widget_buscarsi->hide();
    ui->widget_cargasi->hide();
    ui->widget_reportessi->show();
    
    

    // reportes
    ui->label_tituloavlsi->hide();
    ui->label_foradminavltreesi->hide();
    ui->label_titulolistasi->hide();
    ui->label_forlistadepostssi->hide();

}


void ProfileAdministrator::on_pushButton_reportesfromadminsi_clicked()
{   
    ui->label_titulolistasi->hide();
    ui->label_forlistadepostssi->hide();
    ui->label_tituloavlsi->show();
    ui->label_foradminavltreesi->show();
    // Definir la ruta completa de la imagen
    QString rutaImagen = rutaBase + "salida/arbol_avl.png";

    // Verificar si la imagen existe
    if (!QFile::exists(rutaImagen)) {
        QMessageBox::warning(this, "Error", "No se encontró la imagen en la ruta: " + rutaImagen);
        return;
    }

    // Cargar la imagen desde la ruta
    QImage image(rutaImagen);

    // Verificar si la imagen se cargó correctamente
    if (image.isNull()) {
        QMessageBox::warning(this, "Error", "Error al cargar la imagen: " + rutaImagen);
        return;
    }

    // Asignar la imagen a un QLabel
    ui->label_foradminavltreesi->setPixmap(QPixmap::fromImage(image));

    // Ajustar el tamaño del QLabel para que se ajuste a la imagen
    ui->label_foradminavltreesi->setScaledContents(true);
}


void ProfileAdministrator::on_pushButton_searchemail_admin_clicked()
{   
    QString userfound = ui->lineEdit_searchemail_admin->text();

    Usuario* usuarioEncontrado = arbolUsuariosGeneral->preordenBuscarCorreo(arbolUsuariosGeneral->raiz, userfound);
    qDebug() << usuarioEncontrado;
    
    if(usuarioEncontrado != nullptr){
        qDebug() << "Usuario encontrado";
        qDebug() << "Nombre: " << usuarioEncontrado->nombres;
        qDebug() << "Apellido: " << usuarioEncontrado->apellidos;
        qDebug() << "Correo: " << usuarioEncontrado->correo;
        qDebug() << "Contraseña: " << usuarioEncontrado->contrasena;
        qDebug() << "Fecha de nacimiento: " << usuarioEncontrado->fechaNacimiento;
        
        // Limpiar el contenido del tableWidget antes de agregar los datos del nuevo usuario
        ui->tableWidget_fromsearch_admin->clearContents();
        ui->tableWidget_fromsearch_admin->setRowCount(1);  // Solo se mostrará una fila
        
        // Agregar datos en las columnas correspondientes
        ui->tableWidget_fromsearch_admin->setItem(0, 0, new QTableWidgetItem(usuarioEncontrado->nombres));
        ui->tableWidget_fromsearch_admin->setItem(0, 1, new QTableWidgetItem(usuarioEncontrado->apellidos));
        ui->tableWidget_fromsearch_admin->setItem(0, 2, new QTableWidgetItem(usuarioEncontrado->correo));
        ui->tableWidget_fromsearch_admin->setItem(0, 3, new QTableWidgetItem(usuarioEncontrado->fechaNacimiento));

        // Crear el botón "Modificar"
        QPushButton *modifyButton = new QPushButton("Modificar");
        connect(modifyButton, &QPushButton::clicked, this, [=]() {
            qDebug() << "Botón 'Modificar' presionado";
            // Aquí puedes llamar a la función que permita modificar al usuario
            // modificarUsuario(usuarioEncontrado);
        });
        ui->tableWidget_fromsearch_admin->setCellWidget(0, 4, modifyButton);  // Posición 4 para "Modificar"

        // Crear el botón "Eliminar"
        QPushButton *deleteButton = new QPushButton("Eliminar");
        connect(deleteButton, &QPushButton::clicked, this, [=]() {
            qDebug() << "Botón 'Eliminar' presionado";
            // eliminarUsuario(usuarioEncontrado);
        });
        ui->tableWidget_fromsearch_admin->setCellWidget(0, 5, deleteButton);  // Posición 5 para "Eliminar"
        
    } else {
        qDebug() << "Usuario no encontrado";
        
        // Limpiar el contenido si no se encuentra ningún usuario
        ui->tableWidget_fromsearch_admin->clearContents();
        ui->tableWidget_fromsearch_admin->setRowCount(0);
    }
}


void ProfileAdministrator::on_pushButton_ordercaseaplicar_clicked() {
    // Obtener el índice actual del QComboBox
    int index = ui->comboBox_order->currentIndex();
    QString resultado;

    // Limpiar la tabla antes de llenarla
    ui->tableWidget_fromsearch_admin->clearContents();
    ui->tableWidget_fromsearch_admin->setRowCount(0);
    int size = 0;

    switch (index) {
    case 0: // Preorden
        resultado = "Seleccionaste: Preorden";
        arbolUsuariosGeneral->preordenCase(arbolUsuariosGeneral->raiz, ui->tableWidget_fromsearch_admin, size);
        break;
    case 1: // Postorden
        resultado = "Seleccionaste: Postorden";
        arbolUsuariosGeneral->postordenCase(arbolUsuariosGeneral->raiz, ui->tableWidget_fromsearch_admin, size);
        break;
    case 2: // Inorden
        resultado = "Seleccionaste: Inorden";
        arbolUsuariosGeneral->inordenCase(arbolUsuariosGeneral->raiz, ui->tableWidget_fromsearch_admin, size);
        break;
    default:
        resultado = "Seleccione un recorrido válido";
        break;
    }

    // Llamar a la función para agregar botones después de llenar la tabla
    addButtonsToTable();
    
    // Mostrar un mensaje sobre la opción seleccionada
    QMessageBox::information(this, "Opción Seleccionada", resultado);
}

void ProfileAdministrator::addButtonsToTable() {
    // Limpiar botones existentes para evitar duplicados
    for (int i = 0; i < ui->tableWidget_fromsearch_admin->rowCount(); ++i) {
        // Crear el botón "Modificar" y añadirlo a la columna 4
        QPushButton* modifyButton = new QPushButton("Modificar");
        ui->tableWidget_fromsearch_admin->setCellWidget(i, 4, modifyButton);

        // Crear el botón "Eliminar" y añadirlo a la columna 5
        QPushButton* deleteButton = new QPushButton("Eliminar");
        ui->tableWidget_fromsearch_admin->setCellWidget(i, 5, deleteButton);

        // Conectar las señales de los botones a las funciones correspondientes
        connect(modifyButton, &QPushButton::clicked, [this, i]() {
            // Aquí llamas a la función para modificar los datos del usuario en la fila i
            // modificarUsuario(i);
        });

        connect(deleteButton, &QPushButton::clicked, [this, i]() {
            // Guardar el índice correcto y eliminar la fila
            int rowToDelete = i;

            // Utilizar un temporizador para evitar conflictos en la tabla
            QTimer::singleShot(0, this, [this, rowToDelete]() {
                ui->tableWidget_fromsearch_admin->removeRow(rowToDelete);
                
                // Volver a agregar los botones después de eliminar
                addButtonsToTable();
            });
        });
    }
}

void ProfileAdministrator::on_pushButton_reportesfromadminsi_2_clicked()
{   
    ui->label_tituloavlsi->hide();
    ui->label_foradminavltreesi->hide();
    ui->label_titulolistasi->show();
    ui->label_forlistadepostssi->show();
    QString rutaimgposts = rutaBase + "salida/publicaciones.png";
    // Verificar si la imagen existe
    if (!QFile::exists(rutaimgposts)) {
        QMessageBox::warning(this, "Error", "No se encontró la imagen en la ruta: " + rutaimgposts);
        return;
    }

    // Cargar la imagen desde la ruta
    QImage image(rutaimgposts);

    // Verificar si la imagen se cargó correctamente
    if (image.isNull()) {
        QMessageBox::warning(this, "Error", "Error al cargar la imagen: " + rutaimgposts);
        return;
    }

    // Asignar la imagen a un QLabel
    ui->label_forlistadepostssi->setPixmap(QPixmap::fromImage(image));

    // Ajustar el tamaño del QLabel para que se ajuste a la imagen
    ui->label_forlistadepostssi->setScaledContents(true);

}

