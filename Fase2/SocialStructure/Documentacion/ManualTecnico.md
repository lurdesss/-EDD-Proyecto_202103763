# Manual Técnico del Proyecto: Social Structure

## Universidad San Carlos de Guatemala
**Facultad de Ingeniería**  
**Escuela de Ciencias y Sistemas**  
**Curso: Estructuras de Datos**

**Proyecto Fase 3**

**Implementación de estructuras no lineales**

---

## Índice

1. [Objetivos](#objetivos)
2. [Descripción General](#descripción-general)
3. [Modificaciones](#modificaciones)
   - [Relaciones de Amistad](#relaciones-de-amistad)
   - [Sugerencias de Amistad](#sugerencias-de-amistad)
   - [Compresión y Descompresión de Información](#compresión-y-descompresión-de-información)
   - [Perfil de Usuario](#perfil-de-usuario)
4. [Seguridad](#seguridad)
   - [Blockchain](#blockchain)
   - [Árbol de Merkle](#árbol-de-merkle)
   - [Protección de Datos](#protección-de-datos)
5. [Reportes](#reportes)
6. [Observaciones y Entregables](#observaciones-y-entregables)

---

## Objetivos

### Objetivo General
Aplicar conocimientos avanzados de estructuras de datos para desarrollar soluciones seguras en el contexto de una aplicación social.

### Objetivos Específicos
- Implementar estructuras de datos no lineales.
- Desarrollar una aplicación de escritorio en C++.
- Generar visualizaciones con Graphviz.
- Incorporar tecnología blockchain para mejorar la seguridad de la aplicación.

---

## Descripción General

Este proyecto es la tercera fase de una aplicación social que, debido a su crecimiento, requiere nuevas funcionalidades y mejoras en seguridad, especialmente para proteger la información de los usuarios. En esta fase, se integran mecanismos como la criptografía y blockchain para asegurar los datos.

---

## Modificaciones

### Relaciones de Amistad
La representación de las relaciones de amistad cambia de una matriz dispersa a un **grafo no dirigido** basado en una **lista de adyacencia**. Cada nodo representa un usuario y cada arista representa una relación de amistad. Esta estructura permite una mayor escalabilidad.

```cpp
// Código para representar un grafo no dirigido con lista de adyacencia
class Grafo {
    // Implementación
};
```


### Sugerencias de Amistad
Se introduce un algoritmo para recomendar amigos basado en la distancia de dos saltos en el grafo (amigos de amigos), priorizando aquellos con mayor cantidad de amigos en común.

```cpp

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

```

### Compresión y Descompresión de Información
Los datos de usuarios, amistades, y solicitudes se almacenan comprimidos mediante el método de Huffman. Al cerrar sesión, la información se comprime en archivos `.edd`, y al iniciar sesión, se descomprime para su uso.

```cpp
#include "huffman.h"
#include <cstdlib>
#include <QString>

// Implementación del constructor de HuffmanNode
HuffmanNode::HuffmanNode(char ch, int freq) {
    this->ch = ch;
    this->freq = freq;
    left = right = nullptr;
}

// Implementación del constructor de PriorityQueue
PriorityQueue::PriorityQueue(HuffmanNode* data) : data(data), next(nullptr) {}

// Insertar en la cola de prioridad (ordenado por frecuencia)
void insert(PriorityQueue*& head, HuffmanNode* newNode) {
    PriorityQueue* newElement = new PriorityQueue(newNode);
    if (!head || head->data->freq > newNode->freq) {
        newElement->next = head;
        head = newElement;
    } else {
        PriorityQueue* current = head;
        while (current->next && current->next->data->freq <= newNode->freq) {
            current = current->next;
        }
        newElement->next = current->next;
        current->next = newElement;
    }
}

// Extraer el nodo con la menor frecuencia
HuffmanNode* extractMin(PriorityQueue*& head) {
    if (!head) return nullptr;
    PriorityQueue* temp = head;
    HuffmanNode* minNode = head->data;
    head = head->next;
    delete temp;
    return minNode;
}

// Generar los códigos de Huffman recursivamente
void buildHuffmanCode(HuffmanNode* root, string code, string codes[256]) {
    if (!root) return;
    if (!root->left && !root->right) {
        codes[(unsigned char)root->ch] = code;
    }
    buildHuffmanCode(root->left, code + "0", codes);
    buildHuffmanCode(root->right, code + "1", codes);
}

// Función para comprimir una cadena de texto
string compress(const string& text, string codes[256]) {
    string compressedText = "";
    for (char ch : text) {
        compressedText += codes[(unsigned char)ch];
    }
    return compressedText;
}

// Función para descomprimir el texto comprimido
string decompress(HuffmanNode* root, const string& compressedText) {
    string decompressedText = "";
    HuffmanNode* currentNode = root;
    for (char bit : compressedText) {
        currentNode = (bit == '0') ? currentNode->left : currentNode->right;
        if (!currentNode->left && !currentNode->right) {
            decompressedText += currentNode->ch;
            currentNode = root;
        }
    }
    return decompressedText;
}

// Escapar caracteres especiales para Graphviz
string escapeForGraphviz(const string& str) {
    string escapedStr = str;
    size_t pos = 0;
    while ((pos = escapedStr.find("\"", pos)) != string::npos) {
        escapedStr.insert(pos, "\\");
        pos += 2; // Mover el índice después de las comillas escapadas
    }
    return escapedStr;
}

// Generar archivo .dot para Graphviz
void generateDotFile(HuffmanNode* root, ofstream& dotFile, int& nullCount) {
    if (!root) return;

    string label;
    if (!root->left && !root->right) {
        label = escapeForGraphviz(string(1, root->ch)) + " (" + to_string(root->freq) + ")";
    } else {
        label = "Freq: " + to_string(root->freq);
    }
    
    dotFile << "    \"" << root << "\" [label=\"" << label << "\"];\n";

    if (root->left) {
        dotFile << "    \"" << root << "\" -> \"" << root->left << "\" [label=\"0\"];\n";
        generateDotFile(root->left, dotFile, nullCount);
    } else {
        dotFile << "    null" << nullCount << " [shape=point];\n";
        dotFile << "    \"" << root << "\" -> null" << nullCount++ << " [label=\"0\"];\n";
    }

    if (root->right) {
        dotFile << "    \"" << root << "\" -> \"" << root->right << "\" [label=\"1\"];\n";
        generateDotFile(root->right, dotFile, nullCount);
    } else {
        dotFile << "    null" << nullCount << " [shape=point];\n";
        dotFile << "    \"" << root << "\" -> null" << nullCount++ << " [label=\"1\"];\n";
    }
}

void createGraph(HuffmanNode* root) {
    QString rutaSalida = "/home/lurdes/Escritorio/datastructures/-EDD-Proyecto_202103763/Fase2/SocialStructure/salida/huffman_tree.dot";
    ofstream dotFile(rutaSalida.toStdString());
    
    dotFile << "digraph G {\n";
    dotFile << "    node [fontname=\"Arial\"];\n";
    int nullCount = 0;
    generateDotFile(root, dotFile, nullCount);
    dotFile << "}\n";
    dotFile.close();
    
    std::cout << "Archivo 'huffman_tree.dot' generado correctamente.\n";
    
    // Ejecutar el comando para convertir el archivo .dot a .png
    std::string command = "dot -Tpng " + rutaSalida.toStdString() + " -o /home/lurdes/Escritorio/datastructures/-EDD-Proyecto_202103763/Fase2/SocialStructure/salida/huffman_tree.png";
    system(command.c_str());
    
    std::cout << "Imagen PNG generada: huffman_tree.png\n";
}

```


### Perfil de Usuario
Cada usuario puede modificar su perfil: nombre, apellido, fecha de nacimiento y contraseña.

```cpp
// no se realiza
```

### Seguridad

#### Blockchain
El proyecto implementa una blockchain donde cada bloque contiene información de publicaciones y comentarios, asegurada mediante la función SHA256. Se utiliza un mecanismo de prueba de trabajo con un prefijo de 4 ceros para validar cada nuevo bloque.

```cpp
 #ifndef BLOCKCHAIN_H
 #define BLOCKCHAIN_H
 #include <Qstring>

     int block_id = 0;

 class Block{
 public:
        int index;
        int nonce;
        std::String timeslamp;
        int nodoInicio;
        int nodoFinal;
        int costo;
        std::string previous_hash = "0000";
        std::string root_merkle = "0000";
        std::string hash = "0000";
        std::shared_ptr<Block> next = nullptr;
        std::shared_ptr<ABB> ramas = nullptr;

        Block();

    void generate_block(std::shared_ptr<ABB> newRamas, int idE, int idS, int costo);
    void print_data() const;

private:
    static int block_id;
 };

 class chainer{
    std::shared_ptr<Block> head = nullptr;
    std::shared_ptr<Block> tail = nullptr;

    void add_block(std::shared_ptr<Block> new_block);
    void print_chain() const;
    void genJson() const;
 };

 #endif // BLOCKCHAIN_H 
```

#### Árbol de Merkle
Para la verificación de integridad, se utiliza un Árbol de Merkle donde cada nodo hoja es un hash de una publicación y sus comentarios. La raíz de este árbol proporciona una verificación de la integridad del conjunto de datos.

```cpp
// no se realiza
};

```

#### Protección de Datos
La protección de datos sensibles, como contraseñas, se realiza mediante la función SHA256. Adicionalmente, la blockchain detectará cualquier manipulación en los datos y resaltará los bloques comprometidos.

```cpp
// no se realiza
```


# Reportes

Los reportes incluyen gráficos de amistades y sugerencias de amistad, utilizando colores para distinguir los diferentes tipos de relaciones.

## Administrador

- **Gráfico de amistades**
- **Gráfico de sugerencias de amistad**
- **Gráfico de Blockchain**
- **Gráfico de Árbol de Merkle / para este caso se antepone arbol de Huffman como evidencia**

## Usuario

- **Muestra sugerencias de amisatd en la interfaz**
- **Gráfico de grafo, sugerencias de amistad por color**

## Observaciones y Entregables

- Sistema operatico en el que se realizó la Fase3: Linux Ubuntu
- Version de qt Creator, MinGW x64: 6.8.0
- Link a repositorio.
- Código fuente.
- Manuales técnico y de usuario.

