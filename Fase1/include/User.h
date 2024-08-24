#ifndef USER_H
#define USER_H

#include <string> // biblioteca estándar de cadena de caracteres
using namespace std; // espacio de nombres estándar

struct User { // Nodo de la lista de usuarios
    // Atributos
    int atrId; //id
    string atrFName;
    string atrLName;
    string atrBDate;
    string atrEmail; //email
    string atrPwd;
    User* siguiente; //puntero al siguiente usuario
    
    // Constructor
    User(int paramId, string paramFName, string paramLName, string paramBDate, string paramEmail, string paramPwd);
};

#endif