#include "btree.h"
#include <QDebug> 

void BTree::insert(Comentario* val) {
    Comentario* newval = nullptr;
    BTreeNode *child = nullptr;
    if (setValue(val, &newval, root, &child)) {
        root = createNode(newval, child);
    }
    qDebug() << "Se insertaron correctamente los datos";   
}

int BTree::setValue(Comentario* val, Comentario** pval, BTreeNode *node, BTreeNode **child) {
    int pos;
    if (!node) {
        *pval = val;
        *child = nullptr;
        return 1;
    }

    if (val->key < node->val[1]->key) {
        pos = 0;
    } else {
        for (pos = node->num; (val->key < node->val[pos]->key && pos > 1); pos--);
        if (val->key == node->val[pos]->key) {
            std::cout << "Duplicates not allowed" << std::endl;
            return 0;
        }
    }

    if (setValue(val, pval, node->link[pos], child)) {
        if (node->num < MAX) {
            insertNode(*pval, pos, node, *child);
        } else {
            splitNode(*pval, pval, pos, node, *child, child);
            return 1;
        }
    }
    return 0;
}

BTreeNode* BTree::createNode(Comentario* val, BTreeNode *child) {
    BTreeNode *newNode = new BTreeNode();
    newNode->val[1] = val;
    newNode->num = 1;
    newNode->link[0] = root;
    newNode->link[1] = child;
    return newNode;
}

void BTree::insertNode(Comentario* val, int pos, BTreeNode *node, BTreeNode *child) {
    int j = node->num;
    while (j > pos) {
        node->val[j + 1] = node->val[j];
        node->link[j + 1] = node->link[j];
        j--;
    }
    node->val[j + 1] = val;
    node->link[j + 1] = child;
    node->num++;
}

void BTree::splitNode(Comentario* val, Comentario* *pval, int pos, BTreeNode *node, BTreeNode *child, BTreeNode **newNode) {
    int median, j;
    if (pos > MIN)
        median = MIN + 1;
    else
        median = MIN;

    *newNode = new BTreeNode();
    j = median + 1;

    while (j <= MAX) {
        (*newNode)->val[j - median] = node->val[j];
        (*newNode)->link[j - median] = node->link[j];
        j++;
    }

    node->num = median;
    (*newNode)->num = MAX - median;

    if (pos <= MIN) {
        insertNode(val, pos, node, child);
    } else {
        insertNode(val, pos - median, *newNode, child);
    }

    *pval = node->val[node->num - 1];
    (*newNode)->link[0] = node->link[node->num];
    node->num--;
}

void BTree::traversal(BTreeNode *myNode) {
    if (myNode) {
        qDebug() << "[";
        for (int i = 1; i < myNode->num; i++) {
            traversal(myNode->link[i]);  // Recorre los subárboles
            qDebug() << myNode->val[i]->comentario.toStdString();  // Imprime el valor actual
            if (i < myNode->num - 1) std::cout << ",";
        }
        traversal(myNode->link[myNode->num]);  // Último subárbol
        qDebug() << "]";
    }
}


void BTree::printTree(BTreeNode* node) {
    if (node == nullptr) return;  // Evitar nodos nulos

    // Recorre los elementos del nodo en orden
    for (int i = 1; i < node->num; i++) {
        // Llama recursivamente al hijo izquierdo antes de imprimir el valor actual
        printTree(node->link[i]);

        // Imprime el comentario solo si no es nulo
        Comentario* comentario = node->val[i];
        if (comentario != nullptr) {
                    qDebug() << "Clave: " << comentario->key.toStdString() ;
                    qDebug()  << "Correo: " << comentario->correo.toStdString();
                    qDebug()  << "Comentario: " << comentario->comentario.toStdString();
                    qDebug()  << "Fecha: " << comentario->fecha.toStdString();
                    qDebug()  << "Hora: " << comentario->hora.toStdString();
        }
    }

    // Llama recursivamente al último hijo
    printTree(node->link[node->num]);
}

