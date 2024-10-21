#ifndef RELATIONLIST_H
#define RELATIONLIST_H

#include <iostream>
#include <fstream>
#include <memory>
#include <string>

using namespace std;


class SubNode {
public:
    string targetName; // Nombre del nodo objetivo
    int value;         // Valor asociado con el borde (si es necesario)
    shared_ptr<SubNode> next;

    SubNode(const string& name, int v);
};


class RelationNode {
public:
    int i, j;
    string nombrei, nombrej;
    RelationNode* next;

    RelationNode(int i, int j, const string& nombrei, const string& nombrej);
};

class RelationList {
public:
    RelationNode* head;

    RelationList();
    void addRelation(int i, int j, const string& nombrei, const string& nombrej);
    bool relationExists(const string& nombrei, const string& nombrej);
};


class NodoRelaciones {
public:
    int index;
    string name;
    shared_ptr<SubNode> list; // Lista de SubNode para los bordes
    shared_ptr<NodoRelaciones> next;

    NodoRelaciones(int idx, const string& n);
};

class ListOfList {
public:
    shared_ptr<NodoRelaciones> head; // Cambiar aquí también

    ListOfList();
    void insert(int index, int targetIndex, const string& sourceName, const string& targetName);
    void print();
    void graph();
};

#endif // RELATIONLIST_H
