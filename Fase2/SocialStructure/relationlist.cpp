#include "relationlist.h"
#include <QString>
#include <fstream>
#include <iostream>

// Constructor de SubNode
SubNode::SubNode(const string& name, int v) : targetName(name), value(v), next(nullptr) {}

// Constructor de RelationNode
RelationNode::RelationNode(int i, int j, const string& nombrei, const string& nombrej)
    : i(i), j(j), nombrei(nombrei), nombrej(nombrej), next(nullptr) {}

// Constructor de RelationList
RelationList::RelationList() : head(nullptr) {}

// Agregar una nueva relación a la lista
void RelationList::addRelation(int i, int j, const string& nombrei, const string& nombrej) {
    RelationNode* newNode = new RelationNode(i, j, nombrei, nombrej);
    newNode->next = head;
    head = newNode;
}

// Comprobar si existe una relación
bool RelationList::relationExists(const string& nombrei, const string& nombrej) {
    RelationNode* current = head;
    while (current) {
        if (current->nombrei == nombrei && current->nombrej == nombrej) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Constructor de NodoRelaciones
NodoRelaciones::NodoRelaciones(int idx, const string& n) : index(idx), name(n), next(nullptr), list(nullptr) {}

// Constructor de ListOfList
ListOfList::ListOfList() : head(nullptr) {}

// Insertar una nueva relación
void ListOfList::insert(int index, int targetIndex, const string& sourceName, const string& targetName) {
    // Comprobar si el nodo fuente existe; si no, crearlo
    if (!head) {
        head = make_shared<NodoRelaciones>(index, sourceName);
    }

    shared_ptr<NodoRelaciones> temp = head;
    while (temp) {
        if (temp->name == sourceName) {
            // Encontrado el nodo fuente; ahora agregar el nodo objetivo a la sublista
            if (!temp->list) {
                temp->list = make_shared<SubNode>(targetName, targetIndex);
            } else {
                shared_ptr<SubNode> subTemp = temp->list;
                while (subTemp->next) {
                    subTemp = subTemp->next;
                }
                subTemp->next = make_shared<SubNode>(targetName, targetIndex);
            }
            return; // Salir después de insertar
        }
        if (!temp->next) break; // Si llegamos al final de la lista
        temp = temp->next;
    }

    // Si el nodo fuente no se encuentra, crear un nuevo nodo fuente
    auto newNode = make_shared<NodoRelaciones>(index, sourceName);
    newNode->list = make_shared<SubNode>(targetName, targetIndex);
    temp->next = newNode;
}

// Imprimir la estructura para depuración
void ListOfList::print() {
    shared_ptr<NodoRelaciones> temp = head;
    while (temp) {
        cout << "Nodo: " << temp->name << " -> ";
        shared_ptr<SubNode> subTemp = temp->list;
        while (subTemp) {
            cout << subTemp->targetName << " ";
            subTemp = subTemp->next;
        }
        cout << endl;
        temp = temp->next;
    }
}

// Función para generar el gráfico
void ListOfList::graph() {
    QString rutaBase = "/home/lurdes/Escritorio/datastructures/-EDD-Proyecto_202103763/Fase2/SocialStructure/salida/";

    ofstream file((rutaBase + "graph.dot").toStdString());
    file << "graph G{" << endl;
    file << "rankdir=LR;" << endl;  // Configuración para dirección de izquierda a derecha

    RelationList relations; // Para almacenar relaciones añadidas
    shared_ptr<NodoRelaciones> temp = head;

    while (temp) {
        // Comprobar para cada sub-nodo (objetivo)
        shared_ptr<SubNode> temp2 = temp->list;
        while (temp2) {
            // Agregar solo las relaciones
            if (!relations.relationExists(temp->name, temp2->targetName)) {
                file << temp->name << " -- " << temp2->targetName << ";" << endl; // Cambiar '->' por '--' para relaciones no dirigidas
                relations.addRelation(temp->index, temp2->value, temp->name, temp2->targetName);
            }
            temp2 = temp2->next;
        }
        temp = temp->next;
    }

    file << "}" << endl;
    file.close();

    // Ejecutar el comando de Graphviz para crear la imagen en la carpeta específica
    string command = "dot -Tpng " + rutaBase.toStdString() + "graph.dot -o " + rutaBase.toStdString() + "graph.png";
    if (system(command.c_str()) == 0) {
        cout << "Gráfico creado exitosamente" << endl;
    } else {
        cout << "Error al crear el gráfico" << endl;
    }
}
