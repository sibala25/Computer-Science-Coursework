#include <iostream>
#include "History.h"
#include "globals.h"

using namespace std;

History::History(int nRows, int nCols) : m_rows(nRows), m_cols(nCols)
{
    for (int r = 0; r < m_rows; r++) {
        for (int c = 0; c < m_cols; c++) {
            grid[r][c] = '.';
        }
    }
}

bool History::record(int r, int c) {
    if (r < 1 || r > m_rows || c > m_cols || c < 1) {
        return false;
    }
    else {
        if (grid[r-1][c-1] == '.') {
            grid[r-1][c-1] = 'A';
        }
        else if (grid[r-1][c-1] == 'Z') {
            grid[r-1][c-1] = 'Z';
        }
        else {
            grid[r-1][c-1]++;
        }
        return true;
    }
}
            
void History::display() const {
    clearScreen();
    for (int r = 0; r < m_rows; r++) {
        for (int c = 0; c < m_cols; c++) {
            cout << grid[r][c];
        }
        cout << endl;
    }
    cout << endl;
}
