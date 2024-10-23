#ifndef RELATIONLIST_H
#define RELATIONLIST_H

#include <iostream>
#include <fstream>
#include <memory>
#include <string>

using namespace std;

// Clase para representar cada sub-nodo
class SubNode {
public:
    string targetName; // Nombre del nodo objetivo
    int value;         // Valor asociado con el borde (si es necesario)
    shared_ptr<SubNode> next;

    SubNode(const string& name, int v);
};

// Clase para almacenar relaciones en una lista enlazada
class RelationNode {
public:
    int i, j;
    string nombrei, nombrej;
    RelationNode* next;

    RelationNode(int i, int j, const string& nombrei, const string& nombrej);
};

// Clase para manejar la lista de relaciones
class RelationList {
public:
    RelationNode* head;

    RelationList();
    void addRelation(int i, int j, const string& nombrei, const string& nombrej);
    bool relationExists(const string& nombrei, const string& nombrej);
};

// Clase para almacenar la frecuencia de los nodos
class NodeFrequency {
public:
    string nodeName;
    int frequency;
    NodeFrequency* next;

    NodeFrequency(const string& nodeName);
};

// Clase para manejar la lista de frecuencias
class FrequencyList {
public:
    NodeFrequency* head;

    FrequencyList();
    void addOrUpdate(const string& nodeName);
    void printFrequencies();
};

// Clase para almacenar cada nodo de relaciones
class NodoRelaciones {
public:
    int index;
    string name;
    shared_ptr<SubNode> list; // Lista de SubNode para los bordes
    shared_ptr<NodoRelaciones> next;

    NodoRelaciones(int idx, const string& n);
};

// Clase para manejar la lista de listas de relaciones
class ListOfList {
public:
    shared_ptr<NodoRelaciones> head; // Cambiado a shared_ptr

    ListOfList();
    void insert(int index, int targetIndex, const string& sourceName, const string& targetName);
    void print();
    void graph();
    void bfsFriends(const string& startNode, FrequencyList& frequencyList); // Función para contar amigos
    void graphMeFriendsAndTheirFriends(const string& startNode);
};

#endif // RELATIONLIST_H
