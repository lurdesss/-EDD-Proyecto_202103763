#include "UserList.h"
#include <iostream>

UserList::UserList() : primero(nullptr) {
}

UserList::~UserList() {
    User* actual = primero;
    // limpiando memria
    while (actual != nullptr) {
        User* limpiable = actual;
        actual = actual->siguiente;
        delete limpiable;
    }
}

bool UserList::emailExists(const string& atrEmail) const {
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
    if (emailExists(atrEmail)) {
        cout << "El correo electrónico ya está registrado." << endl;
        return;
    }
    User* nuevoUsuario = new User(atrFName, atrLName, atrBDate, atrEmail, atrPwd);
    nuevoUsuario->siguiente = primero;
    primero = nuevoUsuario;
    cout << "Usuario registrado exitosamente." << endl;
}

void UserList::printUsers() const {
    User* actual = primero;
    while (actual != nullptr) {
        cout << "Nombre: " << actual->atrFName << " " << actual->atrLName << endl;
        cout << "Fecha de nacimiento: " << actual->atrBDate << endl;
        cout << "Correo electrónico: " << actual->atrEmail << endl;
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