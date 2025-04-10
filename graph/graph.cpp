#include "graph.h"

Grafo::Grafo() : cont_nodos(0), capacidad(2) {
    nodos = new Nodo*[capacidad];
}

Grafo::~Grafo() {
    for (int i = 0; i < cont_nodos; i++) {
        delete nodos[i];
    }
    delete[] nodos;
}

void Grafo::agregarNodo(string id, string nombre) {
    if (cont_nodos == capacidad) {
        capacidad *= 2;
        Nodo** temp = new Nodo*[capacidad];
        for (int i = 0; i < cont_nodos; i++) {
            temp[i] = nodos[i];
        }
        delete[] nodos;
        nodos = temp;
    }

    nodos[cont_nodos] = new Nodo(id, nombre);
    cont_nodos++;
}

Nodo* Grafo::buscarNodo(string id) {
    for (int i = 0; i < cont_nodos; i++) {
        if (nodos[i]->id == id) {
            return nodos[i];
        }
    }
    return nullptr;
}

void Grafo::agregarConexion(string id_origen, string id_destino, int peso) {
    Nodo* origen = buscarNodo(id_origen);
    Nodo* destino = buscarNodo(id_destino);

    if (origen && destino) {
        origen->agregarConexion(destino, peso);
    }
}

void Grafo::mostrarRed() {
    cout << "\n=== RED DE COMPUTADORAS ===\n";
    for (int i = 0; i < cont_nodos; i++) {
        cout << "[" << nodos[i]->id << "] " << nodos[i]->nombre << " -> ";
        for (int j = 0; j < nodos[i]->contador_conexiones; j++) {
            cout << nodos[i]->conexiones[j]->id << "(" << nodos[i]->pesos[j] << "ms) ";
        }
        cout << endl;
    }
}

void Grafo::recorridoDFS(string id_inicio) {
    Nodo* inicio = buscarNodo(id_inicio);
    if (!inicio) return;

    bool* visitados = new bool[cont_nodos]{false};
    int* indices = new int[cont_nodos];
    for (int i = 0; i < cont_nodos; i++) {
        indices[i] = -1;
        if (nodos[i]->id == id_inicio) {
            indices[i] = 0;
        }
    }

    cout << "Recorrido DFS desde " << id_inicio << ": ";
    DFS(inicio, visitados, 1, indices);

    cout << "\nOrden de visita: ";
    for (int i = 0; i < cont_nodos; i++) {
        if (indices[i] != -1) {
            cout << nodos[i]->id << "(" << indices[i] << ") ";
        }
    }
    cout << endl;

    delete[] visitados;
    delete[] indices;
}

void Grafo::DFS(Nodo* actual, bool* visitados, int orden, int* indices) {
    cout << actual->id << " ";
    for (int i = 0; i < cont_nodos; i++) {
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
        
        for (int j = 0; j < cont_nodos; j++) {
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

void Grafo::rutaMasCorta(string inicio_id, string fin_id) {
    Nodo* inicio = buscarNodo(inicio_id);
    Nodo* fin = buscarNodo(fin_id);
    if (!inicio || !fin) return;

    int* distancias = new int[cont_nodos];
    bool* visitados = new bool[cont_nodos]{false};
    string* anteriores = new string[cont_nodos];

    for (int i = 0; i < cont_nodos; i++) {
        distancias[i] = INT_MAX;
        anteriores[i] = "";
    }

    int idx_inicio = -1;
    for (int i = 0; i < cont_nodos; i++) {
        if (nodos[i] == inicio) {
            idx_inicio = i;
            distancias[i] = 0;
            break;
        }
    }

    for (int count = 0; count < cont_nodos - 1; count++) {
        int u = minDistancia(distancias, visitados);
        if (u == -1) break;

        visitados[u] = true;

        for (int v = 0; v < cont_nodos; v++) {
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
    for (int i = 0; i < cont_nodos; i++) {
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

int Grafo::minDistancia(int* distancias, bool* visitados) {
    int min = INT_MAX, min_index = -1;

    for (int v = 0; v < cont_nodos; v++) {
        if (!visitados[v] && distancias[v] <= min) {
            min = distancias[v];
            min_index = v;
        }
    }

    return min_index;
}

int Grafo::obtenerPeso(Nodo* origen, Nodo* destino) {
    for (int i = 0; i < origen->contador_conexiones; i++) {
        if (origen->conexiones[i] == destino) {
            return origen->pesos[i];
        }
    }
    return -1;
}

void Grafo::mostrarRuta(string* anteriores, string inicio_id, string actual_id) {
    if (actual_id == inicio_id) {
        cout << actual_id << " ";
        return;
    }

    int idx = -1;
    for (int i = 0; i < cont_nodos; i++) {
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


int Grafo::buscarIndiceNodo(string id) {
    for (int i = 0; i < cont_nodos; i++) {
        if (nodos[i]->id == id) {
            return i;
        }
    }
    return -1;
}

void Grafo::modificarNodo(string id, string nuevo_nombre) {
    Nodo* nodo = buscarNodo(id);
    if (nodo) {
        nodo->nombre = nuevo_nombre;
        cout << "Nodo " << id << " modificado correctamente.\n";
    } else {
        cout << "Error: Nodo " << id << " no encontrado.\n";
    }
}

void Grafo::eliminarNodo(string id) {
    int indice = buscarIndiceNodo(id);
    if (indice == -1) {
        cout << "Error: Nodo " << id << " no encontrado.\n";
        return;
    }

    // Eliminar todas las conexiones que apuntan a este nodo
    for (int i = 0; i < cont_nodos; i++) {
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
    for (int i = indice; i < cont_nodos - 1; i++) {
        nodos[i] = nodos[i + 1];
    }
    
    cont_nodos--;
    cout << "Nodo " << id << " eliminado correctamente.\n";
}

void Grafo::modificarConexion(string id_origen, string id_destino, int nuevo_peso) {
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

void Grafo::eliminarConexion(string id_origen, string id_destino) {
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