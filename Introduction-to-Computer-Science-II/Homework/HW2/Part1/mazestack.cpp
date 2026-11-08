#include <iostream>
#include <stack>
#include <string>
using namespace std;
bool pathExists(char maze[][10], int sr, int sc, int er, int ec);

class Coord {
    public:
        Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
        int r() const { return m_row; }
        int c() const { return m_col; }
    private:
        int m_row;
        int m_col;
    };

bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
    // Return true if there is a path from (sr,sc) to (er,ec)
    // through the maze; return false otherwise
    
    stack<Coord> coordStack;
    Coord starting(sr,sc);
    Coord current(sr,sc);
    Coord ending(er,ec);
    coordStack.push(starting);
    maze[sr][sc] = 'I';
    
    while(!coordStack.empty()) {
        current = coordStack.top();
        coordStack.pop();
        if ( (current.r() == ending.r()) && (current.c() == ending.c()) ) {
            return true;
        }
        // If you can move EAST and haven't encountered that cell yet,
        // then push the coordinate (r,c+1) onto the stack and update
        // maze[r][c+1] to indicate the algorithm has encountered it.
        if (maze[current.r()][current.c()+1] == '.') {
            coordStack.push(Coord(current.r(),current.c()+1));
            maze[current.r()][current.c()+1] = 'I';
        }
        // If you can move SOUTH and haven't encountered that cell yet,
        // then push the coordinate (r+1,c) onto the stack and update
        // maze[r+1][c] to indicate the algorithm has encountered it.
        if (maze[current.r()+1][current.c()] == '.') {
            coordStack.push(Coord(current.r()+1,current.c()));
            maze[current.r()+1][current.c()] = 'I';
        }
        // If you can move WEST and haven't encountered that cell yet,
        // then push the coordinate (r,c-1) onto the stack and update
        // maze[r][c-1] to indicate the algorithm has encountered it.
        if (maze[current.r()][current.c()-1] == '.') {
            coordStack.push(Coord(current.r(),current.c()-1));
            maze[current.r()][current.c()-1] = 'I';
        }
        // If you can move NORTH and haven't encountered that cell yet,
        // then push the coordinate (r-1,c) onto the stack and update
        // maze[r-1][c] to indicate the algorithm has encountered it.
        if (maze[current.r()-1][current.c()] == '.') {
            coordStack.push(Coord(current.r()-1,current.c()));
            maze[current.r()-1][current.c()] = 'I';
        }
    }
    return false;
}

int main()
        {
            char maze[10][10] = {
                { 'X','X','X','X','X','X','X','X','X','X' },
                { 'X','.','.','.','X','.','.','X','.','X' },
                { 'X','.','X','X','X','.','.','.','.','X' },
                { 'X','.','X','.','X','X','X','X','.','X' },
                { 'X','X','X','.','.','.','.','.','.','X' },
                { 'X','.','.','.','X','.','X','X','.','X' },
                { 'X','.','X','.','X','.','.','X','.','X' },
                { 'X','.','X','X','X','X','.','X','.','X' },
                { 'X','.','.','X','.','.','.','X','.','X' },
                { 'X','X','X','X','X','X','X','X','X','X' }
            };

            if (pathExists(maze, 4,3, 1,8))
                cout << "Solvable!" << endl;
            else
                cout << "Out of luck!" << endl;
        }
