#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <QString>

#define MAX 4
#define MIN 2


class Comentario {
public:

    QString correo;
    QString comentario;
    QString fecha;
    QString hora;
    QString key;

    Comentario(QString correo_, QString comentario_, QString fecha_, QString hora_)
        : correo(correo_), comentario(comentario_), fecha(fecha_), hora(hora_) { key = fecha + hora ; }


};

class BTreeNode {
public:
    Comentario* val[MAX + 1];
    int num;
    BTreeNode *link[MAX + 1];

    //BTreeNode(Comentario* val_, int num_, BTreeNode* link_) : val(0), num(num_), link(0) {}

    BTreeNode() : num(0) {
        for (int i = 0; i <= MAX; i++) {
            val[i] = nullptr;
            link[i] = nullptr;
        }
    }

};

class BTree {
public:
    BTreeNode *root = nullptr;

    void insert(Comentario* comment);
    void traversal(BTreeNode *myNode);
    void printTree(BTreeNode *node);

private:
    int setValue(Comentario* cmnt, Comentario* *pval, BTreeNode *node, BTreeNode **child);
    BTreeNode* createNode(Comentario* cmnt, BTreeNode *child);
    void insertNode(Comentario* cmnt, int pos, BTreeNode *node, BTreeNode *child);
    void splitNode(Comentario* cmnt, Comentario* *pval, int pos, BTreeNode *node, BTreeNode *child, BTreeNode **newNode);
};

#endif // BTREE_H
