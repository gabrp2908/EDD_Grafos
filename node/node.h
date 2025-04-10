#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

class Nodo {
public:
    string id;
    string nombre;
    Nodo** conexiones;
    int* pesos;
    int cont_conexiones;
    int capacidad;
    
    Nodo(string id, string nombre);
    ~Nodo();
    void agregarConexion(Nodo* nodo, int peso);
};

#endif