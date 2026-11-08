bool pathExists(char maze[][10], int sr, int sc, int er, int ec);

bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
    // Return true if there is a path from (sr,sc) to (er,ec)
    // through the maze; return false otherwise
    
    if ((sr == er) && (sc == ec)) {
        return true;
    }
    
    maze[sr][sc] = 'I';
        
    // check East and update it
    if (maze[sr][sc+1] == '.') {
        if (pathExists(maze, sr, sc+1, er, ec) == true) {
            return true;
        }
    }
    // check South and update it
    if (maze[sr+1][sc] == '.') {
        if (pathExists(maze, sr+1, sc, er, ec) == true) {
            return true;
        }
    }
    // check West and update it
    if (maze[sr][sc-1] == '.') {
        if (pathExists(maze, sr, sc-1, er, ec) == true) {
            return true;
        }
    }
    // check North and update it
    if (maze[sr-1][sc] == '.') {
        if (pathExists(maze, sr-1, sc, er, ec) == true) {
            return true;
        }
    }
    return false;
}
