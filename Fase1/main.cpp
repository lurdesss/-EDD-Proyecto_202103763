#include <iostream>
#include <windows.h>  // Incluye la biblioteca de Windows para cambiar la página de códigos
#include "include/Utils.h"
#include "include/UserList.h"
#include <limits> // Para std::numeric_limits

using namespace std;

const string ADMIN_EMAIL = "3312"; //admin@gmail.com
const string ADMIN_PASSWORD = "3312"; //EDD2S2024

int main() {
    SetConsoleOutputCP(CP_UTF8); // Cambia la página de códigos a UTF-8
    UserList userList;
    string consoleFName, consoleLName, consoleBDate, consoleEmail, consolePwd; // variables para registro de usuarios
    string email, password; // variables para autenticación de entrada
    
    int option1;

    do {
        cout << endl;
        menuLogin();
        cout << endl;
        cout << "Ingrese una opción: ";
        cin >> option1;
        cout << endl;

        // Verificar si la entrada es inválida
        while (cin.fail()) {
            cin.clear(); // Limpia el estado de error del flujo de entrada
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora el resto de la línea
            cout << "Opcion invalida " << endl;
            cout << "Ingrese una opcion: ";
            cin >> option1;
        }

        // Limpiar el buffer antes de usar getline()
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (option1) {
        case 1:
            cout << "Iniciar sesion" << endl;
            cout << "Ingrese su correo electronico: ";
            getline(cin, email);
            cout << "Ingrese su contrasena: ";
            getline(cin, password);
            cout << endl;

            if (email == ADMIN_EMAIL && password == ADMIN_PASSWORD) {
                cout << "Bienvenido administrador" << endl;
                moduloAdministrador();
            } else if (userList.authenticateUser(email, password)) {
                cout << "Caso de usuario" << endl;
                moduloUsuario(); // vista de usuario
            }
            else {
                cout << "Correo electronico o contrasena incorrectos" << endl;
            }
            break;
        case 2:
            cout << "Registrarse" << endl;
            cout << "Ingrese su nombre: ";
            getline(cin, consoleFName);
            cout << "Ingrese su apellido: ";
            getline(cin, consoleLName);
            cout << "Ingrese su fecha de nacimiento: ";
            getline(cin, consoleBDate);
            cout << "Ingrese su correo electronico: ";
            getline(cin, consoleEmail);
            cout << "Ingrese su contrasena: ";
            getline(cin, consolePwd);
            userList.addUser(consoleFName, consoleLName, consoleBDate, consoleEmail, consolePwd);
            break; // sale del ciclo
        case 3:
            cout << "Informacion" << endl;
            userList.printUsers();
            break;
        case 4:
            cout << "Ha salido de Social structure" << endl;
            break;
        default:
            cout << "Opcion invalida" << endl;
            cout << endl;
            break;
        }
    } while (option1 != 4);
}
