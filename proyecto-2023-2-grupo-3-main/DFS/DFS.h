#ifndef grafo_DFS
#define grafo_DFS
#include <iostream>
#include <map>
#include <unordered_set>
#include <utility>
#include <vector>
#include "../Maze/Laberinto.h"

using namespace std;

class GrafoGrafica{
public:
    virtual void graficar(int, int, Maze &) = 0;
};
class AbstractDFS: public GrafoGrafica {
public:
    virtual void addEdge(int, int) = 0;
    virtual void DFS(int, int) = 0;
    virtual void DFS_Modified(int, int) = 0;
    virtual void setMap(map<int, unordered_set<int>>) = 0;
    virtual void printMazeShortestPath(const unordered_set<int> &, int, int, int, int, const vector<vector<char>> &) const = 0;
    virtual vector<int> getShortestPath() = 0;
    virtual void graficar(int, int, Maze &) = 0;

    virtual ~AbstractDFS() = 0;
};
AbstractDFS::~AbstractDFS() = default;
class GrafoDFS: public AbstractDFS{
public:
    map<int, bool> visited;
    map<int, unordered_set<int>> adj;
    vector<int> currentPath;
    vector<int> shortestPath;
    int shortestPathLength;
    GrafoDFS() = default;
    GrafoDFS(const map<int, unordered_set<int>> &g_map){
        this->setMap(g_map);
    }
    ~GrafoDFS() override = default;
    void addEdge(int, int) override;
    void DFS(int, int) override;
    void DFS_Modified(int, int) override;
    void setMap(map<int, unordered_set<int>>) override;
    void printMazeShortestPath(const unordered_set<int> &, int, int, int, int, const vector<vector<char>> &) const override;
    vector<int> getShortestPath() override;
    void graficar(int , int , Maze &) override;

};

vector<int> GrafoDFS::getShortestPath(){
    return shortestPath;
}
void GrafoDFS::setMap(map<int, unordered_set<int>> NewMap) {
    adj = NewMap;
}

void GrafoDFS::addEdge(int v, int w) {
    adj[v].insert(w);
}

void GrafoDFS::DFS(int v, int end) {
    visited.clear();
    currentPath.clear();
    shortestPath.clear();
    shortestPathLength = INT_MAX;
    DFS_Modified(v, end);
}

void GrafoDFS::DFS_Modified(int current, int end) {
    visited[current] = true;
    currentPath.push_back(current);
    if (current == end && currentPath.size() < shortestPathLength) {
        shortestPath = currentPath;
        shortestPathLength = currentPath.size();
    }
    unordered_set<int>::iterator i;
    for (i = adj[current].begin(); i != adj[current].end(); ++i) {
        if (!visited[*i]) {
            DFS_Modified(*i, end);
        }
    }
    visited[current] = false;
    currentPath.pop_back();
}
unordered_set<int> PasstoUnorderedSet(const vector <int> &vectorPath){
    unordered_set<int> setPath;
    for(int s: vectorPath){
        setPath.insert(s);
    }
    return setPath;
}

void GrafoDFS::graficar(int StartPoint, int EndPoint, Maze &maze){
    this->DFS(StartPoint, EndPoint);
    printMazeShortestPath(PasstoUnorderedSet(this->getShortestPath()), maze.getRows(), maze.getCols(), maze.getBeginRow(), maze.getendRow(), maze.getMazeChar());
}

void GrafoDFS::printMazeShortestPath(const unordered_set<int> &path, int rows, int cols, int beginRow, int endRow, const vector<vector<char>>&maze ) const{
    char a = 178;
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
            SetConsoleTextAttribute(hConsole, 0);\
                cout << a << a;
        }
        for (int j = 0; j < cols; j++)
        {
            if(path.find((i)*(rows)+(j)) != path.end()){
                SetConsoleTextAttribute(hConsole, 4);
                cout << a << a;
            }
            else {

                if (maze[i][j] == 1) {
                    SetConsoleTextAttribute(hConsole, 3);
                    cout << a << a;
                } else if (maze[i][j] == 2) {
                    SetConsoleTextAttribute(hConsole, 0);
                    cout << a << a;
                } else if (maze[i][j] == 4) {
                    SetConsoleTextAttribute(hConsole, 2);
                    cout << a << a;
                } else {
                    SetConsoleTextAttribute(hConsole, 0);
                    cout << "  ";
                }
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
bool IsInRange(vector <vector<int>> &AnalyzeMaze, int &row, int &col, int &i, int &j){
    return (row < AnalyzeMaze.size() && row > - 1 && col < AnalyzeMaze[0].size() && col > -1 && ((i + j)%2 != 0));
}
void ConnectEdges(vector <vector<int>> &AnalyzeMaze, map<int, unordered_set<int>> & MazeGraph, int row, int col){
    int tempRow;
    int tempCol;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            tempRow = row + (i-1);
            tempCol = col + (j-1);
            if(IsInRange(AnalyzeMaze, tempRow, tempCol, i, j) && (AnalyzeMaze[tempRow][tempCol] != -47)){
                MazeGraph[AnalyzeMaze[0].size()*(row) + (col )].insert(AnalyzeMaze[0].size()*(tempRow ) + (tempCol ));
            }
        }
    }
}

map<int, unordered_set<int>> MapMaze(vector <vector<int>> AnalyzeMaze){
    map<int, unordered_set<int>> MapMaze;
    int rows = AnalyzeMaze.size();
    int cols = AnalyzeMaze[0].size();
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(AnalyzeMaze[i][j] != -47) {
                ConnectEdges(AnalyzeMaze, MapMaze, i, j);
            }
        }
    }
    return MapMaze;
}



#endif //grafo_DFS
