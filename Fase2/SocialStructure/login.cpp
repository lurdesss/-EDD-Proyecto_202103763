#include "login.h"
#include "ui_login.h"
#include "QMessageBox"
#include "avltree.h"
#include "listapublicaciones.h"
#include "abb.h"
#include "btree.h"
#include "huffman.h"

// include listasimple pila y grafo
#include "pilasolicitudes.h"
#include "listasimplesolicitudes.h"
// #include "listasimple.h" // solo lista simple
#include "relationlist.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

#include "contador.h"

AVLTree* arbolUsuariosGeneral = new AVLTree();
ListaDePublicaciones* listaDoblePublicaciones = new ListaDePublicaciones();
ABB* abbPublicaciones = new ABB();
BTree* btreeComentarios = new BTree();
// pila
// listasimple
// grafo
PilaSolicitudes* pilaSolicitudes = new PilaSolicitudes();
ListaSimpleSolicitudes* listaSolicitudes = new ListaSimpleSolicitudes();
ListOfList* listOfList = new ListOfList();
ListaSimple* listaSolicitudesEnviadas = new ListaSimple();


Usuario* usuarioensesion;

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    cargandoDefaultIfExists();
}

Login::~Login()
{
    delete ui;
}

// try to login
void Login::on_pushButton_login_clicked()
{
    QString adminEmail = "admin@gmail.com"; //"admin@gmail.com";
    QString adminPassword = "EDD2S2024"; //"EDD2S2024";

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
        profileAdministrator->cargaArchivo(arbolUsuariosGeneral, listaDoblePublicaciones, abbPublicaciones, btreeComentarios, pilaSolicitudes, listaSolicitudes, listOfList, listaSolicitudesEnviadas);  // Carga datos del árbol
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
        profileUser->cargaData(arbolUsuariosGeneral, listaDoblePublicaciones, abbPublicaciones, btreeComentarios, listOfList);

        // pasa como parametros, estructuras inicializadas
        ListaSimple listaSimple;
        listaSimple.carga(pilaSolicitudes, listaSolicitudes);
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

void Login::on_pushButton_cloaseapp_clicked()
{
    // huffman
    // guardarTodoEnJson("general.json");

    QString rutaBase = "/home/lurdes/Escritorio/datastructures/-EDD-Proyecto_202103763/Fase2/SocialStructure/salida/";
    QString nombreArchivo = "general.json";
    QString rutaCompleta = rutaBase + nombreArchivo;

    // Llamar a la función
    guardarTodoEnJson(rutaCompleta);
    huffmanJson();
    QApplication::quit(); // Cierra la aplicación
}



void Login::guardarTodoEnJson(const QString& filePath) {
    QJsonArray usuariosArray;
    QJsonArray amigosArray;
    QJsonArray relacionesArray;

    // Suponiendo que tienes acceso al árbol AVL desde aquí
    arbolUsuariosGeneral->preordenCaseToJson(arbolUsuariosGeneral->raiz, usuariosArray);

    // Llama a la función que guarda amigos en un array
    listOfList->guardarAmigosEnJson(amigosArray); // Necesitarás implementar esta función en ListOfList

    // Guardar las relaciones en el array
    listaSolicitudesEnviadas->guardarRelacionesEnJson(relacionesArray);

    // Crear el objeto JSON principal usando un QJsonArray para el orden
    QJsonArray jsonPrincipalArray;
    
    // Agregar los elementos en el orden deseado
    QJsonObject usuariosObject;
    usuariosObject["usuarios"] = usuariosArray;
    jsonPrincipalArray.append(usuariosObject);

    QJsonObject relacionesObject;
    relacionesObject["solicitudes"] = relacionesArray;
    jsonPrincipalArray.append(relacionesObject);

    QJsonObject amigosObject;
    amigosObject["amigos"] = amigosArray;
    jsonPrincipalArray.append(amigosObject);

    // Crear el documento JSON
    QJsonDocument jsonDoc(jsonPrincipalArray);

    // Guardar el JSON en un archivo
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(jsonDoc.toJson());
        file.close();
    } else {
        qDebug() << "Error al abrir el archivo para guardar el JSON";
    }
}

void Login::huffmanJson() {
    QString rutaBase = "/home/lurdes/Escritorio/datastructures/-EDD-Proyecto_202103763/Fase2/SocialStructure/salida/general.json";

    QFile file(rutaBase);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "No se pudo abrir el archivo JSON." << std::endl;
        return;
    }

    QString jsonData = file.readAll();
    file.close();

    // Convertir QString a std::string para el procesamiento de Huffman
    std::string text = jsonData.toStdString();

    // Contar la frecuencia de cada carácter
    int freq[256] = {0};
    for (char ch : text) {
        freq[(unsigned char)ch]++;
    }

    // Crear cola de prioridad
    PriorityQueue* pq = nullptr;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            HuffmanNode* newNode = new HuffmanNode((char)i, freq[i]);
            insert(pq, newNode);
        }
    }

    // Construir el árbol de Huffman
    while (pq && pq->next) {
        HuffmanNode* left = extractMin(pq);
        HuffmanNode* right = extractMin(pq);
        int sumFreq = left->freq + right->freq;
        HuffmanNode* parent = new HuffmanNode('\0', sumFreq);
        parent->left = left;
        parent->right = right;
        insert(pq, parent);
    }

    // Nodo raíz del árbol
    HuffmanNode* root = extractMin(pq);

    // Generar y mostrar códigos de Huffman
    std::string codes[256];
    buildHuffmanCode(root, "", codes);
    std::cout << "Códigos de Huffman:\n";
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            std::cout << (char)i << ": " << codes[i] << '\n';
        }
    }

    // Comprimir texto
    std::string compressedText = compress(text, codes);
    std::cout << "\nTexto comprimido: " << compressedText << "\n";

    // Descomprimir texto
    std::string decompressedText = decompress(root, compressedText);
    std::cout << "\nTexto descomprimido: " << decompressedText << "\n";

    // Generar el archivo .dot
    createGraph(root);

    // Guardar el texto descomprimido en un archivo JSON
    QString rutaSalida = "/home/lurdes/Escritorio/datastructures/-EDD-Proyecto_202103763/Fase2/SocialStructure/salida/descomprimido.json";
    QFile outFile(rutaSalida);
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        std::cerr << "No se pudo crear el archivo JSON." << std::endl;
        return;
    }

    QTextStream out(&outFile);
    out << QString::fromStdString(decompressedText);  // Escribir texto descomprimido
    outFile.close();
    
    std::cout << "Texto descomprimido guardado en: " << rutaSalida.toStdString() << "\n";
}



#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

void Login::cargandoDefaultIfExists() {
    QString rutaBase = "/home/lurdes/Escritorio/datastructures/-EDD-Proyecto_202103763/Fase2/SocialStructure/salida/general.json";
    
    QFile file(rutaBase);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "No se pudo abrir el archivo JSON.";
        return;
    }

    // Leer el contenido del archivo
    QByteArray jsonData = file.readAll();
    file.close();

    // Parsear el contenido JSON
    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    if (document.isNull()) {
        qDebug() << "Error al parsear el JSON.";
        return;
    }

    // Acceder a los datos
    QJsonArray jsonArray = document.array();
    for (const QJsonValue& value : jsonArray) {
        QJsonObject jsonObject = value.toObject();

        // Obtener usuarios
        if (jsonObject.contains("usuarios")) {
            QJsonArray usuariosArray = jsonObject["usuarios"].toArray();
            for (const QJsonValue& userValue : usuariosArray) {
                QJsonObject userObject = userValue.toObject();
                
                QString nombres = userObject["nombres"].toString();
                QString apellidos = userObject["apellidos"].toString();
                QString correo = userObject["correo"].toString();
                QString contrasena = userObject["contraseña"].toString();
                QString fechaNacimiento = userObject["fecha_de_nacimiento"].toString();

                int repiteId = contadorId++;
                Usuario* userdefault = new Usuario(repiteId, nombres, apellidos, fechaNacimiento, correo, contrasena);
                arbolUsuariosGeneral->add(userdefault);

                // Mostrar recorridos
                qDebug() << "Recorrido en orden:";
                arbolUsuariosGeneral->enorden(arbolUsuariosGeneral->raiz);  // Imprime el recorrido en orden
                qDebug() << "Recorrido preorden:";
                arbolUsuariosGeneral->preorden(arbolUsuariosGeneral->raiz);  // Imprime el recorrido en preorden
                qDebug() << "Recorrido postorden:";
                arbolUsuariosGeneral->postorden(arbolUsuariosGeneral->raiz);  // Imprime el recorrido en postorden
                qDebug() << "Usuario agregado:" << userdefault->correo;
                qDebug() << "Id usuario: " << userdefault->id;
                
                // Imprimir en qDebug
                qDebug() << "Usuario:";
                qDebug() << "Nombres:" << nombres;
                qDebug() << "Apellidos:" << apellidos;
                qDebug() << "Correo:" << correo;
                qDebug() << "Contraseña:" << contrasena;
                qDebug() << "Fecha de Nacimiento:" << fechaNacimiento;


            }
        }

        // Obtener solicitudes
        if (jsonObject.contains("solicitudes")) {
            QJsonArray solicitudesArray = jsonObject["solicitudes"].toArray();
            for (const QJsonValue& solicitudValue : solicitudesArray) {
                QJsonObject solicitudObject = solicitudValue.toObject();
                
                QString emisor = solicitudObject["emisor"].toString();
                QString receptor = solicitudObject["receptor"].toString();
                QString estado = solicitudObject["estado"].toString();

                listaSolicitudesEnviadas->agregarSolicitud(emisor.toStdString(), receptor.toStdString(), estado.toStdString());

                // Imprimir en qDebug
                qDebug() << "Solicitud:";
                qDebug() << "Emisor:" << emisor;
                qDebug() << "Receptor:" << receptor;
                qDebug() << "Estado:" << estado;
            }
        }

        // Obtener amigos
        if (jsonObject.contains("amigos")) {
            QJsonArray amigosArray = jsonObject["amigos"].toArray();
            for (const QJsonValue& amigoValue : amigosArray) {
                QJsonObject amigoObject = amigoValue.toObject();
                
                QString nombreEmisor = amigoObject["nombreEmisor"].toString();
                QString nombreReceptor = amigoObject["nombreReceptor"].toString();

                // Imprimir en qDebug
                qDebug() << "Amigos:";
                qDebug() << "Nombre Emisor:" << nombreEmisor;
                qDebug() << "Nombre Receptor:" << nombreReceptor;


                Usuario* thisemisorout = arbolUsuariosGeneral->preordenBuscarNombres(arbolUsuariosGeneral->raiz, nombreEmisor);
                qDebug() << thisemisorout;
                int emisorId = thisemisorout->id;
                std::string emisorEmail = nombreEmisor.toStdString();
                Usuario* thisreceptorout = arbolUsuariosGeneral->preordenBuscarNombres(arbolUsuariosGeneral->raiz, nombreReceptor);
                qDebug() << thisreceptorout;
                int receptorId = thisreceptorout->id;
                std::string receptorEmail = nombreReceptor.toStdString();
                listOfList->insert(emisorId, receptorId, emisorEmail, receptorEmail);
                qDebug() << "llamo a print ----------------";
                listOfList->print();
                qDebug() << "end -----------------";
            }
        }
    }
}
