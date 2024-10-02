#ifndef ABB_H
#define ABB_H

#include <QString>
#include "btree.h"

class Publicaciones {
public:
    QString correo;
    QString contenido;
    QString fecha;
    QString hora;

    Publicaciones(QString correo_, QString contenido_, QString fecha_, QString hora_)
        : correo(correo_), contenido(contenido_), fecha(fecha_), hora(hora_) {}
};

class NodeABB
{
public:
    //int val;
    Publicaciones* publi;
    BTree* nodoAB;
    NodeABB* left;
    NodeABB* right;
    NodeABB(Publicaciones* publi_): publi(publi_), left(0), right(0), nodoAB(new BTree()) {}
};

class ABB
{
public:
    NodeABB* raiz;
    ABB() : raiz(0) {}

    void add(Publicaciones* publi);
    void add(Publicaciones* publi, NodeABB* tmp);
    // void preorderMod(NodeABB* tmp, std::vector<std::string>& fechas);
    void inorder(NodeABB* tmp);
    void posorder(NodeABB* tmp);
    void levelorder(NodeABB* tmp);
    QString preorderAtProfile(NodeABB* tmp);
    QString posorderAtProfile(NodeABB* tmp);
    QString inorderAtProfile(NodeABB* tmp);
    void generateDotForABB(NodeABB* tmp, std::ofstream& outFile);
    void exportToDotAndGenerateImage();
    void writeDot(NodeABB* tmp, std::ofstream& archivo);
};

#endif // ABB_H
