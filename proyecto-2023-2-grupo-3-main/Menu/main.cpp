#include "../BFS/BFS.h."
#include "../Djikstra/Djikstra.h"
#include "../DFS/DFS.h"
#include <locale>

class AbstractFactory {
public:
    virtual AbstractDFS* crearGrafoDFS(vector<vector<int>>) = 0;
    virtual AbstractBFS* crearGrafoBFS(vector<vector<char>>) = 0;
    virtual AbstractDijsktra* crearGrafoDijsktra(vector<vector<char>>) = 0;
    virtual ~AbstractFactory() = 0;
};
AbstractFactory::~AbstractFactory()= default;
class ConcreteFactory: public AbstractFactory{
public:
    AbstractDFS* crearGrafoDFS(vector<vector<int>> matrix) override{
        return new GrafoDFS(MapMaze(matrix));
    }
    AbstractBFS* crearGrafoBFS(vector<vector<char>> matrix) override{
        AbstractBFS* g_map = new GrafoBFS;
        g_map->newMaze(matrix);
        return g_map;
    }
    AbstractDijsktra* crearGrafoDijsktra(vector<vector<char>> matrix) override{
        AbstractDijsktra* g_map = new GrafoDijsktra;
        g_map->newMaze(matrix);
        return g_map;
    }
    ~ConcreteFactory() override = default;
};

class AdapterGraficaDFS: public GrafoGrafica{
private:
    AbstractDFS* g_dfs;
public:
    AdapterGraficaDFS(AbstractDFS* g_DFS){
        g_dfs = g_DFS;
    }
    void graficar(int StartPoint,int EndPoint, Maze &maze) override{
        g_dfs->graficar(StartPoint, EndPoint, maze);
    };
};

class AdapterGraficaBFS: public GrafoGrafica{
private:
    AbstractBFS* g_bfs;
public:
    AdapterGraficaBFS(AbstractBFS* g_BFS){
        g_bfs = g_BFS;
    }
    void graficar(int StartPoint,int EndPoint, Maze &maze) override{
        g_bfs->setEntry(StartPoint);
        g_bfs->setExit(EndPoint);
        cout << EndPoint << endl;
        g_bfs->BFS();
    };
};
class AdapterGraficaDijkstra: public GrafoGrafica{
private:
    AbstractDijsktra* g_dijkstra;
public:
    AdapterGraficaDijkstra(AbstractDijsktra *g_Dijks){
        g_dijkstra = g_Dijks;
    }
    void graficar(int StartPoint,int EndPoint, Maze &maze) override{
        g_dijkstra->setEntry(StartPoint);
        g_dijkstra->setExit(EndPoint);
        g_dijkstra->setEndRow(maze.getendRow());
        g_dijkstra->dijkstra();
        g_dijkstra->graficar();
    };
};

void ChooseSize(int &rows, int &cols){
    bool decision;
    cout << "¿Deseas elegir un tamaño?" << endl;
    cout << "Si 1, no 0: "; cin >> decision;
    if(decision){
        cout << "ingresa un tamaño" << endl;
        cout << "dimensión: "; cin >> rows;
        cols = rows;
    }else{
        rows = rand()%50;
        cols = rows;
    }
    cout << "Dimensiones " << rows << "x" << cols << endl;
}

void Disponibles(Maze &maze, int cRow){
    vector<vector<int>> m = maze.getMazeInt();
    vector <int> salida;
    for(int i = 0; i < m[cRow].size(); i++){
        if(m[cRow][i] != -47){
            cout << i << " ";
        }
    }
    cout << endl;
}
pair <int, int> GetInicio(Maze &maze){
    bool decision;
    int beginRow, beginCol;
    cout << "¿Deseas elegir un inicio?" << endl;
    cout << "Si 1, no 0: "; cin >> decision;
    if(decision){
        cout << "ingresa la fila y columan del inicio" << endl;
        cout << "fila inicial: "; cin >> beginRow;
        cout << "columnas disponibles:";
        Disponibles(maze, beginRow);
        cout << "columna inicial: "; cin >> beginCol;
    }else {
        beginRow = maze.getStartPoint() / maze.getCols();
        beginCol = 0;
    }
    cout << "Inicio :(" <<beginRow << ";" << beginCol  << ")\n";
    return {beginRow , beginCol };
}
pair <int, int> GetFin(Maze &maze){
    bool decision;
    int endRow, endCol;
    cout << "¿Deseas elegir un final?" << endl;
    cout << "Si 1, no 0: "; cin >> decision;
    if(decision){
        cout << "ingresa la fila y columna del final" << endl;
        cout << "fila final: "; cin >> endRow;
        cout << "columnas disponibles:";
        Disponibles(maze, endRow);
        cout << "columna final: "; cin >> endCol;
    }else{
        endCol = maze.getCols() - 1;
        endRow = maze.getendRow();
    }
    cout << "Final :(" <<endRow << ";" << endCol  << ")\n";
    return {endRow , endCol };
}

int main(){
    locale::global(locale(""));

    int rows, cols;
    ChooseSize(rows,cols);

    Maze laberinto(rows,cols);
    laberinto.generateMaze();
    laberinto.introducirHuecosAleatorios(rows*cols*0.10);

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
    return 0;
}