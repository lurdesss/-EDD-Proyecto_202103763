#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>
#include <string>
#include "ListaSimpleAmigos.h"


using namespace std;

class NodeVal {
public:
    bool exists = false;
    bool value = false;
};

class Node {
public:
    int i = -1, j = -1;
    bool value = false;
    string nombrei;
    string nombrej;
    Node* up = nullptr;
    Node* down = nullptr;
    Node* right = nullptr;
    Node* left = nullptr;

    Node(int i = -1, int j = -1, bool value = false, string nombrei = "", string nombrej = "");
};

class Matrix {
private:
    Node* root = nullptr;
    int width = 0;
    int height = 0;

    Node* searchRow(int i);
    Node* searchColumn(int j);
    bool nodeExists(Node* newNode);
    Node* insertRowHeader(int i);
    Node* insertColumnHeader(int j);
    void insertInRow(Node* newNode, Node* rowHeader);
    void insertInColumn(Node* newNode, Node* columnHeader);
    void printColumnHeaders() const;
    NodeVal getValue(int i, int j) const;

public:
    void insert(int i, int j, bool value, const string& nombrei = "", const string& nombrej = "");
    void print() const;
    void generateGraphvizImage(const std::string& filename) const;
    void imprimirAmigosPorEmail(const string& email) const;
    void agregarAmigosPorEmail(const std::string& email, ListaSimpleAmigos& listaAmigos) const;
};

#endif
