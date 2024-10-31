#include "avltree.h"
#include <QTableWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>


// Definición del constructor de AVLTree
AVLTree::AVLTree() : raiz(nullptr) {}

// Método para agregar un usuario al árbol
void AVLTree::add(Usuario* user) {
    if (raiz != nullptr) add(user, raiz);
    else raiz = new Node(user);
}

// Método privado para agregar un usuario de forma recursiva
void AVLTree::add(Usuario* user, Node*& tmp) {
    if (tmp == nullptr) {
        tmp = new Node(user);
    } else if (user->correo < tmp->user->correo) {
        add(user, tmp->izq);
        // Balanceo
        if ((altura(tmp->izq) - altura(tmp->der)) == 2) {
            if (user->correo < tmp->izq->user->correo) tmp = srl(tmp);
            else tmp = drl(tmp);
        }
    } else if (user->correo > tmp->user->correo) {
        add(user, tmp->der);
        // Balanceo
        if ((altura(tmp->der) - altura(tmp->izq)) == 2) {
            if (user->correo > tmp->der->user->correo) tmp = srr(tmp);
            else tmp = drr(tmp);
        }
    }
    int d = altura(tmp->der);
    int i = altura(tmp->izq);
    int m = maxi(d, i);
    tmp->alt = m + 1;
}

// Método para obtener la altura de un nodo
int AVLTree::altura(Node* tmp) {
    if (tmp == nullptr) return -1;
    else return tmp->alt;
}

// Recorrido preorden
void AVLTree::preorden(Node* tmp) {
    if (tmp != nullptr) {
        std::cout << tmp->user->correo.toStdString() << " ";
        preorden(tmp->izq);
        preorden(tmp->der);
    }
}

// Recorrido enorden
void AVLTree::enorden(Node* tmp) {
    if (tmp != nullptr) {
        enorden(tmp->izq);
        std::cout << tmp->user->correo.toStdString() << " ";
        enorden(tmp->der);
    }
}

// Recorrido postorden
void AVLTree::postorden(Node* tmp) {
    if (tmp != nullptr) {
        postorden(tmp->izq);
        postorden(tmp->der);
        std::cout << tmp->user->correo.toStdString() << " ";
    }
}

Usuario* AVLTree::preordenLogin(Node* tmp, QString& correo, QString& contra) {
    if (tmp != nullptr) {
        if (correo == tmp->user->correo && contra == tmp->user->contrasena) {
            return tmp->user;  // Se encontró el usuario, retornarlo
        }

        // Busca en el subárbol izquierdo
        Usuario* usuarioIzq = preordenLogin(tmp->izq, correo, contra);
        if (usuarioIzq != nullptr) {
            return usuarioIzq;  // Si se encuentra en el subárbol izquierdo, retornarlo
        }

        // Busca en el subárbol derecho
        Usuario* usuarioDer = preordenLogin(tmp->der, correo, contra);
        if (usuarioDer != nullptr) {
            return usuarioDer;  // Si se encuentra en el subárbol derecho, retornarlo
        }
    }
    return nullptr;  // Si no se encuentra el usuario, retorna nullptr
}

Usuario* AVLTree::preordenBuscarCorreo(Node* tmp, const QString& correo) {
    if (tmp != nullptr) {
        if (correo == tmp->user->correo) {
            return tmp->user;  // Se encontró el usuario, retornarlo
        }

        // Busca en el subárbol izquierdo
        Usuario* usuarioIzq = preordenBuscarCorreo(tmp->izq, correo);
        if (usuarioIzq != nullptr) {
            return usuarioIzq;  // Si se encuentra en el subárbol izquierdo, retornarlo
        }

        // Busca en el subárbol derecho
        Usuario* usuarioDer = preordenBuscarCorreo(tmp->der, correo);
        if (usuarioDer != nullptr) {
            return usuarioDer;  // Si se encuentra en el subárbol derecho, retornarlo
        }
    }
    return nullptr;  // Si no se encuentra el usuario, retorna nullptr
}


Node* AVLTree::preordenBuscarCorreoNodo(Node* tmp, const QString& correo) {
    if (tmp != nullptr) {
        if (correo == tmp->user->correo) {
            return tmp;  // Se encontró el usuario, retornarlo
        }

        // Busca en el subárbol izquierdo
        Node* usuarioIzq = preordenBuscarCorreoNodo(tmp->izq, correo);
        if (usuarioIzq != nullptr) {
            return usuarioIzq;  // Si se encuentra en el subárbol izquierdo, retornarlo
        }

        // Busca en el subárbol derecho
        Node* usuarioDer = preordenBuscarCorreoNodo(tmp->der, correo);
        if (usuarioDer != nullptr) {
            return usuarioDer;  // Si se encuentra en el subárbol derecho, retornarlo
        }
    }
    return nullptr;  // Si no se encuentra el usuario, retorna nullptr
}

void AVLTree::preordenCase(Node* tmp, QTableWidget* tableWidget, int& localIndex) {
    if (tmp != nullptr) {
        // Añadir una nueva fila a la tabla
        tableWidget->insertRow(localIndex);

        // Suponiendo que tu clase Usuario tiene estos métodos
        tableWidget->setItem(localIndex, 0, new QTableWidgetItem(tmp->user->nombres)); // Sin fromStdString
        tableWidget->setItem(localIndex, 1, new QTableWidgetItem(tmp->user->apellidos));
        tableWidget->setItem(localIndex, 2, new QTableWidgetItem(tmp->user->fechaNacimiento));
        tableWidget->setItem(localIndex, 3, new QTableWidgetItem(tmp->user->correo));
        // añade boton "Modificar"
        // añade un boton "Eliminar"
        // Incrementar el índice local
        localIndex++;
        // Recorrer el subárbol izquierdo y derecho
        preordenCase(tmp->izq, tableWidget, localIndex);
        preordenCase(tmp->der, tableWidget, localIndex);
    }
}


void AVLTree::postordenCase(Node* tmp, QTableWidget* tableWidget, int& localIndex) {
    if (tmp != nullptr) {

        // Recorrer el subárbol izquierdo y derecho
        postordenCase(tmp->izq, tableWidget, localIndex);
        postordenCase(tmp->der, tableWidget, localIndex);
        // Añadir una nueva fila a la tabla
        tableWidget->insertRow(localIndex);

        // Suponiendo que tu clase Usuario tiene estos métodos
        tableWidget->setItem(localIndex, 0, new QTableWidgetItem(tmp->user->nombres)); // Sin fromStdString
        tableWidget->setItem(localIndex, 1, new QTableWidgetItem(tmp->user->apellidos));
        tableWidget->setItem(localIndex, 2, new QTableWidgetItem(tmp->user->fechaNacimiento));
        tableWidget->setItem(localIndex, 3, new QTableWidgetItem(tmp->user->correo));
        // añade boton "Modificar"
        // añade un boton "Eliminar"
        // Incrementar el índice local
        localIndex++;
    }
}


void AVLTree::inordenCase(Node* tmp, QTableWidget* tableWidget, int& localIndex) {
    if (tmp != nullptr) {

        // Recorrer el subárbol izquierdo y derecho
        inordenCase(tmp->izq, tableWidget, localIndex);
        // Añadir una nueva fila a la tabla
        tableWidget->insertRow(localIndex);

        // Suponiendo que tu clase Usuario tiene estos métodos
        tableWidget->setItem(localIndex, 0, new QTableWidgetItem(tmp->user->nombres)); // Sin fromStdString
        tableWidget->setItem(localIndex, 1, new QTableWidgetItem(tmp->user->apellidos));
        tableWidget->setItem(localIndex, 2, new QTableWidgetItem(tmp->user->fechaNacimiento));
        tableWidget->setItem(localIndex, 3, new QTableWidgetItem(tmp->user->correo));
        // añade boton "Modificar"
        // añade un boton "Eliminar"
        // Incrementar el índice local
        localIndex++;

        inordenCase(tmp->der, tableWidget, localIndex);
    }
}


// Rotación simple a la izquierda
Node* AVLTree::srl(Node* t1) {
    Node* t2 = t1->izq;
    t1->izq = t2->der;
    t2->der = t1;
    t1->alt = maxi(altura(t1->izq), altura(t1->der)) + 1;
    t2->alt = maxi(altura(t2->izq), t1->alt) + 1;
    return t2;
}

// Rotación simple a la derecha
Node* AVLTree::srr(Node* t1) {
    Node* t2 = t1->der;
    t1->der = t2->izq;
    t2->izq = t1;
    t1->alt = maxi(altura(t1->izq), altura(t1->der)) + 1;
    t2->alt = maxi(altura(t2->der), t1->alt) + 1;
    return t2;
}

// Rotación doble a la izquierda
Node* AVLTree::drl(Node* tmp) {
    tmp->izq = srr(tmp->izq);
    return srl(tmp);
}

// Rotación doble a la derecha
Node* AVLTree::drr(Node* tmp) {
    tmp->der = srl(tmp->der);
    return srr(tmp);
}

// Método para obtener el máximo entre dos valores
int AVLTree::maxi(int val1, int val2) {
    return ((val1 > val2) ? val1 : val2);
}

// Método para graficar el árbol en formato DOT
void AVLTree::toDot(Node* tmp, std::ofstream& file) {
    if (tmp != nullptr) {
        // Escapamos el correo
        std::string correoEscapado = tmp->user->correo.toStdString();
        file << "    \"" << correoEscapado << "\" [label=\"" << correoEscapado << "\"];\n";
        if (tmp->izq != nullptr) {
            file << "    \"" << correoEscapado << "\" -> \"" << tmp->izq->user->correo.toStdString() << "\";\n";
            toDot(tmp->izq, file);
        }
        if (tmp->der != nullptr) {
            file << "    \"" << correoEscapado << "\" -> \"" << tmp->der->user->correo.toStdString() << "\";\n";
            toDot(tmp->der, file);
        }
    }
}


// Método para crear el archivo DOT
void AVLTree::generateDot(const std::string& filename) {
    // Modifica aquí la ruta al archivo
    std::string rutaArchivo = "../../salida/" + filename;
    std::ofstream file(rutaArchivo);

    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo: " << rutaArchivo << std::endl;
        return; // Termina el método si hay un error
    }

    file << "digraph AVLTree {\n";
    toDot(raiz, file);
    file << "}\n";
    file.close();
}


// Método público para buscar un usuario por correo
Usuario* AVLTree::buscarPorCorreo(const QString& correo) {
    return buscarPorCorreo(raiz, correo);
}

// Método privado recursivo para buscar un usuario por correo
Usuario* AVLTree::buscarPorCorreo(Node* tmp, const QString& correo) {
    if (tmp == nullptr) {
        return nullptr;  // No se encontró el usuario
    }
    if (correo < tmp->user->correo) {
        // Buscar en el subárbol izquierdo
        return buscarPorCorreo(tmp->izq, correo);
    } else if (correo > tmp->user->correo) {
        // Buscar en el subárbol derecho
        return buscarPorCorreo(tmp->der, correo);
    } else {
        // Se encontró el usuario
        return tmp->user;
    }
}


#include <QString> // Asegúrate de incluir este encabezado para QString

Usuario* AVLTree::preordenBuscarNombres(Node* tmp, const QString& nombres) {
    if (tmp != nullptr) {
        // Convierte QString a std::string
        // std::string nombres = nombres.toStdString();
        
        // Compara el nombre proporcionado con el nombre del usuario en el nodo actual
        if (nombres == tmp->user->nombres) {
            return tmp->user;  // Se encontró el usuario, retornarlo
        }

        // Busca en el subárbol izquierdo
        Usuario* usuarioIzq = preordenBuscarNombres(tmp->izq, nombres);
        if (usuarioIzq != nullptr) {
            return usuarioIzq;  // Si se encuentra en el subárbol izquierdo, retornarlo
        }

        // Busca en el subárbol derecho
        Usuario* usuarioDer = preordenBuscarNombres(tmp->der, nombres);
        if (usuarioDer != nullptr) {
            return usuarioDer;  // Si se encuentra en el subárbol derecho, retornarlo
        }
    }
    return nullptr;  // Si no se encuentra el usuario, retorna nullptr
}



void AVLTree::preordenCaseToJson(Node* tmp, QJsonArray& usuariosArray) {
    if (tmp != nullptr) {
        // Crear un objeto JSON para el usuario actual
        QJsonObject usuarioObject;
        usuarioObject["nombres"] = tmp->user->nombres;
        usuarioObject["apellidos"] = tmp->user->apellidos;
        usuarioObject["fecha_de_nacimiento"] = tmp->user->fechaNacimiento;
        usuarioObject["correo"] = tmp->user->correo;
        usuarioObject["contraseña"] = tmp->user->contrasena;

        // Añadir el usuario al array de usuarios
        usuariosArray.append(usuarioObject);

        // Recorrer el subárbol izquierdo y derecho
        preordenCaseToJson(tmp->izq, usuariosArray);
        preordenCaseToJson(tmp->der, usuariosArray);
    }
}