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
    cout << "2. Carga de solicitudes" << endl;
    cout << "3. Carga de publicaciones" << endl;
    cout << "4. Gestion de usuarios" << endl; // moduloAdministradorA es submenu
    cout << "5. Reportes" << endl;
    cout << "6. Cerrar sesión" << endl;
}

void moduloAdministradorA(){
    cout << "a. Eliminar usuarios" << endl;
    cout << "x. volver" << endl;
}

void moduloUsuario(){
    cout << "1. Perfil" << endl;
    cout << "2. Solicitudes" << endl;
    cout << "3. Publicaciones" << endl; // moduloUsuario3 es submenu
    cout << "4. Reportes" << endl;
    cout << "5. Cerrar sesión" << endl;
}

void moduloUsuario1(){
    cout << "a. Ver perfil" << endl;
    cout << "b. Eliminar cuenta" << endl;
    cout << "x. Volver" << endl;
}

void moduloUsuario2(){
    cout << "a. Ver solicitudes" << endl; // moduloUsuario2I es submenu
    cout << "b. Enviar solicitud" << endl;
    cout << "x. Volver" << endl;
}

void moduloUsuario2I(){
    cout << "i. Elegir usuario a Aceptar/Rechazar" << endl;
    cout << "x. Volver" << endl;
}

void moduloUsuario2ISI(){
    // despues de entrada
    cout << "a. Aceptar" << endl;
    cout << "b. Rechazar" << endl;
    cout << "x. Volver" << endl;
}

void moduloUsuario3(){
    cout << "a. Ver publicaciones" << endl;
    cout << "b. Crear publicacion" << endl;
    cout << "c. Eliminar publicacion" << endl;
    cout << "x. Volver" << endl;
}

void moduloUsuario3A(){
    cout << "a. Ver publicación anterior" << endl;
    cout << "b. Ver publicacion siguiente" << endl;
    cout << "x. Volver" << endl;
}