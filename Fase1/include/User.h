#ifndef USER_H
#define USER_H

#include <string> // biblioteca estándar de cadena de caracteres
using namespace std; // espacio de nombres estándar

struct User {
    // Atributos de la estructura User.
    string atrFName;
    string atrLName;
    string atrBDate;
    string atrEmail; //email
    string atrPwd;
    User* siguiente; //puntero al siguiente usuario
    // Constructor de la estructura User.
    User(string paramFName, string paramLName, string paramBDate, string paramEmail, string paramPwd);
};

#endif