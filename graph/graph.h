#ifndef GRAPH_H
#define GRAPH_H

#include "..\node\node.cpp"
#include <iostream>
using namespace std;

class Grafo {
private:
    Nodo** nodos;
    int cont_nodos;
    int capacidad;

    void DFS(Nodo* actual, bool* visitados, int orden, int* indices);
    int minDistancia(int* distancias, bool* visitados);
    int obtenerPeso(Nodo* origen, Nodo* destino);
    void mostrarRuta(string* anteriores, string inicio_id, string actual_id);
    int buscarIndiceNodo(string id);

public:
    Grafo();
    ~Grafo();
    void agregarNodo(string id, string nombre);
    Nodo* buscarNodo(string id);
    void agregarConexion(string id_origen, string id_destino, int peso);
    void modificarNodo(string id, string nuevo_nombre);
    void eliminarNodo(string id);
    void modificarConexion(string id_origen, string id_destino, int nuevo_peso);
    void eliminarConexion(string id_origen, string id_destino);
    void mostrarRed();
    void recorridoDFS(string id_inicio);
    void rutaMasCorta(string inicio_id, string fin_id);
};

#endif