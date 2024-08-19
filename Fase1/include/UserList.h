#ifndef USERLIST_H
#define USERLIST_H

#include "User.h"

class UserList {
private:
    User* primero;  // Puntero al primer usuario de la lista.
    int tamaño;     // Contador de usuarios

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
};

#endif
