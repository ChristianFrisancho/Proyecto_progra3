#ifndef PROYECTO_DJIKSTRA_H
#define PROYECTO_DJIKSTRA_H
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <string>
#include <utility>
#include <unistd.h>
#include "../Maze/Laberinto.h"

class AbstractDijsktra {
public:
    virtual vector<int> dijkstra() = 0;
    virtual void newMaze (vector<vector<char>> maze) = 0;
    virtual void printAdjList() = 0;
    virtual int getEntry() const = 0;
    virtual void setEntry(int ) = 0;
    virtual int getExit() const = 0;
    virtual void setExit(int ) = 0;
    virtual void graficar() = 0;
    virtual ~AbstractDijsktra() = 0;
    virtual void setEndRow(int) = 0;
};
class GrafoDijsktra: public AbstractDijsktra{
public:
    unordered_map<int, unordered_map<int, int>> adjacencyList;
    unordered_map<int, int> distancias;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> no_visitados;
    unordered_map<int, int> parent;
    vector<vector<char>> mapa;
    vector<int> pathToExit;
    int entry;
    int exit;
    int endRow;
    GrafoDijsktra() = default;
    GrafoDijsktra(unordered_map<int, unordered_map<int, int>> && g_map){
        adjacencyList = std::move(g_map);
    }
    ~GrafoDijsktra() override = default;

    vector<int> dijkstra() override;
    void newMaze (vector<vector<char>> maze) override;
    void printAdjList() override;
    int getEntry() const override;
    void setEntry(int entry) override;
    int getExit() const override;
    void setExit(int exit) override;
    void graficar() override;
    void setEndRow(int) override;
};
void GrafoDijsktra::setEndRow(int v) {
    endRow = v;
}

AbstractDijsktra::~AbstractDijsktra() = default;
void GrafoDijsktra::newMaze(vector<vector<char>> maze){
    mapa = maze;

    int tamano_x = maze[0].size(); // columnas
    int tamano_y = maze.size(); // filas

    for(int i = 0; i < tamano_y; i++){
        for(int j = 0; j < tamano_x; j++){
            int element = maze [i][j] + 0.0;
            int actualElement = (i) * tamano_x + (j);
            if(element == 0 || element == 2){
                // arriba
                if(i > 0 && (maze[i - 1][j] == 0 || maze[i - 1][j] == 2)){
                    int upElement = (i - 1) * tamano_x + (j);
                    adjacencyList[actualElement][upElement] = 1;
                }
                // abajo
                if((i < tamano_y - 1) && (maze[i + 1][j] == 0 || maze[i + 1][j] == 2)){
                    int downElement = (i + 1) * tamano_x + (j);
                    adjacencyList[actualElement][downElement] = 1;
                }
                // izquierda
                if(j > 0 && (maze[i][j - 1] == 0 || maze[i][j - 1] == 2)){
                    int leftElement = (i ) * tamano_x + (j - 1);
                    adjacencyList[actualElement][leftElement] = 1;
                }
                // derecha
                if((j < tamano_x - 1) && (maze[i][j + 1] == 0 || maze[i][j + 1] == 2)){
                    int rightElement = (i ) * tamano_x + (j + 1);
                    adjacencyList[actualElement][rightElement] = 1;
                }
            }
        }
    }
}
unordered_map<int, unordered_map<int, int>> newMazeDijsktra(vector<vector<char>> maze){
    vector<vector<char>> mapa = maze;
    unordered_map<int, unordered_map<int, int>> adjacencyList;
    int tamano_x = maze[0].size(); // columnas
    int tamano_y = maze.size(); // filas

    for(int i = 0; i < tamano_y; i++){
        for(int j = 0; j < tamano_x; j++){
            int element = maze [i][j] + 0.0;
            int actualElement = (i) * tamano_x + (j);
            if(element == 0 || element == 2){
                // arriba
                if(i > 0 && (maze[i - 1][j] == 0 || maze[i - 1][j] == 2)){
                    int upElement = (i - 1) * tamano_x + (j);
                    adjacencyList[actualElement][upElement] = 1;
                }
                // abajo
                if((i < tamano_y - 1) && (maze[i + 1][j] == 0 || maze[i + 1][j] == 2)){
                    int downElement = (i + 1) * tamano_x + (j);
                    adjacencyList[actualElement][downElement] = 1;
                }
                // izquierda
                if(j > 0 && (maze[i][j - 1] == 0 || maze[i][j - 1] == 2)){
                    int leftElement = (i ) * tamano_x + (j - 1);
                    adjacencyList[actualElement][leftElement] = 1;
                }
                // derecha
                if((j < tamano_x - 1) && (maze[i][j + 1] == 0 || maze[i][j + 1] == 2)){
                    int rightElement = (i ) * tamano_x + (j + 1);
                    adjacencyList[actualElement][rightElement] = 1;
                }
            }
        }
    }
    return adjacencyList;
}


void GrafoDijsktra::printAdjList() {
    for(auto actual: adjacencyList){
        cout << "Actual: " << actual.first << endl;
        for(auto alrededor: actual.second){
            cout << "Alrededor: "<< alrededor.first << " " << alrededor.second << endl;
        }
    }
    cout << endl;
}

vector<int> GrafoDijsktra::dijkstra() {
    for(const auto& elemento: adjacencyList){
        distancias[elemento.first] = INT_MAX;
        parent[elemento.first] = elemento.first;
    }
    distancias[entry] = 0;
    // source node
    no_visitados.push(pair<int,int> (0, entry));
    while(no_visitados.size() != 0){
        // elemento con la distancia minima
        int topNode = no_visitados.top().second;
        int topDist = no_visitados.top().first;
        no_visitados.pop();
        // adjacent nodeS from the source ndoe
        for(auto adjacent: adjacencyList[topNode]){
            int adjacentDist = adjacent.second;
            int adjacentNode = adjacent.first;

            if(topDist + adjacentDist < distancias[adjacentNode]){
                distancias[adjacentNode] = topDist + adjacentDist;
                no_visitados.push(pair<int, int> (topDist + adjacentDist, adjacentNode));

                parent[adjacentNode] = topNode;
            }
        }
    }
    // Verificar si no hay camino hasta el nodo
    if(distancias[exit] == INT_MAX){
        return {-1};
    }
    // Si el orgien del nodo no es el mismo, entonces el camino no esta completo
    while(parent[exit] != exit){
        pathToExit.push_back(exit);
        exit = parent[exit];
    }
    pathToExit.push_back(entry);
    reverse(pathToExit.begin(), pathToExit.end());
    return pathToExit;
}


void GrafoDijsktra::graficar(){
    int tamano_x = mapa[0].size();
    int tamano_y = mapa.size();
    int cols = tamano_y;
    int rows = tamano_x;
    int beginRow = (entry)/tamano_y;
    int mapaDjikstra [tamano_x][tamano_y];
    cout << exit << endl;
    for (int i = 0; i < tamano_x; ++i) {
        for (int j = 0; j < tamano_y; ++j) {
            mapaDjikstra[i][j]= mapa[i][j] + 0.0;
        }
    }
    for(auto element: pathToExit){
        int cor_j = element % tamano_x;
        int cor_i = element / tamano_x;
        mapaDjikstra[cor_i][cor_j] = 8;
    }
    cout << "Maze with djiksta: " << endl;
    char a = 178;
    char b = 219;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < cols + 2; i++)
    {
        SetConsoleTextAttribute(hConsole, 2);
        cout << a << a;
    }
    cout << endl;
    for (int i = 0; i < rows; i++)
    {

        if(i != beginRow){
            SetConsoleTextAttribute(hConsole, 2);
            cout << a << a;
        }
        else {
            SetConsoleTextAttribute(hConsole, 0);
                cout << a << a;
        }
        for (int j = 0; j < cols; j++)
        {
            if (mapaDjikstra[i][j] == 1)
            {
                SetConsoleTextAttribute(hConsole, 3);
                cout << a << a;
            }
            else if (mapaDjikstra[i][j] == 2)
            {
                SetConsoleTextAttribute(hConsole, 0);
                cout << a << a;
            }
            else if (mapaDjikstra[i][j] == 4)
            {
                SetConsoleTextAttribute(hConsole, 2);
                cout << a << a;
            }
            else if(mapaDjikstra[i][j] == 8)
            {
                SetConsoleTextAttribute(hConsole, 6);
                cout << a << a;
            }
            else
            {
                SetConsoleTextAttribute(hConsole, 0);
                cout << "  ";
            }
        }
        if(i != endRow){
            SetConsoleTextAttribute(hConsole, 2);
            cout << a << a;
        } else {
            SetConsoleTextAttribute(hConsole, 0);
            cout << a << a;
        }
        cout << endl;
    }
    for (int i = 0; i < cols + 2; i++)
    {
        SetConsoleTextAttribute(hConsole, 2);
        cout << a << a;
    }
    cout << endl;
}

int GrafoDijsktra::getEntry() const {
    return entry;
}

void GrafoDijsktra::setEntry(int entry) {
    GrafoDijsktra::entry = entry;
}

int GrafoDijsktra::getExit() const {
    return exit;
}

void GrafoDijsktra::setExit(int exit) {
    this->exit = exit;
}



#endif //PROYECTO_DJIKSTRA_H
