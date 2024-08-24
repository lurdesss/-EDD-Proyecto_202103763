#include "UserList.h"
#include <iostream>
#include <cstdlib>

UserList::UserList() : primero(nullptr), tamaño(0), usrId(1) {}

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

    User* nuevoUsuario = new User(usrId, atrFName, atrLName, atrBDate, atrEmail, atrPwd);
    nuevoUsuario->siguiente = primero;
    primero = nuevoUsuario;
    usrId++;
    tamaño++;
    cout << atrFName << " " << atrLName << " registrado exitosamente." << endl;
}

void UserList::printUsers() const {
    User* actual = primero;
    while (actual != nullptr) {
        cout << "ID: " << actual->atrId << endl;
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

string UserList::getBirthDateByEmail(const string& atrEmail) {
    User* actual = primero;
    while (actual != nullptr) {
        if (actual->atrEmail == atrEmail) {
            return actual->atrBDate;
        }
        actual = actual->siguiente;
    }
    return "";
}

int UserList::getId(const string& atrEmail) {
    User* actual = primero;
    while (actual != nullptr) {
        if (actual->atrEmail == atrEmail) {
            return actual->atrId;
        }
        actual = actual->siguiente;
    }
    return -1;
}


void UserList::generateDot(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "digraph G {" << std::endl;
        file << "node [shape=box, style=filled, fillcolor=yellow, fontcolor=black, color=none];" << std::endl;
        file << "rankdir=RL;" << std::endl;

        User* current = primero;
        int id = 0;
        while (current != nullptr) {
            file << "node" << id << " [label=\"" 
                << "[usuario] " << current->atrId << "\\n"
                << current->atrFName << " " << current->atrLName 
                << "\\n" << current->atrEmail 
                << "\\n" << current->atrBDate 
                << "\"];" << std::endl;
                
            if (current->siguiente != nullptr) {
                file << "node" << id << " -> node" << (id + 1) << ";" << std::endl;
            }
            current = current->siguiente;
            id++;
        }

        file << "}" << std::endl;  // Se cierra la definición del gráfico
        file.close();
    } else {
        std::cout << "No se pudo abrir el archivo" << std::endl;
    }
}



void UserList::renderGraphviz(const std::string& dotFilename, const std::string& imageFilename) const {
    std::string command = "dot -Tpng " + dotFilename + " -o " + imageFilename;
    system(command.c_str());

    // Abrir el archivo de imagen después de generarlo
    #ifdef _WIN32
        std::string openCommand = "start " + imageFilename;
    #elif __APPLE__
        std::string openCommand = "open " + imageFilename;
    #elif __linux__
        std::string openCommand = "xdg-open " + imageFilename;
    #else
    #error "Sistema operativo no soportado"
    #endif
    
    system(openCommand.c_str());
}
