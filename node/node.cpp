#include "node.h"

Nodo::Nodo(string id, string nombre) : id(id), nombre(nombre), contador_conexiones(0), capacidad(2) {
    conexiones = new Nodo*[capacidad];
    pesos = new int[capacidad];
}

Nodo::~Nodo() {
    delete[] conexiones;
    delete[] pesos;
}

void Nodo::agregarConexion(Nodo* nodo, int peso) {
    if (contador_conexiones == capacidad) {
        capacidad *= 2;
        Nodo** temp_conexiones = new Nodo*[capacidad];
        int* temp_pesos = new int[capacidad];

        for (int i = 0; i < contador_conexiones; i++) {
            temp_conexiones[i] = conexiones[i];
            temp_pesos[i] = pesos[i];
        }

        delete[] conexiones;
        delete[] pesos;

        conexiones = temp_conexiones;
        pesos = temp_pesos;
    }

    conexiones[contador_conexiones] = nodo;
    pesos[contador_conexiones] = peso;
    contador_conexiones++;
}