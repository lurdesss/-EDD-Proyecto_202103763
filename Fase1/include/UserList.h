// // Protege contra inclusiones múltiples del mismo archivo.
// #ifndef USERLIST_H
// #define USERLIST_H

// // Incluye la estructura User.
// #include "User.h"

// // Clase que maneja una lista simplemente enlazada de usuarios.
// class UserList {
// private:
//     User* primero;  // Puntero al primer usuario de la lista.

// public:
//     // Constructor que inicializa la lista vacía.
//     UserList();

//     // Destructor que libera la memoria ocupada por la lista de usuarios.
//     ~UserList();

//     // Método que verifica si un correo electrónico ya existe en la lista.
//     bool emailExists(const string& atrEmail) const;

//     // Método que agrega un nuevo usuario a la lista.
//     void addUser(const string& atrFName, const string& atrLName, const string& atrBDate, const string& atrEmail, const string& atrPwd);

//     // Método que imprime todos los usuarios registrados.
//     void printUsers() const;
//     bool authenticateUser(const string& atrEmail, const string& atrPwd) const;
// };

// #endif // Finaliza la protección contra inclusiones múltiples.


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
};

#endif
