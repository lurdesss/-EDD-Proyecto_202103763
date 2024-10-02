// #include "redsocial.h"
// #include <fstream>
// #include <iostream>
// #include <json.hpp>

// using json = nlohmann::json;
// using namespace std;

// // Implementación del constructor
// RedSocial::RedSocial(UserList* listaUsuarios) : listaUsuarios(listaUsuarios) {}

// // Implementación del método para cargar solicitudes desde un archivo JSON
// void RedSocial::cargarSolicitudesDesdeJSON(const std::string& filePath) {
//     std::ifstream archivo(filePath);
//     if (!archivo.is_open()) {
//         cerr << "No se pudo abrir el archivo " << filePath << endl;
//         return;
//     }

//     json solicitudesJSON;
//     archivo >> solicitudesJSON;

//     for (const auto& solicitud : solicitudesJSON) {
//         string emisor = solicitud["emisor"];
//         string receptor = solicitud["receptor"];
//         string estado = solicitud["estado"];

//         // Verificar que ambos correos estén registrados
//         if (!listaUsuarios->emailExists(emisor) || !listaUsuarios->emailExists(receptor)) {
//             cout << "Uno o ambos correos electrónicos no están registrados." << endl;
//             continue;
//         }

//         // Verificar si ya existe una solicitud aceptada entre emisor y receptor o viceversa
//         bool existeAceptada = listaSolicitudesEnviadas.existeSolicitudAceptada(emisor, receptor) ||
//                               listaSolicitudesEnviadas.existeSolicitudAceptada(receptor, emisor);

//         // Verificar si ya existe una solicitud pendiente del emisor al receptor o viceversa
//         bool existePendiente = listaSolicitudesEnviadas.existeSolicitudPendiente(emisor, receptor) ||
//                                listaSolicitudesEnviadas.existeSolicitudPendiente(receptor, emisor);
//         if (estado == "PENDIENTE") {
//             if (existeAceptada) {
//                 // Si ya hay una solicitud aceptada, se elimina cualquier solicitud pendiente existente
//                 listaSolicitudesEnviadas.eliminarSolicitud(emisor, receptor, "PENDIENTE");
//                 listaSolicitudesEnviadas.eliminarSolicitud(receptor, emisor, "PENDIENTE");
//             } else if (!existePendiente) {
//                 // Si no hay una solicitud pendiente, se agrega la solicitud pendiente
//                 listaSolicitudesEnviadas.agregarSolicitud(emisor, receptor, estado);
//                 cout << "La solicitud de " << emisor << " a " << receptor << " ha sido añadida en estado: PENDIENTE" << endl;
//             }
//         } else if (estado == "ACEPTADA") {
//             if (existePendiente) {
//                 // Si existe una solicitud pendiente, se elimina y se cambia el estado a "ACEPTADA"
//                 listaSolicitudesEnviadas.eliminarSolicitud(emisor, receptor, "PENDIENTE");
//                 listaSolicitudesEnviadas.eliminarSolicitud(receptor, emisor, "PENDIENTE");
//             }
//             if (!existeAceptada) {
//                 // Inserta en la matriz de amigos y agrega la solicitud aceptada
//                 cout << "La solicitud de " << emisor << " a " << receptor << " ha sido añadida con estado: ACEPTADA" << endl;
//                 bool valor = true;
//                 int emisorId = listaUsuarios->getId(emisor);
//                 int receptorId = listaUsuarios->getId(receptor);
//                 matrizAmigos.insert(emisorId, receptorId, valor, emisor, receptor);
//                 matrizAmigos.insert(receptorId, emisorId, valor, receptor, emisor);
//             }
//         }
//     }
// }

