#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <fstream>
#include <cstdlib> // Para usar system()
#include <QString>
#include <QTableWidget>
#include "abb.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

class Usuario {
public:
    int id;
    QString nombres;
    QString apellidos;
    QString fechaNacimiento;
    QString correo;
    QString contrasena;

    // Constructor actualizado
    Usuario(int id_, QString nombres_, QString apellidos_, QString fechaNacimiento_, QString correo_, QString contrasena_)
        : id(id_), nombres(nombres_), apellidos(apellidos_), fechaNacimiento(fechaNacimiento_), correo(correo_), contrasena(contrasena_) {}
};


class Node {
public:
    Usuario* user; // Cambiado de int val a Usuario* user
    Node* izq;
    Node* der;
    int alt;
    ABB* abbcadausr;

    Node(Usuario* user_) : user(user_), izq(nullptr), der(nullptr), alt(0), abbcadausr(new ABB()) {}
};

class AVLTree {
public:
    Node* raiz;
    AVLTree();

    void add(Usuario* user); // Cambiado de void add(int val) a void add(Usuario* user);
    void preorden(Node* tmp);
    void enorden(Node* tmp);
    void postorden(Node* tmp);
    void generateDot(const std::string& filename);

    // Nueva función de búsqueda por correo
    Usuario* buscarPorCorreo(const QString& correo);  // Busca un usuario por correo electrónico
    Usuario* preordenLogin(Node* tmp, QString& correo, QString& contra);
    Usuario* preordenBuscarCorreo(Node* tmp, const QString& correo);
    // Usuario* preordenLoginSearch(Node* tmp, QString& correo);
    // Usuario* preordenCase(Node* tmp);
    void preordenCase(Node* tmp, QTableWidget* tableWidget, int& localIndex);
    void postordenCase(Node* tmp, QTableWidget* tableWidget, int& localIndex);
    void inordenCase(Node* tmp, QTableWidget* tableWidget, int& localIndex);
    Node* preordenBuscarCorreoNodo(Node* tmp, const QString& correo);

    // Usuario* preordenBuscarNombres(Node* tmp, const std::string& nombres);
    Usuario* preordenBuscarNombres(Node* tmp, const QString& nombres);
    void preordenCaseToJson(Node* tmp, QJsonArray& usuariosArray);

private:
    void add(Usuario* user, Node*& tmp);
    int altura(Node* tmp);
    Node* srl(Node* t1);
    Node* srr(Node* t1);
    Node* drl(Node* tmp);
    Node* drr(Node* tmp);
    int maxi(int val1, int val2);
    void toDot(Node* tmp, std::ofstream& file);

    // Función privada recursiva para la búsqueda
    Usuario* buscarPorCorreo(Node* tmp, const QString& correo);
};

#endif // AVLTREE_H
