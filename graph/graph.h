#ifndef GRAPH_H
#define GRAPH_H

#include "..\node\node.cpp"
#include <iostream>
using namespace std;

class Graph{
    private:
        Nodo **nodos;
        int contador_nodos;
        int capacidad;
        int buscarIndiceNodo(string id);

    public:
        Graph();
        ~Graph();
        void agregarNodo(string id, string nombre);
        Nodo *buscarNodo(string id);
        void modificarNodo(string id, string nuevo_nombre);
        void eliminarNodo(string id);
};

#endif