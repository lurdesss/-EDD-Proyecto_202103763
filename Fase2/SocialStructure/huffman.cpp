#include "huffman.h"
#include <cstdlib>

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

// Generar archivo .dot para Graphviz
void generateDotFile(HuffmanNode* root, ofstream& dotFile, int& nullCount) {
    if (!root) return;
    if (!root->left && !root->right) {
        dotFile << "    \"" << root << "\" [label=\"" << root->ch << " (" << root->freq << ")\"];\n";
    } else {
        dotFile << "    \"" << root << "\" [label=\"Freq: " << root->freq << "\"];\n";
    }
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

// Crear archivo .dot y convertir a imagen PNG
void createGraph(HuffmanNode* root) {
    ofstream dotFile("huffman_tree.dot");
    dotFile << "digraph G {\n";
    dotFile << "    node [fontname=\"Arial\"];\n";
    int nullCount = 0;
    generateDotFile(root, dotFile, nullCount);
    dotFile << "}\n";
    dotFile.close();
    cout << "Archivo 'huffman_tree.dot' generado correctamente.\n";
    system("dot -Tpng huffman_tree.dot -o huffman_tree.png");
    cout << "Imagen PNG generada: huffman_tree.png\n";
}
