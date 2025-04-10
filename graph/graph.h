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
        void agregarConexion(string id_origen, string id_destino, int peso);
        void modificarConexion(string id_origen, string id_destino, int nuevo_peso);
        void eliminarConexion(string id_origen, string id_destino);
};

#endif