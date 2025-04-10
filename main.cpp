#include ".\graph\graph.cpp"

void demostrarOperaciones(Grafo& red) {
    // Mostrar red original
    cout << "\n=== RED INICIAL ===";
    red.mostrarRed();

    // Modificar un nodo
    red.modificarNodo("S1", "Servidor Web Actualizado");
    
    // Modificar una conexión
    red.modificarConexion("R1", "S1", 2);
    
    // Mostrar red después de modificaciones
    cout << "\n=== DESPUES DE MODIFICACIONES ===";
    red.mostrarRed();
    
    // Eliminar una conexión
    red.eliminarConexion("S1", "PC2");
    
    // Eliminar un nodo
    red.eliminarNodo("PC3");
    
    // Mostrar red final
    cout << "\n=== RED FINAL ===";
    red.mostrarRed();
    
    // Mostrar recorrido DFS y rutas después de los cambios
    cout << "\n=== RECORRIDOS Y RUTAS ACTUALIZADOS ===";
    red.recorridoDFS("R1");
    red.rutaMasCorta("R1", "PC2");
}

int main() {
    Grafo red;

    // Crear nodos de la red
    red.agregarNodo("R1", "Router Principal");
    red.agregarNodo("S1", "Servidor Web");
    red.agregarNodo("S2", "Servidor BD");
    red.agregarNodo("PC1", "Computadora 1");
    red.agregarNodo("PC2", "Computadora 2");
    red.agregarNodo("PC3", "Computadora 3");

    // Establecer conexiones
    red.agregarConexion("R1", "S1", 5);
    red.agregarConexion("R1", "S2", 3);
    red.agregarConexion("R1", "PC1", 2);
    red.agregarConexion("S1", "S2", 4);
    red.agregarConexion("S1", "PC2", 6);
    red.agregarConexion("S2", "PC3", 1);
    red.agregarConexion("PC1", "PC2", 3);
    red.agregarConexion("PC2", "PC3", 2);

    // Demostrar operaciones de modificación y eliminación
    demostrarOperaciones(red);

    return 0;
}