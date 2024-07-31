#ifndef Laberinto
#define Laberinto
#include <iostream>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <windows.h>
#include <unordered_set>
using namespace std;

class Maze
{
private:
    int rows, cols;
    vector<vector<char>> maze;
    vector<vector<int>> mazeForSearch;
    int beginRow, endRow;

public:
    Maze(int rows, int cols) : rows(rows), cols(cols), maze(rows, vector<char>(cols, 1)), beginRow(0), endRow(0) {}
    Maze() = default;

    void printMazeAux(){
        for(const vector<char>& vec: maze){
            for(char el: vec){
                cout << el+0.0;
            }
            cout << endl;
        }
    }
    int getBeginRow() const{
        return beginRow;
    }
    int getendRow() const{
        return endRow;
    }

    int getCols() const{
        return cols;
    }
    int getRows() const{
        return rows;
    }
    vector<vector<char>> getMazeChar() {
        return maze;
    }
    vector<vector<int>> getMazeInt(){
        mazeForSearch.resize(maze.size());
        for(int i = 0; i < maze.size(); i++){
            mazeForSearch[i].resize(maze[i].size());
            for(int j = 0; j < maze[0].size(); j++){
                mazeForSearch[i][j] = maze[i][j] - '0';
            }
        }
        return mazeForSearch;
    }
    int getStartPoint() const{
        return beginRow*cols + 0;
    }
    int getEndPoint() const{
        return endRow*cols + cols - 1;
    }

    void generateMaze()
    {
        srand(time(0));
        int startRow = rand() % rows;
        int startCol = rand() % cols;
        generatePath(startRow, startCol);
        setEntryAndExit();
    }

    void generatePath(int row, int col)
    {
        maze[row][col] = 0;
        const int directions[4][2] = {
                {-2, 0},
                {0, 2},
                {2, 0},
                {0, -2}
        };
        int dirs[4] = {
                0,
                1,
                2,
                3
        };
        for (int i = 0; i < 4; ++i)
        {
            int j = rand() % (i + 1);
            swap(dirs[i], dirs[j]);
        }
        for (int i = 0; i < 4; ++i)
        {
            int newRow = row + directions[dirs[i]][0];
            int newCol = col + directions[dirs[i]][1];
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && maze[newRow][newCol] == 1)
            {
                maze[(row + newRow) / 2][(col + newCol) / 2] = 0;
                generatePath(newRow, newCol);
            }
        }
    }

    void setEntryAndExit()
    {
        int entryRow = rand() % rows;
        maze[entryRow][0] = 2;
        maze[entryRow][1] = 2;
        beginRow = entryRow;
        int exitRow = rand() % rows;
        maze[exitRow][cols - 1] = 2;
        maze[exitRow][cols - 2] = 2;
        endRow = exitRow;
    }

    void printMaze() const
    {
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

                if (maze[i][j] == 1)
                {
                    SetConsoleTextAttribute(hConsole, 3);
                    cout << a << a;
                }
                else if (maze[i][j] == 2)
                {
                    SetConsoleTextAttribute(hConsole, 0);
                    cout << a << a;
                }
                else if (maze[i][j] == 4)
                {
                    SetConsoleTextAttribute(hConsole, 2);
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
    void introducirHuecosAleatorios(int cantidadDeHuecos)
    {
        srand(time(0));

        for (int i = 0; i < cantidadDeHuecos; ++i)
        {
            int randomRow = rand() % rows;
            int randomCol = rand() % cols;

            if (maze[randomRow][randomCol] == 1)
            {
                maze[randomRow][randomCol] = 0;
            }
        }
    }


};

#endif // Laberinto
