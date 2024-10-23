#include "relationlist.h"
#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <QString>

using namespace std;

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

void ListOfList::insert(int index, int targetIndex, const string& sourceName, const string& targetName) {
    if (!head) {
        // Crear el primer nodo en la lista
        head = make_shared<NodoRelaciones>(index, sourceName);
    }

    shared_ptr<NodoRelaciones> temp = head;
    shared_ptr<NodoRelaciones> prev = nullptr;

    // Buscar el nodo fuente (sourceName) en la lista
    while (temp && temp->name != sourceName) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        // Si no encontramos el nodo fuente, lo creamos y lo añadimos al final
        temp = make_shared<NodoRelaciones>(index, sourceName);
        if (prev) {
            prev->next = temp;
        }
    }

    // Verificar si ya existe la relación con targetName
    shared_ptr<SubNode> subTemp = temp->list;
    while (subTemp) {
        if (subTemp->targetName == targetName) {
            return;  // La relación ya existe, no hacer nada
        }
        subTemp = subTemp->next;
    }

    // Si no existe la relación, añadirla
    shared_ptr<SubNode> newSubNode = make_shared<SubNode>(targetName, targetIndex);
    if (!temp->list) {
        temp->list = newSubNode;
    } else {
        // Añadir al final de la lista de relaciones
        shared_ptr<SubNode> lastSubNode = temp->list;
        while (lastSubNode->next) {
            lastSubNode = lastSubNode->next;
        }
        lastSubNode->next = newSubNode;
    }
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
    file << "rankdir=LR;" << endl;  // Configuration for left-to-right direction

    RelationList relations; // To store added relations
    shared_ptr<NodoRelaciones> temp = head;

    while (temp) {
        shared_ptr<SubNode> temp2 = temp->list;
        while (temp2) {
            if (!relations.relationExists(temp->name, temp2->targetName)) {
                file << temp->name << " -- " << temp2->targetName << ";" << endl; // Use '--' for undirected relations
                relations.addRelation(temp->index, temp2->value, temp->name, temp2->targetName);
            }
            temp2 = temp2->next;
        }
        temp = temp->next;
    }

    file << "}" << endl;
    file.close();

    // Execute the Graphviz command to create the image in the specified folder
    string command = "dot -Tpng " + rutaBase.toStdString() + "graph.dot -o " + rutaBase.toStdString() + "graph.png";
    if (system(command.c_str()) == 0) {
        cout << "Gráfico creado exitosamente" << endl;
    } else {
        cout << "Error al crear el gráfico" << endl;
    }
}


void ListOfList::graphMeFriendsAndTheirFriends(const string& startNode) {
    QString rutaBase = "/home/lurdes/Escritorio/datastructures/-EDD-Proyecto_202103763/Fase2/SocialStructure/salida/";
    ofstream file((rutaBase + "graph_friends.dot").toStdString());
    file << "graph G{" << endl;
    file << "rankdir=LR;" << endl;  // Configuración de dirección izquierda a derecha

    RelationList relations; // Para almacenar las relaciones agregadas
    shared_ptr<NodoRelaciones> temp = head;

    // Buscamos el nodo de inicio
    while (temp && temp->name != startNode) {
        temp = temp->next;
    }

    if (!temp) {
        cout << "Nodo inicial no encontrado!" << endl;
        return;
    }

    // Estructura para realizar BFS
    struct QueueNode {
        shared_ptr<NodoRelaciones> node;
        int level;
        QueueNode* next;
    };

    QueueNode* front = nullptr;
    QueueNode* rear = nullptr;

    // Función para encolar un nodo
    auto enqueue = [&](shared_ptr<NodoRelaciones> node, int level) {
        QueueNode* newNode = new QueueNode{node, level, nullptr};
        if (!rear) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    };

    // Función para desencolar un nodo
    auto dequeue = [&]() -> QueueNode* {
        if (!front) return nullptr;
        QueueNode* tempNode = front;
        front = front->next;
        if (!front) rear = nullptr;
        return tempNode;
    };

    enqueue(temp, 0); // Encolar el nodo inicial con nivel 0

    // Procesar los nodos en la cola
    while (front) {
        QueueNode* qNode = dequeue();
        if (!qNode) break;

        // Procesamos las relaciones de nivel 0 (nodo inicial) y nivel 1 (amigos directos)
        shared_ptr<SubNode> subTemp = qNode->node->list;
        while (subTemp) {
            // Añadir la relación del nodo actual al amigo
            if (!relations.relationExists(qNode->node->name, subTemp->targetName)) {
                file << qNode->node->name << " -- " << subTemp->targetName << ";" << endl;
                relations.addRelation(qNode->node->index, subTemp->value, qNode->node->name, subTemp->targetName);
            }

            // Encolar los amigos de nivel 1 para llegar al nivel 2
            if (qNode->level == 0) {
                // Buscar el nodo correspondiente al subTemp->targetName
                shared_ptr<NodoRelaciones> nextNode = head;
                while (nextNode) {
                    if (nextNode->name == subTemp->targetName) {
                        enqueue(nextNode, qNode->level + 1);  // Encolar al siguiente nivel (nivel 1)
                        break;
                    }
                    nextNode = nextNode->next;
                }
            }

            subTemp = subTemp->next;
        }

        // Ahora, buscamos relaciones donde el nodo actual es un destino (nivel 0)
        // Buscamos nodos que apuntan al nodo de inicio
        temp = head;
        while (temp) {
            shared_ptr<SubNode> subTempBack = temp->list;
            while (subTempBack) {
                if (subTempBack->targetName == qNode->node->name) {
                    // Si el nodo actual tiene una relación hacia el nodo de inicio, la añadimos
                    if (!relations.relationExists(temp->name, qNode->node->name)) {
                        file << temp->name << " -- " << qNode->node->name << ";" << endl;
                        relations.addRelation(temp->index, qNode->node->index, temp->name, qNode->node->name);
                    }

                    // Ahora procesamos los amigos del nodo que apunta hacia el nodo de inicio
                    shared_ptr<SubNode> friendsOfParent = temp->list;
                    while (friendsOfParent) {
                        // Añadir la relación del padre al amigo
                        if (!relations.relationExists(temp->name, friendsOfParent->targetName)) {
                            file << temp->name << " -- " << friendsOfParent->targetName << ";" << endl;
                            relations.addRelation(temp->index, friendsOfParent->value, temp->name, friendsOfParent->targetName);
                        }
                        friendsOfParent = friendsOfParent->next;
                    }
                }
                subTempBack = subTempBack->next;
            }
            temp = temp->next;
        }

        delete qNode;  // Liberar memoria del nodo en la cola
    }

    file << "}" << endl;
    file.close();

    // Ejecutar el comando de Graphviz para generar la imagen en la carpeta especificada
    string command = "dot -Tpng " + rutaBase.toStdString() + "graph_friends.dot -o " + rutaBase.toStdString() + "graph_friends.png";
    if (system(command.c_str()) == 0) {
        cout << "Gráfico de amigos y amigos de amigos creado exitosamente" << endl;
    } else {
        cout << "Error al crear el gráfico de amigos" << endl;
    }
}



// Constructor de NodeFrequency
NodeFrequency::NodeFrequency(const string& nodeName) : nodeName(nodeName), frequency(1), next(nullptr) {}

// Constructor de FrequencyList
FrequencyList::FrequencyList() : head(nullptr) {}

// Agregar o actualizar un nodo en la lista de frecuencias
void FrequencyList::addOrUpdate(const string& nodeName) {
    NodeFrequency* current = head;
    NodeFrequency* prev = nullptr;

    while (current) {
        if (current->nodeName == nodeName) {
            current->frequency++;
            return;
        }
        prev = current;
        current = current->next;
    }

    NodeFrequency* newNode = new NodeFrequency(nodeName);
    if (!prev) {
        head = newNode;
    } else {
        prev->next = newNode;
    }
}

// Imprimir frecuencias
void FrequencyList::printFrequencies() {
    cout << "Frecuencias de Nodos: ";
    NodeFrequency* current = head;
    int totalNodes = 0;
    while (current) {
        totalNodes += current->frequency;
        current = current->next;
    }
    cout << totalNodes << endl;

    current = head;
    while (current) {
        cout << "Nodo: " << current->nodeName << ", Frecuencia: " << current->frequency << endl;
        current = current->next;
    }
}

void ListOfList::bfsFriends(const string& startNode, FrequencyList& frequencyList) {
    struct QueueNode {
        shared_ptr<NodoRelaciones> node;
        int level;
        QueueNode* next;
    };

    QueueNode* front = nullptr;
    QueueNode* rear = nullptr;

    // Buscar el nodo inicial
    shared_ptr<NodoRelaciones> temp = head;
    while (temp && temp->name != startNode) {
        temp = temp->next;
    }
    if (!temp) {
        cout << "Nodo inicial no encontrado!" << endl;
        return;
    }

    // Función para encolar un nodo
    auto enqueue = [&](shared_ptr<NodoRelaciones> node, int level) {
        QueueNode* newNode = new QueueNode{node, level, nullptr};
        if (!rear) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    };

    // Función para desencolar un nodo
    auto dequeue = [&]() -> QueueNode* {
        if (!front) return nullptr;
        QueueNode* tempNode = front;
        front = front->next;
        if (!front) rear = nullptr;
        return tempNode;
    };

    enqueue(temp, 0); // Encolar el nodo inicial con nivel 0

    // Procesar los nodos en la cola
    while (front) {
        QueueNode* qNode = dequeue();
        if (!qNode) break;

        if (qNode->level == 1) {
            // Solo procesar si estamos en el nivel 1 (amigos directos)
            shared_ptr<SubNode> subTemp = qNode->node->list;
            while (subTemp) {
                frequencyList.addOrUpdate(subTemp->targetName);
                subTemp = subTemp->next;
            }
        } else if (qNode->level < 1) {
            // Encolar los amigos de este nodo (siguiente nivel será 1)
            shared_ptr<SubNode> subTemp = qNode->node->list;
            while (subTemp) {
                // Buscar el nodo correspondiente al subTemp->targetName
                shared_ptr<NodoRelaciones> nextNode = head;
                while (nextNode) {
                    if (nextNode->name == subTemp->targetName) {
                        enqueue(nextNode, qNode->level + 1); // Encolar al siguiente nivel
                        break;
                    }
                    nextNode = nextNode->next;
                }
                subTemp = subTemp->next;
            }
        }

        delete qNode; // Liberar memoria del nodo de la cola
    }
}
