#ifndef USERLIST_H
#define USERLIST_H

#include "User.h"
#include <string>
#include <fstream>

class UserList {
private:
    User* primero;  // Puntero al primer usuario de la lista.
    int tamaño;     // Contador de usuarios
    int usrId; // Contador para generar IDs únicos

public:
    UserList();
    ~UserList();

    bool emailExists(const string& atrEmail) const;
    void addUser(const string& atrFName, const string& atrLName, const string& atrBDate, const string& atrEmail, const string& atrPwd);
    void printUsers() const;
    bool authenticateUser(const string& atrEmail, const string& atrPwd) const;
    void deleteUserByEmail(const string& atrEmail);
    int getSize() const;  // Método para obtener el tamaño de la lista
    string foundUser(const string& atrEmail);
    string getBirthDateByEmail(const string& atrEmail);
    int getId(const string& atrEmail);

    void generateDot(const std::string& filename) const;
    void renderGraphviz(const std::string& dotFilename, const std::string& imageFilename) const;
};

#endif
