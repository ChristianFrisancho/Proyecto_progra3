[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/tKGF1GRg)

# Programación III: Proyecto Final

## Integrantes

- Christian Frisancho
- Diego Quispe
- Juan Aquino


## PathFinder in C++

PathFinder es un programa en C++ que diseña laberintos y mapas con obstaculos. Asimismo, utiliza diferentes algoritmos para encontrar el camino desde un entry a un exit point determinado por el usuario.

## Getting Started

### Prerrequisitos

Para el uso de librerias incluidas en el proyecto, se requiere:

- **Version** C++ 17
  **Procesador:** Se recomienda un procesador de al menos 2 GHz.
- **Memoria RAM:** Se recomienda al menos 4 GB de RAM.
- **Almacenamiento:** Espacio disponible en disco suficiente para compilar y almacenar el programa.

### Crear laberintos y encontrar el camino

En el siguiente ejemplo, se llama a ChooseSize para que el usuario seleccione las dimensiones del laberinto, con estas dimensiones, en Maze laberinto(rows,cols) se crea el laberinto.generateMaze(). 
En GetInicio(laberinto) y GetFin(laberinto) se pide al usuario los puntos de entrada y salida del laberinto, estos puntos no deben ser una pared. Luego estas coordenadas son convertidas a indices unicos. 
En *AbstractFactory factory = new ConcreteFactory* se crea una fabrica de algoritmos y luego se crea instancias de cada uno. Luego, se crean Adapter para los graficos para cada algoritmo. Por ultimo, se libera la memoria dinamica.
```
    int rows, cols;
    ChooseSize(rows,cols);

    Maze laberinto(rows,cols);
    laberinto.generateMaze();

    pair<int, int> inicio = GetInicio(laberinto);
    pair<int, int> final = GetFin(laberinto);

    int startPoint = inicio.first*cols + inicio.second;
    int endPoint = final.first*cols + final.second;
    AbstractFactory* factory = new ConcreteFactory;

    AbstractDFS* algoritmo1 = factory->crearGrafoDFS(laberinto.getMazeInt());
    AbstractBFS* algoritmo2 = factory->crearGrafoBFS(laberinto.getMazeChar());
    AbstractDijsktra* algoritmo3 = factory->crearGrafoDijsktra(laberinto.getMazeChar());

    AdapterGraficaDFS grafica1(algoritmo1);
    AdapterGraficaBFS grafica2(algoritmo2);
    AdapterGraficaDijkstra grafica3(algoritmo3);
    //grafica1.graficar(startPoint, endPoint, laberinto);
    //grafica2.graficar(startPoint, endPoint, laberinto);
    grafica3.graficar(startPoint, endPoint, laberinto);
    delete algoritmo1;
    delete algoritmo2;
    delete algoritmo3;
```

### Crear mapa con obstaculos y encontrar el camino

Para crear un mapa con obtaculos, se agrega la funcion *laberinto.introducirHuecosAleatorios*, la cual elimina paredes en el laberinto a eleccion del usuario, donde n es un parametro que representa un numero entre 0 y 1 que elimina un porcentaje de las paredes del laberinto.
```
...
Maze laberinto(rows,cols);
laberinto.generateMaze();

laberinto.introducirHuecosAleatorios(rows*cols*n);

...
```

### Compilacion y Ejecucion
```bash
    g++ -o main main.cpp
    ./main
```

## Algoritmos implementados

- **Recursive Backtracking**
 Este algoritmo se utilizo para la generacion del laberinto. Para ello, primero se genero todas las celdas de nuestra matriz como "1", lo cual representa las paredes, luego se colocó un punto de "inicio" aleatorio en el laberinto. Despues de esto, se uso la funcion "generatePath" para marcar las celdas de 0, en esta funcion se definio las direcciones en las que se puede mover el algoritmo, en este caso arriba, abajo, derecha e izquierda. Estas fueron elegidas aleatoriamiente para explorar caminos en un orden aleatorio. De esta manera, se coloco un 0 en las celdas que se visitaron y se dejo a los lados las paredes que son 1 . Se hizo esto consecutivamente hasta que todas las celdas sean visitadas recursivamente, logrando generar el laberinto, luego de esto se creo una función "introducirHuecosAleatorios", para que hayan menos paredes en el laberinto, ya que esto permite una mayor cantidad de posibles caminos, por lo que, los algoritmos utilizados puedan determinar el camino mas corto.

Para implementar los algoritmos que solucionan el laberinto, se utilizó la matriz de valores generada para representar el laberinto.

- **Djiktra**
En el desarrollo del algoritmo de Djikstra, cada valor en la matriz se consideró como un nodo, y se construyeron aristas del grafo al analizar los nodos adyacentes vertical y horizontalmente. Esta información se almacenó en una lista de adyacencia, donde cada nodo estaba asociado con sus nodos adyacentes y el peso de las aristas entre ellos. Luego, al aplicar el algoritmo, se comenzó desde un punto de entrada (entry point), y se exploraron los nodos vecinos en un orden determinado por una priority queue. Esta cola de prioridad ordenó los nodos por visitar de manera que el nodo con el peso menor representaba el próximo nodo más cercano a analizar. En cada iteración, cuando se encontró un camino más corto hacia un nodo en comparación con los caminos anteriores, se registró esta nueva distancia y se almacenó el nodo padre desde el cual se originaba el camino más corto. Esta información permitió, posteriormente, determinar el camino más corto desde el entry point hasta cualquier otro nodo en el grafo.
- **BFS**
En el desarrollo del algoritmo BFS, similar al algortimo de Djikstra, cada valor se considero un nodo. Sin embargo, en la lista de adyacencia, solo se almacenó la información del nodo y sus nodos adyacentes en direcciones vertical y horizontal, sin tener en cuenta los pesos de las aristas. Al ejecutar el algoritmo, se inició desde un punto de entrada (entry point) y los nodos adyacentes se encolaron, de manera que el próximo nodo a visitar siempre estaba en el frente de la cola. Cada vez que se encontraba un nodo no visitado, se registraba el nodo padre del cual provenía. De esta manera, se garantizó una exploración secuencial en niveles, lo que permitió determinar el camino más corto desde el punto de entrada hasta cualquier otro nodo en el grafo.
- **DFS**
Para la implementación del algoritmo DFS en la búsqueda del camino más corto, se genero dos contenedores, uno para el camino más corto 'shortestPath' y el actual 'currentPath', el algoritmo iterara en todas las filas y columnas, encontrando todos los posibles caminos, pero comparar la longitud de estos con shorthestPath, de ese modo actualizara el camino más corto. El algortimo comienza recorriendo el mapa de adyacencia, a profundidad, se marcan los nodos visitados y se añaden a currentPath, una vez que se compruebe que el valor actual es igual al valor del endPoint, se evalua si debe actualizarse shortestPath, por otro lado si no se llego al endPoint pero se acabaron los nodos adyancentes, se elmina de currentPath el úlimo elemento, de este modo se genera un retroceso al punto de giro anterior, finalizando al haber recorrido todos los posibles caminos del laberinto.
## Librerias
Las librerias empleadas fueron:

- iostream: Para entrada y salida estándar.
- ctime: Para utilizar funciones relacionadas con el tiempo. En este caso, se usa para sembrar la semilla del generador de números aleatorios (srand(time(0))).
- vector: Para manejar matrices dinámicas bidimensionales que representan el laberinto.
- cstdlib: Para funciones relacionadas con la generación de números aleatorios (rand()) y para manipular la linea de comandos, en este caso, para limpiar la pantalla.
- windows.h: Esta librería es específica de Windows y se utiliza aquí para cambiar los colores del texto en la consola mediante SetConsoleTextAttribute, ya que gracias a esta libreria,podemos imprimir la matriz de una manera que sea visualmente atractiva, ayudandonos a crear nuestro demo, en este codigo, el numero 1, que representa las paredes, es pintado de azul y los 0, que representan los lugares vacios, no son pintados. A su vez, los numeros 4, son los bordes del laberinto, por lo que se pintaron de verde.
- unistd.h: Se utilizo usleep() para agregar una pausa en cada iteracion de la ejecucion de los algoritmos, de manera que se pueda apreciar visualmente el proceso para encontrar la solucion del laberinto.
## Patrones de diseño:
- Abstract Factory:
Uno de los patrones de diseño utilizados fue Abstract Factory debido a que se requiere instancia diferentes algoritmos (DFS, BFS y Djikstra) pero que comparten el interfaz enfocado en resolver el laberinto, de este modo se garanriza la estructuración correcta del orden de ejecución, así como la apertura a la implementación de otros algoritmos que podrán agregarse de manera rápida sin necesidad de replantear la estructura interna de las clases y del interfaz. La clase concreta de AbstractFactory y ConcreteFactory instancian las diferentes clases de algoritmos con una matriz de acuerdo al grafo necesario que necesita cada clase, lo cual es necesario ya que cada uno utiliza diferentes estructuras de datos y almacenan los nodos adyacentes de diferente manera.
- Adapter: 
Este patron nos permitio hacer posible que, desde la interfaz, el usuario pueda obtener los graficos con los datos de los distintos algoritmos sin tener que cambiar de manera directa GrafoGrafica, conectando todas las clases y permitiendo la utilización de un interfaz común para la ejecución del programa, facilitando el avance, comunicación y monitereamiento de la ejecución de cada algoritmo.
## Link del video con la explicación de la demo:
https://drive.google.com/drive/folders/1KXyiM_lUacO-MhPUrOA3Ooir1wOV0FWh?usp=sharing
## Referencias:
Abed-Esfahani.Aryan(2021).Maze Generation — Recursive Backtracking.
Recuperado de:
https://aryanab.medium.com/maze-generation-recursive-backtracking-5981bc5cc766#:~:text=Recursive%20backtracking%20is%20a%20relatively,achieves%20this%20by%20using%20recursion.

-Universidad de Oviedo(2013). Manejo básico de la interfaz de programación Win32.
Recuperado de:

https://www.atc.uniovi.es/telematica/2ac/Practicas/Interfaz-Win32-Sesion-2.pdf

Causevic.Siwei(2021).Search Algorithms — Concepts and Implementation.

Recuperado de :

https://towardsdatascience.com/search-algorithms-concepts-and-implementation-1073594aeda6

Lujan.Ganuza.Maria(2019).INGENIERÍA DE APLICACIONES.

Recuperado de :

http://www.cs.uns.edu.ar/~mlg/iap/downloads/Clases%20Teoricas/10_PatronesD_IAP_2019.pdf


