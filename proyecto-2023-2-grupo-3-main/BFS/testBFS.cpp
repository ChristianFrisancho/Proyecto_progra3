
#include "BFS.h"

int main() {
    int rows, cols;

    cout << "Ingrese el número de filas del laberinto: ";
    cin >> rows;

    cout << "Ingrese el número de columnas del laberinto: ";
    cin >> cols;
    cout << "\n\n";

    Maze maze(rows, cols);
    maze.generateMaze();
    maze.printMazeAux();
    maze.printMaze();

    GrafoBFS grafoBfs;
    grafoBfs.newMaze(maze.getMazeChar());
    cout << "Ingrese entry point\n";
    int entryPoint;
    cin >> entryPoint;
    grafoBfs.setEntry(entryPoint);
    cout << "Ingrese exit point\n";
    int exitPoint;
    cin >> exitPoint;
    grafoBfs.setExit(exitPoint);

    grafoBfs.BFS();
}