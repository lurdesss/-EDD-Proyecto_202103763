#include "UserList.h"
#include <iostream>

UserList::UserList() : primero(nullptr), tamaño(0) {}

UserList::~UserList() {
    User* actual = primero;
    while (actual != nullptr) {
        User* limpiable = actual;
        actual = actual->siguiente;
        delete limpiable;
    }
}

bool UserList::emailExists(const string& atrEmail) const {
    if (atrEmail.empty()) {
        return false;
    }

    User* actual = primero;
    while (actual != nullptr) {
        if (actual->atrEmail == atrEmail) {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

void UserList::addUser(const string& atrFName, const string& atrLName, const string& atrBDate, const string& atrEmail, const string& atrPwd) {
    if (atrFName.empty() || atrLName.empty() || atrBDate.empty() || atrEmail.empty() || atrPwd.empty()) {
        cout << "Todos los campos deben estar completos." << endl;
        return;
    }

    if (emailExists(atrEmail)) {
        cout << "El correo electrónico ya está registrado." << endl;
        return;
    }

    User* nuevoUsuario = new User(atrFName, atrLName, atrBDate, atrEmail, atrPwd);
    nuevoUsuario->siguiente = primero;
    primero = nuevoUsuario;
    tamaño++;
    cout << "Usuario registrado exitosamente." << endl;
}

void UserList::printUsers() const {
    User* actual = primero;
    while (actual != nullptr) {
        cout << "Usuario: " << actual->atrFName << " " << actual->atrLName << endl;
        // cout << "Fecha de nacimiento: " << actual->atrBDate << endl;
        cout << "Correo: " << actual->atrEmail << endl;
        cout << "Contraseña: " << actual->atrPwd << endl;
        cout << endl;
        actual = actual->siguiente;
    }
}

bool UserList::authenticateUser(const string& atrEmail, const string& atrPwd) const {
    User* actual = primero;
    while (actual != nullptr) {
        if (actual->atrEmail == atrEmail && actual->atrPwd == atrPwd) {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

void UserList::deleteUserByEmail(const string& atrEmail) {
    if (atrEmail.empty()) {
        cout << "El correo electrónico no puede estar vacío." << endl;
        return;
    }

    User* actual = primero;
    User* previo = nullptr;

    while (actual != nullptr) {
        if (actual->atrEmail == atrEmail) {
            if (previo != nullptr) {
                previo->siguiente = actual->siguiente;
            } else {
                primero = actual->siguiente;
            }
            delete actual;
            tamaño--;
            cout << "Usuario eliminado exitosamente." << endl;
            return;
        }
        previo = actual;
        actual = actual->siguiente;
    }

    cout << "Usuario no encontrado." << endl;
}

int UserList::getSize() const {
    return tamaño;
}

string UserList::foundUser(const string& atrEmail) {
    User* actual = primero;
    while (actual != nullptr) {
        if (actual->atrEmail == atrEmail) {
            return actual->atrFName + " " + actual->atrLName;
        }
        actual = actual->siguiente;
    }
    return "";
}