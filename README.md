# README - Sistema de Red de Computadoras con Grafos

## ¿Qué es un Grafo?

Un grafo es una estructura de datos no lineal que consiste en un conjunto de **vértices (nodos)** conectados por **aristas (arcos)**. Los grafos son herramientas fundamentales en ciencias de la computación y matemáticas discretas para representar relaciones complejas.

## Componentes Básicos

- **Vértices/Nodos**: Elementos fundamentales del grafo (p. ej.: ciudades en un mapa, usuarios en una red social).
- **Aristas/Arcos**: Conexiones entre vértices que pueden ser:
  - **Dirigidas** (con dirección, como en grafos dirigidos)
  - **No dirigidas** (sin dirección, conexión mutua)
- **Peso**: Valor opcional asignado a las aristas (p. ej.: distancia, costo).

## Usos Comunes

- Sistemas de navegación (GPS)
- Redes sociales (relaciones entre usuarios)
- Internet y redes de computadoras
- Diseño de circuitos electrónicos
- Bases de datos y sistemas de recomendación
- Biología (redes de proteínas, cadenas alimenticias)
- Sistemas de transporte y logística

## Funcionamiento Básico

### Representaciones comunes:

1. **Matriz de adyacencia**: Matriz cuadrada donde `1` indica conexión y `0` ausencia.
2. **Lista de adyacencia**: Lista donde cada nodo apunta a sus vecinos.

### Operaciones básicas:

- **Inserción/eliminación** de vértices y aristas
- **Búsqueda** de caminos entre nodos
- **Recorridos** (DFS - Depth First Search, BFS - Breadth First Search)
- **Detección de ciclos**
- **Cálculo del camino más corto** (algoritmos como Dijkstra)
# README - Sistema de Red de Computadoras con Grafos

## Descripción del aplicacion del grafo 
Este proyecto implementa una red de computadoras modelada como un grafo, donde los nodos representan dispositivos (routers, servidores, computadoras) y las aristas representan conexiones entre ellos con sus respectivos tiempos de latencia.

## Características principales 
- **Estructura de grafo** con nodos y conexiones ponderadas
- **Operaciones CRUD** para nodos y conexiones
- **Algoritmo DFS** para recorrido en profundidad
- **Algoritmo de Dijkstra** para encontrar rutas más cortas
- **Gestión dinámica de memoria** con arreglos redimensionables

## Estructura del proyecto 
```
red-computadoras-grafo/
│
├── graph/
│   ├── graph.h       # Declaración de la clase Grafo
│   └── graph.cpp     # Implementación de la clase Grafo
│
├── node/
│   └── node.cpp      # Implementación de la clase Nodo
│
├── main.cpp          # Programa principal con casos de prueba
└── README.md         # Este archivo
```

## Compilación y ejecución 
```bash
g++ -o red_computadoras main.cpp graph/graph.cpp node/node.cpp
./red_computadoras
```

## Uso del programa 💻
El programa demuestra automáticamente las siguientes operaciones:

1. Creación de una red con:
   - 1 router principal
   - 2 servidores
   - 3 computadoras

2. Operaciones demostrativas:
   - Modificación de nodos y conexiones
   - Eliminación de nodos y conexiones
   - Recorrido DFS desde un nodo
   - Cálculo de rutas más cortas

## Documentación de clases 

### Clase `Grafo`
- **Métodos públicos**:
  - `agregarNodo(id, nombre)`: Añade un nuevo dispositivo
  - `buscarNodo(id)`: Busca un nodo por su ID
  - `agregarConexion(origen, destino, peso)`: Establece una conexión
  - `mostrarRed()`: Muestra toda la red
  - `recorridoDFS(id_inicio)`: Realiza recorrido en profundidad
  - `rutaMasCorta(inicio, fin)`: Calcula la ruta más corta

### Clase `Nodo`
- Almacena:
  - ID del dispositivo
  - Nombre descriptivo
  - Lista de conexiones salientes
  - Pesos de las conexiones

### Contribución
Este proyecto fue desarrollado por Gabriela Rey, Erick Diaz y Luis ALvarez siguiendo las normas de:

Estructura de carpetas especificada
Convención de commits
Explicacion y desarrollo del programa
