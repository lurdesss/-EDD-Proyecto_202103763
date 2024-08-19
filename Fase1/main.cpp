#include <iostream>
#include <windows.h>  // Incluye la biblioteca de Windows para cambiar la página de códigos
#include "include/Utils.h"
#include "include/UserList.h"
#include "include/listapublicaciones.h"
#include <limits> // Para std::numeric_limits
#include <fstream>
#include "json.hpp"
#include <ctime>

using namespace std;

const string ADMIN_EMAIL = "3312"; //admin@gmail.com
const string ADMIN_PASSWORD = "3312"; //EDD2S2024

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
        std::string contrasena = usuario["contrasena"];
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

    // Variables
    string consoleFName, consoleLName, consoleBDate, consoleEmail, consolePwd; // variables para registro de usuarios
    string email, password; // variables para autenticación de entrada
    string emailToDelete; // variable para eliminar usuario
    string usuarioActual; // variable para almacenar el usuario actual
    string micorreo, micontenido, mifecha, mihora; // variables para publicaciones
    string fechaAElimiar, horaAEliminar, emailToDeleteNews; // variables para eliminar publicaciones


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
                    cout << "Bienvenido administrador" << endl;
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
                                cargarUsuariosDesdeJSON(userList);
                                break;
                            case 2:
                                cout << "Carga de relaciones" << endl;
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
                                cout << "Reportes" << endl;
                                userList.printUsers();
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
                                    cout << "Ingrese una opción (a para ver perfil, b para eliminar cuenta, x para volver): ";
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
                                    cout << "Ingrese una opción (a para ver solicitudes, b para enviar solicitud, x para volver): ";
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
                                            cout << "Ver solicitudes" << endl;
                                            break;
                                        case 'b':
                                            cout << "Enviar solicitud" << endl;
                                            break;
                                        case 'x':
                                            cout << YELLOW << "Saliendo de solicitudes..." << RESET << endl;
                                            break;
                                        default:
                                            cout << "Opción inválida" << endl;
                                            cout << endl;
                                            break;
                                    }
                                } while (optionuser2 != 'x');
                                break;
                            case 3:
                                cout << "Publicaciones" << endl;
                                char optionuser3;
                                do {
                                    moduloUsuario3();
                                    cout << "Ingrese una opción (a para ver publicaciones, b para crear publicación, c para eliminar publicación, x para volver): ";
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
                                            cout << "Ver publicaciones" << endl;
                                            // lista circular doblemente enlazada mis publicaciones y las de mis amigos
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
                                            cout << "Eliminar publicación" << endl;
                                            emailToDeleteNews = email;
                                            cout << "Ingrese la fecha de la publicación a eliminar (YYYY-MM-DD): ";
                                            getline(cin, fechaAElimiar);
                                            cout << "Ingrese la hora de la publicación a eliminar (HH:MM:SS): ";
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
                                cout << "Reportes" << endl;
                                cout << "Imprimiendo reportes para " << GREEN << usuarioActual << RESET << endl;
                                cout << "Solicitudes enviadas y recibidas" << endl; //GRAFICO: lista de solicitudes enviadas, pila de solicitudes recibidas
                                cout << "Relacion de amistad" << endl; // GRAFICO: Matriz dispersa de relaciones de amistad
                                cout << "Publicaciones" << endl; // GRAFICO: lista circular de publicaciones de usuario y amigos
                                cout << "Mis amigos" << endl; // LISTA: lista de amigos
                                cout << endl;

                                break;
                            case 5:
                                cout << RED << "Ha cerrado sesión" << RESET << endl;
                                break;
                            default:
                                cout << "Opcion invalida" << endl;
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
                cout << "Ingrese su contrasena: ";
                getline(cin, consolePwd);

                userList.addUser(consoleFName, consoleLName, consoleBDate, consoleEmail, consolePwd);
                break;
            }
            case 3:
                cout << GREEN << "[ Fase 1 ]" << RESET << endl;
                cout << endl;
                cout << CYAN << "Nombre: " << RESET << endl;
                cout << "       Jennifer Yulissa Lourdes Taperio Manuel " << endl;
                cout << CYAN << "Carnet: " << RESET << endl;
                cout << "       202103763 " << endl;
                cout << CYAN << "Curso: " << RESET << endl;
                cout << "       Estructura de Datos " << endl;
                cout << CYAN << "Seccion: " << RESET << endl;
                cout << "       C " << endl;
                listaDePublicaciones.mostrarPublicaciones();
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