#include "graph.h"

Graph::Graph() : contador_nodos(0), capacidad(2) {
    nodos = new Nodo*[capacidad];
}

Graph::~Graph() {
    for (int i = 0; i < contador_nodos; i++) {
        delete nodos[i];
    }
    delete[] nodos;
}

void Graph::agregarNodo(string id, string nombre) {
    if (contador_nodos == capacidad) {
        capacidad *= 2;
        Nodo** temp = new Nodo*[capacidad];
        for (int i = 0; i < contador_nodos; i++) {
            temp[i] = nodos[i];
        }
        delete[] nodos;
        nodos = temp;
    }

    nodos[contador_nodos] = new Nodo(id, nombre);
    contador_nodos++;
}

Nodo* Graph::buscarNodo(string id) {
    for (int i = 0; i < contador_nodos; i++) {
        if (nodos[i]->id == id) {
            return nodos[i];
        }
    }
    return nullptr;
}

void Graph::modificarNodo(string id, string nuevo_nombre) {
    Nodo* nodo = buscarNodo(id);
    if (nodo) {
        nodo->nombre = nuevo_nombre;
        cout << "Nodo " << id << " modificado correctamente.\n";
    } else {
        cout << "Error: Nodo " << id << " no encontrado.\n";
    }
}

int Graph::buscarIndiceNodo(string id) {
    for (int i = 0; i < contador_nodos; i++) {
        if (nodos[i]->id == id) {
            return i;
        }
    }
    return -1;
}

void Graph::eliminarNodo(string id) {
    int indice = buscarIndiceNodo(id);
    if (indice == -1) {
        cout << "Error: Nodo " << id << " no encontrado.\n";
        return;
    }

    // Eliminar todas las conexiones que apuntan a este nodo
    for (int i = 0; i < contador_nodos; i++) {
        if (nodos[i]->id != id) {
            for (int j = 0; j < nodos[i]->cont_conexiones; j++) {
                if (nodos[i]->conexiones[j]->id == id) {
                    // Eliminar esta conexión
                    for (int k = j; k < nodos[i]->cont_conexiones - 1; k++) {
                        nodos[i]->conexiones[k] = nodos[i]->conexiones[k + 1];
                        nodos[i]->pesos[k] = nodos[i]->pesos[k + 1];
                    }
                    nodos[i]->cont_conexiones--;
                    j--; // Revisar la misma posición nuevamente
                }
            }
        }
    }

    // Eliminar el nodo
    delete nodos[indice];
    
    // Mover los nodos restantes
    for (int i = indice; i < contador_nodos - 1; i++) {
        nodos[i] = nodos[i + 1];
    }
    
    contador_nodos--;
    cout << "Nodo " << id << " eliminado correctamente.\n";
}

void Graph::agregarConexion(string id_origen, string id_destino, int peso) {
    Nodo* origen = buscarNodo(id_origen);
    Nodo* destino = buscarNodo(id_destino);

    if (origen && destino) {
        origen->agregarConexion(destino, peso);
    }
}

void Graph::modificarConexion(string id_origen, string id_destino, int nuevo_peso) {
    Nodo* origen = buscarNodo(id_origen);
    Nodo* destino = buscarNodo(id_destino);

    if (!origen || !destino) {
        cout << "Error: Nodo origen o destino no encontrado.\n";
        return;
    }

    bool conexion_encontrada = false;
    for (int i = 0; i < origen->cont_conexiones; i++) {
        if (origen->conexiones[i]->id == id_destino) {
            origen->pesos[i] = nuevo_peso;
            conexion_encontrada = true;
            break;
        }
    }

    if (conexion_encontrada) {
        cout << "Conexion " << id_origen << " -> " << id_destino 
            << " modificada a " << nuevo_peso << "ms.\n";
    } else {
        cout << "Error: Conexion no encontrada.\n";
    }
}

void Graph::eliminarConexion(string id_origen, string id_destino) {
    Nodo* origen = buscarNodo(id_origen);
    if (!origen) {
        cout << "Error: Nodo origen no encontrado.\n";
        return;
    }

    bool conexion_encontrada = false;
    for (int i = 0; i < origen->cont_conexiones; i++) {
        if (origen->conexiones[i]->id == id_destino) {
            // Eliminar la conexión
            for (int j = i; j < origen->cont_conexiones - 1; j++) {
                origen->conexiones[j] = origen->conexiones[j + 1];
                origen->pesos[j] = origen->pesos[j + 1];
            }
            origen->cont_conexiones--;
            conexion_encontrada = true;
            break;
        }
    }

    if (conexion_encontrada) {
        cout << "Conexion " << id_origen << " -> " << id_destino << " eliminada.\n";
    } else {
        cout << "Error: Conexion no encontrada.\n";
    }
}