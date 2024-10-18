#include "abb.h"
#include <queue>
#include <iostream>
#include <fstream>
#include <cstdlib>  // Para usar std::system

void ABB::add(Publicaciones* publi)
{
    if (raiz != 0) add(publi, raiz);
    else raiz = new NodeABB(publi);
}

void ABB::add(Publicaciones* publi, NodeABB* tmp)
{
    if (publi->fecha < tmp->publi->fecha)
    {
        if (tmp->left != 0) add(publi, tmp->left);
        else tmp->left = new NodeABB(publi);
    }
    else
    {
        if (tmp->right != 0) add(publi, tmp->right);
        else tmp->right = new NodeABB(publi);
    }
}


// void ABB::preorderMod(NodeABB* tmp, std::vector<std::string>& fechas)
// {
//     if (tmp != 0)
//     {
//         //std::cout << tmp->publi->fecha.toStdString() << " \n";
//         fechas.push_back(tmp->publi->fecha.toStdString());
//         preorderMod(tmp->left);
//         preorderMod(tmp->right);
//     }
// }


void ABB::inorder(NodeABB* tmp)
{
    if (tmp != 0)
    {
        inorder(tmp->left);
        std::cout << tmp->publi->fecha.toStdString() << " ";
        inorder(tmp->right);
    }
}

void ABB::posorder(NodeABB* tmp)
{
    if (tmp != 0)
    {
        posorder(tmp->left);
        posorder(tmp->right);
        std::cout << tmp->publi->fecha.toStdString() << " ";
    }
}

void ABB::levelorder(NodeABB* tmp)
{
    if (tmp == 0) return;

    std::queue<NodeABB*> q;
    q.push(tmp);

    while (!q.empty())
    {
        NodeABB* node = q.front();
        std::cout << node->publi->fecha.toStdString() << " ";
        q.pop();

        if (node->left != 0) q.push(node->left);
        if (node->right != 0) q.push(node->right);
    }
}


QString ABB::preorderAtProfile(NodeABB* tmp)
{
    QString resultado;
    if (tmp != 0)
    {
        resultado += tmp->publi->fecha + " \n";
        resultado += tmp->publi->contenido + " \n";
        resultado += tmp->publi->hora + " \n";
        resultado += preorderAtProfile(tmp->left);
        resultado += preorderAtProfile(tmp->right);
    }
    return resultado;
}

QString ABB::posorderAtProfile(NodeABB* tmp)
{
    QString resultado;
    if (tmp != 0)
    {
        resultado += posorderAtProfile(tmp->left);  // Recorrer el subárbol izquierdo
        resultado += posorderAtProfile(tmp->right); // Recorrer el subárbol derecho
        resultado += tmp->publi->fecha + " \n";   // Visitar el nodo actual
        resultado += tmp->publi->contenido + " \n";
        resultado += tmp->publi->hora + " \n";
    }
    return resultado;
}

QString ABB::inorderAtProfile(NodeABB* tmp)
{
    QString resultado;
    if (tmp != 0)
    {
        resultado += inorderAtProfile(tmp->left);   // Recorrer el subárbol izquierdo
        resultado += tmp->publi->fecha + " \n";   // Visitar el nodo actual
        resultado += tmp->publi->contenido + " \n";
        resultado += tmp->publi->hora + " \n";
        resultado += inorderAtProfile(tmp->right);  // Recorrer el subárbol derecho
    }
    return resultado;
}


void ABB::generateDotForABB(NodeABB* tmp, std::ofstream& outFile)
{
    if (tmp != nullptr)
    {
        // Crear un nodo en el archivo DOT con el contenido de la publicación
        outFile << "\"" << tmp << "\" [label=\"Fecha: " << tmp->publi->fecha.toStdString() 
                << "\\nContenido: " << tmp->publi->contenido.toStdString() 
                << "\\nHora: " << tmp->publi->hora.toStdString() << "\"];\n";

        // Recorrer el subárbol izquierdo, si existe
        if (tmp->left != nullptr)
        {
            outFile << "\"" << tmp << "\" -> \"" << tmp->left << "\";\n";  // Conexión con el nodo izquierdo
            generateDotForABB(tmp->left, outFile);  // Recursión para el subárbol izquierdo
        }

        // Recorrer el subárbol derecho, si existe
        if (tmp->right != nullptr)
        {
            outFile << "\"" << tmp << "\" -> \"" << tmp->right << "\";\n";  // Conexión con el nodo derecho
            generateDotForABB(tmp->right, outFile);  // Recursión para el subárbol derecho
        }
    }
}

void ABB::exportToDotAndGenerateImage()
{
    // Crear el archivo .dot
    std::ofstream archivo("../../salida/arbol.dot");
    if (!archivo.is_open()) {
        std::cerr << "No se pudo crear el archivo .dot" << std::endl;
        return;
    }

    archivo << "digraph ABB {\n";
    archivo << "\tnode [shape=egg];\n";  // Cambiar la forma de los nodos a "egg"

    // Llamar a la función que recorre el ABB y escribe en el archivo DOT
    writeDot(raiz, archivo);

    archivo << "}\n";
    archivo.close();

    // Generar la imagen PNG utilizando Graphviz
    std::string comando = "dot -Tpng ../../salida/arbol.dot -o ../../salida/arbol.png";
    system(comando.c_str());
}

// Función recursiva para escribir los nodos y las conexiones en el archivo DOT
void ABB::writeDot(NodeABB* tmp, std::ofstream& archivo)
{
    if (tmp != nullptr)
    {
        // Etiqueta del nodo con la fecha y contenido
        archivo << "\"" << tmp->publi->fecha.toStdString() << "\" [label=\"Fecha: " 
                << tmp->publi->fecha.toStdString() << "\\nContenido: " 
                << tmp->publi->contenido.toStdString() << "\"];\n";

        // Conexión hacia el hijo izquierdo si existe
        if (tmp->left != nullptr)
        {
            archivo << "\"" << tmp->publi->fecha.toStdString() << "\" -> \"" 
                    << tmp->left->publi->fecha.toStdString() << "\" [label=\"left\"];\n";
        }

        // Conexión hacia el hijo derecho si existe
        if (tmp->right != nullptr)
        {
            archivo << "\"" << tmp->publi->fecha.toStdString() << "\" -> \"" 
                    << tmp->right->publi->fecha.toStdString() << "\" [label=\"right\"];\n";
        }

        // Llamada recursiva para recorrer los subárboles izquierdo y derecho
        writeDot(tmp->left, archivo);
        writeDot(tmp->right, archivo);
    }
}


