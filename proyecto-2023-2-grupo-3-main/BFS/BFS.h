#ifndef grafo_BFS_Djikstra
#define grafo_BFS_Djikstra
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <string>
#include <unistd.h>
#include "../Maze/Laberinto.h"

class AbstractBFS {
public:
    virtual int getEntry() const = 0;
    virtual void setEntry(int entry) = 0;
    virtual int getExit() const = 0;
    virtual void setExit(int exit) = 0;
    virtual void newMaze(vector<vector<char>>) = 0;
    virtual vector<int> BFS() = 0;
    virtual vector<int> BFSaux(int actualNode) = 0;
    virtual vector<int> getPathToExit() = 0;
    virtual void graficarAux() const = 0;
    virtual void Graficar() = 0;
    virtual void changeValueNode(int nodo, int value) = 0;
    virtual ~AbstractBFS() = 0;
};
AbstractBFS::~AbstractBFS() = default;

class GrafoBFS: public AbstractBFS{
public:
    unordered_map<int, unordered_set<int>> adjacencyMap;
    unordered_set<int> visitados;
    vector<vector<int>> mapa;
    vector<int> pathToExit;
    unordered_map<int, int> parent;
    GrafoBFS() = default;
    ~GrafoBFS() override = default;
    GrafoBFS(unordered_map<int, unordered_set<int>> &&g_map){
        adjacencyMap = std::move(g_map);
    }
    int entry;
    int exit;
    int tamano_x;
    int tamano_y;
    int getEntry() const override;
    void setEntry(int entry) override;
    int getExit() const override;
    void setExit(int exit) override;
    void newMaze(vector<vector<char>>) override;
    vector<int> BFS() override;
    vector<int> BFSaux(int actualNode) override;
    vector<int> getPathToExit() override;
    void graficarAux() const override;
    void Graficar() override;
    void changeValueNode(int nodo, int value) override;
};

int GrafoBFS::getEntry() const {
    return entry;
}

void GrafoBFS::setEntry(int entry) {
    GrafoBFS::entry = entry;
}

int GrafoBFS::getExit() const {
    return exit;
}

void GrafoBFS::setExit(int exit) {
    GrafoBFS::exit = exit;
}

void GrafoBFS::newMaze(vector<vector<char>> maze) {

    tamano_x = maze[0].size(); // columnas
    tamano_y = maze.size(); // filas

    mapa = std::vector<std::vector<int>>(tamano_y, std::vector<int>(tamano_x, 0));

    for(int i = 0; i < tamano_y; i++){
        for(int j = 0; j < tamano_x; j++){
            int element = maze [i][j] + 0.0;
            mapa[i][j] = maze [i][j] + 0.0;
            int actualElement = (i) * tamano_x + (j);
            unordered_set<int> nodosVecinos;
            if(element == 0 || element == 2){
                // arriba
                if(i > 0 && (maze[i - 1][j] == 0 || maze[i - 1][j] == 2)){
                    int upElement = (i - 1) * tamano_x + (j);
                    nodosVecinos.insert(upElement);
                }
                // abajo
                if((i < tamano_y - 1) && (maze[i + 1][j] == 0 || maze[i + 1][j] == 2)){
                    int downElement = (i + 1) * tamano_x + (j);
                    nodosVecinos.insert(downElement);
                }
                // izquierda
                if(j > 0 && (maze[i][j - 1] == 0 || maze[i][j - 1] == 2)){
                    int leftElement = (i ) * tamano_x + (j - 1);
                    nodosVecinos.insert(leftElement);
                }
                // derecha
                if((j < tamano_x - 1) && (maze[i][j + 1] == 0 || maze[i][j + 1] == 2)){
                    int rightElement = (i ) * tamano_x + (j + 1);
                    nodosVecinos.insert(rightElement);
                }
            }
            adjacencyMap[actualElement] = nodosVecinos;
        }
    }
}

unordered_map<int, unordered_set<int>> newMazeBFS(vector<vector<char>> maze) {
    unordered_map<int, unordered_set<int>> adjacencyMap;
    int tamano_x = maze[0].size(); // columnas
    int tamano_y = maze.size(); // filas

    vector<vector<int>> mapa = vector<vector<int>>(tamano_y, vector<int>(tamano_x, 0));
    for(int i = 0; i < tamano_y; i++){
        for(int j = 0; j < tamano_x; j++){
            int element = maze [i][j] + 0.0;
            mapa[i][j] = maze [i][j] + 0.0;
            int actualElement = (i) * tamano_x + (j);
            unordered_set<int> nodosVecinos;
            if(element == 0 || element == 2){
                // arriba
                if(i > 0 && (maze[i - 1][j] == 0 || maze[i - 1][j] == 2)){
                    int upElement = (i - 1) * tamano_x + (j);
                    nodosVecinos.insert(upElement);
                }
                // abajo
                if((i < tamano_y - 1) && (maze[i + 1][j] == 0 || maze[i + 1][j] == 2)){
                    int downElement = (i + 1) * tamano_x + (j);
                    nodosVecinos.insert(downElement);
                }
                // izquierda
                if(j > 0 && (maze[i][j - 1] == 0 || maze[i][j - 1] == 2)){
                    int leftElement = (i ) * tamano_x + (j - 1);
                    nodosVecinos.insert(leftElement);
                }
                // derecha
                if((j < tamano_x - 1) && (maze[i][j + 1] == 0 || maze[i][j + 1] == 2)){
                    int rightElement = (i ) * tamano_x + (j + 1);
                    nodosVecinos.insert(rightElement);
                }
            }
            adjacencyMap[actualElement] = nodosVecinos;
        }
    }
    return adjacencyMap;
}
void limpiarPantalla(){
    system("CLS");
}


vector<int> GrafoBFS::BFSaux(int actualNode) {
    queue<int> nodosPorVisitar;
    nodosPorVisitar.push(actualNode);

    vector<int> secuenciaVisitada;

    visitados.insert(actualNode);
    parent[actualNode] = actualNode;

    limpiarPantalla();
    changeValueNode(actualNode, 5);
    graficarAux();
    usleep(50000);


    while(!nodosPorVisitar.empty()){
        int nodoVisitado = nodosPorVisitar.front();
        nodosPorVisitar.pop();

        secuenciaVisitada.push_back(nodoVisitado);

        for(auto nodoVecino: adjacencyMap[nodoVisitado]){
            auto verificarVisitado = visitados.find(nodoVecino);
            if(verificarVisitado == visitados.end()){
                nodosPorVisitar.push(nodoVecino);

                visitados.insert(nodoVecino);
                parent[nodoVecino] = nodoVisitado;

                limpiarPantalla();
                changeValueNode(nodoVecino, 5);
                graficarAux();
                usleep(50000);
            }
        }
    }
    getPathToExit();
    Graficar();
    return secuenciaVisitada;
}

vector<int> GrafoBFS::BFS(){
    cout << entry << endl;
    return BFSaux(entry);
}

vector<int> GrafoBFS::getPathToExit(){
    int temp = exit;
    while(temp != entry){
        pathToExit.push_back(temp);
        temp = parent[temp];
    }
    pathToExit.push_back(entry);
    return pathToExit;
}

void GrafoBFS::Graficar(){
    vector<vector<int>> mapaBFS= mapa;

    for(auto element: pathToExit){
        limpiarPantalla();
        changeValueNode(element, 8);
        graficarAux();
        usleep(50000);
    }
}
void GrafoBFS::graficarAux() const{
    cout << "Maze with BFS: " << endl;
    char a = 178;
    char b = 219;
    char c = 177;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < tamano_x; ++i) {
        for (int j = 0; j < tamano_y; ++j) {
            if (mapa[i][j] == 1)
            {
                SetConsoleTextAttribute(hConsole, 3);
                cout << a << a;
            }
            else if (mapa[i][j] == 2)
            {
                SetConsoleTextAttribute(hConsole, 0);
                cout << a << a;
            }
            else if (mapa[i][j] == 4)
            {
                SetConsoleTextAttribute(hConsole, 2);
                cout << a << a;
            }
            else if (mapa[i][j] == 8)
            {
                SetConsoleTextAttribute(hConsole, 4);
                cout << b << b;
            }
            else if (mapa[i][j] == 5)
            {
                SetConsoleTextAttribute(hConsole, 5);
                cout << c << c;
            }
            else
            {
                SetConsoleTextAttribute(hConsole, 0);
                cout << "  ";
            }
            //cout << mapaDjikstra[i][j] ;
        }
        cout << endl;
    }
    return;
}

void GrafoBFS::changeValueNode(int nodo, int value){
    int cor_j = nodo % tamano_x;
    int cor_i = nodo / tamano_x;
    mapa[cor_i][cor_j] = value;
}
#endif //grafo_BFS_Djikstra