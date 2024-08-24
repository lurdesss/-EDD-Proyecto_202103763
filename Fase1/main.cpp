#include <iostream>
#include <windows.h>  // Incluye la biblioteca de Windows para cambiar la página de códigos
#include "include/Utils.h"
#include "include/UserList.h"
#include "include/listapublicaciones.h"
#include "include/RedSocial.h"
#include "include/ListaCircularDoble.h"
#include "include/ListaSimpleAmigos.h"
#include <limits> // Para std::numeric_limits
#include <fstream>
#include "json.hpp"
#include <ctime>

using namespace std;

const string ADMIN_EMAIL = "admin@gmail.com"; 
const string ADMIN_PASSWORD = "EDD2S2024"; 

// ANSI para consola
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";
const string RESET = "\033[0m";


using json = nlohmann::json;

void cargarPublicacionesDesdeJSON(ListaDePublicaciones& listaDePublicaciones) {
    std::string filePath;
    std::cout << "Ingrese el path del archivo JSON: ";
    std::getline(std::cin, filePath);

    std::ifstream archivo(filePath);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << filePath << std::endl;
        return;
    }

    json publicacionesJSON;
    archivo >> publicacionesJSON;

    for (const auto& publicacion : publicacionesJSON) {
        std::string correo = publicacion["correo"];
        std::string contenido = publicacion["contenido"];
        std::string fecha = publicacion["fecha"];
        std::string hora = publicacion["hora"];
        listaDePublicaciones.agregarPublicacion(correo, contenido, fecha, hora);
    }

    archivo.close();
    std::cout << "Proceso de carga desde " << filePath << " finalizado." << std::endl;
}

void cargarUsuariosDesdeJSON(UserList& userList) {
    std::string filePath;
    std::cout << "Ingrese el path del archivo JSON: ";
    std::getline(std::cin, filePath);

    std::ifstream archivo(filePath);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << filePath << std::endl;
        return;
    }

    json usuariosJSON;
    archivo >> usuariosJSON;

    for (const auto& usuario : usuariosJSON) {
        std::string nombres = usuario["nombres"];
        std::string apellidos = usuario["apellidos"];
        std::string fecha_de_nacimiento = usuario["fecha_de_nacimiento"];
        std::string correo = usuario["correo"];
        std::string contrasena = usuario["contraseña"];
        userList.addUser(nombres, apellidos, fecha_de_nacimiento, correo, contrasena);
    }

    archivo.close();
    std::cout << "Proceso de carga desde " << filePath << " finalizado." << std::endl;
}


int main() {
    SetConsoleOutputCP(CP_UTF8); // Cambia la página de códigos a UTF-8
    // Listas
    UserList userList; // Lista de usuarios
    ListaDePublicaciones listaDePublicaciones(&userList);
    RedSocial redSocial(&userList);
    ListaCircularDoble listaCircularDoblePublicaciones;
    ListaSimpleAmigos listaAmigosDeUsuario;

    // Variables
    string consoleFName, consoleLName, consoleBDate, consoleEmail, consolePwd; // variables para registro de usuarios
    string email, password; // variables para autenticación de entrada
    string emailToDelete; // variable para eliminar usuario
    string usuarioActual; // variable para almacenar el usuario actual
    string micorreo, micontenido, mifecha, mihora; // variables para publicaciones
    string fechaAElimiar, horaAEliminar, emailToDeleteNews; // variables para eliminar publicaciones
    string fileRelaciones; // variable para cargar solicitudes desde JSON:
    string filedot, filepng; // variable para generar el archivo .dot
    string emisorMain; // variable para aceptar/rechazar solicitudes
    string receptorMain; // variable para enviar solicitudes


    // fecha y hora actual
    std::time_t tiempoActual = std::time(nullptr);
    std::tm* tiempoLocal = std::localtime(&tiempoActual);

    // Formatear la fecha y la hora
    char fecha[11]; // Buffer para la fecha en formato "YYYY-MM-DD"
    std::strftime(fecha, sizeof(fecha), "%Y-%m-%d", tiempoLocal);

    char hora[9]; // Buffer para la hora en formato "HH:MM:SS"
    std::strftime(hora, sizeof(hora), "%H:%M:%S", tiempoLocal);
    
    int optionmain;

    do {
        cout << endl;
        menuLogin();
        cout << endl;
        cout << "Ingrese una opción: ";
        cin >> optionmain;
        cout << endl;

        // Verificar si la entrada es inválida
        while (cin.fail()) {
            cin.clear(); // Limpia el estado de error del flujo de entrada
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora el resto de la línea
            cout << "Opcion invalida " << endl;
            cout << "Ingrese una opcion: ";
            cin >> optionmain;
        }

        // Limpiar el buffer antes de usar getline()
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (optionmain) {
            case 1: {
                cout << "Iniciar sesion" << endl;
                cout << "Ingrese su correo electronico: ";
                getline(cin, email);
                cout << "Ingrese su contrasena: ";
                getline(cin, password);
                cout << endl;
                // Inicio de sesión de administrador
                if (email == ADMIN_EMAIL && password == ADMIN_PASSWORD) {
                    cout << GREEN << "  Bienvenido Administrador" << RESET << endl;
                    int optionadmin;
                    do {
                        cout << endl;
                        moduloAdministrador();
                        cout << "Ingrese una opcion: ";
                        cin >> optionadmin;
                        cout << endl;

                        while (cin.fail()) {
                            cin.clear(); // Limpia el estado de error del flujo de entrada
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora el resto de la línea
                            cout << "Opcion invalida " << endl;
                            cout << "Ingrese una opcion: ";
                            cin >> optionadmin;
                        }

                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        switch (optionadmin) {
                            case 1:
                                cout << "Carga de usuarios" << endl;
                                cout << "Ingrese el path del archivo JSON: ";
                                cargarUsuariosDesdeJSON(userList);
                                break;
                            case 2:
                                cout << "Carga de solicitudes" << endl;
                                cout << "Ingrese el path del archivo JSON: ";
                                getline(cin, fileRelaciones);
                                redSocial.cargarSolicitudesDesdeJSON(fileRelaciones);
                                break;
                            case 3:
                                cout << "Carga de publicaciones" << endl;
                                cargarPublicacionesDesdeJSON(listaDePublicaciones);
                                break;
                            case 4: {
                                cout << "Gestión de usuarios" << endl;
                                char optionadmina;
                                do {
                                    // Mostrar opciones de gestión de usuarios para el administrador
                                    moduloAdministradorA();
                                    cout << endl;
                                    cout << "Ingrese una opción (a para eliminar usuarios, x para volver al menu): ";
                                    cin >> optionadmina;
                                    cout << endl;

                                    // Verificar si la entrada es inválida
                                    while (cin.fail()) {
                                        cin.clear(); // Limpia el estado de error del flujo de entrada
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora el resto de la línea
                                        cout << "Opción inválida" << endl;
                                        cout << "Ingrese una opción: ";
                                        cin >> optionadmina;
                                    }

                                    // Limpiar el buffer antes de usar getline(), si es necesario
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                                    switch (optionadmina) {
                                        case 'a':
                                            cout << "Eliminar usuarios [Administrador]" << endl;
                                            userList.printUsers();
                                            cout << "Ingrese el correo del usuario a eliminar: ";
                                            getline(cin, emailToDelete);
                                            userList.deleteUserByEmail(emailToDelete);
                                            cout << "Se ha eliminado al usuario" << emailToDelete << endl;
                                            break;
                                        case 'x':
                                            cout << "Saliendo de gestión de usuarios..." << endl;
                                            break;
                                        default:
                                            cout << "Opción inválida" << endl;
                                            cout << endl;
                                            break;
                                    }
                                } while (optionadmina != 'x');
                                break;
                            }
                            case 5:
                                cout << "Reportes para Administrador" << endl;
                                // grafico de lista de usuarios (1)
                                userList.generateDot("usuarios.dot");
                                userList.renderGraphviz(
                                    "usuarios.dot", "usuarios.png");
                                // grafico de relaciones de amistad (2)
                                redSocial.matrizAmigos.generateGraphvizImage("relaciones.png");
                                // grafico de lista doblemente enlazada de publicaciones (3)
                                listaDePublicaciones.generateDot("publicaciones.dot");
                                listaDePublicaciones.renderGraphviz("publicaciones.dot", "publicaciones.png");
                                // top 5 usuarios con más publicaciones
                                listaDePublicaciones.mostrarTopPublicaciones();
                                // top 5 usuarios con menos amigos
                                // userList.printUsers();
                                break;
                            case 6:
                                cout << RED << "Ha cerrado sesión" << RESET << endl;
                                break;
                            default:
                                cout << "Opcion invalida" << endl;
                                cout << endl;
                                break;
                        }
                    } while (optionadmin != 6);

                // Inicio de sesión de usuario
                } else if (userList.authenticateUser(email, password)) {
                    usuarioActual = userList.foundUser(email);
                    int optionuser;
                    do {
                        cout << endl;
                        cout << usuarioActual << GREEN << " [Activo] "  << RESET << endl;
                        moduloUsuario();
                        cout << "Ingrese una opcion: ";
                        cin >> optionuser;
                        cout << endl;

                        while (cin.fail()) {
                            cin.clear(); // Limpia el estado de error del flujo de entrada
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora el resto de la línea
                            cout << "Opcion invalida " << endl;
                            cout << "Ingrese una opcion: ";
                            cin >> optionuser;
                        }

                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        switch (optionuser) {
                            case 1: {
                                cout << "Perfil" << endl;
                                char optionuser1;
                                do {
                                    moduloUsuario1();
                                    cout << "Ingrese una opción (a)Ver perfil (b)Eliminar cuenta (x)Volver: ";
                                    cin >> optionuser1;
                                    cout << endl;

                                    while (cin.fail()) {
                                        cin.clear(); // Limpia el estado de error del flujo de entrada
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora el resto de la línea
                                        cout << "Opción inválida" << endl;
                                        cout << "Ingrese una opción: ";
                                        cin >> optionuser1;
                                    }

                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                                    switch (optionuser1) {
                                        case 'a':
                                            cout << usuarioActual << GREEN << " [ Estado: Activo ]" << RESET << endl;
                                            cout << "Correo: " << email << endl;
                                            cout << "Fecha de nacimiento: " << userList.getBirthDateByEmail(email) << endl;
                                            cout << "Amigos en [Social structure] " << endl;
                                            cout << endl;
                                            redSocial.matrizAmigos.imprimirAmigosPorEmail(email);
                                            break;
                                        case 'b':
                                            userList.deleteUserByEmail(email);
                                            optionuser1 = 'x';
                                            optionuser =5;
                                            cout << RED << "Su cuenta ha sido eliminada" << RESET << endl;
                                            break;
                                        case 'x':
                                            cout << "Saliendo de perfil..." << endl;
                                            break;
                                        default:
                                            cout << "Opción inválida" << endl;
                                            cout << endl;
                                            break;
                                    }
                                } while (optionuser1 != 'x');
                                break;
                            }
                            case 2:
                                cout << "Solicitudes" << endl;
                                char optionuser2;
                                do {
                                    moduloUsuario2();
                                    cout << "Ingrese una opción (a)Ver solicitudes (b)Enviar solicitud (x)Volver: ";
                                    cin >> optionuser2;
                                    cout << endl;

                                    while (cin.fail()) {
                                        cin.clear(); // Limpia el estado de error del flujo de entrada
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora el resto de la línea
                                        cout << "Opción inválida" << endl;
                                        cout << "Ingrese una opción: ";
                                        cin >> optionuser2;
                                    }
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    switch (optionuser2) {
                                        case 'a':
                                            char optionuser2i;
                                            do {
                                                redSocial.listaSolicitudesEnviadas.pilaSolicitudes.limpiarPila();
                                                redSocial.listaSolicitudesEnviadas.buscarPorReceptor(email);
                                                redSocial.listaSolicitudesEnviadas.listaSolicitudes.limpiarLista();
                                                redSocial.listaSolicitudesEnviadas.buscarPorEmisor(email);
                                                cout << endl;
                                                cout << "Solicitudes recibidas en estado " << YELLOW << "[PENDIENTE]" << RESET << endl;
                                                cout << endl;
                                                redSocial.listaSolicitudesEnviadas.pilaSolicitudes.imprimirPila(); // recibidas
                                                cout << endl;
                                                moduloUsuario2I();
                                                cout << "Ingrese una opción (i para elegir a una solicitud a aceptar/rechazar, x para volver): ";
                                                cin >> optionuser2i;
                                                cout << endl;
                                                while (cin.fail()) {
                                                    cin.clear(); // Limpia el estado de error del flujo de entrada
                                                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora el resto de la línea
                                                    cout << "Opción inválida" << endl;
                                                    cout << "Ingrese una opción: ";
                                                    cin >> optionuser2i;
                                                }
                                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                                switch (optionuser2i){
                                                    case 'i':
                                                        cout << "Ingrese el correo del usuario a Aceptar/Rechazar: ";
                                                        getline(cin, emisorMain);
                                                        if (redSocial.listaSolicitudesEnviadas.pilaSolicitudes.existeSolicitudPendiente(emisorMain, email)) {
                                                            char optionuser2ik;
                                                            do {
                                                                moduloUsuario2ISI();
                                                                cout << "Ingrese una opción (a)Aceptar (b)Rechazar (x)Volver): ";
                                                                cin >> optionuser2ik;
                                                                cout << endl;
                                                                while (cin.fail()) {
                                                                    cin.clear(); // Limpia el estado de error del flujo de entrada
                                                                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora el resto de la línea
                                                                    cout << "Opción inválida" << endl;
                                                                    cout << "Ingrese una opción: ";
                                                                    cin >> optionuser2ik;
                                                                }
                                                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                                                switch (optionuser2ik) {
                                                                    case 'a':
                                                                        redSocial.listaSolicitudesEnviadas.eliminarSolicitud(emisorMain, email, "PENDIENTE");
                                                                        redSocial.matrizAmigos.insert(userList.getId(emisorMain), userList.getId(email), true, emisorMain, email);
                                                                        redSocial.matrizAmigos.insert(userList.getId(email), userList.getId(emisorMain), true, email, emisorMain);

                                                                        cout << "Se ha " << GREEN << "ACEPTADO" << RESET << " la solicitud de " << emisorMain << endl;
                                                                        optionuser2ik = 'x';
                                                                        break;
                                                                    case 'b':
                                                                        redSocial.listaSolicitudesEnviadas.eliminarSolicitud(emisorMain, email, "PENDIENTE");
                                                                        cout << "Se ha " << RED << "RECHAZADO" << RESET << " la solicitud de " << emisorMain << endl;
                                                                        optionuser2ik = 'x';
                                                                        break;
                                                                    case 'x':
                                                                        cout << "Saliendo de aceptar/rechazar..." << endl;
                                                                        break;
                                                                    default:
                                                                        cout << "Opción inválida" << endl;
                                                                        cout << endl;
                                                                        break;
                                                                }
                                                            } while (optionuser2ik != 'x');
                                                        } else {
                                                            cout << "No existe una solicitud pendiente de " << emisorMain << " a " << email << endl;
                                                        }
                                                        break;
                                                    case 'x':
                                                        cout << "Saliendo de vista de [solicitudes]" << endl;
                                                        break;
                                                    default:
                                                        cout << "Opción inválida" << endl;
                                                        break;
                                                }
                                            } while (optionuser2i != 'x');
                                            break;
                                        case 'b':
                                            redSocial.listaSolicitudesEnviadas.listaSolicitudes.limpiarLista();
                                            redSocial.listaSolicitudesEnviadas.buscarPorEmisor(email);
                                            cout << "Solicitudes enviadas" << endl;
                                            cout << endl;
                                            redSocial.listaSolicitudesEnviadas.listaSolicitudes.imprimirLista(); // enviadas
                                            cout << endl;
                                            cout << "Ingrese el correo del usuario a enviar solicitud: ";
                                            getline(cin, receptorMain);
                                            if (!userList.emailExists(receptorMain)) {
                                                cout << "Correo electrónico no registrado." << endl;
                                                continue;
                                            }
                                            redSocial.listaSolicitudesEnviadas.agregarSolicitud(email, receptorMain, "PENDIENTE");
                                            cout << "Se ha enviado una solicitud de amistad a " << receptorMain << endl;
                                            break;
                                        case 'x':
                                            cout << "Saliendo de solicitudes..." << endl;
                                            break;
                                        default:
                                            cout << "Opción inválida" << endl;
                                            break;
                                    }
                                } while (optionuser2 != 'x');
                                break;
                            case 3:
                                cout << "Publicaciones" << endl;
                                char optionuser3;
                                do {
                                    moduloUsuario3();
                                    cout << "Ingrese una opción (a)Ver publicaciones (b)Crear publicación (c)Eliminar publicación (x) volver): ";
                                    cin >> optionuser3;
                                    cout << endl;

                                    while (cin.fail()) {
                                        cin.clear(); // Limpia el estado de error del flujo de entrada
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora el resto de la línea
                                        cout << "Opción inválida" << endl;
                                        cout << "Ingrese una opción: ";
                                        cin >> optionuser3;
                                    }

                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                                    switch (optionuser3) {
                                        case 'a':
                                            cout << "Ver publicaciones de " << GREEN << usuarioActual << RESET << endl;
                                            // lista circular doblemente enlazada mis publicaciones y las de mis amigos
                                            listaCircularDoblePublicaciones.limpiar();
                                            listaDePublicaciones.buscarPublicacionesPorEmail(email, listaCircularDoblePublicaciones);
                                            listaAmigosDeUsuario.limpiarLista();
                                            redSocial.matrizAmigos.agregarAmigosPorEmail(email, listaAmigosDeUsuario);
                                            listaDePublicaciones.buscarPublicacionesPorListaEmails(listaAmigosDeUsuario, listaCircularDoblePublicaciones);
                                            cout << endl;
                                            listaCircularDoblePublicaciones.navegarPublicaciones();
                                            break;
                                        case 'b':
                                            cout << "Crear publicación" << endl;
                                            micorreo = email;
                                            cout << "Ingrese el contenido de la publicación: ";
                                            getline(cin, micontenido);
                                            mifecha = fecha;
                                            mihora = hora;
                                            listaDePublicaciones.agregarPublicacion(micorreo, micontenido, mifecha, mihora);
                                            break;
                                        case 'c':
                                            listaCircularDoblePublicaciones.limpiar();
                                            listaDePublicaciones.buscarPublicacionesPorEmail(email, listaCircularDoblePublicaciones);
                                            listaCircularDoblePublicaciones.mostrarPublicaciones();
                                            cout << "Eliminar publicación" << endl;
                                            emailToDeleteNews = email;
                                            cout << "Ingrese" << YELLOW << " FECHA " << RESET <<"de publicación a eliminar (YYYY-MM-DD) [formato opcional]: ";
                                            getline(cin, fechaAElimiar);
                                            cout << "Ingrese" << YELLOW << " HORA " << RESET <<"de publicación a eliminar (HH:MM:SS) [formato opcional]: ";
                                            getline(cin, horaAEliminar);
                                            listaDePublicaciones.eliminarPublicacion(emailToDeleteNews, fechaAElimiar, horaAEliminar);
                                            break;
                                        case 'x':
                                            cout << "Saliendo de publicaciones..." << endl;
                                            break;
                                        default:
                                            cout << "Opción inválida" << endl;
                                            cout << endl;
                                            break;
                                    }
                                } while (optionuser3 != 'x');
                                break;
                            case 4:
                                cout << endl;
                                cout << "Imprimiendo reportes para " << YELLOW << usuarioActual << RESET << endl;
                                cout << "Gráfico de solicitudes [enviadas] / [recibidas]" << endl; //GRAFICO: lista de solicitudes enviadas, pila de solicitudes recibidas
                                // caso 1
                                redSocial.listaSolicitudesEnviadas.pilaSolicitudes.limpiarPila();
                                redSocial.listaSolicitudesEnviadas.buscarPorReceptor(email);
                                // caso 2
                                redSocial.listaSolicitudesEnviadas.listaSolicitudes.limpiarLista();
                                redSocial.listaSolicitudesEnviadas.buscarPorEmisor(email);
                                cout << "Generando gráfico de pila de solicitudes RECIBIDAS" << endl; // caso 1
                                redSocial.listaSolicitudesEnviadas.pilaSolicitudes.generarDot("solicitudesRecibidas.dot");
                                redSocial.listaSolicitudesEnviadas.pilaSolicitudes.renderGraphviz("solicitudesRecibidas.dot", "solicitudesRecibidas.png");
                                cout << "Generando gráfico de lista de solicitudes ENVIADAS" << endl; // caso 2
                                redSocial.listaSolicitudesEnviadas.listaSolicitudes.generateDot("solicitudesEnviadas.dot");
                                redSocial.listaSolicitudesEnviadas.listaSolicitudes.renderGraphviz("solicitudesEnviadas.dot", "solicitudesEnviadas.png");
                                
                                cout << "Relacion de amistad" << endl; // GRAFICO: Matriz dispersa de relaciones de amistad
                                // no realizado
                                cout << "Publicaciones" << endl; // GRAFICO: lista circular de publicaciones de usuario y amigos
                                listaCircularDoblePublicaciones.limpiar();
                                listaDePublicaciones.buscarPublicacionesPorEmail(email, listaCircularDoblePublicaciones);
                                listaAmigosDeUsuario.limpiarLista();
                                redSocial.matrizAmigos.agregarAmigosPorEmail(email, listaAmigosDeUsuario);
                                listaDePublicaciones.buscarPublicacionesPorListaEmails(listaAmigosDeUsuario, listaCircularDoblePublicaciones);
                                listaCircularDoblePublicaciones.generateDot("publicacionesUsuario.dot");
                                listaCircularDoblePublicaciones.renderGraphviz("publicacionesUsuario.dot", "publicacionesUsuario.png");
                                cout << "Mis amigos" << endl; // LISTA: lista de amigos
                                cout << endl;
                                redSocial.matrizAmigos.imprimirAmigosPorEmail(email);
                                break;
                            case 5:
                                cout << RED << "Ha cerrado sesión" << RESET << endl;
                                break;
                            default:
                                cout << "Opcion inválida" << endl;
                                cout << endl;
                                break;
                        }
                    } while (optionuser != 5);
                } else {
                    cout << "Error: Credenciales inválidas." << endl;
                }
                break;
            }
            case 2: {
                cout << "[ Registro ]" << endl;
                cout << endl;
                cout << "Ingrese su nombre: ";
                getline(cin, consoleFName);
                cout << "Ingrese su apellido: ";
                getline(cin, consoleLName);
                cout << "Ingrese su fecha de nacimiento (DD/MM/AAAA): ";
                getline(cin, consoleBDate);
                cout << "Ingrese su correo electronico: ";
                getline(cin, consoleEmail);
                cout << "Ingrese su contraseña: ";
                getline(cin, consolePwd);

                userList.addUser(consoleFName, consoleLName, consoleBDate, consoleEmail, consolePwd);
                break;
            }
            case 3:
                cout << GREEN << " PROYECTO FASE 1 " << RESET << endl;
                cout << endl;
                cout << CYAN << "Nombre: " << RESET << endl;
                cout << "       Jennifer Yulissa Lourdes Taperio Manuel " << endl;
                cout << CYAN << "Carnet: " << RESET << endl;
                cout << "       202103763 " << endl;
                cout << CYAN << "Curso: " << RESET << endl;
                cout << "       Estructura de Datos " << endl;
                cout << CYAN << "Seccion: " << RESET << endl;
                cout << "       C " << endl;
                break;
            case 4:
                cout << RED << "Ha salido de [social structure]" << RESET << endl;
                cout << endl;
                break;
            default:
                cout << "Opcion invalida" << endl;
                break;
        }
    } while (optionmain != 4);
    return 0;
}