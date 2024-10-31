#include "relationlist.h"
#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

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

void ListOfList::cargaData(ListaSugerencias* listasug){
    this->listaSugerencias = listasug;
}

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

// Constructor de ChildFrequencyList

ChildFrequencyList::ChildFrequencyList() : head(nullptr) {}

ChildFrequencyList::~ChildFrequencyList() {
    while (head) {
        ChildNode* temp = head;
        head = head->next;
        delete temp;
    }
}

// Añadir un hijo o incrementar su contador
void ChildFrequencyList::addChild(const string& childName) {
    ChildNode* temp = head;

    // Busca si el hijo ya está en la lista
    while (temp) {
        if (temp->childName == childName) {
            temp->frequency++;  // Incrementa el contador
            return;
        }
        temp = temp->next;
    }

    // Si el hijo no está, se añade a la lista
    ChildNode* newChild = new ChildNode{childName, 1, head}; // Nuevo hijo con frecuencia 1
    head = newChild;  // Actualiza la cabeza de la lista
}

// Obtener la frecuencia de un hijo
int ChildFrequencyList::getFrequency(const string& childName) const {
    ChildNode* temp = head;

    // Busca el hijo en la lista
    while (temp) {
        if (temp->childName == childName) {
            return temp->frequency;  // Retorna la frecuencia encontrada
        }
        temp = temp->next;
    }

    return 0;  // Si no se encuentra el hijo, retorna 0
}

// Función para imprimir la lista de frecuencias (opcional para debugging)
void ChildFrequencyList::printList() const {
    ChildNode* temp = head;
    while (temp) {
        std::cout << "Hijo: " << temp->childName << ", Frecuencia: " << temp->frequency << std::endl;
        temp = temp->next;
    }
}

void ListOfList::graphMeFriendsAndTheirFriends(const string& startNode) {
    // Establece la ruta base para guardar el archivo de salida
    QString rutaBase = "/home/lurdes/Escritorio/datastructures/-EDD-Proyecto_202103763/Fase2/SocialStructure/salida/";
    ofstream file((rutaBase + "graph_friends.dot").toStdString()); // Crea un flujo de salida para el archivo DOT
    file << "graph G{" << endl; // Inicia la definición del gráfico
    file << "rankdir=LR;" << endl;  // Configura la dirección del gráfico de izquierda a derecha

    RelationList relations; // Estructura para almacenar las relaciones agregadas
    ChildFrequencyList childFrequency; // Lista de frecuencias para los nodos hijos

    shared_ptr<NodoRelaciones> temp = head; // Inicializa un puntero temporal al inicio de la lista

    // Buscamos el nodo de inicio
    while (temp && temp->name != startNode) {
        temp = temp->next; // Avanza en la lista hasta encontrar el nodo deseado
    }

    // Verifica si el nodo de inicio fue encontrado
    if (!temp) {
        cout << "Nodo inicial no encontrado!" << endl; // Mensaje de error si el nodo no existe
        return; // Termina la función
    }

    // Definición de colores para los nodos
    const string startNodeColor = "#A3D9A5";       // Color para el nodo inicial
    const string friendNodeColor = "#B2E1D6";      // Color para amigos directos
    const string friendOfFriendColor = "#F6E79E";

    struct QueueNode {
        shared_ptr<NodoRelaciones> node; // Nodo actual
        int level;                        // Nivel del nodo (distancia desde el nodo inicial)
        QueueNode* next;                 // Puntero al siguiente nodo en la cola
    };

    // Inicialización de la cola
    QueueNode* front = nullptr; // Frente de la cola
    QueueNode* rear = nullptr;  // Final de la cola

    auto enqueue = [&](shared_ptr<NodoRelaciones> node, int level) {
        QueueNode* newNode = new QueueNode{node, level, nullptr}; // Crea un nuevo nodo de la cola
        if (!rear) {
            front = rear = newNode; // Si la cola estaba vacía, establece el nuevo nodo como frente y final
        } else {
            rear->next = newNode; // Enlaza el nuevo nodo al final de la cola
            rear = newNode;       // Actualiza el final de la cola
        }
    };

    auto dequeue = [&]() -> QueueNode* {
        if (!front) return nullptr; // Si la cola está vacía, retorna nullptr
        QueueNode* tempNode = front; // Almacena el nodo frontal
        front = front->next; // Mueve el frente al siguiente nodo
        if (!front) rear = nullptr; // Si la cola queda vacía, actualiza el final a nullptr
        return tempNode; // Retorna el nodo desencolado
    };

    enqueue(temp, 0); // Encola el nodo inicial con nivel 0

    // Dentro del procesamiento de nodos en la cola
    while (front) {
        QueueNode* qNode = dequeue(); // Desencola un nodo
        if (!qNode) break; // Si no hay más nodos, termina el bucle

        string nodeColor = (qNode->level == 0) ? startNodeColor :
                               (qNode->level == 1) ? friendNodeColor :
                               friendOfFriendColor;

        file << qNode->node->name << " [color=\"" << nodeColor << "\", fontcolor=\"black\", style=\"filled\", shape=\"egg\"];" << endl;

        cout << "Nodo añadido: " << qNode->node->name << " con color " << nodeColor << endl;

        shared_ptr<SubNode> subTemp = qNode->node->list;
        while (subTemp) {
            if (!relations.relationExists(qNode->node->name, subTemp->targetName)) {
                file << qNode->node->name << " -- " << subTemp->targetName << ";" << endl;
                cout << "Relación añadida: " << qNode->node->name << " -- " << subTemp->targetName << endl;
                relations.addRelation(qNode->node->index, subTemp->value, qNode->node->name, subTemp->targetName);
            }

            if (qNode->level == 0) {
                shared_ptr<NodoRelaciones> nextNode = head;
                while (nextNode) {
                    if (nextNode->name == subTemp->targetName) {
                        enqueue(nextNode, qNode->level + 1);
                        file << nextNode->name << " [color=\"" << friendNodeColor << "\", fontcolor=\"black\", style=\"filled\", shape=\"egg\"];" << endl;

                        cout << "Nodo de nivel 1 añadido: " << nextNode->name << endl;
                        
                        break;
                    }
                    nextNode = nextNode->next;
                }
            } else if (qNode->level == 1) {
                shared_ptr<NodoRelaciones> nextNode = head;
                while (nextNode) {
                    if (nextNode->name == subTemp->targetName) {
                        file << nextNode->name << " [color=\"" << friendOfFriendColor << "\", fontcolor=\"black\", style=\"filled\", shape=\"egg\"];" << endl;
                        cout << "Nodo de nivel 2 añadido: " << nextNode->name << endl;

                        // CONTADOR QUE INCREMENTA ACA : contador2
                        childFrequency.addChild(nextNode->name);
                        string nameusr1 = nextNode->name;
                        int frq1 = childFrequency.getFrequency(nextNode->name);
                        cout << "Frecuencia de " << nameusr1 << " incrementada. Total: " << frq1 << endl;
                        if (listaSugerencias) {
                            listaSugerencias->agregarSugerencia(frq1, nameusr1);
                        } else {
                            cout << "Error: listaSugerencias es nulo" << endl;
                        }

                        break;
                    }
                    nextNode = nextNode->next;
                }
            }

            subTemp = subTemp->next;
        }

        temp = head;
        while (temp) {
            shared_ptr<SubNode> subTempBack = temp->list;
            while (subTempBack) {
                if (subTempBack->targetName == qNode->node->name) {
                    if (!relations.relationExists(temp->name, qNode->node->name)) {
                        file << temp->name << " -- " << qNode->node->name << ";" << endl;
                        cout << "Relación añadida: " << temp->name << " -- " << qNode->node->name << endl;
                        relations.addRelation(temp->index, qNode->node->index, temp->name, qNode->node->name);

                        file << temp->name << " [color=\"" << friendNodeColor << "\", fontcolor=\"black\", style=\"filled\", shape=\"egg\"];" << endl;
                        cout << "Nodo de nivel 1 añadido: " << temp->name << endl;
                    }

                    shared_ptr<SubNode> friendsOfParent = temp->list;
                    while (friendsOfParent) {
                        if (!relations.relationExists(temp->name, friendsOfParent->targetName)) {
                            file << temp->name << " -- " << friendsOfParent->targetName << ";" << endl;
                            relations.addRelation(temp->index, friendsOfParent->value, temp->name, friendsOfParent->targetName);

                            file << friendsOfParent->targetName << " [color=\"" << friendOfFriendColor << "\", fontcolor=\"black\", style=\"filled\", shape=\"egg\"];" << endl;
                            cout << "Amigo de un amigo añadido: " << friendsOfParent->targetName << endl;

                            // CONTADOR QUE INCREMENTA ACA : contador2
                            childFrequency.addChild(friendsOfParent->targetName);
                            string nameusr2 = friendsOfParent->targetName;
                            int frq2 = childFrequency.getFrequency(friendsOfParent->targetName);
                            cout << "Frecuencia de " << nameusr2 << " incrementada. Total: " << frq2 << endl;
                            if (listaSugerencias) {
                                listaSugerencias->agregarSugerencia(frq2, nameusr2);
                            } else {
                                cout << "Error: listaSugerencias es nulo" << endl;
                            }
                        }
                        friendsOfParent = friendsOfParent->next;
                    }
                }
                subTempBack = subTempBack->next;
            }
            temp = temp->next;
        }

        delete qNode;
    }

    file << "}" << endl;
    file.close();

    string command = "dot -Tpng " + rutaBase.toStdString() + "graph_friends.dot -o " + rutaBase.toStdString() + "graph_friends.png";
    if (system(command.c_str()) == 0) {
        cout << "Gráfico de amigos y amigos de amigos creado exitosamente" << endl;
    } else {
        cout << "Error al crear el gráfico de amigos" << endl;
    }
}




void ListOfList::graphOfAdyacencia() {
    QString rutaBase = "/home/lurdes/Escritorio/datastructures/-EDD-Proyecto_202103763/Fase2/SocialStructure/salida/";
    ofstream file((rutaBase + "graph_adyacencia.dot").toStdString());
    file << "digraph G{" << endl;
    file << "rankdir=LR;" << endl;  // Configuración para que el gráfico sea horizontal
    file << "node [shape=record];" << endl;  // Usamos nodos con forma de registro para representar listas de adyacencia

    shared_ptr<NodoRelaciones> temp = head;  // Inicia desde la cabeza de la lista

    // Recorre todos los nodos en la lista de listas
    while (temp) {
        // Definir un nodo con sus conexiones como un registro (cuadro con varias entradas)
        file << temp->name << " [label=\"{" << temp->name << "|";

        shared_ptr<SubNode> tempSub = temp->list;  // Recorre la lista de adyacencia del nodo
        bool first = true;
        while (tempSub) {
            if (!first) {
                file << " | ";  // Separador entre los nodos adyacentes
            }
            file << tempSub->targetName;
            first = false;
            tempSub = tempSub->next;  // Avanza al siguiente nodo adyacente
        }
        file << "}\"];" << endl;

        temp = temp->next;  // Avanza al siguiente nodo principal
    }

    file << "}" << endl;  // Cierra la definición del gráfico
    file.close();

    // Ejecuta el comando Graphviz para generar el gráfico en formato PNG
    string command = "dot -Tpng " + rutaBase.toStdString() + "graph_adyacencia.dot -o " + rutaBase.toStdString() + "graph_adyacencia.png";
    if (system(command.c_str()) == 0) {
        cout << "Gráfico de lista de adyacencia creado exitosamente" << endl;
    } else {
        cout << "Error al crear el gráfico de adyacencia" << endl;
    }
}


void ListOfList::guardarAmigosEnJson(QJsonArray& amigosArray) {
    shared_ptr<NodoRelaciones> temp = head;

    while (temp) {
        shared_ptr<SubNode> subTemp = temp->list;
        while (subTemp) {
            // Crear un objeto JSON para cada relación
            QJsonObject amigoObject;
            amigoObject["nombreEmisor"] = QString::fromStdString(temp->name);
            amigoObject["nombreReceptor"] = QString::fromStdString(subTemp->targetName);

            amigosArray.append(amigoObject);
            subTemp = subTemp->next;
        }
        temp = temp->next;
    }
}


