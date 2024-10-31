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
