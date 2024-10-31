#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Definición de nodo del árbol de Huffman
struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode *left, *right;

    HuffmanNode(char ch, int freq);
};

// Lista enlazada para manejar la cola de prioridad manualmente
struct PriorityQueue {
    HuffmanNode* data;
    PriorityQueue* next;

    PriorityQueue(HuffmanNode* data);
};

// Funciones de manipulación de la cola de prioridad
void insert(PriorityQueue*& head, HuffmanNode* newNode);
HuffmanNode* extractMin(PriorityQueue*& head);

// Funciones para el algoritmo de Huffman
void buildHuffmanCode(HuffmanNode* root, string code, string codes[256]);
string compress(const string& text, string codes[256]);
string decompress(HuffmanNode* root, const string& compressedText);

// Funciones para graficar el árbol en formato Graphviz
void generateDotFile(HuffmanNode* root, ofstream& dotFile, int& nullCount);
void createGraph(HuffmanNode* root);
string escapeForGraphviz(const string& str);

#endif
