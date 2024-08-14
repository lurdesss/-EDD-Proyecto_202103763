// voids.cpp
#include "../include/Utils.h"
#include <iostream>
using namespace std;

void menuLogin(){
    cout << "Social structure [login]" << endl;
    cout << "1. Iniciar sesion" << endl;
    cout << "2. Registrarse" << endl;
    cout << "3. Informacion" << endl;
    cout << "4. Salir" << endl;
}

void moduloAdministrador(){
    cout << "1. Carga de usuarios" << endl;
    cout << "2. Carga de relaciones" << endl;
    cout << "3. Carga de publicaciones" << endl;
    cout << "4. Gestion de usuarios" << endl; // moduloAdministradorA es submenu
    cout << "5. Reportes" << endl;
}

void moduloAdministradorA(){
    cout << "a. Eliminar usuarios" << endl;
}

void moduloUsuario(){
    cout << "1. Perfil" << endl;
    cout << "2. Solicitudes" << endl;
    cout << "3. Publicaciones" << endl;
    cout << "4. Reportes" << endl;
    cout << "5. Salir" << endl;
}

void moduloUsuario1(){
    cout << "a. Ver perfil" << endl;
    cout << "b. Eliminar cuenta" << endl;
}

void moduloUsuario2(){
    cout << "a. Ver solicitudes" << endl; // moduloUsuario2I es submenu
    cout << "b. Enviar solicitud" << endl;
}

void moduloUsuario2I(){
    cout << "i. Aceptar/Rechazar" << endl;
}

void moduloUsuario3(){
    cout << "a. Ver publicaciones" << endl;
    cout << "b. Crear publicacion" << endl;
    cout << "c. Eliminar publicacion" << endl;
}