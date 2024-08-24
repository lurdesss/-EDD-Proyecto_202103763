#include "Matrix.h"
#include <fstream>
#include <cstdlib>  // Para system()

Node::Node(int i, int j, bool value, string nombrei, string nombrej)
    : i(i), j(j), value(value), nombrei(nombrei), nombrej(nombrej) {}

void Matrix::insert(int i, int j, bool value, const string& nombrei, const string& nombrej) {
    Node* newNode = new Node(i, j, value, nombrei, nombrej);

    if (!root) {
        root = new Node(-1, -1);
    }

    Node* row = searchRow(i);
    Node* column = searchColumn(j);

    if (j > width) width = j;
    if (i > height) height = i;

    if (!nodeExists(newNode)) {
        if (!column) {
            column = insertColumnHeader(j);
        }

        if (!row) {
            row = insertRowHeader(i);
        }
        insertInColumn(newNode, row);
        insertInRow(newNode, column);
    }
}

Node* Matrix::searchRow(int i) {
    Node* current = root;

    while (current) {
        if (current->i == i) return current;
        current = current->down;
    }
    return nullptr;
}

Node* Matrix::searchColumn(int j) {
    Node* current = root;

    while (current) {
        if (current->j == j) return current;
        current = current->right;
    }
    return nullptr;
}

bool Matrix::nodeExists(Node* newNode) {
    Node* rowHeader = root;

    while (rowHeader) {
        if (rowHeader->i == newNode->i) {
            Node* column = rowHeader;
            while (column) {
                if (column->j == newNode->j) {
                    column->value = newNode->value;
                    column->nombrei = newNode->nombrei;
                    column->nombrej = newNode->nombrej;
                    return true;
                }
                column = column->right;
            }
            return false;
        }
        rowHeader = rowHeader->down;
    }
    return false;
}

Node* Matrix::insertRowHeader(int i) {
    Node* newRowHeader = new Node(i, -1);
    insertInRow(newRowHeader, root);
    return newRowHeader;
}

Node* Matrix::insertColumnHeader(int j) {
    Node* newColumnHeader = new Node(-1, j);
    insertInColumn(newColumnHeader, root);
    return newColumnHeader;
}

void Matrix::insertInRow(Node* newNode, Node* rowHeader) {
    Node* current = rowHeader;

    while (current->down) {
        if (newNode->i < current->down->i && newNode->i > current->i) {
            newNode->down = current->down;
            newNode->up = current;
            current->down->up = newNode;
            current->down = newNode;
            return;
        }
        current = current->down;
    }

    current->down = newNode;
    newNode->up = current;
}

void Matrix::insertInColumn(Node* newNode, Node* columnHeader) {
    Node* current = columnHeader;

    while (current->right) {
        if (newNode->j < current->right->j && newNode->j > current->j) {
            newNode->right = current->right;
            newNode->left = current;
            current->right->left = newNode;
            current->right = newNode;
            return;
        }
        current = current->right;
    }

    current->right = newNode;
    newNode->left = current;
}

void Matrix::print() const {
    printColumnHeaders();

    for (int i = 0; i <= height; ++i) {
        cout << "\n" << setw(3) << i;
        for (int j = 0; j <= width; ++j) {
            NodeVal val = getValue(i, j);
            if (!val.exists) {
                cout << setw(3) << "X";
            } else {
                cout << setw(3) << val.value;
            }
        }
    }
    cout << endl;
}

void Matrix::printColumnHeaders() const {
    for (int j = -1; j <= width; ++j) {
        cout << setw(3) << j;
    }
}

NodeVal Matrix::getValue(int i, int j) const {
    NodeVal val;
    Node* rowHeader = root;

    while (rowHeader) {
        if (rowHeader->i == i) {
            Node* column = rowHeader;
            while (column) {
                if (column->j == j) {
                    val.value = column->value;
                    val.exists = true;
                    return val;
                }
                column = column->right;
            }
            return val;
        }
        rowHeader = rowHeader->down;
    }
    return val;
}

void Matrix::generateGraphvizImage(const std::string& filename) const {
    std::string dotFilename = "temp.dot";
    std::ofstream file(dotFilename);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo temporal para escribir el gráfico DOT." << std::endl;
        return;
    }

    file << "digraph G {\n";
    file << "    node [shape=record];\n";
    file << "    rankdir=LR;\n";  // Disposición horizontal

    Node* row = root->down;
    while (row) {
        Node* column = row->right;
        while (column) {
            file << "    \"" << column->nombrei << "_" << column->nombrej << "\" [label=\"{" << column->nombrei << "|" << column->nombrej << "|" << (column->value ? "1" : "0") << "}\"];\n";

            if (column->right) {
                file << "    \"" << column->nombrei << "_" << column->nombrej << "\" -> \"" << column->right->nombrei << "_" << column->right->nombrej << "\";\n";
            }
            if (column->down) {
                file << "    \"" << column->nombrei << "_" << column->nombrej << "\" -> \"" << column->down->nombrei << "_" << column->down->nombrej << "\";\n";
            }

            column = column->right;
        }
        row = row->down;
    }

    file << "}\n";
    file.close();

    std::string command = "dot -Tpng " + dotFilename + " -o " + filename;
    int result = system(command.c_str());
    if (result != 0) {
        std::cerr << "Error al generar la imagen PNG con Graphviz." << std::endl;
    }

    std::remove(dotFilename.c_str());
}

void Matrix::generateGraphvizImage2(const std::string& filename) const {
    std::string dotFilename = "temp.dot";
    std::ofstream file(dotFilename);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo temporal para escribir el gráfico DOT." << std::endl;
        return;
    }

    file << "digraph G {\n";
    file << "    node [shape=record];\n";

    // Crear subgrafos para alinear nodos en la misma fila
    for (int i = 0; i <= height; ++i) {
        file << "    { rank=same; ";
        Node* row = root->down;
        while (row) {
            if (row->i == i) {
                Node* column = row->right;
                while (column) {
                    file << "\"" << column->nombrei << "_" << column->nombrej << "\" ";
                    column = column->right;
                }
                break;
            }
            row = row->down;
        }
        file << "}\n";
    }

    // Crear los nodos y conexiones entre ellos
    Node* row = root->down;
    while (row) {
        Node* column = row->right;
        while (column) {
            // Crear nodo
            file << "    \"" << column->nombrei << "_" << column->nombrej << "\" [label=\"{" << column->nombrei << "|" << column->nombrej << "|" << (column->value ? "1" : "0") << "}\"];\n";

            // Conectar a la derecha
            if (column->right) {
                file << "    \"" << column->nombrei << "_" << column->nombrej << "\" -> \"" << column->right->nombrei << "_" << column->right->nombrej << "\" [dir=both];\n";
            }

            // Conectar hacia abajo
            if (column->down) {
                file << "    \"" << column->nombrei << "_" << column->nombrej << "\" -> \"" << column->down->nombrei << "_" << column->down->nombrej << "\" [dir=both];\n";
            }

            column = column->right;
        }
        row = row->down;
    }

    file << "}\n";
    file.close();

    // Generar la imagen PNG
    std::string command = "dot -Tpng " + dotFilename + " -o " + filename;
    int result = system(command.c_str());
    if (result != 0) {
        std::cerr << "Error al generar la imagen PNG con Graphviz." << std::endl;
    }

    std::remove(dotFilename.c_str());
}
