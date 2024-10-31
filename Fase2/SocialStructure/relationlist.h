#ifndef RELATIONLIST_H
#define RELATIONLIST_H

#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include "listasugerencias.h"

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
    void graphMeFriendsAndTheirFriends(const string& startNode);
    void graphOfAdyacencia();
    void cargaData(ListaSugerencias* listasug);

private:
    ListaSugerencias* listaSugerencias;
};


// Estructura para almacenar un hijo y su frecuencia (número de padres)
struct ChildNode {
    string childName;    // Nombre del hijo
    int frequency;       // Frecuencia (número de padres)
    ChildNode* next;     // Puntero al siguiente nodo en la lista
};

// Lista enlazada para almacenar todos los hijos y sus frecuencias
class ChildFrequencyList {
private:
    ChildNode* head;     // Puntero al primer nodo en la lista

public:
    ChildFrequencyList();  // Constructor
    ~ChildFrequencyList(); // Destructor

    // Función para añadir un hijo o incrementar su contador
    void addChild(const string& childName);

    // Función para obtener la frecuencia de un hijo
    int getFrequency(const string& childName) const;

    // Función para imprimir la lista (debugging)
    void printList() const;
};


#endif // RELATIONLIST_H
