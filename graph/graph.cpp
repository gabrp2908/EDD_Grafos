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
            for (int j = 0; j < nodos[i]->contador_conexiones; j++) {
                if (nodos[i]->conexiones[j]->id == id) {
                    // Eliminar esta conexión
                    for (int k = j; k < nodos[i]->contador_conexiones - 1; k++) {
                        nodos[i]->conexiones[k] = nodos[i]->conexiones[k + 1];
                        nodos[i]->pesos[k] = nodos[i]->pesos[k + 1];
                    }
                    nodos[i]->contador_conexiones--;
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
    for (int i = 0; i < origen->contador_conexiones; i++) {
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
    for (int i = 0; i < origen->contador_conexiones; i++) {
        if (origen->conexiones[i]->id == id_destino) {
            // Eliminar la conexión
            for (int j = i; j < origen->contador_conexiones - 1; j++) {
                origen->conexiones[j] = origen->conexiones[j + 1];
                origen->pesos[j] = origen->pesos[j + 1];
            }
            origen->contador_conexiones--;
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

void Graph::mostrarRed() {
    cout << "\n=== RED DE COMPUTADORAS ===\n";
    for (int i = 0; i < contador_nodos; i++) {
        cout << "[" << nodos[i]->id << "] " << nodos[i]->nombre << " -> ";
        for (int j = 0; j < nodos[i]->contador_conexiones; j++) {
            cout << nodos[i]->conexiones[j]->id << "(" << nodos[i]->pesos[j] << "ms) ";
        }
        cout << endl;
    }
}

void Graph::recorridoDFS(string id_inicio) {
    Nodo* inicio = buscarNodo(id_inicio);
    if (!inicio) return;

    bool* visitados = new bool[contador_nodos]{false};
    int* indices = new int[contador_nodos];
    for (int i = 0; i < contador_nodos; i++) {
        indices[i] = -1;
        if (nodos[i]->id == id_inicio) {
            indices[i] = 0;
        }
    }

    cout << "Recorrido DFS desde " << id_inicio << ": ";
    DFS(inicio, visitados, 1, indices);

    cout << "\nOrden de visita: ";
    for (int i = 0; i < contador_nodos; i++) {
        if (indices[i] != -1) {
            cout << nodos[i]->id << "(" << indices[i] << ") ";
        }
    }
    cout << endl;

    delete[] visitados;
    delete[] indices;
}

void Graph::DFS(Nodo* actual, bool* visitados, int orden, int* indices) {
    cout << actual->id << " ";
    for (int i = 0; i < contador_nodos; i++) {
        if (nodos[i] == actual) {
            visitados[i] = true;
            if (indices[i] == -1) {
                indices[i] = orden;
            }
            break;
        }
    }

    for (int i = 0; i < actual->contador_conexiones; i++) {
        Nodo* vecino = actual->conexiones[i];
        bool visitado = false;
        int idx = -1;
        
        for (int j = 0; j < contador_nodos; j++) {
            if (nodos[j] == vecino) {
                visitado = visitados[j];
                idx = j;
                break;
            }
        }

        if (!visitado && idx != -1) {
            DFS(vecino, visitados, orden + 1, indices);
        }
    }
}

void Graph::rutaMasCorta(string inicio_id, string fin_id) {
    Nodo* inicio = buscarNodo(inicio_id);
    Nodo* fin = buscarNodo(fin_id);
    if (!inicio || !fin) return;

    int* distancias = new int[contador_nodos];
    bool* visitados = new bool[contador_nodos]{false};
    string* anteriores = new string[contador_nodos];

    for (int i = 0; i < contador_nodos; i++) {
        distancias[i] = INT_MAX;
        anteriores[i] = "";
    }

    int idx_inicio = -1;
    for (int i = 0; i < contador_nodos; i++) {
        if (nodos[i] == inicio) {
            idx_inicio = i;
            distancias[i] = 0;
            break;
        }
    }

    for (int count = 0; count < contador_nodos - 1; count++) {
        int u = minDistancia(distancias, visitados);
        if (u == -1) break;

        visitados[u] = true;

        for (int v = 0; v < contador_nodos; v++) {
            if (!visitados[v]) {
                int peso = obtenerPeso(nodos[u], nodos[v]);
                if (peso != -1 && distancias[u] != INT_MAX && distancias[u] + peso < distancias[v]) {
                    distancias[v] = distancias[u] + peso;
                    anteriores[v] = nodos[u]->id;
                }
            }
        }
    }

    cout << "\nRutas mas cortas desde " << inicio_id << ":\n";
    for (int i = 0; i < contador_nodos; i++) {
        cout << "A " << nodos[i]->id << ": ";
        if (distancias[i] == INT_MAX) {
            cout << "No alcanzable";
        } else {
            cout << "Distancia: " << distancias[i] << "ms, Ruta: ";
            mostrarRuta(anteriores, inicio_id, nodos[i]->id);
        }
        cout << endl;
    }

    delete[] distancias;
    delete[] visitados;
    delete[] anteriores;
}

int Graph::minDistancia(int* distancias, bool* visitados) {
    int min = INT_MAX, min_index = -1;

    for (int v = 0; v < contador_nodos; v++) {
        if (!visitados[v] && distancias[v] <= min) {
            min = distancias[v];
            min_index = v;
        }
    }

    return min_index;
}

int Graph::obtenerPeso(Nodo* origen, Nodo* destino) {
    for (int i = 0; i < origen->contador_conexiones; i++) {
        if (origen->conexiones[i] == destino) {
            return origen->pesos[i];
        }
    }
    return -1;
}

void Graph::mostrarRuta(string* anteriores, string inicio_id, string actual_id) {
    if (actual_id == inicio_id) {
        cout << actual_id << " ";
        return;
    }

    int idx = -1;
    for (int i = 0; i < contador_nodos; i++) {
        if (nodos[i]->id == actual_id) {
            idx = i;
            break;
        }
    }

    if (idx == -1 || anteriores[idx] == "") {
        cout << "No hay ruta";
        return;
    }

    mostrarRuta(anteriores, inicio_id, anteriores[idx]);
    cout << actual_id << " ";
}